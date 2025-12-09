/*    PortTool v2.2     FDIVEVW.CPP          */

// fdivevw.cpp : CFdiverView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "ColorDlg.h"
#include "Fdiver.h"

#include "fdivedoc.h"
#include "fdivevw.h"
#include "findlist.h"
#include "finddlg.h"
#include "ffile.h"
#include "findopti.h"
#include "findlog.h"
#include "Mainfrm.h"
extern CFindDlg *vpFindDlg;
extern CFindFile *vpcFind;
extern CFindOption *vpFindOption;


CFindList *vpFindList=NULL;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ=NULL
extern CFileTransArray *vpFileTransArray;
struct BSLIST_RESIDS bsl_resid[1] = {16,IDB_LSTENT1};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFdiverView

IMPLEMENT_DYNCREATE(CFdiverView, CView)

BEGIN_MESSAGE_MAP(CFdiverView, CView)
	//{{AFX_MSG_MAP(CFdiverView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDR_ACT_FIND, OnFind)
	ON_COMMAND(IDR_ACT_FINDSTOP, OnFindStop)
	ON_COMMAND(IDR_ACT_CLEARSEL, OnFClearsel)
	ON_COMMAND(IDR_ACT_DISPDOC, OnActDispdoc)
	ON_COMMAND(IDR_ACT_DISPDOCEDIT, OnActDispdocedit)
	ON_COMMAND(IDR_DSP_CLOSETODIR, OnDspClosetodir)
	ON_COMMAND(IDR_DSP_CLOSETOFILE, OnDspClosetofile)
	ON_COMMAND(IDR_DSP_SORTBYDATE, OnDspSortbydate)
	ON_COMMAND(IDR_DSP_SORTBYEXP, OnDspSortbyexp)
	ON_COMMAND(IDR_DSP_SORTBYNAME, OnDspSortbyname)
	ON_COMMAND(IDR_DSP_SORTBYSIZE, OnDspSortbysize)
	ON_COMMAND(IDR_OPT_DISPBYFILE, OnOptDispbyfile)
	ON_COMMAND(IDR_OPT_DISPBYPATH, OnOptDispbypath)
	ON_COMMAND(IDR_OPT_DISPLIST, OnOptDisplist)
	ON_COMMAND(IDR_OPT_DISPTREE, OnOptDisptree)
	ON_COMMAND(IDR_OPT_DRAG_SERVER, OnOptDragServer)
	ON_UPDATE_COMMAND_UI(IDR_ACT_FIND, OnUpdateActFind)
	ON_UPDATE_COMMAND_UI(IDR_ACT_FINDSTOP, OnUpdateActFindstop)
	ON_UPDATE_COMMAND_UI(IDR_ACT_CLEARSEL, OnUpdateActClearsel)
	ON_UPDATE_COMMAND_UI(IDR_ACT_DISPDOC, OnUpdateActDispdoc)
	ON_UPDATE_COMMAND_UI(IDR_ACT_DISPDOCEDIT, OnUpdateActDispdocedit)
	ON_UPDATE_COMMAND_UI(IDR_DSP_CLOSETODIR, OnUpdateDspClosetodir)
	ON_UPDATE_COMMAND_UI(IDR_DSP_CLOSETOFILE, OnUpdateDspClosetofile)
	ON_UPDATE_COMMAND_UI(IDR_DSP_SORTBYDATE, OnUpdateDspSortbydate)
	ON_UPDATE_COMMAND_UI(IDR_DSP_SORTBYEXP, OnUpdateDspSortbyexp)
	ON_UPDATE_COMMAND_UI(IDR_DSP_SORTBYNAME, OnUpdateDspSortbyname)
	ON_UPDATE_COMMAND_UI(IDR_DSP_SORTBYSIZE, OnUpdateDspSortbysize)
	ON_UPDATE_COMMAND_UI(IDR_OPT_DISPBYFILE, OnUpdateOptDispbyfile)
	ON_UPDATE_COMMAND_UI(IDR_OPT_DISPBYPATH, OnUpdateOptDispbypath)
	ON_UPDATE_COMMAND_UI(IDR_OPT_DISPLIST, OnUpdateOptDisplist)
	ON_UPDATE_COMMAND_UI(IDR_OPT_DISPTREE, OnUpdateOptDisptree)
	ON_COMMAND(IDR_OPT_DSPFINDLOG, OnOptDspfindlog)
	ON_UPDATE_COMMAND_UI(IDR_OPT_DSPFINDLOG, OnUpdateOptDspfindlog)
	ON_UPDATE_COMMAND_UI(IDR_DSP_LISTFONT, OnUpdateDspListfont)
	ON_COMMAND(IDR_DSP_LISTFONT, OnDspListfont)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HEADERBAR, OnUpdateViewHeaderbar)
	ON_COMMAND(ID_VIEW_HEADERBAR, OnViewHeaderbar)
	ON_UPDATE_COMMAND_UI(IDR_ACT_TAGTEXT, OnUpdateActTagtext)
	ON_COMMAND(IDR_ACT_TAGTEXT, OnActTagtext)
	ON_UPDATE_COMMAND_UI(IDR_DSP_COLORS, OnUpdateDspColors)
	ON_COMMAND(IDR_DSP_COLORS, OnDspColors)
	ON_UPDATE_COMMAND_UI(IDR_DSP_OPENLIST, OnUpdateDspOpenlist)
	ON_COMMAND(IDR_DSP_OPENLIST, OnDspOpenlist)
	ON_UPDATE_COMMAND_UI(IDR_ACT_KFT_TRANS_VIEW, OnUpdateActOrginal)
	ON_COMMAND(IDR_ACT_KFT_TRANS_VIEW, OnActOrginal)
	ON_UPDATE_COMMAND_UI(IDR_ZOOM_IN, OnUpdateZoomIn)
	ON_COMMAND(IDR_ZOOM_IN, OnZoomIn)
	ON_UPDATE_COMMAND_UI(IDR_ZOOM_OUT, OnUpdateZoomOut)
	ON_COMMAND(IDR_ZOOM_OUT, OnZoomOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFdiverView クラスの構築/消滅

CFdiverView::CFdiverView()
{
	m_pKftDll = NULL;
}


CFdiverView::~CFdiverView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CFdiverView クラスの描画

void CFdiverView::OnDraw(CDC* pDC)
{
	CFdiverDoc* pDoc = GetDocument();

	// TODO: この場所に描画用のコードを追加します。
}



/////////////////////////////////////////////////////////////////////////////
// CFdiverView クラスの診断

#ifdef _DEBUG
void CFdiverView::AssertValid() const
{
	CView::AssertValid();
}

void CFdiverView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFdiverDoc* CFdiverView::GetDocument() // デバッグ環境でない場合はインライン展開となります。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFdiverDoc)));
	return (CFdiverDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFdiverView クラスのメッセージ ハンドラ

int CFdiverView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CView::OnCreate(lpCreateStruct);

	vpFindList = ((CFdiverDoc *)GetDocument())->m_pFindList;
	ASSERT(vpFindList);
	RECT rect;
	::SetRect(&rect, 0,0,0,0);
	vpFindList->Create( WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOINTEGRALHEIGHT |
		LBS_DISABLENOSCROLL , rect, /*AfxGetApp()->m_pMainWnd*/this, 1);

	//ﾌｫﾝﾄの設定
	memset(&m_lf, 0, sizeof(LOGFONT));
	m_lf.lfHeight = vpFindOption->m_lfHeight;				//13;
	m_lf.lfWeight = 400;
	m_lf.lfCharSet = vpFindOption->m_lfCharSet;				//SHIFTJIS_CHARSET;
	m_lf.lfQuality = DRAFT_QUALITY;
	m_lf.lfPitchAndFamily = vpFindOption->m_lfPitchAndFamily;//50;
	//warning C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//strcpy(m_lf.lfFaceName, vpFindOption->m_lfFaceName);	//_T("ＭＳ Ｐゴシック")
	strcpy_s(m_lf.lfFaceName, sizeof(m_lf.lfFaceName), vpFindOption->m_lfFaceName);	//_T("ＭＳ Ｐゴシック")
	VERIFY(m_font.CreateFontIndirect(&m_lf));

	COLORREF frColor, bkColor;
	CString str,strR,strG,strB;
	str = vpFindOption->m_strFrColor;
	strR = GetPartString(str, ',');
	strG = GetPartString(str, ',');
	strB = GetPartString(str, ',');
	frColor = RGB(atol(strR), atol(strG), atol(strB));
	str = vpFindOption->m_strBkColor;
	strR = GetPartString(str, ',');
	strG = GetPartString(str, ',');
	strB = GetPartString(str, ',');
	bkColor = RGB(atol(strR), atol(strG), atol(strB));
	vpFindList->SetColors(frColor, bkColor, vpFindOption->m_ratioBetweenLine, FALSE);

	vpFindList->Initial(&bsl_resid[0], 1, (HFONT)m_font.GetSafeHandle()) ;
	vpFindList->ShowWindow ( SW_SHOWNA ) ;
	vpFindList->DragAcceptFiles();
	return 0;
}

void CFdiverView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CFindList *pFindList = ((CFdiverDoc *)GetDocument())->m_pFindList;
	if (pFindList)
		{
		RECT rect;
		::SetRect(&rect,0,0,cx,cy);
		pFindList->LayoutWindowRect(&rect, vpFindOption->m_bHeaderBar);
		pFindList->SetFocus();
		}
}
void CFdiverView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
//#ifdef BUG
	CFindList *pFindList = ((CFdiverDoc *)GetDocument())->m_pFindList;
	if (pFindList)
		pFindList->SetFocus();
