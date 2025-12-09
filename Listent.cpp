/*    PortTool v2.2     LISTENT.CPP          */

#include "stdafx.h"
#include "fdiver.h"
#include "mainfrm.h"

#include "lstent.h"

#include "findopti.h"
#include "resource.h"
#include "finddlg.h"
#include "..\mdfc\dstring.h"
#include "filetran.h"
extern CFindOption *vpFindOption;
extern CFindDlg *vpFindDlg;
extern CFileTransArray *vpFileTransArray;

IMPLEMENT_SERIAL(CListEntryArray, CObject, 2)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CListEntryArray::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{{
		// m_wMaxEntryを使っている分だけにする。
//#ifdef WIN32
//		ar << (LONG)m_wUseEntry;
//#else
		ar << (DWORD)m_wUseEntry;
//#endif
		for (size_ent w=0; w<m_wUseEntry; w++)
			{
			//CListEntryはCObjectの派生ではないので、ここでCListEntryのSerialize()ｺｰﾄﾞを書く
			m_bse[w].pcdFile->Serialize(ar);
			ar << *m_bse[w].pcdStr;
			ar << m_bse[w].lLineNum;
			ar << m_bse[w].dwHexNum;
			//takaso2010
			m_bse[w].m_paryMark->Serialize(ar);
			}
	}}
	else
	{{
//#ifdef WIN32
//		long entrys;
//		ar >> entrys;
//#else
		DWORD entrys;
		ar >> entrys;
//#endif
		DeleteContent();
		if (!FExpandEntry( (size_ent)entrys ))
			{
			AfxThrowMemoryException();
			}
		for (size_ent w=0; w<m_wUseEntry; w++)
			{
			//CListEntryはCObjectの派生ではないので、ここでCListEntryのSerialize()ｺｰﾄﾞを書く
			m_bse[w].pcdFile->Serialize(ar);
			ar >> *m_bse[w].pcdStr;
			ar >> m_bse[w].lLineNum;
			ar >> m_bse[w].dwHexNum;
			//takaso2010
			m_bse[w].m_paryMark->Serialize(ar);
			}
	}}
}

/*************************************************************************
-- Routine:BOOL THIS_CLASS::FExpandEntry (  size_ent entrys )
-- Description and Usage:
		登録ｴﾝﾄﾘｰを拡張する
-- Arguments:
		size_ent entrys - 登録する構造体の数.
-- Returns:
		TRUE  - 成功.
		FALSE - 失敗.		
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
BOOL CListEntryArray::FExpandEntry ( size_ent entrys )
{
/*	// ﾒﾓﾘの拡張
	if (entrys>m_wMaxEntry)
		{
		void far *p;
		if ((p=realloc(m_bse, entrys*sizeof(CListEntry)))==NULL)
			{
			TRACE ( "\nメモリが足りません." ) ;
			return ( FALSE ) ;
			}
		m_bse = (CListEntry* )p;
		for (size_ent i=m_wMaxEntry; i<entrys; i++)
			{
			if (!m_bse[i].Initialize())
				return FALSE;
			}
		m_wMaxEntry = entrys;
		}
	m_wUseEntry = entrys;
	return TRUE;
*/
#ifdef WIN32
	if (entrys<=m_wMaxEntry)
		{
		m_wUseEntry = entrys;
		return TRUE;
		}
	else
		{
#define MAX_ENTRYS	0x1000
#define UNIT_ENTRYS	0x0100
		void far *p;
		size_ent wExpand = entrys;
		if (MAX_ENTRYS>wExpand)
			{
			wExpand = MAX_ENTRYS;
			//takaso2010 this is Hack code !!!
			if ((p = realloc(m_bse, wExpand*sizeof(CListEntry))))
				{
				m_bse = (CListEntry far* )p;
				m_wUseEntry = entrys;
				while (m_wMaxEntry < wExpand)
					{{
					if (!m_bse[m_wMaxEntry++].Initialize())
						{
						m_wMaxEntry--;
						break;
						}
					}}
				return TRUE;
				}
			}
		else
			{
			wExpand += UNIT_ENTRYS;
			if ((p = realloc(m_bse, wExpand*sizeof(CListEntry))))
				{
				m_bse = (CListEntry far* )p;
				m_wUseEntry = entrys;
				while (m_wMaxEntry < wExpand)
					{{
					if (!m_bse[m_wMaxEntry++].Initialize())
						{
						m_wMaxEntry--;
						break;
						}
					}}
				return TRUE;
				}
			}
		}
	return FALSE;
