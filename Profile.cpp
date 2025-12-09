// Profile.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <Share.h>

#include "Profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProfile theProfile;


/////////////////////////////////////////////////////////////////////////////
// CProfile

bool GetFileStat(const char *szFileName, struct _stat &filestat)
{
//#ifdef WIN32
//   if (_stati64( szFileName, &filestat ) != 0)
//	   return false;
//#else
   if (_stat( szFileName, &filestat ) != 0)
	   return false;
//#endif
   return true;
}
bool IsExistFile_slowway(const char *szFileName)
{
   int fh;
   
   // warning C4996: '_open': This function or variable may be unsafe. Consider using _sopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
   //if( (fh = _open( szFileName, _O_RDONLY )) == -1 )
   if( _sopen_s(&fh, szFileName, _O_RDONLY, _SH_DENYNO, _S_IREAD ) != 0 )
	   return false;
   _close( fh );
   return true;

}

bool IsExistFile(const char *szFileName)
{
	//DWORD dw = GetFileAttributes(szFileName);
	//TRACE("%s attrib=0x%dh\n", szFileName, dw);
   //return dw!=0xFFFFFFFF && !(dw & FILE_ATTRIBUTE_DIRECTORY);
   //HACK!
	//ファイルがなくともエラーにならない。
	//NT4.0では、0x32で返るので、FILE_ATTRIBUTE_DIRECTORYが立ってない場合
	//を条件に加える。
	//#define FILE_ATTRIBUTE_READONLY         0x00000001  
	//#define FILE_ATTRIBUTE_HIDDEN           0x00000002  
	//#define FILE_ATTRIBUTE_SYSTEM           0x00000004  
	//#define FILE_ATTRIBUTE_DIRECTORY        0x00000010  
	//#define FILE_ATTRIBUTE_ARCHIVE          0x00000020  
	//#define FILE_ATTRIBUTE_NORMAL           0x00000080  
	//#define FILE_ATTRIBUTE_TEMPORARY        0x00000100  
	//#define FILE_ATTRIBUTE_COMPRESSED       0x00000800  
	//#define FILE_ATTRIBUTE_OFFLINE          0x00001000  

   struct _stat filestat;
	if (!GetFileStat(szFileName, filestat))
		return false;

	//   if( result != 0 )
	//	perror( "ファイルの情報を取得できませんでした" );
	//else   {
	//		/* 統計情報の一部を表示 */
	//	printf( "ファイルの大きさ : %ld\n", filestat.st_size );
	//	printf( "ドライブ         : %c:\n", filestat.st_dev + 'A' );
	//	printf( "更新時刻         : %s", ctime( &filestat.st_atime ) );
	//}
   if (filestat.st_size>0)
	   return true;
   return IsExistFile_slowway(szFileName);
   //return result==0 && filestat.st_size>0*/; //Size==0でもファイルはある
}

/////////////////////////////////////////////////////////////////////////////
// CProfile
CProfile::CProfile()

{
	m_pArc = NULL;
	m_sizefileArc = 0;
}