//#endif
}

void CFdiverView::OnFind()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	if (vpFindDlg->DoModal())
		{
		// 検索開始
		// ｸﾞﾛｰﾊﾞﾙへ設定
		vpFindList = ((CFdiverDoc *)GetDocument())->m_pFindList;
		ASSERT(vpFindList);
		((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(TRUE);

		// ﾂｰﾙﾊﾞｰを更新する為、OnIdle()を呼び出す！
//		CWinApp::OnIdle(0);
		// CDFilesオブジェクトの作成
		if (!vpcFind->FInitFiles(vpFindDlg->GetFilePath(), vpFindDlg->GetFileSpec(), vpFindDlg->FSubDir(), vpFindDlg->FArc()))
			goto Err;
		//((CFdiverDoc *)GetDocument())->SetModifiedFlag();

		if (vpFindOption->m_fIcon)
			((CFdiverApp *)AfxGetApp())->m_pMainWnd->ShowWindow(SW_MINIMIZE);
#ifdef NOSEARCH_ONIDLE
//->move from OnIdle!
		if (m_fFindDoing)
			{
			if (vpFindDlg->FFindFileOnly())
				{
				vpcFind->StartScan(NULL, NULL, NULL);
				}
			else
				{
				int iPatternLength;
				if ((iPatternLength=vpcGrep->Init(vpcFind))==NULL)
					goto Err;
				vpcFind->StartScan(vpcGrep->GetEngin(), vpFindOption->m_lReadSize, iPatternLength);
				}
			}
//<-move from OnIdle!

#else
		return ;
#endif //NOSEARCH_ONIDLE

//		if (vpFindDlg->FFindFileOnly())
//			{
//			vpcFind->StartScan(NULL, NULL, NULL);
//			}
//		else
//			{
//			int iPatternLength;
//			if ((iPatternLength=vpcGrep->Init(vpFindDlg->GetOptFind(), vpcFind))==NULL)
//				goto Err;
//  
//			vpcFind->StartScan(vpcGrep->GetEngin(), vpFindOption->m_lReadSize, iPatternLength);
//			}

		}
Err:
	((CFdiverApp *)AfxGetApp())->FinishFind();
}
void CFdiverView::OnFindStop()
{
	((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
}
void CFdiverView::OnFClearsel()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	((CFdiverDoc *)GetDocument())->m_pFindList->SendMessage (LB_SETCURSEL, (WPARAM)-1, 0L ) ;
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetHeaderType(TRUE);
}

void CFdiverView::OnActDispdoc()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	if (vpFindOption->m_aryStrKickApps.GetSize()>0) {
		CMenu popMenu;
		popMenu.CreatePopupMenu();
		for (int i=0; i<vpFindOption->m_aryStrKickApps.GetSize();i++)	{
			ASSERT(IDC_KICK_APP_START+i<IDC_KICK_APP_END);
			popMenu.AppendMenu(MF_STRING | MF_ENABLED , IDC_KICK_APP_START+i, vpFindOption->m_aryStrKickApps[i]);
		}
		CString str;
		str.LoadString(IDS_KICK_APP_OTHER);
		popMenu.AppendMenu(MF_STRING | MF_ENABLED , IDC_KICK_APP_OTHER, str);
		CRect rc;
		int index = ((CMainFrame*)AfxGetMainWnd())->m_wndToolBar.CommandToIndex(IDR_ACT_DISPDOC);
		((CMainFrame*)AfxGetMainWnd())->m_wndToolBar.GetItemRect(index, &rc);
		AfxGetMainWnd()->ClientToScreen(&rc);
		popMenu.TrackPopupMenu(0,rc.left,rc.bottom, this);//AfxGetMainWnd());
	}else
		((CFdiverDoc *)GetDocument())->m_pFindList->OpenDocument(FALSE);
}

void CFdiverView::OnActDispdocedit()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	((CFdiverDoc *)GetDocument())->m_pFindList->OpenDocument(TRUE);
}
void CFdiverView::OnDspClosetodir()
{
	((CFdiverDoc *)GetDocument())->m_pFindList->ListInPathOrFile(FALSE, FALSE);
}

