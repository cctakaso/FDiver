/*    PortTool v2.2     FINDLIST.CPP          */

#include "stdafx.h"
#include "..\mdfc\ch.h"
#include "..\mdfc\dfile.h"
#include "Fdiver.h"
#include "fdivedoc.h"
#include "fdivevw.h"
#include "mainfrm.h"
#include "findlist.h"
#include "findopti.h"
#include "finddlg.h"
#include "..\mdfc\dfile.h"
extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CFindOption *vpFindOption;
extern CFindDlg *vpFindDlg;
BOOL FCheckEsc();	// グローバル ESCチェック関数
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DISP_PERFECT
//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
//'\0'は、スペースに変換

IMPLEMENT_DYNCREATE(CFindList, CDBmpStrList)
BEGIN_MESSAGE_MAP(CFindList, CDBmpStrList)
	//{{AFX_MSG_MAP(CFindList)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_DROPFILES()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDR_ACT_DISPDOCEDIT, OnActDispdocedit)
	ON_COMMAND(IDR_ACT_DISPDOC, OnActDispdoc)
	ON_COMMAND(IDR_ACT_OPENFOLDER, OnOpenFolder)
	ON_COMMAND(IDR_EDIT_COPY_1, OnEditCopy1)
	ON_COMMAND(IDR_EDIT_REF_FILE, OnEditRefFile)
	ON_UPDATE_COMMAND_UI(IDR_ACT_DISPDOCEDIT, OnUpdateActDispdocedit)
	ON_UPDATE_COMMAND_UI(IDR_ACT_DISPDOC, OnUpdateActDispdoc)
	ON_UPDATE_COMMAND_UI(IDR_EDIT_COPY_1, OnUpdateEditCopy1)
	ON_UPDATE_COMMAND_UI(IDR_EDIT_REF_FILE, OnUpdateEditRefFile)
	ON_UPDATE_COMMAND_UI(IDR_EDIT_DELL_FILE, OnUpdateEditDellFile)
	ON_COMMAND(IDR_EDIT_DELL_FILE, OnEditDellFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifdef _DBCS
CT CtByteAt(BYTE far *szFirst, int bOffset)
{
	BYTE far *sz = szFirst;
	BYTE far *szCheck = &szFirst[bOffset];
	while ( TRUE )
		{
		if (sz==szCheck)
			break;
		else
			{
			if ( IsDBCSLeadByte ( *sz ) )
				{
				sz++ ;
				if (sz==szCheck)
					return ctDbc2b;
				}
			sz++;
			}
		}
	return IsDBCSLeadByte ( *sz ) ? ctDbc1b:ctSbc;
}
#endif //_DBCS

CFindList::CFindList()
{
	ResetList();
}
CFindList::~CFindList()
{
}

void CFindList::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		{
		ar << m_wFileCount;	// file counter
		ar << m_wFoundDirs;	// found counter
		ar << m_wFoundFiles;	// found counter
		ar << m_wFoundCount;	// found counter
		}
	else
		{
		ResetContent();
		ar >> m_wFileCount;	// file counter
		ar >> m_wFoundDirs;	// found counter
		ar >> m_wFoundFiles;	// found counter
		ar >> m_wFoundCount;	// found counter
		wsprintf(vz, "%3d", m_wFoundDirs);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 1);
		wsprintf(vz, "%4d", m_wFoundFiles);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 2);
		wsprintf(vz, "%5d", m_wFoundCount);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 3);
		wsprintf(vz, "%6d", m_wFileCount);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 4);
		}

	CDBmpStrList::Serialize(ar);
	m_FindLog.Serialize(ar);
}

/*BOOL CFindList::Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int nHeight,
		struct BSLIST_RESIDS *bsl_resids, int entrys, HFONT hfont)
{
	BOOL b = Create (dwStyle, rect, pParentWnd, nID, nHeight,
		bsl_resids, entrys, hfont);
//	COleDropTarget m_dropTarget;
//	m_dropTarget.Register(this);
	return b;
}
BOOL CFindList::Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL b = Create (dwStyle, rect, pParentWnd, nID);
//	COleDropTarget m_dropTarget;
//	m_dropTarget.Register(this);
	return b;
}
*/

BOOL CFindList::FAddList(CFindFile *pFindFile, ReturnLogic rl)
{
	ASSERT(rl==rlTrue || rl==rlNutral);
	m_LstEntry.ResetDataForFileEntry();


	// ディレクトリで最初のファイルか？
	if (pFindFile->m_fFirstFileOfDir)
		{
		// ディレクトリのエントリー
		// 変換ファイルサポート
		if (pFindFile->m_TranData.fTrans)
			m_LstEntry.pcdFile->SetFName(pFindFile->m_TranData.cdPath.GetBuffer());
		else
			m_LstEntry.pcdFile->SetFName(pFindFile->GetFindFile()->GetPath());
		if (rl==rlTrue)
			{
			if (!AddString())
				return FALSE;
			pFindFile->m_fFirstFileOfDir = FALSE;
			wsprintf(vz, "%3d", ++m_wFoundDirs);
			((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 1);
			}
		else
			{
			if (!AddStringToMemOnly())
				return FALSE;
			}
		}
	// 変換ファイルサポート
	if (pFindFile->m_TranData.fTrans)
		{
		// 変換ファイルの場合
		m_LstEntry.pcdFile->SetFName(pFindFile->m_TranData.dFileCollectBefor.GetBuffer());
		if (vpFindDlg->FFindFileOnly())
			m_LstEntry.pcdStr->Empty();
		else
			*m_LstEntry.pcdStr = pFindFile->m_TranData.dFileCollectAfter.GetBuffer();
		m_LstEntry.pcdFile->MakeAttrFromDosData(pFindFile->m_TranData.pFileTrans->PGetDta());
		}
	else
		{
		// 通常の場合
		m_LstEntry.pcdFile->SetFName(pFindFile->GetFindFile()->GetName());
		m_LstEntry.pcdStr->Empty();
		m_LstEntry.pcdFile->MakeAttrFromDosData(pFindFile->PGetDta());
		}

	m_LstEntry.m_paryMark->RemoveAll();//takaso2010

	//コード変換した？
//	int kanjType;
//	if (pFindFile->m_pKftDll) {
//		kanjType = pFindFile->m_pKftDll->DoGetType();
//		ASSERT(kanjType != kt_binary);
//		//ASSERT(kanjType != kt_unknown);
//		if (kanjType == kt_jis || kanjType == kt_euc || kanjType == kt_utf8)
//			*m_LstEntry.pcdFile->GetString() += "*";
//	}
	
	
	// ｽﾃｰﾀｽﾊﾞｰに処理ﾌｧｲﾙ数を表示
	BOOL bRtn;
	if (rl==rlTrue)
		{
		wsprintf(vz, "%4d", ++m_wFoundFiles);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 2);
		bRtn = AddString();
		}
	else
		{
		bRtn = AddStringToMemOnly();
		}

	//漢字コード変換マーク"*"の為に、ファイル名エントリーへのポインタを保存しておく
	if (bRtn) {
		m_wLastFileListEntry = m_pEntryArray->m_wUseEntry-1;
	}
	return bRtn;
}