#else
	if (entrys<=m_wMaxEntry)
		{
		m_wUseEntry = entrys;
		return TRUE;
		}
	else
		{
#define MAX_ENTRYS	0xD00	//3328//4681=0x1249//(0x10000/sizeof(CListEntry))
		void far *p;
		size_ent wExpand = entrys;
		if (MAX_ENTRYS>wExpand)
			{
			wExpand = MAX_ENTRYS;
			if ((p = _frealloc(m_bse, wExpand*sizeof(CListEntry))))
				{
				m_bse = (CListEntry far* )p;
				m_wUseEntry = entrys;
				while (m_wMaxEntry < wExpand)
					{{
					if (!m_bse[m_wMaxEntry++].Initialize())
						{
						m_wMaxEntry--;
						break;
						}
					}}
				return TRUE;
				}
			}
		}
	return FALSE;
#endif //WIN32
}

void CListEntryArray::DeleteContent()
{
	if (m_bse)
		{
		for ( size_ent i = 0; i < m_wMaxEntry; i++ )
			m_bse[i].DeleteContent();
		free(m_bse);
		}
	Initialize();
}
void CListEntryArray::Initialize()
{
	m_bse = NULL;
	m_wMaxEntry = 0;	// ｴﾝﾄﾘｰﾊﾞｯﾌｧの最大ｴﾝﾄﾘｰ数
	m_wUseEntry = 0;	// ｴﾝﾄﾘｰﾊﾞｯﾌｧの使用ｴﾝﾄﾘｰ数
	ResetSort();
	m_cxSbc = 0;
}
// ｿｰﾄｲﾝﾃﾞｯｸｽの作成
BOOL CListEntryArray::FMakeSortIndexOfPath(BOOL fFile)
{
	// パスについて名前順とする。
	BOOL fContinue=TRUE;
	CListEntry *pcListEnt;
	CDFileExp *pcdFile;
	CDString *pcdStr;
	size_ent nMin;
	register size_ent k,n;
	size_ent kMax, nMax;
	BOOL fPathSorted = (m_bse[0].nSortIndex != -1);

	for (n=0, kMax=0; (fContinue = !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) &&
				 n<m_wUseEntry; n++)
		{{
		if (GetEntryType(n)==BFT_DIR)
			{
			if (fPathSorted && fFile)
				fContinue = FMakeSortIndexOfFile(n);
			else
				{
				kMax++;
				nMax = n;
				}
			}
		}}
	if (fPathSorted || !fContinue)
		return fContinue;
	for (k=0; (fContinue = !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) &&
				 k<kMax; k++)
		{{
		nMin=(size_ent)-1;
		for (n=0; n<=nMax; n++)
			{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcListEnt->GetEntryType()==BFT_DIR && pcListEnt->nSortIndex == -1)
				{
				if (nMin == (size_ent)-1 || pcdStr->Compare(pcdFile->GetBuffer())>0)
					{
					nMin = n;
					pcdStr = pcdFile->GetString();
					}
				}
			}
		ASSERT(nMin!=(size_ent)-1);
		m_bse[nMin].nSortIndex = k;
		if (fFile)
			fContinue = FMakeSortIndexOfFile(nMin);
		}}
	return fContinue;
}

// ﾌｧｲﾙのｿｰﾄｲﾝﾃﾞｯｸｽの作成
BOOL CListEntryArray::FMakeSortIndexOfFile(size_ent nIndex)
{
	// パスについて名前順とする。
	BOOL fContinue=TRUE;
	CListEntry *pcListEnt;
	CDFileExp *pcdFile;
	size_ent nMin;
	register size_ent k,n;
	size_ent kMax, nMax;
	int et;
	for (n=nIndex+1, kMax=0; (fContinue = !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) && 
				n<m_wUseEntry; n++)
		{{
		pcListEnt = &m_bse[n];
		pcdFile = pcListEnt->pcdFile;
		if ((et=pcListEnt->GetEntryType())==BFT_DIR)
			break;
		else if (et!=BFT_NO)
			{ // ﾌｧｲﾙ
			pcListEnt->nSortIndex = (size_ent)-1; //ｸﾘｱ
			kMax++;
			}
		}}
	if (!fContinue)
		return fContinue;
	nMax = n;
	for (k=0; (fContinue = !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) && k<kMax; k++)
		{{
		nMin=(size_ent)-1;
		for (n=nIndex+1; n<nMax; n++)
			{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && pcdFile->FExistName() && pcListEnt->nSortIndex == -1)
				{
				if (nMin==-1 || CompareFileEntry(nMin, n)>0)
					nMin = n;
				}
			}
		ASSERT(nMin!=(size_ent)-1);
		m_bse[nMin].nSortIndex = k;
		}}
	return fContinue;
}