void CFdiverView::OnDspClosetofile()
{
	((CFdiverDoc *)GetDocument())->m_pFindList->ListInPathOrFile(TRUE, FALSE);
}

void CFdiverView::OnDspOpenlist() 
{
	((CFdiverDoc *)GetDocument())->m_pFindList->ListInPathOrFile(TRUE, TRUE);
}

void CFdiverView::OnDspSortbyname()
{
	((CFdiverDoc *)GetDocument())->m_pFindList->SortList(SORTTYPE_NAME);
}

void CFdiverView::OnDspSortbyexp()
{
	((CFdiverDoc *)GetDocument())->m_pFindList->SortList(SORTTYPE_EXTENTION);
}


void CFdiverView::OnDspSortbysize()
{
	((CFdiverDoc *)GetDocument())->m_pFindList->SortList(SORTTYPE_SIZE);
}
void CFdiverView::OnDspSortbydate()
{
	((CFdiverDoc *)GetDocument())->m_pFindList->SortList(SORTTYPE_DATE);
}

void CFdiverView::OnOptDisptree()
{
	vpFindOption->m_fDir = TRUE;
	vpFindOption->m_fFile = TRUE;
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetSort();
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetViewString(TRUE); // 検索ﾘｽﾄ表示へのｱｯﾌﾟﾃﾞｰﾄ
}
void CFdiverView::OnOptDisplist()
{
	vpFindOption->m_fDir = FALSE;
	vpFindOption->m_fFile = FALSE;
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetSort();
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetViewString(TRUE); // 検索ﾘｽﾄ表示へのｱｯﾌﾟﾃﾞｰﾄ
}
void CFdiverView::OnOptDispbypath()
{
	vpFindOption->m_fDir = TRUE;
	vpFindOption->m_fFile = FALSE;
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetSort();
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetViewString(TRUE); // 検索ﾘｽﾄ表示へのｱｯﾌﾟﾃﾞｰﾄ
}
void CFdiverView::OnOptDispbyfile()
{
	vpFindOption->m_fDir = FALSE;
	vpFindOption->m_fFile = TRUE;
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetSort();
	((CFdiverDoc *)GetDocument())->m_pFindList->ResetViewString(TRUE); // 検索ﾘｽﾄ表示へのｱｯﾌﾟﾃﾞｰﾄ
}
void CFdiverView::OnOptDragServer()
{
	vpFindOption->m_fDragServer = !vpFindOption->m_fDragServer;
}