BOOL CFindList::FAddList(CFindFile *pFindFile, long lMatchFirst, long cchMatched, BYTE far *lpchDoc, ReturnLogic rl)
{
	ASSERT(rl==rlTrue || rl==rlNutral);

	m_LstEntry.ResetDataForDocEntry((DWORD)lMatchFirst);

	size_ent len = vpFindOption->m_iDspListColum;
	//takaso2010
	MARK_FIND mf;


	// 行番号
	if (vpFindDlg->m_optDispNum==1)
		{
		BYTE far *lpchLine;
		long lLine;
		if (lpchLine = pFindFile->GetLineInfo(lMatchFirst, cchMatched, &lLine))
			{ // 文書表示する。
			BYTE far *lpch = lpchLine;
			if (!FMachBefor(pFindFile->GetFindFileBuffer(), lLine)) {
				ASSERT(vpFindDlg->m_fDispDoc);
				m_LstEntry.lLineNum = lLine;
				int iOffset = 0;
	#ifndef DISP_PERFECT
	//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
	//'\0'は、スペースに変換
				if (len>strlen((char far *)lpch))
					len = strlen((char far *)lpch);
	#endif
				BYTE ch;
				while(TRUE)
					{{
					//012345
					//     
					if (iOffset++>=len)
						break;
					ch = *lpch;
	#ifndef DISP_PERFECT
	#ifdef _DBCS
					if ( IsDBCSLeadByte ( ch ) )
						{
						if (iOffset++ >= len)
							break;
						lpch+=2;
						}
					else
	#endif //_DBCS
	#endif
					{
	#ifdef DISP_PERFECT
	//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
	//'\0'は、スペースに変換
						if (ch < chSpace) {
							if (ch == chReturn || ch == chNL)
								break;
							else {
								*lpch = chSpace;
							}
						}
	#else
						if (ch == chReturn || ch == '\0' || ch == chNL)
							break;
	#endif
						lpch++;
						}

					}}
				len = lpch-lpchLine;
#ifdef BUG20120117
				strncpy_s(vz, sizeof(vz),(char far *)lpchLine, len);
#else
				//warning C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
				strncpy(vz, (char far *)lpchLine, len);
#endif
				ASSERT(len<=vpFindOption->m_iDspListColum);
				vz[len] = '\0';
				*m_LstEntry.pcdStr = (char *)vz;
				m_LstEntry.m_paryMark->RemoveAll();//takaso2010
			}
			//takaso2010
			mf.pos = lMatchFirst - pFindFile->GetSeekLineBefor();
			mf.len = cchMatched;
			//if (m_LstEntry.m_paryMark->GetSize()>0) {//既に１つ追加してある
			//	mf.len = cchMatched > m_pLstEntry_save->pcdStr->GetLength() ? m_pLstEntry_save->pcdStr->GetLength():cchMatched;
			//}else{
			//	mf.len = cchMatched > m_LstEntry.pcdStr->GetLength() ? m_LstEntry.pcdStr->GetLength():cchMatched;
			//}
			m_LstEntry.m_paryMark->Add(mf);
			}
		else
			{
			if (FMachBefor(pFindFile->GetFindFileBuffer(), lLine))
				return TRUE;
			m_LstEntry.lLineNum = lLine;
			}
		}
	else if (vpFindDlg->m_fDispDoc)	// ﾄﾞｷｭﾒﾝﾄ表示
		{
		int boffset = lpchDoc - pFindFile->GetBuffer();
		if ( (len=vpFindOption->m_iDspListColum-1) >= pFindFile->GetReadSize()-boffset)
			len = (int)(pFindFile->GetReadSize()-boffset);
		else
			{
			ASSERT(lpchDoc[len-1] || !lpchDoc[len-1]);	// memory acsess check!
			if (CtByteAt(lpchDoc, len-1)==ctDbc2b)
				len--;
			}
		ASSERT(len>=0 && len<vpFindOption->m_iDspListColum);

#ifdef BUG20120117
		strncpy_s(vz, sizeof(vz), (char far *)lpchDoc, len);
#else
		//warning C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
		strncpy(vz, (char far *)lpchDoc, len);
#endif

		vz[len]='\0';
		*m_LstEntry.pcdStr = (char *)vz;
		m_LstEntry.m_paryMark->RemoveAll();//takaso2010

		//takaso2010
		mf.pos = 0;
		mf.len = cchMatched>len ?  len:cchMatched;
		m_LstEntry.m_paryMark->Add(mf);
		}

#ifndef DISP_PERFECT
	if (!m_LstEntry.pcdStr->IsEmpty())
		{
		BYTE ch;
		//0x20未満のキャラクタはTAB以外全て'.'にする。
		for (BYTE *pch=(BYTE *)m_LstEntry.pcdStr->GetBuffer(0); (ch=*pch)!='\0'; pch++)
			{{
			if (ch<chSpace)
				{
				if (ch==chTab)
					*pch = chSpace;
				else
					*pch = chDot;
				}
			}}
		}
#endif

	//takaso2010
	if (m_LstEntry.m_paryMark->GetSize()>1) {//既に１つ追加してある
		m_pLstEntry_save->m_paryMark->Add(mf);
		return true;
	}

	// ｽﾃｰﾀｽﾊﾞｰに処理ﾌｧｲﾙ数を表示
	if (rl==rlTrue)
		{
		wsprintf(vz, "%5d", ++m_wFoundCount);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 3);
#ifdef BUG20120117
		strcat_s(vz, sizeof(vz), " - FDiver");
#else
		// warning C4996: 'strcat': This function or variable may be unsafe. Consider using strcat_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
		strcat(vz, " - FDiver");
#endif
		((CMainFrame *)AfxGetMainWnd())->SetWindowText(vz);
		return AddString();
		}
	else
		{
		return AddStringToMemOnly();
		}
	return TRUE; //for compiler
}
// ﾃﾝﾎﾟﾗﾘｴﾝﾄﾘｰ配列から最後のｴﾝﾄﾘｰのみを破棄する
void CFindList::DeleteLastOneOfList()
{
	ASSERT((m_pEntryArray->m_wUseEntry > (size_ent)SendMessage( LB_GETCOUNT, 0, 0 )) &&
			(m_wTmpEntry>0) );
	m_pEntryArray->m_wUseEntry--;
	m_wTmpEntry--; //ﾃﾝﾎﾟﾗﾘｶｳﾝﾀ･ﾃﾞｸﾘﾒﾝﾄ
}