// ﾌｧｲﾙのｿｰﾄｲﾝﾃﾞｯｸｽの作成
BOOL CListEntryArray::FMakeSortIndexFlat()
{
	// パスについて名前順とする。
	BOOL fContinue=TRUE;
	CListEntry *pcListEnt;
	CDFileExp *pcdFile;
	size_ent nMin, kMax;
	register size_ent k,n;
	int et;
	for (k=0, kMax=0; (fContinue = !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) && 
				k<m_wUseEntry; k++)
		{{
		pcListEnt = &m_bse[k];
		pcdFile = pcListEnt->pcdFile;
		pcListEnt->nSortIndex = (size_ent)-1; //ｸﾘｱ
		if ((et=pcListEnt->GetEntryType())!=BFT_DIR && et!=BFT_NO)
			{ // ﾌｧｲﾙ
			kMax++;
			}
		}}
	if (!fContinue)
		return fContinue;
	for (k=0; (fContinue = !(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) && 
				k<kMax; k++)
		{{
		for (n=0,nMin=(size_ent)-1; n<m_wUseEntry; n++)
			{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if ((et=GetEntryType(n))!=BFT_DIR && et!=BFT_NO)
				{ // ﾌｧｲﾙ
				if (pcdFile && pcListEnt->nSortIndex == -1 && pcdFile->FExistName())
					{
					if (nMin==-1 || CompareFileEntry(nMin, n)>0)
						nMin = n;
					}
				}
			}
		ASSERT(nMin!=(size_ent)-1);
		m_bse[nMin].nSortIndex = k;
		}}
	return fContinue;
}

// ｿｰﾄｲﾝﾃﾞｯｸｽに従ってあるパス以下のﾌｧｲﾙを順次取得する
size_ent CListEntryArray::GetFileIndexInPath(size_ent nIndexPath, size_ent keyIndex)
{
	nIndexPath++;
	if (m_SortType==SORTTYPE_NO)
		{
		CListEntry *pcListEnt;
		CDFileExp *pcdFile;
		for (register size_ent n=nIndexPath; n<m_wUseEntry; n++)
			{{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && !pcdFile->GetString()->IsEmpty())
				{
				if (pcdFile->FExistName())
					{
					if (keyIndex-- == 0)
						return n;
					}
				else //if (pcdFile->FExistPath())
					break;
				}
			}}
		return (size_ent)-1; // not found
		}
	else
		{
		CListEntry *pcListEnt;
		CDFileExp *pcdFile;
		for (register size_ent n=nIndexPath; n<m_wUseEntry; n++)
			{{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && !pcdFile->GetString()->IsEmpty())
				{
				if (pcdFile->FExistName())
					{
					if (pcListEnt->nSortIndex == keyIndex)
						return n;
					}
				else //if (pcdFile->FExistPath())
					break;
				}
			}}
		return (size_ent)-1; // not found
	}
}

size_ent CListEntryArray::GetPathIndex(size_ent keyIndex)
{
	if (m_SortType==SORTTYPE_NO)
		{
		CListEntry *pcListEnt;
		CDFileExp *pcdFile;
		for (register size_ent n=0; n<m_wUseEntry; n++)
			{{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && !pcdFile->GetString()->IsEmpty())
				{
				// && !pcdFile->FExistName()は変換ファイル対応
				if (pcdFile->FExistPath() && !pcdFile->FExistName())
					{
					if (keyIndex-- == 0)
						return n;
					}
				}
			}}
		return (size_ent)-1; // not found
		}
	else
		{
		CListEntry *pcListEnt;
		CDFileExp *pcdFile;
		for (register size_ent n=0; n<m_wUseEntry; n++)
			{{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && !pcdFile->GetString()->IsEmpty())
				{
				// && !pcdFile->FExistName()は変換ファイル対応
				if (pcdFile->FExistPath() && !pcdFile->FExistName())
					{
					if (pcListEnt->nSortIndex == keyIndex)
						return n;
					}
				}
			}}
		return (size_ent)-1; // not found
	}
}