void CFdiverView::OnUpdateActFind(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	BOOL f = !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg();
	pCmdUI->Enable(f);
	// Drag & Drop Accept
	DragAcceptFiles(f);
}

void CFdiverView::OnUpdateActFindstop(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	pCmdUI->Enable(((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}
void CFdiverView::OnUpdateActClearsel(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	//if (((CFdiverDoc *)GetDocument()))
		pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->SendMessage( LB_GETCOUNT, 0, 0 )>0
		&& ((CFdiverDoc *)GetDocument())->m_pFindList->SendMessage( LB_GETCURSEL, 0, 0)!=LB_ERR);
}

void CFdiverView::OnUpdateActDispdoc(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->IsSelectedFile());
}

void CFdiverView::OnUpdateActDispdocedit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->IsSelectedFile());
}
void CFdiverView::OnUpdateDspClosetodir(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

void CFdiverView::OnUpdateDspClosetofile(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}


void CFdiverView::OnUpdateDspSortbyname(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
	pCmdUI->SetCheck(((CFdiverDoc *)GetDocument())->m_pFindList->GetSortType()==SORTTYPE_NAME);
}

void CFdiverView::OnUpdateDspSortbyexp(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
	pCmdUI->SetCheck(((CFdiverDoc *)GetDocument())->m_pFindList->GetSortType()==SORTTYPE_EXTENTION);
}


void CFdiverView::OnUpdateDspSortbysize(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
	pCmdUI->SetCheck(((CFdiverDoc *)GetDocument())->m_pFindList->GetSortType()==SORTTYPE_SIZE);
}
void CFdiverView::OnUpdateDspSortbydate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
	pCmdUI->SetCheck(((CFdiverDoc *)GetDocument())->m_pFindList->GetSortType()==SORTTYPE_DATE);
}