// ﾃﾝﾎﾟﾗﾘｴﾝﾄﾘｰ配列から実データへｱｯﾌﾟﾃﾞｰﾄして、ﾃﾝﾎﾟﾗﾘを破棄する
BOOL CFindList::FAddListFromTempList(CFindFile *pFindFile, ReturnLogic rl)
{

	ASSERT(rl==rlTrue || rl==rlFalse);

	BOOL rtn = TRUE;
	if (m_wTmpEntry==0)
		return TRUE;			// 全然テンポラリエントリーがない

	if (rl==rlTrue)
		{
		m_fStopScroll = TRUE;
		for (register size_ent i= m_pEntryArray->m_wUseEntry - m_wTmpEntry; i<m_pEntryArray->m_wUseEntry; i++)
			{
			if (FCheckEsc())
				{
				m_wTmpEntry =  m_pEntryArray->m_wUseEntry - i;
				rtn = FALSE;	// ﾕｰｻﾞによる中断
				break;
				}
			// ｴﾝﾄﾘｰのｺﾋﾟｰ
			//m_LstEntry = m_pEntryArray->m_bse[i];
			switch(m_pEntryArray->m_bse[i].GetEntryType())
				{
				case BFT_NO:
					//ﾌｧｲﾙの数のｲﾝｸﾘﾒﾝﾄ
					wsprintf(vz, "%5d", ++m_wFoundCount);
					((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 3);
					//if (SendMessage( LB_GETCURSEL, 0, 0)==LB_ERR)
					//	{
					//	int index = (int)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
					//	SendMessage( LB_SETTOPINDEX, index, 0) ;
					//	}
					break;
				case BFT_DIR:
					if (pFindFile->m_fFirstFileOfDir) //パス名のｴﾝﾄﾘｰがあるか？
						{//ﾊﾟｽｴﾝﾄﾘｰの数のｲﾝｸﾘﾒﾝﾄ
						wsprintf(vz, "%3d", ++m_wFoundDirs);
						((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 1);
						}
					pFindFile->m_fFirstFileOfDir = FALSE; //初めてのパス名のｴﾝﾄﾘｰﾌﾗｸﾞのクリア
					break;
				default:
					//ﾌｧｲﾙの数のｲﾝｸﾘﾒﾝﾄ
					wsprintf(vz, "%4d", ++m_wFoundFiles);
					((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 2);
					break;
				}
			// ｴﾝﾄﾘｰの追加
			if (!AddStringToLstBoxOnly(i))
				{
				//正常にﾃﾝﾎﾟﾗﾘｴﾝﾄﾘに追加出来たかった分をｶｳﾝﾄ
				// m_wTmpEntry - (i - (m_pEntryArray->m_wUseEntry - m_wTmpEntry) )
				m_wTmpEntry =  m_pEntryArray->m_wUseEntry - i;
				rtn = FALSE;
				break;
				}
			}
		wsprintf(vz, "%5d - FDiver", ++m_wFoundCount);
		((CMainFrame *)AfxGetMainWnd())->SetWindowText(vz);
		//正常に全てのﾃﾝﾎﾟﾗﾘｴﾝﾄﾘを追加できたので
		if (rtn==TRUE)
			m_wTmpEntry = 0;	//ﾃﾝﾎﾟﾗﾘｶｳﾝﾀ･ｸﾘｱ
		if (SendMessage( LB_GETCURSEL, 0, 0)==LB_ERR)
			{
			int index = (int)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			SendMessage( LB_SETTOPINDEX, index, 0) ;
			}
		}

	m_fStopScroll = FALSE;
	// 残りのﾃﾝﾎﾟﾗﾘﾘｽﾄｴﾝﾄﾘｰﾘｽﾄの数をｸﾘｱする
	ASSERT(m_pEntryArray->m_wUseEntry>=m_wTmpEntry);
	m_pEntryArray->m_wUseEntry-=m_wTmpEntry; //ﾃﾝﾎﾟﾗﾘｴﾝﾄﾘの分をｸﾘｱ
	m_wTmpEntry = 0;	//ﾃﾝﾎﾟﾗﾘｶｳﾝﾀ･ｸﾘｱ
	return rtn;
}


BOOL CFindList::AddString()
{

	//32bitバージョンでは、ﾒﾓﾘは余裕があるのでListのｴﾝﾄﾘｰ数で制限する
	if (m_wFoundCount>vpFindOption->m_iMaxLines)
	//16bitバージョンでは、ﾒﾓﾘを厳密に規定する必要があるのでListのｴﾝﾄﾘｰ数で制限する
	//if (m_pEntryArray->m_wUseEntry>vpFindOption->m_iMaxLines)
	// 大部分は、m_wFoundCountで数えても余裕があるはず。
		{
		wsprintf(vz, "%5d", --m_wFoundCount);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 3);
		BeepMessageLog(IDS_OVERENTRY_FORLST);
		return FALSE ;
		}
//#ifndef WIN32
	RECT rc;
	BOOL fValid = !GetUpdateRect(&rc);	
//#endif //!WIN32
	// ﾘｽﾄへの反映
	if (AddString(&m_LstEntry)>=0)
		{		
		size_ent index;
#ifdef WIN32
		// 挿入前が更新領域がなくて、挿入後更新領域のある場合
		if (fValid && GetUpdateRect(&rc))
			{
			index = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			ValidateRect(NULL);
			SendMessage( LB_GETITEMRECT, index, (LPARAM)(LPSTR)&rc ) ;
			InvalidateRect(&rc);
			UpdateWindow();
			}
		// ﾘｽﾄの項目は一つも選ばれていない場合は、最終ｴﾝﾄﾘｰが見えるようにｽｸﾛｰﾙさせる
		else 
		if (SendMessage( LB_GETCURSEL, 0, 0)==LB_ERR)
			{
			index = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			if (fValid)
				::SendMessage ( m_hWnd, WM_SETREDRAW, (WPARAM)FALSE, (LPARAM)0 ) ;
			SendMessage( LB_SETTOPINDEX, index, 0) ;
			if (fValid)
				{
				int nScr = (int)SendMessage( LB_GETITEMHEIGHT, index, 0);
				GetClientRect(&rc);
				rc.top +=nScr;
				::SendMessage ( m_hWnd, WM_SETREDRAW, (WPARAM)TRUE, (LPARAM)0 ) ;
				ScrollWindow(0,-nScr, &rc);
				ValidateRect(NULL);
				SendMessage( LB_GETITEMRECT, index, (LPARAM)(LPSTR)&rc ) ;
				InvalidateRect(&rc);
				UpdateWindow();
				}
			}
#else
		// 挿入前が更新領域がなくて、挿入後更新領域のある場合
		if (fValid && GetUpdateRect(&rc))
			{
			index = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			ValidateRect(NULL);
			SendMessage( LB_GETITEMRECT, index, (LPARAM)(LPSTR)&rc ) ;
			InvalidateRect(&rc);
			UpdateWindow();
			}
		// ﾘｽﾄの項目は一つも選ばれていない場合は、最終ｴﾝﾄﾘｰが見えるようにｽｸﾛｰﾙさせる
		else 
		if (SendMessage( LB_GETCURSEL, 0, 0)==LB_ERR)
			{
			index = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			SendMessage( LB_SETTOPINDEX, index, 0) ;
			}
#endif //WIN32
		return TRUE;
		}
	else
		return FALSE;
}
BOOL CFindList::AddStringToMemOnly()
{
	return AddStringToMemOnly(&m_LstEntry);
}
BOOL CFindList::AddStringToLstBoxOnly(int indexAppend)
{
	//32bitバージョンでは、ﾒﾓﾘは余裕があるのでListのｴﾝﾄﾘｰ数で制限する
	if (m_wFoundCount>vpFindOption->m_iMaxLines)
	//16bitバージョンでは、ﾒﾓﾘを厳密に規定する必要があるのでListのｴﾝﾄﾘｰ数で制限する
	//if (m_pEntryArray->m_wUseEntry>vpFindOption->m_iMaxLines)
	// 大部分は、m_wFoundCountで数えても余裕があるはず。
		{
		wsprintf(vz, "%5d", --m_wFoundCount);
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 3);
		BeepMessageLog(IDS_OVERENTRY_FORLST);
		return FALSE ;
		}

//#ifndef WIN32
	RECT rc;
	BOOL fValid = !GetUpdateRect(&rc);	
//#endif //!WIN32
	// ﾘｽﾄへの反映
	if (ViewString(indexAppend, TRUE)>=0)
		{		
		size_ent index;
//#ifndef WIN32
		// 挿入前が更新領域がなくて、挿入後更新領域のある場合
		if (fValid && GetUpdateRect(&rc))
			{
			index = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			ValidateRect(NULL);
			SendMessage( LB_GETITEMRECT, index, (LPARAM)(LPSTR)&rc ) ;
			InvalidateRect(&rc);
			UpdateWindow();
			}
		// ﾘｽﾄの項目は一つも選ばれていない場合は、最終ｴﾝﾄﾘｰが見えるようにｽｸﾛｰﾙさせる
		else 
//#endif //!WIN32
		if (/*!m_fStopScroll &&*/ SendMessage( LB_GETCURSEL, 0, 0)==LB_ERR)
			{
			index = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 ) -1;
			SendMessage( LB_SETTOPINDEX, index, 0) ;
			}
		return TRUE;
		}
	else
		return FALSE;
}
/*************************************************************************
-- Routine:int CFindList::AddString ( CListEntry *entry)
-- Description and Usage:
		リスト内の項目に、新しい項目を追加登録する.
-- Arguments:
		char sz	- ｴﾝﾄﾘｰ文字列
		int et	- ｴﾝﾄﾘｰﾀｲﾌﾟ
-- Returns:
-- Notes:

-- History:
		'95.1	- created		(M.Design)
*************************************************************************/
int CFindList::AddString ( CListEntry *entry )
{
//	TRACE ( "\n - THIS_CLASS::AddString - " ) ;

	// ﾒﾓﾘの拡張
	if (!m_pEntryArray->FExpandEntry ( m_pEntryArray->m_wUseEntry +1 ))
		{
		BeepMessageLog(IDS_OVERMEM_FORLST);
		return ( BMPSTR_ERRSPACE ) ;
		}
	
	// ﾊﾟﾗﾒｰﾀﾃﾞｰﾀのｺﾋﾟｰ
	// ::SendMessage(m_hWnd, , 0, 0);	// ﾘｽﾄをｱｯﾌﾟﾃﾞｰﾄしない。
	ASSERT(m_pEntryArray->m_wUseEntry>0);
	m_pEntryArray->m_bse[m_pEntryArray->m_wUseEntry-1] = *entry;

	m_pLstEntry_save = &m_pEntryArray->m_bse[m_pEntryArray->m_wUseEntry-1]; //takaso2010

	return ViewString(m_pEntryArray->m_wUseEntry-1, TRUE);

}
BOOL CFindList::AddStringToMemOnly ( CListEntry *entry)
{
//	TRACE ( "\n - THIS_CLASS::AddString - " ) ;

	// ﾒﾓﾘの拡張
	if (!m_pEntryArray->FExpandEntry ( m_pEntryArray->m_wUseEntry +1 ))
		{
		BeepMessageLog(IDS_OVERMEM_FORLST);
		return ( FALSE ) ;
		}
	
	// ﾊﾟﾗﾒｰﾀﾃﾞｰﾀのｺﾋﾟｰ
	// ::SendMessage(m_hWnd, , 0, 0);	// ﾘｽﾄをｱｯﾌﾟﾃﾞｰﾄしない。
	ASSERT(m_pEntryArray->m_wUseEntry>0);
	m_pEntryArray->m_bse[m_pEntryArray->m_wUseEntry-1] = *entry;

	m_pLstEntry_save = &m_pEntryArray->m_bse[m_pEntryArray->m_wUseEntry-1]; //takaso2010

	m_wTmpEntry++;	//ﾃﾝﾎﾟﾗﾘｶｳﾝﾀ･ｲﾝｸﾘﾒﾝﾄ
	return TRUE;
}