// ｿｰﾄｲﾝﾃﾞｯｸｽに従ってあるパス以下のﾌｧｲﾙを順次取得する
size_ent CListEntryArray::GetFileIndexFlat(size_ent keyIndex)
{
	if (m_SortType==SORTTYPE_NO)
		{
		CListEntry *pcListEnt;
		CDFileExp *pcdFile;
		for (register size_ent n=0; n<m_wUseEntry; n++)
			{{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && !pcdFile->GetString()->IsEmpty())
				{
				if (pcdFile->FExistName())
					return n;
				else //if (pcdFile->FExistPath())
					break;
				}
			}}
		return (size_ent)-1; // not found
		}
	else
		{
		CListEntry *pcListEnt;
		CDFileExp *pcdFile;
		for (register size_ent n=0; n<m_wUseEntry; n++)
			{{
			pcListEnt = &m_bse[n];
			pcdFile = pcListEnt->pcdFile;
			if (pcdFile && !pcdFile->GetString()->IsEmpty())
				{
				if (pcdFile->FExistName())
					{
					if (pcListEnt->nSortIndex == keyIndex)
						return n;
					}
				//else //if (pcdFile->FExistPath())
				//	break;
				}
			}}
		return (size_ent)-1; // not found
	}
}

// SortTypeに従って２つのﾌｧｲﾙｴﾝﾄﾘｰを比べる
int CListEntryArray::CompareFileEntry(size_ent ent1, size_ent ent2)
{
	if (!m_bAsc)
		{
		size_ent entT=ent1;
		ent1 = ent2;
		ent2 = entT;
		}

	int comp;
	switch(m_SortType)
		{
		case SORTTYPE_NAME:
			return m_bse[ent1].pcdFile->GetString()->CompareNoCase(m_bse[ent2].pcdFile->GetBuffer());
			break;
		case SORTTYPE_EXTENTION: // 拡張子別
			comp = _mbsicmp((unsigned char *)m_bse[ent1].pcdFile->GetBufferExtention(), (unsigned char *)m_bse[ent2].pcdFile->GetBufferExtention());
			break;
		case SORTTYPE_SIZE:
			if (m_bse[ent1].pcdFile->m_Attr.dwHighLen == m_bse[ent2].pcdFile->m_Attr.dwHighLen)
				{
				if (m_bse[ent1].pcdFile->m_Attr.dwLowLen != m_bse[ent2].pcdFile->m_Attr.dwLowLen)
					return ((m_bse[ent1].pcdFile->m_Attr.dwLowLen > m_bse[ent2].pcdFile->m_Attr.dwLowLen) ? 1:-1);
				comp =  0;
				}
			else
				return ((m_bse[ent1].pcdFile->m_Attr.dwHighLen > m_bse[ent2].pcdFile->m_Attr.dwHighLen) ? 1:-1);
			break;
		case SORTTYPE_DATE:
			comp = (m_bse[ent1].pcdFile->m_Attr.cTime > m_bse[ent2].pcdFile->m_Attr.cTime  ? -1:1); //ここだけ昇順とする
			break;
		default:
			ASSERT(FALSE);
			comp =  0;
			break;
		}
	if (comp==0) //その他のタイプで同じである場合は、名前でソートする
		return m_bse[ent1].pcdFile->GetString()->Compare(m_bse[ent2].pcdFile->GetBuffer());
	return comp;	
}

void CListEntryArray::ResetSort()
{
	m_SortType = SORTTYPE_NO;
	m_bAsc = TRUE;
}

// パラメータに従ってパスまたはファイルのｵｰﾌﾟﾝ状態を設定します。
void CListEntryArray::MarkeFOpenOfFiles(BOOL fOpenPath, BOOL fOpenFile)
{
	register size_ent n;
	for (n=0; n<m_wUseEntry; n++)
		{{
		switch(GetEntryType(n))
			{
			case BFT_DIR:
				m_bse[n].fOpen = fOpenPath;
				break;
			case BFT_NO:
				break;
			default:
				m_bse[n].fOpen = ((n+1<m_wUseEntry) && GetEntryType(n+1)==BFT_NO) ? fOpenFile:TRUE;
				break;
			}
		}}
}

// エントリーのタブ位置を取得する
// リストの場合は、文書エントリーのみ１タブ
// ツリーの場合は、ディレクトリの深さに相当する
int CListEntryArray::GetTabOfEntry(size_ent nIndex)
{
	int tab=0;
	switch(m_bse[nIndex].GetEntryType())
		{
		case BFT_DIR:
			break;
		case BFT_NO:
			if (vpFindOption->m_fDir)
				tab++;
			if (vpFindOption->m_fFile)
				tab++;
			break;
		//case BFT_PROG:
		//case BFT_SYS:
		//case BFT_DOC:
		//case BFT_OTHERS:
		default:
			if (vpFindOption->m_fDir)
				tab++;
			break;
		}
	return tab;
}