void CFdiverView::OnUpdateOptDisptree(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0);
	pCmdUI->SetCheck(vpFindOption->m_fDir && vpFindOption->m_fFile);
}
void CFdiverView::OnUpdateOptDisplist(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0);
	pCmdUI->SetCheck(!vpFindOption->m_fDir && !vpFindOption->m_fFile);
}
void CFdiverView::OnUpdateOptDispbypath(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0);
	pCmdUI->SetCheck(vpFindOption->m_fDir && !vpFindOption->m_fFile);
}
void CFdiverView::OnUpdateOptDispbyfile(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0);
	pCmdUI->SetCheck(!vpFindOption->m_fDir && vpFindOption->m_fFile);
}

void CFdiverView::OnOptDspfindlog() 
{
	((CFdiverDoc *)GetDocument())->m_pFindList->m_FindLog.DoModal();
}

void CFdiverView::OnUpdateOptDspfindlog(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}


void CFdiverView::OnUpdateDspListfont(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

void CFdiverView::OnUpdateDspOpenlist(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0 &&
	 !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

void CFdiverView::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}
void CFdiverView::OnZoomIn() 
{
	SetFont(1);
}

void CFdiverView::SetFont(int iZoom)
{

	CDC dcScreen;
	dcScreen.Attach(::GetDC(NULL));

	// now bring up the dialog since we know the printer DC

	if (iZoom!=0) {
		// map the resulting logfont back to printer metrics.
		m_lf.lfHeight = abs(m_lf.lfHeight);

		//m_lf.lfHeight = vpFindOption->div10plus(m_lf.lfHeight, iZoom, 5);

		m_lf.lfHeight = m_lf.lfHeight<1 ? 1:m_lf.lfHeight;
		if (iZoom>0) //zoom in
			m_lf.lfHeight += max(m_lf.lfHeight/10,1);
		else {
			if (m_lf.lfHeight>7)
				m_lf.lfHeight -= max(m_lf.lfHeight/10,1);
		}

		
		m_lf.lfHeight = - abs(m_lf.lfHeight);

		CFont font;
		VERIFY(font.CreateFontIndirect(&m_lf));
		if (font.GetSafeHandle()) {
			vpFindOption->m_lfHeight = m_lf.lfHeight;

			vpFindList->Initial(&bsl_resid[0], 1, (HFONT)font.GetSafeHandle()) ;
			m_font.DeleteObject();
			m_font.Attach((HFONT)font.GetSafeHandle());
			font.Detach();
			vpFindList->ShowWindow ( SW_SHOWNA ) ;
		}
	}

	::ReleaseDC(NULL, dcScreen.Detach());

	vpFindOption->ResizeHeaderCx(iZoom);

	vpFindList->ResetHeaderCx();
}

void CFdiverView::OnUpdateZoomOut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CFdiverView::OnZoomOut() 
{
	SetFont(-1);
}

void CFdiverView::OnDspListfont() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CDC dcScreen;
	dcScreen.Attach(::GetDC(NULL));

	// now bring up the dialog since we know the printer DC
	CFontDialog dlg(&m_lf, CF_SCREENFONTS, &dcScreen);
	if (dlg.DoModal() == IDOK)
		{
		// map the resulting logfont back to printer metrics.
		m_lf = dlg.m_lf;
		m_lf.lfWeight = 400;
		CFont font;
		VERIFY(font.CreateFontIndirect(&m_lf));
		if (font.GetSafeHandle())
			{
			vpFindOption->m_lfHeight = m_lf.lfHeight;
			vpFindOption->m_lfCharSet = m_lf.lfCharSet;
			vpFindOption->m_lfPitchAndFamily = m_lf.lfPitchAndFamily;
			vpFindOption->m_lfFaceName = m_lf.lfFaceName;

			vpFindList->Initial(&bsl_resid[0], 1, (HFONT)font.GetSafeHandle()) ;
			m_font.DeleteObject();
			m_font.Attach((HFONT)font.GetSafeHandle());
			font.Detach();
			vpFindList->ShowWindow ( SW_SHOWNA ) ;
			}
		}

	::ReleaseDC(NULL, dcScreen.Detach());
}

