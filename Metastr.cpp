/*    PortTool v2.2     METASTR.CPP          */
//metastr.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
#include "metastr.h"
#include "..\mdfc\dstring.h"
#include "greppat.h"
#include "findopti.h"
#include "UserPath.h"
#include "Fdiver.h"
#include "Profile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKeyOutLogic *vpKeyOutLogic;
extern CFindOption *vpFindOption;

#ifndef BUG_20120112
extern BOOL vbUperVista;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMetaString
CString CMetaString::GetStrForLst()
{
	CString cstr;
	cstr = m_strTitle;
	cstr += " = ";
	cstr += m_strKey;
	return cstr;
}
CString CMetaString::GetStrForTitle()
{
	STRSPEC_METACHARS *pme = &vpFindOption->m_metaChars.m_metaCharsData;
	CString cstr;
	cstr = pme->str[mcSBlaketL];
	cstr += pme->str[mcSBlaketL];
	cstr += m_strTitle; 
	cstr += pme->str[mcSBlaketR];
	cstr += pme->str[mcSBlaketR];
	return cstr;
}
const CMetaString& CMetaString::operator = ( CMetaString &src )
{
	// IniFile名称はわざとコピーしない事！

	m_strTitle = src.m_strTitle;
	m_strKey = src.m_strKey;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CMetaStringArray

CMetaStringArray::CMetaStringArray()	// 標準のコンストラクタ
{
	SetIniFile();
	ReadWriteProfile(TRUE);
}
CMetaStringArray::CMetaStringArray(CMetaStringArray *pMetaString)
{
	*this = *pMetaString; //Copy whith out IniFile setting!
}

CMetaStringArray::~CMetaStringArray()
{
	ReadWriteProfile(FALSE);
	for (int i=0; i<GetSize();i++)
		delete PGetMetaString(i);
}

// プロファイルを読み書きする。
void CMetaStringArray::ReadWriteProfile(BOOL fRead)
{
	if (m_strIniFile.IsEmpty())
		return ;

	if (fRead)
		{
		CMetaString *pMetaString;
		#define DEntryLen	(256*10)
		char *pNew = (char *) new char[DEntryLen] ;
		char *pch;
		GetPrivateProfileString("MetaString", NULL , "" , pNew, DEntryLen, m_strIniFile.GetBuffer(0));
		pch = pNew;
		while(pch && *pch)
			{
			if (FValidNewTitle(pch))
				{
				pMetaString = new CMetaString();
				if (!pMetaString)
					{
					ASSERT(FALSE); //ﾒﾓﾘがない！
					break;
					}
				pMetaString->m_strTitle	= pch;
				GetPrivateProfileString("MetaString", pch , "" , vz, sizeof(vz), m_strIniFile.GetBuffer(0));
				pMetaString->m_strKey	= vz; //ｷｰがなくてもＯＫとする
				Add(pMetaString);
				}
			// 次のｴﾝﾄﾘｰへ
			pch = strchr(pch,'\0')+1;
			}
		delete [] pNew;
		if (GetSize()==0)
			{
			STRSPEC_METACHARS *pme = &vpFindOption->m_metaChars.m_metaCharsData;
			CString cstr;
#ifdef _JPN
			pMetaString = new CMetaString();
			if (!pMetaString)
				{
				ASSERT(FALSE); //ﾒﾓﾘがない！
				return;
				}
			cstr = "株式会社";
			pMetaString->m_strTitle	= cstr.GetBuffer(0);
			// ""
			cstr.Empty();
			cstr = cstr + "株式会社 " + pme->str[mcOr] + " （株） " + pme->str[mcOr];
			cstr = cstr + " " + pme->str[mcPrefix] + "(株" + pme->str[mcPrefix] + ") " + pme->str[mcOr];
			cstr = cstr + " ㈱ "  + pme->str[mcOr] +  " KK.";
			pMetaString->m_strKey	= cstr.GetBuffer(0);
			Add(pMetaString);

			pMetaString = new CMetaString();
			if (!pMetaString)
				{
				ASSERT(FALSE); //ﾒﾓﾘがない！
				return;
				}
			cstr = "パソコンの主な接続機器";
			pMetaString->m_strTitle	= cstr.GetBuffer(0);
			// ""
			cstr.Empty();
			cstr = cstr + "ｷｰﾎﾞｰﾄﾞ " + pme->str[mcOr] + " ﾏｳｽ " + pme->str[mcOr];
			cstr = cstr + " ﾃﾞｨｽﾌﾟﾚｲ "  + pme->str[mcOr] +  " ｽﾋﾟｰｶｰ " + pme->str[mcOr] +  " ﾌﾟﾘﾝﾀ ";
			pMetaString->m_strKey	= cstr.GetBuffer(0);
			Add(pMetaString);

			pMetaString = new CMetaString();
			if (!pMetaString)
				{
				ASSERT(FALSE); //ﾒﾓﾘがない！
				return;
				}
			cstr = "ｳｨﾝﾄﾞｳｽﾞについての記述";
			pMetaString->m_strTitle	= cstr.GetBuffer(0);
			// "[Windows|ウィンドウズ][95|NT|XP|2008|Vista|7]"
			cstr.Empty();
			cstr = cstr + pme->str[mcSBlaketL] + "Windows" + pme->str[mcSOr] + "ウィンドウズ" + pme->str[mcSBlaketR];
			cstr = cstr + pme->str[mcSBlaketL] + "95" + pme->str[mcSOr] + "NT" + pme->str[mcSOr] + "XP"+ pme->str[mcSOr] + "2008"+ pme->str[mcSOr] + "Vista"+ pme->str[mcSOr] + "7"+ pme->str[mcSBlaketR];
			pMetaString->m_strKey	= cstr.GetBuffer(0);
			Add(pMetaString);

#ifdef SHARWARE
			pMetaString = new CMetaString();
			if (!pMetaString)
				{
				ASSERT(FALSE); //ﾒﾓﾘがない！
				return;
				}
			cstr = "くまのプーさん登場人物";
			pMetaString->m_strTitle	= cstr.GetBuffer(0);
			cstr.Empty();
			cstr = cstr + "ﾌﾟｰ " + pme->str[mcOr] + " ﾃｨｶﾞｰ " + pme->str[mcOr];
			cstr = cstr + " ﾗﾋﾞｯﾄ "  + pme->str[mcOr] +  " ｵｳﾙ "+ pme->str[mcOr];
			cstr = cstr + " ﾋﾟｸﾞﾚｯﾄ " +  pme->str[mcOr] + " ｲｰﾖｰ ";
			pMetaString->m_strKey	= cstr.GetBuffer(0);
			Add(pMetaString);
#endif //SHARWARE
#endif //_JPN
			}
		}
	else
		{
		// 登録前に全てを削除する
		WritePrivateProfileString("MetaString", NULL, NULL, m_strIniFile.GetBuffer(0));
		for (int i=0; i<GetSize();i++)
			{
			if (!WritePrivateProfileString("MetaString", PGetMetaString(i)->m_strTitle.GetBuffer(0),
				 PGetMetaString(i)->m_strKey.GetBuffer(0), m_strIniFile.GetBuffer(0)))
				 {
				 ASSERT(FALSE);
				 break;
				 }
			}
		}
}

BOOL CMetaStringArray::FValidNewTitle(char *sz, BOOL fMsg/*=FALSE*/, int iSel/*=-1 このｴﾝﾄﾘｰだけは許すというｲﾝﾃﾞｯｸｽ*/)
{
	for (int i=0; i<GetSize();i++)
		{
		if ((PGetMetaString(i)->m_strTitle == sz) && (i != iSel) )
			{
			if (fMsg)
				Message(IDS_SAMENAME_ERR);
			return FALSE;
			}
		}
	return TRUE;
}
const CString CMetaStringArray::GetKey(char *sz, int *pIndex/*=NULL*/)
{
	for (int i=0; i<GetSize();i++)
		{
		if (PGetMetaString(i)->m_strTitle == sz)
			{
			if (pIndex)
				*pIndex = i;
			return PGetMetaString(i)->m_strKey;
			}
		}
	CString cstr;
	return cstr;
}
BOOL CMetaStringArray::FValidKeyLogic(char *sz)
{
	if (sz==NULL || *sz=='\0')
		{
		Message(IDS_PLEASE_KEYWORD);
		return FALSE;
		}
	// 正規表現をチェックする
	//return vpKeyOutLogic->Initialize(sz);
	CString cstrWord = sz;
	CDString cdstr;
	TRY {
	cdstr = vpKeyOutLogic->TransFromEntryMetaString(cstrWord.GetBuffer(0), TRUE, this);
	}
	CATCH(CMacroException, e)
		{
		ASSERT(cdstr.IsEmpty());
		Message(IDS_ERR_METASTRENTRY_LOOP);
		return FALSE;
		}
	END_CATCH
	return TRUE;
}

void CMetaStringArray::SetIniFile()
{
	//GetModuleFileName(AfxGetApp()->m_hInstance, (char *)vz, sizeof(vz));
	//CDString cdstr = (char *)vz;
	//cdstr += '\\' + METAINI_FILENAME;

#ifdef BUG_20120112

#ifdef BUG_20111218
	CDString cdstr = UserPath::myDocuments().c_str();
	cdstr += '\\' + METAINI_FILENAME;
#else
	bool isAppDataLow = true;
	PWSTR pBuffer = NULL;
	HRESULT hr =SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, NULL, &pBuffer );
	if( SUCCEEDED( hr ) )
	{
		// いろいろ処理する
		m_strIniFile = pBuffer;
		// メモリを解放
		CoTaskMemFree( pBuffer );
	}	
	m_strIniFile += "\\webinter.net";

	if (!CheckPath(m_strIniFile.GetBuffer(0))) {
		if (!FCreateDirectory(m_strIniFile.GetBuffer(0))) {
			isAppDataLow = false;
		}
	}

	if (isAppDataLow) {
		m_strIniFile += '\\';
		m_strIniFile += METAINI_FILENAME;
	}else{
		m_strIniFile = METAINI_FILENAME;
	}

#endif
#else

// バージョン情報の取得 

#if 0
    OSVERSIONINFO OSver; 
    OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
    GetVersionEx(&OSver); 
 
    // もし Windows 6(Windows Vista/Windows Server 2008) 以降のバージョン?
	sprintf(vz,"dwMajorVersion=%d, dwMinorVersion=%d",(int)OSver.dwMajorVersion&0xff,(int)OSver.dwMinorVersion&0xff);
	MessageBox(NULL, vz, _T("バージョン情報 - Metastr.cpp"), MB_OK);
    vbUperVista = OSver.dwMajorVersion >= 6; 
#endif 

	if (vbUperVista) {
		m_strIniFile = theProfile.getProfileDir();
		m_strIniFile += '\\';
	}else{
		m_strIniFile=((CFdiverApp *)AfxGetApp())->GetDefaultPath();
		m_strIniFile += '\\';
	}
	m_strIniFile += METAINI_FILENAME;
#endif
	
/*	if (cdstr.IsEmpty())
		{
		ASSERT(FALSE);
		return;
		}
	else
		{
		int i = cdstr.ReverseFind('\\');
		if (i<0)
			{
			ASSERT(FALSE);
			return;
			}
		m_strIniFile = cdstr.Left(i+1) + METAINI_FILENAME;
		}
*/
	ReadWriteProfile(TRUE);
}

const CMetaStringArray& CMetaStringArray::operator = ( CMetaStringArray &src )
{
	// IniFile名称はわざとコピーしない事！
	CMetaString *pMetaString;
	RemoveAll();
	for (int i=0; i<src.GetSize(); i++)
		{
		pMetaString = new CMetaString();
		if (!pMetaString)
			{
			ASSERT(FALSE);
			break;
			}
		*pMetaString = *src.PGetMetaString(i);
		Add(pMetaString);
		}
	return *this;
}

//const CMetaStringArray *CMetaStringArray::operator[] ( int i ) const
//{
//	ASSERT(i>=0 && i<GetSize());
//	return (CMetaString *)GetAt(i);
//}