//エントリー文字列を取得する
int  CListEntryArray::GetEntryString(size_ent nIndex, CString &str1, CString &str2, CString &str3, CString &str4, CString &str5)
{
	CListEntry *pListEntry = &m_bse[nIndex];
	CDString strNum;
	CString strPath;
	CDFileExp *pcdFile = pListEntry->pcdFile;
	int posstr=0;
	switch(pListEntry->GetEntryType())
		{
		case BFT_DIR:
			ASSERT(vpFindOption->m_fDir);
			str1 = pcdFile->GetPathName();
			break;
		case BFT_NO:
			if (vpFindOption->m_optDispNum == 1)
				strNum.AddNumString(pListEntry->lLineNum);
			else
				{
				strNum.AddNumString(pListEntry->dwHexNum, 16);
				strNum.MakeUpper();
				}
			strNum += ":";
			if (!vpFindOption->m_fFile)
				{
				if (!vpFindOption->m_fDir)
					{
					str2 = GetFName(nIndex, vpFindOption->m_fDir, strPath);
					str1 = strPath;
					str3 = strNum;
					if (vpFindOption->m_fDispDoc){
						str4 = pListEntry->pcdStr->GetBuffer();
						posstr=4;
					}
				}else{
					str1 = GetFName(nIndex, vpFindOption->m_fDir, strPath);
					str2 = strNum;
					if (vpFindOption->m_fDispDoc){
						str3 = pListEntry->pcdStr->GetBuffer();
						posstr=3;
					}
				}
			}else{
				str1 = strNum;
				if (vpFindOption->m_fDispDoc){
					str2 = pListEntry->pcdStr->GetBuffer();
					posstr=2;
				}
			}
			break;
		//case BFT_PROG:
		//case BFT_SYS:
		//case BFT_DOC:
		//case BFT_OTHERS:
		default:
			ASSERT(vpFindOption->m_fFile || vpFindDlg->FFindFileOnly());
			str1 = GetFName(nIndex, vpFindOption->m_fDir, strPath);
			if (!vpFindOption->m_fDir)
				{
				str2 = strPath;
				str3 = pcdFile->GetStrSize();
				str4 = pcdFile->GetStrTime();
				str5 = pcdFile->GetStrAttr();
				}
			else
				{
				str2 = pcdFile->GetStrSize();
				str3 = pcdFile->GetStrTime();
				str4 = pcdFile->GetStrAttr();
				}
			break;
		}
	return posstr;
}

#ifdef _TAG_TEXT
BOOL CListEntryArray::GetEntryStringForTagText(size_ent nIndex, CString &str)
{
	CListEntry *pListEntry = &m_bse[nIndex];
	CDString strT;
	CDFileExp *pcdFile = pListEntry->pcdFile;
	switch(pListEntry->GetEntryType())
		{
		case BFT_NO:
			strT = GetFName(nIndex, FALSE, str);
			str += strT;
			strT = '(';
			if (vpFindOption->m_optDispNum == 1)
				strT.AddNumString(pListEntry->lLineNum);
			else
				{
				strT.AddNumString(pListEntry->dwHexNum, 16);
				strT.MakeUpper();
				}
			strT += "):";
			str += strT;
			str += pListEntry->pcdStr->GetBuffer();
			break;
		case BFT_DIR:
			return FALSE;
		//case BFT_PROG:
		//case BFT_SYS:
		//case BFT_DOC:
		//case BFT_OTHERS:
		default:
			if (vpFindDlg->FFindFileOnly()) {
				strT = GetFName(nIndex, FALSE, str);
				str += strT;
			}else
				return FALSE;
		}
	return TRUE;
}
#endif //_TAG_TEXT

int CListEntryArray::GetTabPostion(CDC *pDC, int lenPath)
{
	//virtual CSize TabbedTextOut( int x, int y, LPCSTR lpszString, int nCount
	//, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin );
// タブストップを取得する
#define MAXFILENAME (14)	//MAXFILENAMELEN
	if (!m_cxSbc)
		MakeCharWidthTbl(pDC);
	return m_cxSbc * (MAXFILENAME+lenPath);
}