CProfile::~CProfile()
{
	if (m_pArc) {
		ResetArc();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProfile メッセージ ハンドラ
// プロファイルを読み書きする。
bool CProfile::SetProfile(const char *szProfile, const char *szProfileDirDir, const char*szExtent)
{
//	ASSERT(!IsOpen_ArcFile());

//	ASSERT(IsValidDataSz(szProfile));
	m_strProfile_nameonly = szProfile;

	if (szProfileDirDir) {
		m_strProfileDir = szProfileDirDir;
		m_strProfile = szProfileDirDir;
		if (!m_strProfile.IsEmpty() && m_strProfile.Right(1)!="\\")
			m_strProfile += "\\";
		m_strProfile += szProfile;
	}else
		m_strProfile = szProfile;
	if (szExtent) {
		m_strProfile += '.';
		m_strProfile += szExtent;
	}
	if (m_strProfile.GetLength()==0)
		return false;

	return true;
}

bool CProfile::ResetArcMode(UINT mode, bool bCreate)
{
	if (m_pArc && IsOpen_ArcFile()) {
		if (mode==CArchive::load ? m_pArc->IsLoading():m_pArc->IsStoring())
			return true;
	}

	return SetArc(mode, bCreate);
}
bool CProfile::WriteString(const char *szSect, const char *szKey, const char *szVal)
{
	return WritePrivateProfileString(szSect, szKey, szVal, m_strProfile.GetBuffer())>0;
}
bool CProfile::WriteInt(const char *szSect, const char *szKey, const int val)
{
	return WritePrivateProfileString(szSect, szKey, itostring(val).GetBuffer(), m_strProfile.GetBuffer())>0;
}
CString CProfile::ReadString(const char *szSect, const char *szKey, const char *def)
{
	CString str = "";
	char sz[1024];
	if (GetPrivateProfileString(szSect, szKey, def, sz, sizeof(sz), m_strProfile.GetBuffer())>0)
		str = sz;
	return str;
}
int CProfile::ReadInt(const char *szSect, const char *szKey, int def)
{
	return GetPrivateProfileInt(szSect, szKey, def, m_strProfile.GetBuffer());
}
//////////////////////////////////////////////////////////
//Arc->
void CProfile::ReadWriteString(const int mode, CString &str) 
{
	if (mode==__read)
		str = ReadString();
	else
		WriteString(str.GetBuffer());
}
CString CProfile::ReadString(bool bthrow)
{
	CString str = "";
	try {
	if (m_pArc) {
		CString cstr;
		ASSERT(m_pArc->IsLoading());
		//I don't use read/write Stirng function!
		//m_pArc->ReadString(cstr);
		LONG len;
		*m_pArc >> len;
		if (len>m_sizefileArc)
			throw new CArchiveException; //CException;
		else  if (len>0) {
			void *p = new BYTE[len];
			m_pArc->Read((void*)p, len); //値
			//str.append((char*)p, len);
			CString strT = CString((char*)p);
			strT.Left(len);
			str += strT;
			delete [] p;
		}
	}
	}catch(CException *e) {
		if (bthrow)
			throw;
		e->Delete();
	}
	return str;
}
bool CProfile::WriteString(const char *szVal, bool bthrow)
{
	try{
	if (m_pArc) {
		int len = strlen(szVal);
		ASSERT(m_pArc->IsStoring());
		//I don't use read/write Stirng function!
		//m_pArc->WriteString(szVal);
		*m_pArc << len;
		if (len>0)
			m_pArc->Write((void*)szVal, len);
		return true;
	}
	}catch(CException *e) {
		if (bthrow)
			throw;
		e->Delete();
	}
	return false;
}
void CProfile::ReadWriteInt(int mode, int &val)
{
	if (mode==__read)
		val = ReadInt();
	else
		WriteInt(val);
}
void CProfile::ReadWriteBool(int mode, bool &val)
{
	if (mode==__read)
		val = ReadBool();
	else
		WriteBool(val);
}
int CProfile::ReadInt(bool bthrow)
{
	try {
	if (m_pArc) {
		LONG value;
		ASSERT(m_pArc->IsLoading());
		*m_pArc >> value;
		return value;
	}
	}catch(CException *e) {
		if (bthrow)
			throw;
		e->Delete();
	}
	return 0;
}
bool CProfile::WriteInt(const int val, bool bthrow)
{
	try{
	if (m_pArc) {
		ASSERT(m_pArc->IsStoring());
		*m_pArc << (LONG)val;	//値
		return true;
	}
	}catch(CException *e) {
		if (bthrow)
			throw;
		e->Delete();
	}
	return false;
}
void CProfile::ReadWriteBytes(int mode, void *pval, int size)
{
	if (mode==__read)
		ReadBytes(pval, size);
	else
		WriteBytes(pval, size);
}
bool CProfile::ReadBytes(void *pval, const int size, bool bthrow)
{
	try{
	if (m_pArc) {
		ASSERT(m_pArc->IsLoading());
		LONG value;
		*m_pArc >> value;
		ASSERT(value==size);
		if (value>m_sizefileArc)
			throw new CArchiveException; //CException;
		else if (value>0)
			m_pArc->Read(pval, value); //値
		return true;
	}
	}catch(CException *e) {
		if (bthrow)
			throw;
		e->Delete();
	}
	return false;
}
bool CProfile::WriteBytes(const void *pval, int size, bool bthrow)
{
	try{
	if (m_pArc) {
		ASSERT(m_pArc->IsStoring());
		*m_pArc << (LONG)size;
		if (size>0)
			m_pArc->Write(pval, size);	//値
		return true;
	}
	}catch(CException *e) {
		if (bthrow)
			throw;
		e->Delete();
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////
//
bool CProfile::IsOpen_ArcFile()
{
	CFileStatus status;
	return m_fileArc.GetStatus( status )==TRUE;
}

void CProfile::ResetArc()
{
	if (!m_pArc)
		return;
	m_sizefileArc = 0;
	try{
		if (!m_pArc->IsLoading()) {
			m_pArc->Flush();
			if (m_pArc->GetFile())
				m_pArc->GetFile()->Close();
		}
	}catch(CException *e) {
		e->Delete();
	}
	delete m_pArc;
	m_pArc = NULL;
	m_fileArc.Abort();
}
bool CProfile::SetArc(UINT mode, bool bCrate)
{
	ASSERT(m_strProfile.GetLength()>0);
	ResetArc();
	bool bExist = IsExistFile(m_strProfile.GetBuffer());

	if( !m_fileArc.Open( m_strProfile.GetBuffer(), (mode == __read ?  CFile::modeRead:CFile::modeWrite) | ((!bExist && (bCrate || mode == __write)) ? CFile::modeCreate:0)) ) {
#ifdef _DEBUG
		afxDump << "Unable to open file" << "\n";
		return false;
#endif
	}
	try{
		m_sizefileArc = m_fileArc.GetLength();
	}catch(CException *e) {
		e->Delete();
	}

	//CArchive::load:CArchive::store
	m_pArc = new CArchive( &m_fileArc, mode);
	return m_pArc!=NULL;
}