void CFdiverView::OnUpdateActTagtext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg() && ((CFdiverDoc *)GetDocument())->m_pFindList->GetMemEntrys()>0);
}


void CFdiverView::OnActTagtext() 
{
#define DEFAULT_TAGTEXT_FILENAME	_T("_tagtxt_.txt")

	CFindList *pFindList = ((CFdiverDoc *)GetDocument())->m_pFindList;
	if (pFindList)
		{
		CStdioFile file;
		int nMsg = 0;
		CString strPath = ((CFdiverApp *)AfxGetApp())->PGetDefaltPath();
		strPath += '\\';
		CString str;
		str = strPath + DEFAULT_TAGTEXT_FILENAME;
		try { try{
		//Create files
		if (!file.Open(str, (CFile::typeText | CFile::modeCreate | CFile::modeWrite /*| CFile::shareDenyWrite*/)))
			AfxThrowFileException(CFileException::invalidFile);
			}catch(CException* ){
				nMsg = IDS_MSG_TAGTEXT_ERR_CREATE;
				throw;
			}
		pFindList->WriteTagText(file);
		//ﾌﾗｯｼｭ
		file.Flush();
		if (file.GetLength()<=0)
			nMsg = IDS_MSG_TAGTEXT_HOWTOUSE;
		}catch(CException* e){
			if (!nMsg)
				nMsg = IDS_MSG_TAGTEXT_ERR_WRITE;
			e->Delete();
		}
		//ﾌｧｲﾙを閉じる
		if (file.m_pStream)
			file.Close();
		if (nMsg)
			AfxMessageBox(nMsg);
		else
			pFindList->OpenDocument(str);
		}
}

void CFdiverView::OnUpdateDspColors(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

void CFdiverView::OnDspColors() 
{
	CColorDlg dlg;
	dlg.DoModal();
}



void CFdiverView::OnUpdateActOrginal(CCmdUI* pCmdUI) 
{
	if (vpFileTransArray && m_pKftDll==NULL) {
		m_pKftDll = (CDLLDoc*)vpFileTransArray->m_arypDll.PDll(EXT_KFT);
	}
	if (/*((CFdiverDoc *)GetDocument())->m_pFindList->IsSelectedFile() &&*/ m_pKftDll) {
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(vpFindOption->m_bKftTransFileView);
	}else
		pCmdUI->Enable(FALSE);
}

void CFdiverView::OnActOrginal() 
{
	vpFindOption->m_bKftTransFileView = !vpFindOption->m_bKftTransFileView;
}


BOOL CFdiverView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam>=IDC_KICK_APP_START && wParam<=IDC_KICK_APP_OTHER) {
		if (wParam==IDC_KICK_APP_OTHER) {
			((CFdiverDoc *)GetDocument())->m_pFindList->OpenDocument(FALSE);
			return TRUE;
		}
		wParam -= IDC_KICK_APP_START;
		if (wParam<vpFindOption->m_aryStrKickApps.GetSize()) {
			((CFdiverDoc *)GetDocument())->m_pFindList->OpenDocumentByApp(vpFindOption->m_aryStrKickApps[wParam].GetBuffer(0));
			return TRUE;
		}
	}
	
	return CView::OnCommand(wParam, lParam);
}

void CFdiverView::OnViewHeaderbar() 
{
	CFindList *pFindList = ((CFdiverDoc *)GetDocument())->m_pFindList;
	if (pFindList)
		{
		RECT rect;
		GetClientRect(&rect);
		pFindList->LayoutWindowRect(&rect, vpFindOption->m_bHeaderBar=!vpFindOption->m_bHeaderBar);
		pFindList->SetFocus();
		}
}

void CFdiverView::OnUpdateViewHeaderbar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if (vpFindOption)
		pCmdUI->SetCheck(vpFindOption->m_bHeaderBar);
}