// ｷｬﾗｸﾀ幅ﾃｰﾌﾞﾙを作成する
void CListEntryArray::MakeCharWidthTbl(CDC *pDC)
{
/*
	int cx;
	VERIFY(pDC->GetCharWidth('%','%',&m_cxSbc));
	VERIFY(pDC->GetCharWidth('W','W',&cx));
	if (cx>m_cxSbc)
		m_cxSbc = cx;
	VERIFY(pDC->GetCharWidth('$','$',&cx));
	if (cx>m_cxSbc)
		m_cxSbc = cx;
	size_ent w=0x829f; //ひらがな　あ
	VERIFY(pDC->GetCharWidth(w,w,&cx));
	if ((cx/=2)>m_cxSbc)
		m_cxSbc = cx;
*/
	VERIFY(pDC->GetCharWidth('1','1',&m_cxSbc));
}
// GetTextExtent()のﾛｰｶﾙﾊﾞｰｼﾞｮﾝ
int CListEntryArray::MyGetTextExtentX(CDC *pDC, CDString *pcdStr)
{
	CSize csize;

/*    PortTool v2.2     1995/10/16    8:4          */
/*      Found   : GetTextExtent          */
/*      Issue   : ポータブルな GetTextExtentPoint に置き換わりました          */
//  WIN API:GetTextEntent()->GetTextEntentPoint32()だが、MFCの以下の関数はそのまま
	csize = pDC->GetTextExtent(pcdStr->GetBuffer(), pcdStr->GetByteLength());
	return csize.cx;
}

// ファイル名を取得する
CDString CListEntryArray::GetFName(size_ent nIndex, BOOL fNameOnly, LSTENT_TYPE iTranFile/*=LSTENT_NORMAL*/)
{
	CListEntry *pListEntry = &m_bse[nIndex];
	CDFileExp *pcdFile = pListEntry->pcdFile;
	CDFileExp cdFileExp;
	CDFile cdfile;
	size_ent n;
	if (pcdFile==NULL || pcdFile->GetString()->IsEmpty())
		{
		// Scanning File Name and Path!
		nIndex=ScanBeforeFileOrPath(nIndex, FALSE);
		pListEntry = &m_bse[nIndex];
		pcdFile = pListEntry->pcdFile;
		}
	cdFileExp = *pcdFile;
	//漢字コードマークアップを削除
	//BOOL bKft = TrimMarkOfKftTransFile(cdFileExp);
	EXT_TYPE ext_type = TrimMarkOfKftTransFile(cdFileExp);
	pcdFile = &cdFileExp;
	if (pcdFile->FExistName())
		{
		if (!pListEntry->pcdStr->IsEmpty() || CDFileCollect(pcdFile->GetBuffer()).GetSize()>1)
			{
			switch(iTranFile)
				{
				case LSTENT_DOC:
				case LSTENT_TXT:
					{
					for (int i=0; i<2; i++)
						{
						CDFileCollect cdFileCol = pListEntry->pcdStr->GetBuffer(0);
						int iSelMac = cdFileCol.GetSize()-1;
						iSelMac = (iSelMac<0 ? 0:iSelMac);
						if (iTranFile==LSTENT_TXT)
							cdfile = cdFileCol.GetString(iSelMac);
						else
							{
							int iSel = ((iSelMac==0) ? 0:iSelMac-1);
							cdfile = cdFileCol.GetString(iSel);
							if (FIsArcExtention(cdfile.GetBufferExtention()))
								{
								if (iSel<iSelMac)
									cdfile = cdFileCol.GetString(iSelMac);
								}
							}
						if (cdfile.GetString()->IsEmpty() || !cdfile.FExistRealFile())
							{
							AfxGetApp()->DoWaitCursor(1);
							//ステータスバーの表示	
							CString cstrMsg;
							cstrMsg = pcdFile->GetBuffer();
//							cstrMsg.MakeLower();
							cstrMsg += " Scan....";
							((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));
							//FindFileOnlyなどでファイルがない場合は展開する
							TransData tranData;
							//元ファイルのパス取得
							n=ScanBeforeFileOrPath(nIndex, TRUE);
							tranData.pdFile = new CDFile;
							tranData.cdPath = m_bse[n].pcdFile->GetPath();
							tranData.dFileCollectBefor = pcdFile->GetBuffer();
							tranData.dFileCollectAfter = cdFileCol.GetBuffer();
							BOOL fDo = vpFileTransArray->FDoTrans(tranData, iTranFile==LSTENT_TXT);
							delete tranData.pdFile;
							AfxGetApp()->DoWaitCursor(-1);
							if (fDo)
								{
								*pListEntry->pcdStr = tranData.dFileCollectAfter.GetBuffer();
								continue;
								}
							else
								cdfile.GetString()->Empty();
							}
						break;
						}
					//if (bKft)
					if (iTranFile == LSTENT_TXT && ext_type != EXT_NON)
						KftTransFile(cdfile, ext_type, TRUE);
					return cdfile.GetFName();
					}
					break;
				case LSTENT_NORMAL:	//表示用
					cdfile = pcdFile->GetBuffer();
					break;
				default:
					ASSERT(FALSE);
					break;
				}
			}
		else
			{
			cdfile = *pcdFile;
			}
		if (fNameOnly)
			return pcdFile->GetFName();
		// Scanning File Path!
		n=ScanBeforeFileOrPath(nIndex, TRUE);
		cdfile.GetString()->InsertAt(0,m_bse[n].pcdFile->GetPath());
		//漢字コードマークアップを削除
		if (iTranFile == LSTENT_TXT && ext_type != EXT_NON){
			((CMainFrame *)AfxGetMainWnd())->SetPaneText("");
			KftTransFile(cdfile, ext_type);
		}
		return cdfile.GetFName();
		}
	else
		{
		// Path Only.
		if (fNameOnly)
			return cdfile.GetName();
		ASSERT(pcdFile->FExistAbsPath());
		return pcdFile->GetFName();
		}
}