void CFindList::ListInPathOrFile(BOOL bOpenPath, BOOL bOpenFile)
{
	m_pEntryArray->MarkeFOpenOfFiles(bOpenPath, vpFindDlg->FFindFileOnly() ? TRUE:bOpenFile);
	wsprintf(vz, "%d paths - %d files - %d lines", (int)m_wFoundDirs, (int)m_wFoundFiles, (int)m_wFoundCount);
	((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz);
	ResetViewString(TRUE);
}

void CFindList::SortList(SORTTYPE st)
{
	if (GetMemEntrys()<=0 ||
		((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
		return;

	AfxGetApp()->DoWaitCursor(1);


	CString cstr;
	cstr.LoadString(IDS_STBAR_STOP);

	if (m_pEntryArray->m_SortType == st)
		m_pEntryArray->m_bAsc = !m_pEntryArray->m_bAsc;
	else
		{
		m_pEntryArray->m_SortType = st;
		m_pEntryArray->m_bAsc = TRUE;
		}

	if (m_pEntryArray->m_SortType!=SORTTYPE_NO)
		{
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(_T("now sorting..../stop:[ESC]-key"));
		if (vpFindOption->m_fDir ? !m_pEntryArray->FMakeSortIndexOfPath(TRUE):!m_pEntryArray->FMakeSortIndexFlat())
			{
			((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstr.GetBuffer(0));
			ResetSort();
			}
		}
	else
		ResetSort();

	wsprintf(vz, "%d paths - %d files - %d lines", (int)m_wFoundDirs, (int)m_wFoundFiles, (int)m_wFoundCount);
	((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz);

	ResetViewString(TRUE);

	AfxGetApp()->DoWaitCursor(-1);
}

int CFindList::ResetViewString(BOOL bSel)
{
	size_ent nIndexSel=-1;
	if (bSel)
		{
		nIndexSel = GetDataIndexFromSel(GetCurSel());
		ResetHeaderType(FALSE);
		}
	BASE_CLASS::ResetContent();

	m_OptOfViewString = 0;
	if (m_pEntryArray->m_SortType == SORTTYPE_NO)
		{
		for (register size_ent i=0; i<m_pEntryArray->m_wUseEntry; i++)
			{{
			if (ViewString(i, TRUE)<0)
				goto Err;
			}}
		}
	else
		{
		size_ent sel=0;
		size_ent nIndexPath, nIndexFile;
		if (!vpFindOption->m_fDir)
			for (size_ent key = 0; ; key++)
				{{
				if ((nIndexFile = m_pEntryArray->GetFileIndexFlat(key))!=(size_ent)-1)
					{
					if (ViewString (nIndexFile, TRUE, sel++)<0)
						goto Err;
					size_ent nAfter = m_pEntryArray->ScanAfterFileAndPath(nIndexFile);
					for (size_ent n = nIndexFile+1; n<nAfter; n++)
						{
						if (ViewString (n, TRUE, sel++)<0)
							goto Err;
						}
					}
				else
					break;
				}}
		else
		for (size_ent keyP = 0; ; keyP++)
			{{
			if ((nIndexPath= m_pEntryArray->GetPathIndex(keyP))!=(size_ent)-1)
				{
				if (ViewString (nIndexPath, TRUE, sel++)<0)
					goto Err;
				for (size_ent key = 0; ; key++)
					{
					if ((nIndexFile= m_pEntryArray->GetFileIndexInPath(nIndexPath, key))!=(size_ent)-1)
						{
						if (ViewString (nIndexFile, TRUE, sel++)<0)
							goto Err;
						size_ent nAfter = m_pEntryArray->ScanAfterFileAndPath(nIndexFile);
						for (size_ent n = nIndexFile+1; n<nAfter; n++)
							{
							if (ViewString (n, TRUE, sel++)<0)
								goto Err;
							}
						}
					else
						break;
					}
				}
			else
				break;
			}}
		}									
	if (nIndexSel!=(size_ent)-1)
		{
		SetSelFromDataIndex(nIndexSel);
		ResetHeaderType(FALSE);
		}
	else
		{
		SetCurSel(0);
		ResetHeaderType(FALSE);
		}
	return 0;//default
Err:
	SetCurSel(0);
	ResetHeaderType(FALSE);
	return -1;
}

int CFindList::ViewString (size_ent nIndex, BOOL fCheckOpen, int insPos)
{
	int iRet;
	// ﾘｽﾄへの反映

	if (fCheckOpen)
		{
		if (nIndex == 0)
			m_OptOfViewString = 0;	//ｲﾆｼｬﾙｸﾘｱ
		ASSERT(nIndex >= 0 && nIndex < m_pEntryArray->m_wUseEntry);
		CListEntry *pcListEntry = &m_pEntryArray->m_bse[nIndex];
		CDFileExp *pcdFe = pcListEntry->pcdFile;
		// パスのｴﾝﾄﾘｰか?
		// && !pcdFile->FExistName()は変換ファイル対応
		if (pcdFe->FExistPath() && !pcdFe->FExistName())
			{
			if (!vpFindOption->m_fDir)
				return 0; //Set default
			if (!pcListEntry->fOpen && vpFindOption->m_fDir)
				m_OptOfViewString = 1; //path closed mark set!
			else
				m_OptOfViewString = 0; //path open!
			}
		else
			{
			if (m_OptOfViewString==1)//path closed ?
				return 0;
			//ファイルのｴﾝﾄﾘｰか？
			if (pcdFe->FExistName())
				{
				if (!vpFindDlg->FFindFileOnly() && !vpFindOption->m_fFile)
					return 0; //Set default
				if (!pcListEntry->fOpen && vpFindOption->m_fFile)
					m_OptOfViewString |= 2; //file closed mark set!
				else
					m_OptOfViewString &= 1; //file open!
				}
			// 文書または位置のｴﾝﾄﾘｰ
			else
				{
				if (m_OptOfViewString>0)//path or file closed ?
					return 0;
				//文書または位置表示ではない？
				if (!vpFindOption->m_optDispNum && !vpFindOption->m_fDispDoc)
					return 0; //Set default
				}
			}
		iRet= (int)::SendMessage( m_hWnd, BMPSTR_ADDSTRING, 0, (LPARAM) nIndex) ;
		}
	else
		iRet= (int)::SendMessage( m_hWnd, BMPSTR_INSERTSTRING, insPos, (LPARAM) nIndex) ;

	if (iRet<0)
		{
		BeepMessageLog(IDS_OVERMEM_FORLST);
		((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
		}
	return iRet;
}


void CFindList::ResetContent()
{
	// ﾘｽﾄｴﾝﾄﾘｰのﾘｾｯﾄ
	THIS_CLASS::ResetContent();
	ResetHeaderType(TRUE);
	ResetList();
}

void CFindList::ResetList()
{
	m_wFileCount =0 ;
	m_wFoundDirs =0;
	m_wFoundFiles =0;
	m_wFoundCount =0;
	m_dTmpFileTxt = "readme.txt";
	ResetSort();
	m_lLineBefor = -1;
	m_wTmpEntry = 0;
	m_fStopScroll = FALSE;
}

BOOL CFindList::FMachBefor(char *sz, long lLine)
{
	BOOL f=FALSE;
	if (m_cStrLstBefor.CompareNoCase(sz)==0)
		f = (m_lLineBefor == lLine);
	m_lLineBefor = lLine;
	m_cStrLstBefor = sz;
	return f;
}

/*************************************************************************
-- Routine:BOOL CFindList::OnChildNotify(UINT message, WPARAM,
										LPARAM lParam, LRESULT* pLResult)

-- Description and Usage:
		リストボックスにメッセージが post された時に呼ばれる
-- Arguments:
		UINT message	  - メッセージ
		WPARAM			  - WPARAM
		LPARAM lParam	  - LPARAM
		LRESULT* pLResult - 

-- Returns:
		そのままメッセージを親へ戻す

-- Notes:

-- History:
		'94.8	- created		(M.Design)
*************************************************************************/
BOOL CFindList::OnChildNotify ( UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT* pLResult )
{
	switch ( uMessage ){

/*    PortTool v2.2     1995/10/16    8:4          */
/*      Found   : WM_COMMAND          */
/*      Issue   : wParam/lParam の取り扱いに注意。詳細についてはテクニカルリファレンスをご覧下さい。          */
		case WM_COMMAND:
#ifdef WIN16_32
			switch ( DGetWmCommandCmd(wParam,lParam))
				{
				case LBN_DBLCLK:
					EnterListItem(!(::GetAsyncKeyState(VK_CONTROL)&0x8000));
					break;
				case LBN_SELCHANGE:
					//Headerの書き換え
					ResetHeaderType();
					AfxGetApp()->CWinApp::OnIdle(0);
					break;
				default:
					break;
				}
			return( CListBox::OnChildNotify(uMessage, wParam, lParam, pLResult)) ;
#else
			if ( HIWORD (lParam) == LBN_DBLCLK )
				EnterListItem(!(::GetAsyncKeyState(VK_CONTROL)&0x8000));
			else if ( HIWORD (lParam) == LBN_SELCHANGE )
				AfxGetApp()->CWinApp::OnIdle(0);
			return( CListBox::OnChildNotify(uMessage, wParam, lParam, pLResult)) ;
#endif //WIN _32
		default:
			return( CListBox::OnChildNotify(uMessage, wParam, lParam, pLResult)) ;
	}
	return TRUE ;
}
void CFindList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
#define VK_CTR_RETURN  0x0A
	if (nChar == VK_RETURN || nChar == VK_CTR_RETURN || (nChar == VK_SPACE && GetCurSel()>=0))
		EnterListItem(!(::GetAsyncKeyState(VK_CONTROL)&0x8000), nChar);
	//else if (nChar == VK_CONTROL && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	//	OnLButtonDown(NULL, NULL);
	/*else*/ //don't else!
	THIS_CLASS::OnChar(nChar, nRepCnt, nFlags);
}
void CFindList::EnterListItem(BOOL fEditer, UINT nChar)
{
	int sel = GetCurSel();
	size_ent nIndex = GetDataIndexFromSel(sel);
	if (nIndex != -1)
		{
		int et= m_pEntryArray->GetEntryType(nIndex);
		switch (et)
			{
			case BFT_NO:
				if (nChar!=VK_SPACE && nChar!=VK_LEFT && nChar!=VK_RIGHT)
					OpenDocument(fEditer);
				break;
			//case BFT_PROG:
			//case BFT_SYS:
			//case BFT_DOC:
			//case BFT_OTHERS:
			//case BFT_DIR:
			default:
				if ( nChar!=VK_SPACE && nChar!=VK_LEFT && nChar!=VK_RIGHT && 
					(et!=BFT_DIR && 
					(::GetAsyncKeyState(VK_SHIFT)&0x8000 || ::GetAsyncKeyState(VK_CONTROL)&0x8000
					 || vpFindDlg->FFindFileOnly()
					 || (nIndex+1<m_pEntryArray->m_wUseEntry && m_pEntryArray->GetEntryType(nIndex+1)!=BFT_NO) ))//this is for "!abc" cases.
					 )
					OpenDocument(fEditer);
				else
					{
					size_ent entrys;
					size_ent nAfter;
					if (((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
						return; //検索中は、だめ！
					if (m_pEntryArray->m_bse[nIndex].fOpen ? nChar==VK_RIGHT:nChar==VK_LEFT)
						return;//ｵｰﾌﾟﾝ状態の入れ子をガード
					ASSERT(nIndex >= 0 && nIndex < m_pEntryArray->m_wUseEntry);
					if (m_pEntryArray->m_bse[nIndex].fOpen = !m_pEntryArray->m_bse[nIndex].fOpen)
						{
						//Do open
						//表示登録のインサート
						size_ent addNum=0;
						if (et==BFT_DIR)
							{
							nAfter = m_pEntryArray->ScanAfterPath(nIndex);
							if (vpFindOption->m_fFile)
								//view file only
								{
								// sort
								size_ent nIndexFile;
								for (size_ent key = 0; ; key++)
									{{
									if ((nIndexFile= m_pEntryArray->GetFileIndexInPath(nIndex, key))!=(size_ent)-1)
										{
										ASSERT(nIndexFile >= 0 && nIndexFile < m_pEntryArray->m_wUseEntry);
										m_pEntryArray->m_bse[nIndexFile].fOpen = vpFindDlg->FFindFileOnly();
										addNum++;
										if (ViewString(nIndexFile, FALSE, ++sel)<0)
											return;
										}
									else
										break;
									}}
								}
							else
								{
								// sort
								size_ent nIndexFile;
								for (size_ent key = 0; ; key++)
									{{
									if ((nIndexFile= m_pEntryArray->GetFileIndexInPath(nIndex, key))!=(size_ent)-1)
										{
										nAfter = m_pEntryArray->ScanAfterFileAndPath(nIndexFile);
										for (size_ent n = nIndexFile+1; n<nAfter; n++)
											{
											addNum++;
											if (ViewString (n, FALSE, ++sel)<0)
												return;
											}
										}
									else
										break;
									}}
								}
							wsprintf(vz, "%d files in this path", (int)addNum);
							}
						else
							{
							//view all doc item
							nAfter = m_pEntryArray->ScanAfterFileAndPath(nIndex);
							for (size_ent n = nIndex+1; n<nAfter; n++)
								{{
								addNum++;
								if (ViewString (n, FALSE, ++sel)<0)
									return;
								}}
							wsprintf(vz, "%d lines in this file", (int)addNum);
							}
						((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz);
						}
					else
						{
						//Do close
						if (et==BFT_DIR)
							{
							//どれが見えているか解らない
							nAfter = m_pEntryArray->ScanAfterPath(nIndex, entrys);
							DeleteString (sel+1, entrys);
							}
						else  //if (!vpFindDlg->FFindFileOnly())
							{
							// 文書登録全てを削除
							nAfter = m_pEntryArray->ScanAfterFileAndPath(nIndex);
							DeleteString (sel+1, nAfter - nIndex - 1);
							}
						((CMainFrame *)AfxGetMainWnd())->SetPaneText("");
						}
					}
				break;
			}
		}
}

void CFindList::OpenDocument(BOOL fEditer)
{
	BOOL fNoDDE=FALSE;
	CDString cdstr;
	long lLine = 0;
	DWORD dwHexNum = 0;


	int sel = GetCurSel();
	size_ent nIndex = GetDataIndexFromSel(sel);

	if (nIndex==(size_ent)-1)
		return ; //選ばれていない
	int et = m_pEntryArray->GetEntryType(nIndex);
	if (et==BFT_NO)
		{
		cdstr = m_pEntryArray->GetFName(nIndex, FALSE, (fEditer ? LSTENT_TXT:LSTENT_DOC));
		lLine = m_pEntryArray->m_bse[nIndex].lLineNum;
		dwHexNum = m_pEntryArray->m_bse[nIndex].dwHexNum;
		}
	else if (et==BFT_DIR)
		return ; //ディレクトリを選んでる
	else 
		cdstr = m_pEntryArray->GetFName(nIndex, FALSE, (fEditer ? LSTENT_TXT:LSTENT_DOC));


	if (cdstr.IsEmpty())
		return;
	//cdstr.MakeUpper();

	OpenDocument(cdstr, lLine, dwHexNum, fEditer);
}

void CFindList::OpenDocumentByApp(char *szExe)
{
	BOOL fNoDDE=FALSE;
	CDString cdstr;
	long lLine = 0;
	DWORD dwHexNum = 0;

	int sel = GetCurSel();
	size_ent nIndex = GetDataIndexFromSel(sel);

	if (nIndex==(size_ent)-1)
		return ; //選ばれていない
	int et = m_pEntryArray->GetEntryType(nIndex);
	if (et==BFT_NO)
		{
		cdstr = m_pEntryArray->GetFName(nIndex, FALSE, LSTENT_DOC);
		lLine = m_pEntryArray->m_bse[nIndex].lLineNum;
		dwHexNum = m_pEntryArray->m_bse[nIndex].dwHexNum;
		}
	else if (et==BFT_DIR)
		return ; //ディレクトリを選んでる
	else 
		cdstr = m_pEntryArray->GetFName(nIndex, FALSE, LSTENT_DOC);


	if (cdstr.IsEmpty())
		return;
	//cdstr.MakeUpper();

	OpenDocument(cdstr, lLine, dwHexNum, FALSE, szExe);
}

void CFindList::OpenDocument(LPCSTR lpszFileName, long lLine, DWORD dwHexNum, BOOL fEditer, char *szExe)
{
	BOOL fNoDDE=FALSE;

	ASSERT(lpszFileName);


	CDFile cdfile;
	CDString cdStrParam;

	// 実行ﾌｧｲﾙ名の取得

	CDFile cdstrFile = lpszFileName;
	CDString cdstrPath = cdstrFile.GetPath();
	HINSTANCE hInst;
//	cdstrFile.GetString()->MakeUpper();
//	BOOL fTxt=(cdstrFile.GetName().Find(".TXT")!=(COFFSET)-1);
	if (cdstrPath.GetByteLength()!=3)
		cdstrPath.FRemoveTail();
	{
	CString str;
	str = _T("\"");
	str += cdstrFile.GetBuffer();
	str += _T("\"");
	cdstrFile = str;
	str = _T("\"");
	str += cdstrPath.GetBuffer();
	str += _T("\"");
	cdstrPath = str;
	}
TryAgain:
	if (szExe) {
		cdfile = szExe;
		fNoDDE = TRUE;
	}else if (fEditer /*|| fTxt*/)
		{
		// 指定エディタを試してみる
		if (!vpFindOption->m_strEditer.IsEmpty())
			{
			CString str;
			str = _T("\"")+vpFindOption->m_strEditer+_T("\"");
			//hInst=FindExecutable(str, cdstrPath.GetBuffer(), vz);
			cdfile = str;
			//cdfile.GetString()->MakeUpper();
			hInst = (HINSTANCE)32;
			}
		else
			hInst = 0;
		if ((UINT)hInst<=31)
			{
			// HACK! ここでは、通常のREGデータによりNOTEPAD.EXEが取得されたら
			//WIN.INIの設定優先させる。
			hInst=FindExecutable(/*fTxt ? cdstrFile.GetBuffer():*/m_dTmpFileTxt.GetBuffer(), cdstrPath.GetBuffer(), vz);
			cdfile = vz;
			cdfile.GetString()->MakeUpper();
			if ((UINT)hInst<=31 || cdfile.GetString()->Find("NOTEPAD.EXE")!=(COFFSET)-1)
				{
				vz[0] = '\0';
				::GetProfileString("Extensions","TXT","", vz, sizeof(vz)-1);
				char *pExt=strchr(vz, (int)'^');
				if (!pExt)
					pExt=vz+strlen(vz);
				*pExt ='\0';
				if (strlen(vz)==0)
					cdfile = "NOTEPAD.EXE";
				else
					cdfile = vz;
				}
			}
		fNoDDE = TRUE;
		}
	else
		{
//BUGFIX:みつからなくても DDEには行くようにする。
//		hInst=FindExecutable(cdstrFile.GetBuffer(), cdstrPath.GetBuffer(), vz);
//		if ((UINT)hInst<=31)
//			{
//			fEditer = TRUE;
//			goto TryAgain;
//			}
//		cdfile = vz;
		}
	// 大文字にしておく
	cdfile.GetString()->MakeUpper();

	// 実行ﾌｧｲﾙのｵｰﾌﾟﾝﾊﾟﾗﾒｰﾀの取得
	if (!cdfile.GetString()->IsEmpty()) {
		if (lLine>0) { // 行番号表示
			//1999.10.31
			//mint.exe -JB%L %F
			CDString cdParam = vpFindOption->GetExeParam(cdfile.GetName().GetBuffer());
			if (!cdParam.IsEmpty())	{
				// 起動オプションのあるものは、すべてDDEオープンコマンドではジャンプできないはず。
				fNoDDE = TRUE;
				//cdStrParam = (char)chSpace;

				CDString cdStrNum;
				COFFSET off;
/*				if (cdfile.GetName().ComparePrefix("MIW.EXE")==0) {
					cdStrNum.AddNumString(lLine);
					cdStrParam = " \"";
					cdStrParam += lpszFileName;
					cdStrParam += "+";
					cdStrParam += cdStrNum;
					cdStrParam += "\"";
				}else{
*/
				if (cdfile.GetName().ComparePrefix("MINT")==0 && cdParam.Find("/JB")!=-1)
						cdStrNum.AddNumString(dwHexNum);
					else
						cdStrNum.AddNumString(lLine);
					off = cdParam.Find("\\L");
					if (off != -1) {
						cdStrParam = cdParam.Mid(0, off) + cdStrNum + cdParam.Mid(off+2);
					}else{
						cdStrParam = cdParam;
						cdStrParam += cdStrNum;
					}

					off = cdStrParam.Find("\\F");
					if (off != -1) {
						cdStrParam = cdStrParam.Mid(0, off) + cdstrFile.GetBuffer() + cdStrParam.Mid(off+2);
					}else{
						cdStrParam += (char)chSpace;
						cdStrParam += cdstrFile.GetBuffer();
					}
//				}
			}
		}
	}
	if (fNoDDE) {
		//ｺﾏﾝﾄﾞﾌﾟﾛﾝﾌﾟﾄの結合
		if (cdStrParam.IsEmpty()) {
			*cdfile.GetString() += (char)chSpace;
			*cdfile.GetString() += cdstrFile.GetBuffer();
		}else{
			*cdfile.GetString() += cdStrParam;
		}

		//実行
		if (::WinExec(cdfile.GetBuffer(), SW_SHOWNORMAL)<=31)
			goto Err;
		else
			SetActiveWindow();
	}else {
		hInst = ShellExecute(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), "open",
				cdstrFile.GetBuffer(), NULL, NULL, SW_SHOWNORMAL);
		if ((UINT)hInst<=31) {
			TRACE("Try Secand ShellExecute()\n");
			if (::WinExec(cdstrFile.GetBuffer(), SW_SHOWNORMAL)<=31) {
				if ((UINT)(hInst = ShellExecute(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), NULL/*"open"*/,
					cdstrFile.GetBuffer(), cdStrParam.GetBuffer(), cdstrPath.GetBuffer(), SW_SHOW))<=31)
					goto Err;
			}
		}
	}
	return;
Err:
	Message(IDS_ASSO_ERR, FALSE);
}


BOOL CFindList::IsSelectedFile() 
{
	size_ent nIndex = GetDataIndexFromSel(GetCurSel());
	if (nIndex==(size_ent)-1)
		return FALSE; //選ばれていない
	return m_pEntryArray->GetEntryType(nIndex) != BFT_DIR;
}

BOOL CFindList::IsSelectedLine() 
{
	size_ent nIndex = GetDataIndexFromSel(GetCurSel());
	if (nIndex==(size_ent)-1)
		return FALSE; //選ばれていない
	return m_pEntryArray->GetEntryType(nIndex) == BFT_NO;
}

void CFindList::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDBmpStrList::OnLButtonDown(nFlags, point);
	//SendMessage(WM_LBUTTONDOWN, nFlags,
	//	(LONG) MAKELONG(point.x, point.y));
	//SendMessage(WM_LBUTTONUP, nFlags,
	//	(LONG) MAKELONG(point.x, point.y));

	// if control-key downed then try drag & drop server!
#ifdef DRAGSAVER_WITH_SHIFTKEY
	if (::GetAsyncKeyState(VK_SHIFT)&0x8000)
		SendMessage(WM_LBUTTONUP, nFlags,
			(LONG) MAKELONG(point.x, point.y));
	else
		return;
#else
	if (vpFindOption->m_fDragServer)
		SendMessage(WM_LBUTTONUP, nFlags,
			(LONG) MAKELONG(point.x, point.y));
	else
		return;
#endif

	// ﾘｽﾄのどの項目を選んでいるか？
	//long lLine = 0;
	int sel = GetCurSel();
	size_ent nIndex = GetDataIndexFromSel(sel);
	if (nIndex==(size_ent)-1)
		return ; //選ばれていない
	int et = m_pEntryArray->GetEntryType(nIndex);

	if (et==BFT_DIR)
		return ; //ディレクトリを選んでる

	// Drag & Drop Server Start
	//AfxGetApp()->m_pMainWnd->DragAcceptFiles(FALSE);
	if (!DragServerForSingleFile(/*AfxGetApp()->m_pMainWnd->*/GetSafeHwnd(), m_pEntryArray, nIndex, ::GetAsyncKeyState(VK_CONTROL)&0x8000))
		BeepMessage(IDS_OPENDOC_ERR);
	//AfxGetApp()->m_pMainWnd->DragAcceptFiles(TRUE);
}
/*
void CFindList::OnBeginDrag(NMHDR *pNotifyStruct,LRESULT *result)
{
	size_ent nIndex = GetDataIndexFromSel(GetCurSel());
	if (nIndex==(size_ent)-1)
			return ; //選ばれていない
	int et;
	if ((et=m_pEntryArray->GetEntryType(nIndex))!=BFT_DIR)
		{
		CDBmpStrList::OnBeginDrag(NMHDR *pNotifyStruct,LRESULT *result);
		}

	switch (nImageID)
	{
		case IID_TABLE:
		case IID_QUERYDEF:
			CSharedFile globFile;
			CArchive ar(&globFile,CArchive::store);
			CDragItem dragItem(nImageID,m_pDB->GetName(),m_pDB->GetConnect(),m_ItemSel.GetText());
			dragItem.Serialize(ar);
			ar.Close();

			COleDataSource srcItem;

			srcItem.CacheGlobalData(m_nIDClipFormat,globFile.Detach());
			srcItem.DoDragDrop();
	}
}


DROPEFFECT CFindList::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	return CDBmpStrList::OnDragEnter(pDataObject, dwKeyState, point);
}

DROPEFFECT CFindList::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	return CDBmpStrList::OnDragOver(pDataObject, dwKeyState, point);
}
*/

BOOL DragServerForSingleFile(HWND hWnd, CListEntryArray *pEntryArray, size_ent nIndex, BOOL fCtrKey)
{
// if return FALSE then Err ocured.
#ifdef UNICODE
#define WndAcceptsFiles(hwnd) \
	(GetWindowExStyle((hwnd)) && WS_EX_ACCEPTFILES)
#else
#define WndAcceptsFiles(hwnd) \
	(GetWindowLong(hwnd, GWL_EXSTYLE) && WS_EX_ACCEPTFILES)
#endif
	HWND hWndSubject;
	BOOL fOkToDrop=FALSE;
	BOOL fInNonClientArea;
	POINT ptMousePos,ptMousePosOrg;
	HDROP hDrop,hDropT;
	MSG Msg;
	BOOL fStop=FALSE;
	BOOL fMouseMove=FALSE;
	BOOL fThisWnd=FALSE;

	// Get Cursors
	HCURSOR hCurDrpNot = AfxGetApp()->LoadCursor(IDC_DRP_NG);
	HCURSOR hCurDrpSingle = AfxGetApp()->LoadCursor(IDC_DRP_SINGLE);
	// Loop for determining the dropfile client window
	SetCapture(hWnd);

	GetCursorPos(&ptMousePosOrg);
	while(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
		while(::PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE) && !fStop)
			{
			// stop action when left mouse button click.
			switch(Msg.message)
				{
				case WM_RBUTTONDOWN:
					fStop = TRUE;
					break;
				case WM_KEYDOWN:
					TranslateMessage(&Msg);
					if (Msg.wParam==VK_ESCAPE)
						fStop = TRUE;
					break;
				default:
					::DispatchMessage(&Msg);
					break;
				}
			}

		if (fStop)
			break;

		//Get cursor position & window under the cursor
		::GetCursorPos(&ptMousePos);
		if (!fMouseMove)
			{
			if ((ptMousePos.x == ptMousePosOrg.x) && (ptMousePos.y == ptMousePosOrg.y))
				continue;
			else
				fMouseMove = TRUE;
			}
		hWndSubject = ::WindowFromPoint(ptMousePos);
		fThisWnd = (hWndSubject == hWnd);
		//See if the subject window or any of its parent
		//windows are prepared to accept dropped files
		while(IsWindow(hWndSubject))
			{
			if (WndAcceptsFiles(hWndSubject))
				break;
			hWndSubject = GetParent(hWndSubject);
			}
		fOkToDrop = IsWindow(hWndSubject) &&
			WndAcceptsFiles(hWndSubject);
		SetCursor(fOkToDrop ? hCurDrpSingle:hCurDrpNot);
		// Terminate loop when mouse button is released
		}
	ReleaseCapture();

	// Free the loaded cursors
	DestroyCursor(hCurDrpNot);
	DestroyCursor(hCurDrpSingle);

	if (!fOkToDrop || fStop || fThisWnd) // AfxGetApp()->m_pMainWnd->GetSafeHwnd() == hWndSubject
		return TRUE;

	// Is the cursor in the window's non-client area?
	fInNonClientArea = (HTCLIENT !=
		SendMessage(hWndSubject, WM_NCHITTEST, 0,
		(LONG) MAKELONG(ptMousePos.x, ptMousePos.y)));

	//Create drop-file memory block and initialize it
	ScreenToClient(hWndSubject, &ptMousePos);
	hDrop = DragCreateFiles(&ptMousePos, fInNonClientArea);
	if (hDrop == NULL)
		return FALSE;

	// ここで初めてファイル名を取得する
	CDString cdstr;
	cdstr = pEntryArray->GetFName(nIndex, FALSE, (!fCtrKey ?  LSTENT_TXT:LSTENT_DOC));

	if (cdstr.IsEmpty())
		return FALSE;

	// Appent each full pathname to the drop-file memory block
	hDropT = DragAppendFile((HGLOBAL)hDrop, cdstr.GetBuffer(0));
	if (!hDropT)
		{
		GlobalFree(hDrop);
		return FALSE;
		}
	else
		hDrop = hDropT;
	// All pathnemaes appended sucessfully
	// post the message to the drop-file client window
	::PostMessage(hWndSubject, WM_DROPFILES, (UINT)hDrop, 0L);

	// Don't free the memory,
	// the Dropfile client will do it!

	return TRUE;
}

// Drop-file struct memory block create function
HDROP DragCreateFiles(LPPOINT lpptMousePos, BOOL fInNonClientArea)
{
	HDROP hDrop;
	LPDROPFILESTRUCT lpDropFileStruct;
	// Get memory block
	hDrop = (HDROP)GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE | GMEM_ZEROINIT, 
		sizeof(DROPFILESTRUCT)+
#ifdef UNICODE
		sizeof(WCHAR));
#else
		sizeof(char));
#endif

	if (!hDrop)
		return NULL;
	// Lock block and initialize the data members
	lpDropFileStruct = (LPDROPFILESTRUCT)GlobalLock(hDrop);
	lpDropFileStruct->wSize = sizeof(DROPFILESTRUCT);
	lpDropFileStruct->ptMousePos = *lpptMousePos;
	lpDropFileStruct->fInNonClientArea = fInNonClientArea;
#ifdef WIN32
#ifdef UNICODE
	lpDropFileStruct->fUnicode = TRUE;
#else
	lpDropFileStruct->fUnicode = FALSE;
#endif //UNICODE
#endif //WIN32
	GlobalUnlock(hDrop);
	return hDrop;
}

// Append file name to Drop-file struct memory block function
HDROP DragAppendFile(HGLOBAL hDrop, LPCSTR szPathname)
{
	LPDROPFILESTRUCT lpDropFileStruct;
	LPCSTR lpCrnt;
	int wSize;

#ifdef UNICODE
	ASSERT(FALSE); //Plase look MSJ.No.32 1994 173page c-list.
#endif

	lpDropFileStruct = (LPDROPFILESTRUCT) GlobalLock(hDrop);
	// Point first pathname in list
	lpCrnt = (LPSTR)lpDropFileStruct + lpDropFileStruct->wSize;
	//Search for a pathname were first byte is a zero byte
	while(*lpCrnt)
		{
		while(*lpCrnt)
			lpCrnt++;
		lpCrnt++;
		}
	//Calculate current size of block
	wSize = (WORD)(lpCrnt - (LPSTR)lpDropFileStruct + 1);
	GlobalUnlock(hDrop);

	hDrop = GlobalReAlloc(hDrop, wSize + lstrlen(szPathname) + 1,
		GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE);

	// Return NULL if insufficient memory
	if ( hDrop == NULL)
		return NULL;

	lpDropFileStruct = (LPDROPFILESTRUCT)GlobalLock(hDrop);
	//Appent the pathname to the block
	lstrcpy((LPSTR)lpDropFileStruct + wSize -1, szPathname);
	GlobalUnlock(hDrop);
	return (HDROP)hDrop;
}

void CFindList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
#ifdef DRAGSAVER_WITH_SHIFTKEY
	if (nChar == VK_SHIFT && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		OnLButtonDown(NULL, NULL);
	/*else*/ //don't else!
#endif
	if (((nChar == VK_RIGHT || nChar == VK_LEFT) && GetCurSel()>=0)) {
		EnterListItem(!(::GetAsyncKeyState(VK_CONTROL)&0x8000), nChar);
		return;
	}
	THIS_CLASS::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFindList::OnDropFiles(HDROP hDropInfo)
{
	((CMainFrame *)AfxGetMainWnd())->OnDropFiles(hDropInfo);
}

void CFindList::ResetHeaderType(BOOL bReset)
{
	if (bReset)
		m_header.ResetHeaderType();
	else
		{
		size_ent nIndex = GetDataIndexFromSel(GetCurSel());
		if (nIndex==(size_ent)-1)
			{
			m_header.ResetHeaderType();
			return ; //選ばれていない
			}
		int et = m_pEntryArray->GetEntryType(nIndex);
		//Headerの書き換え
		m_header.ResetHeaderType(et);
		}
}
#ifdef _TAG_TEXT
void CFindList::WriteTagText(CStdioFile &file)
{
	//現在のソート状態のまま書き出す
	try {
	size_ent count = (size_ent)SendMessage( LB_GETCOUNT, 0, 0 );	
	CString str;
	BOOL bData=FALSE;
	int sel;
	for (sel=0; sel<count && !bData; sel++)
		{
		size_ent nIndex = GetDataIndexFromSel(sel);
		if (nIndex != -1 && m_pEntryArray->GetEntryStringForTagText(nIndex, str))
			{
			bData = TRUE;
			}
		}
	if (bData)
		{
		CString str, strPart;
		for (str=vpFindList->m_FindLog.m_strLog; !(strPart = GetPartString(str, "\r\n")).IsEmpty(); ) {
			file.WriteString(strPart);
			file.WriteString("\n");
		}
		file.WriteString("---------------------------------------------------------------\n");
		}
	for (sel=0; sel<count; sel++)
		{
		size_ent nIndex = GetDataIndexFromSel(sel);
		if (nIndex != -1)
			{
			if (m_pEntryArray->GetEntryStringForTagText(nIndex, str))
				{
				str += "\n";
				file.WriteString(str);
				}
			}
		}
	}catch(CException* ){
		throw;
	}
}
#endif //_TAG_TEXT

void CFindList::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu popMenu;
	BOOL bEnable = IsSelectedFile();
	popMenu.LoadMenu(IDR_POPMENU_EDIT);
	//AfxGetMainWnd()->ClientToScreen(&point);
	ClientToScreen(&point);
	popMenu.EnableMenuItem(IDR_ACT_DISPDOCEDIT, (bEnable ? MF_ENABLED:MF_GRAYED));
	popMenu.EnableMenuItem(IDR_EDIT_DELL_FILE, bEnable ? MF_ENABLED:MF_GRAYED);
	popMenu.EnableMenuItem(IDR_ACT_DISPDOC, bEnable ? MF_ENABLED:MF_GRAYED);
	popMenu.EnableMenuItem(IDR_ACT_OPENFOLDER, GetCurSel()!=-1 ? MF_ENABLED : MF_GRAYED);
	popMenu.EnableMenuItem(IDR_EDIT_COPY_1, ((bEnable = IsSelectedLine()) ? MF_ENABLED : MF_GRAYED));
	popMenu.EnableMenuItem(IDR_EDIT_REF_FILE, bEnable ? MF_ENABLED:MF_GRAYED);
	::TrackPopupMenu(popMenu.GetSubMenu(0)->m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN, point.x, point.y, 0, m_hWnd, NULL);//AfxGetMainWnd());
	CDBmpStrList::OnRButtonDown(nFlags, point);
}

void CFindList::OnActDispdocedit() 
{
	((CFdiverView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView())->OnActDispdocedit();
}

void CFindList::OnActDispdoc() 
{
	((CFdiverView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView())->OnActDispdoc();
}


BOOL CopyToClipBoard(HWND hWnd, LPSTR lpstr)
{
	ASSERT(hWnd!=NULL && lpstr!=NULL);

	//クリップボードにデータをコピー
	long len = strlen(lpstr);
	HANDLE	hData = GlobalAlloc(GHND, len+1);
	LPSTR	lpData = (LPSTR)GlobalLock(hData);

	//lstrcpy(lpData, lpstr);
	//warning C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//strncpy(lpData, lpstr, len);
	strncpy_s(lpData, len+1, lpstr, len);

	lpData[len] = '\0';

	if ( !OpenClipboard(hWnd) )
		return FALSE;
	EmptyClipboard();
	if ( ::SetClipboardData( CF_TEXT, hData ) == NULL )
	{
		CloseClipboard();
		return FALSE;
	}
	GlobalUnlock(hData);
	CloseClipboard();

	return TRUE;
}

void CFindList::OnOpenFolder()
{
	CDString cdstr;
	int sel = GetCurSel();
	size_ent nIndex = GetDataIndexFromSel(sel);

	if (nIndex == (size_ent)-1)
		return; //選ばれていない

	CListEntry *pListEntry = m_pEntryArray->GetEntry(sel);
	int et = pListEntry->GetEntryType();
	CDFileExp *pcdFile = pListEntry->pcdFile;

	if (et == BFT_DIR) {
		cdstr = pcdFile->GetPathName();
		ShellExecute(NULL, "open", cdstr, NULL, NULL, SW_SHOWDEFAULT);
	}
	else{
		//cdstr = pcdFile->GetPath();
		CString str1, str2;
		str1 = m_pEntryArray->GetFName(nIndex, false, str2);
		cdstr = str2;
		cdstr += str1;

		ITEMIDLIST *pidl = ILCreateFromPath(cdstr);
		if (pidl) {
			SHOpenFolderAndSelectItems(pidl, 0, 0, 0);
			ILFree(pidl);
		}
	}


}

void CFindList::OnEditCopy1() 
{
	CListEntry *pListEntry = GetSelListEntry();
	if (pListEntry) {
		CopyToClipBoard(AfxGetMainWnd()->GetSafeHwnd(), pListEntry->pcdStr->GetBuffer(0));
	}
}


void CFindList::OnEditRefFile() 
{
}


void CFindList::OnUpdateActDispdocedit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelectedFile());
}

void CFindList::OnUpdateActDispdoc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelectedFile());
}

void CFindList::OnUpdateEditCopy1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelectedLine());
}

void CFindList::OnUpdateEditRefFile(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelectedFile());
}

void CFindList::OnUpdateEditDellFile(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsSelectedFile());
}

void CFindList::OnEditDellFile() 
{
	CDString cdstr;
	int sel = GetCurSel();
	size_ent nIndex = GetDataIndexFromSel(sel);

	if (nIndex==(size_ent)-1)
		return ; //選ばれていない
	int et = m_pEntryArray->GetEntryType(nIndex);

	if (et!=BFT_DIR)
		cdstr = m_pEntryArray->GetFName(nIndex, FALSE, LSTENT_TXT);

	RemoveFile_Prompt(cdstr.GetBuffer());
}