//漢字コードマークアップを削除
void CListEntryArray::KftTransFile(CDFile &cdfile, EXT_TYPE type, BOOL bArc)
{
	CString str = cdfile.GetBuffer();
	if (type == EXT_XDOC) {
		if (vpFileTransArray->FDoKftTrans(str, type, bArc))
			cdfile.SetFName(str);
	}else if (type == EXT_KFT) {
//takaso2010
//		if (vpFindOption->m_bKftTransFileView /*(::GetAsyncKeyState(VK_SHIFT)&0x8000)*/
//			&& vpFileTransArray->FDoKftTrans(str, type, bArc))
//			cdfile.SetFName(str);
	}
}

/*
BOOL CListEntryArray::TrimMarkOfKftTransFile(CDFile &cdfile)
{
#define MARK_SIZE (6)
	CString strTmp = cdfile.GetFName();
	int len = strTmp.GetLength() - MARK_SIZE;
	if (len>0) {
		CString strTmp2 = strTmp.Right(MARK_SIZE);
		if (strTmp2==" <jis>" || strTmp2==" <euc>") {
			strTmp2 = strTmp.Left(len);
			cdfile.SetFName(strTmp2);
			return TRUE;
		}
	}
	return FALSE;
}
*/
EXT_TYPE CListEntryArray::TrimMarkOfKftTransFile(CDFile &cdfile)
{
#define MARK_MIN_LEN (6)	//" <jis>"・・・区切りの空白文字含む
#define MARK_BLAKETS_LEN (3)	//" <>"・・・区切りの空白文字含む
	CString strTmp = cdfile.GetFName();

	if ((strTmp.GetLength() - MARK_MIN_LEN)>0) {
		CString strMark = PickupMarkString(strTmp.GetBuffer());
		if (!strMark.IsEmpty()) {
			int len = strTmp.GetLength() - (MARK_BLAKETS_LEN + strMark.GetLength());
			if (strMark=="jis" || strMark=="euc" || strMark=="utf") {
				cdfile.SetFName(strTmp.Left(len));
				return EXT_KFT;
			}else if (vpFindDlg->m_fileSpecDlg.ExtxFromSzExt(strMark.GetBuffer()) != EXTX_NO) {
				cdfile.SetFName(strTmp.Left(len));
				return EXT_XDOC;
			}
		}
	}
	return EXT_NON;
}
CString CListEntryArray::PickupMarkString(char *psz)
{
	CString str;
	int len = strlen(psz);
	char *pszBlkStart;
	if (len!=0 && psz[len-1]=='>') {
		pszBlkStart = strrchr(psz, '<');
		if (pszBlkStart!=NULL) {
			pszBlkStart++;
			len = strlen(pszBlkStart);
			str = pszBlkStart;
			str.Delete(len-1, 1);
		}
	}
	return str;
}

CDString CListEntryArray::GetFName(size_ent nIndex, BOOL fNameOnly, CString& strPath)
{
	CListEntry *pListEntry = &m_bse[nIndex];
	CDFileExp *pcdFile = pListEntry->pcdFile;
	CDFile cdfile;
	size_ent n;
	if (pcdFile==NULL || pcdFile->GetString()->IsEmpty())
		{
		// Scanning File Name and Path!
		nIndex=ScanBeforeFileOrPath(nIndex, FALSE);
		pListEntry = &m_bse[nIndex];
		pcdFile = pListEntry->pcdFile;
		}
	if (pcdFile->FExistName())
		{
		//if (!pListEntry->pcdStr->IsEmpty() || CDFileCollect(pcdFile->GetBuffer()).GetSize()>1)
		//	cdfile = pcdFile->GetBuffer();
		//else
			cdfile = *pcdFile;
		if (!fNameOnly)
			{
			// Scanning File Path!
			n=ScanBeforeFileOrPath(nIndex, TRUE);
			strPath = m_bse[n].pcdFile->GetPath();
			}
		}
	else
		{
		// Path Only.
		if (!fNameOnly)
			{
			ASSERT(pcdFile->FExistAbsPath());
			strPath = pcdFile->GetPath();
			}
		}
	return cdfile.GetName();
}
// ファイル名およびパスのあるエントリーにリストを遡る
size_ent CListEntryArray::ScanBeforeFileOrPath(size_ent nIndex, register BOOL fPath)
{
	register size_ent n;
	ASSERT(nIndex>=0);
	register CDFileExp *pcdFile;
	for (n=nIndex-1; n>=0; n--)
		{
		pcdFile = m_bse[n].pcdFile;
		if (pcdFile)
			{
			if (fPath)
				{
				// && !pcdFile->FExistName()は変換ファイル対応
				if (pcdFile->FExistPath() && !pcdFile->FExistName())
					break;
				}
			else
				{
				if (pcdFile->FExistName())
					break;
				}
			}
		}
	return n;
}

// ファイル名/パスのあるエントリーにリストをスキャンする
size_ent CListEntryArray::ScanAfterFileAndPath(size_ent nIndex)
{
	register size_ent n;
	ASSERT(nIndex>=0);
	register CDFileExp *pcdFile;
	for (n=nIndex+1; n<m_wUseEntry; n++)
		{
		pcdFile = m_bse[n].pcdFile;
		if (pcdFile && !pcdFile->GetString()->IsEmpty())
			{
			//if (pcdFile->FExistName())
				break;
			//if (pcdFile->FExistPath())
			//	break;
			}
		}
	return n;
}
size_ent CListEntryArray::ScanAfterPath(size_ent nIndex)
{
	register CDFileExp *pcdFile;
	register size_ent n;
	ASSERT(nIndex>=0);
	for (n=nIndex+1; n<m_wUseEntry; n++)
		{
		pcdFile = m_bse[n].pcdFile;
		if (pcdFile && !pcdFile->GetString()->IsEmpty())
			{
			// && !pcdFile->FExistName()は変換ファイル対応
			if (pcdFile->FExistPath() && !pcdFile->FExistName())
				break;
			}
		}
	return n;
}

size_ent CListEntryArray::ScanAfterPath(size_ent nIndex, size_ent &entrys)
{
	register size_ent n;
	BOOL fCountDoc=TRUE;
	ASSERT(nIndex>=0);
	entrys = 0;
	register CDFileExp *pcdFile;
	for (n=nIndex+1; n<m_wUseEntry; n++)
		{
		pcdFile = m_bse[n].pcdFile;
		if (pcdFile && !pcdFile->GetString()->IsEmpty())
			{
			if (pcdFile->FExistName())
				{
				if (vpFindOption->m_fFile)
					{
					entrys++;
					if (m_bse[n].fOpen)
						fCountDoc=TRUE;
					else
						fCountDoc=FALSE;
					}
				}
			else// if (pcdFile->FExistPath())
				break;
			}
		else if (fCountDoc)
			entrys++;
		}
	return n;
}

// ビットマップタイプを取得する
int CListEntry::GetEntryTypeOfBmp()
{
	int et;
	/*if ((et=GetEntryType())==0)
		return 0;
	return (et-1)*2 + 1 + (fOpen ? 1:0);
	*/
	et = GetEntryType();
	return et*2 + 1 + (fOpen ? 1:0);
}
int CListEntry::GetEntryType()
{
	if (pcdFile==NULL)
		return -1;	// ｴﾝﾄﾘｰがない
	return pcdFile->GetBmpFileType();
}

// ｴﾝﾄﾘｰをｺﾋﾟｰする
/*************************************************************************
-- Routine: const CListEntry& CListEntry::operator = ( CListEntry &entrySrc )
-- Description and Usage:
		文字を CListEntry オブジェクトに入れる.
-- Arguments:
		CListEntry - 入れる文字.
-- Returns:
        CListEntry オブジェクト.
-- Notes:
-- History:
		'95.1	- created		(M.Design)
*************************************************************************/
const CListEntry& CListEntry::operator = ( CListEntry &entrySrc )
{
	*pcdFile = *entrySrc.pcdFile;		// ﾊﾟｽ名またはﾌｧｲﾙ名(ﾌｧｲﾙｱﾄﾘﾋﾞｭｰﾄ有り)    始めてのものだけ
	*pcdStr = *entrySrc.pcdStr;
	fOpen = entrySrc.fOpen;
	lLineNum = entrySrc.lLineNum;		// 番号(LineNum)
	dwHexNum = entrySrc.dwHexNum;		// 番号(HEX)
	//takaso2010
	m_paryMark->Copy(*entrySrc.m_paryMark);

	return *this;
}

