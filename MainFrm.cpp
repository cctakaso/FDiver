/*    PortTool v2.2     MAINFRM.CPP          */

// mainfrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "Fdiver.h"

#include "mainfrm.h"
#include "findlist.h"
#include "fdivedoc.h"
#include "findopti.h"
#include "finddlg.h"
#include "fdivevw.h"
#include "metainp.h"
#include "metastr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern BOOL vfCloseApp;	// ｱﾌﾟﾘｹｰｼｮﾝの終了
extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CFindOption *vpFindOption;
extern CFindDlg *vpFindDlg;
extern CMetaStringArray *vpMetaStringArray;
extern CStringArray varyParams;
extern CFindFile *vpcFind;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(IDR_OPT_FIND, OnUpdateOptFind)
	ON_UPDATE_COMMAND_UI(ID_FINDDIRS, OnUpdateFinditems)
	ON_UPDATE_COMMAND_UI(ID_SEARCHFILES, OnUpdateSearchfiles)
	ON_UPDATE_COMMAND_UI(ID_FINDDOING, OnUpdateFinddoing)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(IDR_ACT_TOPMOST, OnUpdateActTopmost)
	ON_UPDATE_COMMAND_UI(ID_MYHELP_INDEX, OnUpdateHelpIndex)
	ON_UPDATE_COMMAND_UI(IDR_ACT_EDITER, OnUpdateActEditer)
	ON_UPDATE_COMMAND_UI(IDR_ACT_CLONE, OnUpdateActClone)
	ON_UPDATE_COMMAND_UI(IDR_OPT_ICON, OnUpdateOptIcon)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_WM_SETFOCUS()
	ON_WM_DROPFILES()
	ON_UPDATE_COMMAND_UI(IDR_OPT_DRAG_SERVER, OnUpdateOptDragServer)
	ON_WM_ACTIVATE()
	ON_COMMAND(IDR_APP_EXIT, OnAppExtFromBtn)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(IDR_OPT_KEYENTRY, OnOptKeyentry)
	ON_UPDATE_COMMAND_UI(IDR_OPT_KEYENTRY, OnUpdateOptKeyentry)
	ON_COMMAND(ID_MYHELP_INDEX, OnMyHelpIndex)
	ON_MESSAGE(WM_FINDDLG_OPEN, OnMessageFindDlgOpen)
	ON_UPDATE_COMMAND_UI(ID_FINDFILES, OnUpdateFinditems)
	ON_UPDATE_COMMAND_UI(ID_FINDITEMS, OnUpdateFinditems)
	ON_UPDATE_COMMAND_UI(IDR_APP_EXIT, OnUpdateAppExit)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateViewStatusBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// コントロールバーの初期化に使用する ID の配列

// ツールバー用のボタン - ID はコマンドボタンです。
static UINT BASED_CODE buttons[] =
{
	// ビットマップファイル 'toolbar.bmp' と同じ並び順です。
	
	IDR_ACT_TOPMOST,
	ID_FILE_OPEN,
//	ID_FILE_SAVE_AS,
		ID_SEPARATOR,
	IDR_ACT_FIND,
	IDR_ACT_FINDSTOP,
		ID_SEPARATOR,
	IDR_ACT_CLEARSEL,
	IDR_ACT_DISPDOCEDIT,
	IDR_DSP_CLOSETODIR,
	IDR_DSP_CLOSETOFILE,
		ID_SEPARATOR,
	IDR_OPT_FIND,
	ID_MYHELP_INDEX,
	IDR_APP_EXIT
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,			// ステータス ライン インジケータ
	ID_FINDDIRS,
	ID_FINDFILES,
	ID_FINDITEMS,
	ID_SEARCHFILES,
	ID_FINDDOING,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理のコードを追加してください。
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	// ｳｨﾝﾄﾞｳｻｲｽﾞ･ｲﾆｼｬﾙｾｯﾄの為非表示でｸﾘｴｲﾄする
	// lpCreateStruct->style ^= WS_VISIBLE;
//	lpCreateStruct->x = vpFindOption->m_left;
//	lpCreateStruct->cx = vpFindOption->m_right - vpFindOption->m_left;
//	lpCreateStruct->y = vpFindOption->m_top;
//	lpCreateStruct->cy = vpFindOption->m_bottom - vpFindOption->m_top;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifdef OLDVER
	if (!m_wndToolBar.Create(this))
		goto ErrToolBar;
	else
		{
		CSize sizeButton, sizeImage;
		sizeButton.cx = 40;//44;//26;
		sizeButton.cy = 38;//40;//42;
		sizeImage.cx = 28;//32;//16;
		sizeImage.cy = 28;//30;//15;
		m_wndToolBar.SetSizes(sizeButton, sizeImage);
		}
	if (!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
		{
ErrToolBar:
		TRACE("ツールバーの作成に失敗しました\n");
		return -1;		// 作成に失敗した時、戻り値は -1 となります。
		}
#else
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//if (!m_wndToolBar.Create(this) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
		{
		TRACE("ツールバーの作成に失敗しました\n");
		return -1;		// 作成に失敗した時、戻り値は -1 となります。
		}
#endif

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("ステータス バーの作成に失敗しました\n");
		return -1;		// 作成に失敗した時、戻り値は -1 となります。
	}


#ifdef WIN32
	// TODO: ツールバーをドッキング可能にしない場合は以下の 3 行を削除してください。

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: もしツールチップスが必要ない場合、ここを削除してください。
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
#endif //WIN32

//	{
//	UINT nID;
//	UINT nStyle;
//	int cxWidth;
//	m_wndStatusBar.GetPaneInfo(1, nID, nStyle, cxWidth);
//	m_wndStatusBar.SetPaneInfo(1, nID, nStyle & ~SBPS_DISABLED, cxWidth);
	SetPaneText();
//	}
/*	{
	RECT rc;
	m_wndStatusBar.GetItemRect(3, &rc);
	CDC *pcdc=(CWnd)m_wndStatusBar.GetDC();
	(CWnd)m_wndStatusBar.ReleaseDC();
	}
*/
	ShowControlBar(&m_wndStatusBar, vpFindOption->m_bStatusBar, FALSE);
	ShowControlBar(&m_wndToolBar, vpFindOption->m_bToolBar, FALSE);

	return 0;

}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	return CFrameWnd::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG



void CMainFrame::OnUpdateOptFind(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
	
}

void CMainFrame::OnUpdateFinditems(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnUpdateSearchfiles(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnUpdateFinddoing(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnClose()
{
	if(((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
		return; //((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);

	vfCloseApp=TRUE;	// ｱﾌﾟﾘｹｰｼｮﾝの終了ﾌﾗｸﾞｵﾝ

#ifdef _TAG_AUTOOPEN		//Default Tag Open
	if (vpFindOption->m_fDefTagAuto)
		{
		CDocument *pDoc=GetActiveDocument();
		if (pDoc)
			{
		//	CString cstr=pDoc->GetPathName();
		//	cstr.MakeLower();
		//	if (cstr != ((CFdiverApp *)AfxGetApp())->m_cDefTagFile.GetBuffer())
		//		((CFdiverApp *)AfxGetApp())->m_cDefTagFile.SetModifyed();
		//	// Default FileにAutoセーブする
		//	if (((CFdiverApp *)AfxGetApp())->m_cDefTagFile.GetModifyed())
				pDoc->OnSaveDocument(((CFdiverApp *)AfxGetApp())->m_cDefTagFile.GetBuffer());	// 
			}
		}
#endif 	

	// 次に起動する時のサイズをｾｰﾌﾞ
	if (!AfxGetApp()->m_pMainWnd->IsIconic() && !AfxGetApp()->m_pMainWnd->IsZoomed())
		{
		RECT rc;
		AfxGetApp()->m_pMainWnd->GetWindowRect(&rc);
		vpFindOption->m_left = rc.left;
		vpFindOption->m_width = rc.right-rc.left;
		vpFindOption->m_top = rc.top;
		vpFindOption->m_hight = rc.bottom-rc.top;
		}

	// 次に起動する時のサイズをｾｰﾌﾞ
//	RECT rc;
//#ifdef _DEBUG
//	WINDOWPLACEMENT winplace;
//	GetWindowPlacement(&winplace);
//#endif
//	rc = winplace.rcNormalPosition;
//	vpFindOption->m_left = rc.left;
//	vpFindOption->m_width = rc.right-rc.left;
//	vpFindOption->m_top = rc.top;
//	vpFindOption->m_hight = rc.bottom-rc.top;

	CFrameWnd::OnClose();
}

void CMainFrame::OnUpdateActTopmost(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	if (vpFindOption)
		pCmdUI->SetCheck(vpFindOption->m_fTopMost!=0);
	
}


void CMainFrame::OnUpdateHelpIndex(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

//void CMainFrame::OnUpdateActSortlst(CCmdUI* pCmdUI)
//{
//	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
//	pCmdUI->Enable(((CFdiverDoc *)GetActiveDocument())->SendMessage( LB_GETCOUNT, 0, 0 )>0);
//} 


void CMainFrame::OnUpdateActEditer(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateActClone(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してください。
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateOptIcon(CCmdUI* pCmdUI)
{
	// TODO: この位置にコマンド更新 UI ハンドラのコードを追加してくだ・
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
	if (vpFindOption)
		pCmdUI->SetCheck(vpFindOption->m_fIcon);
	
}

void CMainFrame::OnUpdateAppExit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
#ifdef BUG
	CFrameWnd::OnSetFocus(pOldWnd);
	CView *pView = GetActiveView();
	if (pView)
		pView->SetFocus();
#else
	CFrameWnd::OnSetFocus(pOldWnd);
	if (vpFindList)
		vpFindList->SetFocus();
#endif
}


// Drag & Drop
void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	// Set Drop Files and Path
	UINT uiMax= DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);
	CDFile cFile;
	CDString cdstr;
	for (UINT ui=0; ui<uiMax; ui++)
		{
		DragQueryFile(hDropInfo, ui, vz, sizeof(vz));
		cFile = vz;
		if (CheckPath(cFile.GetBuffer()))
			AddLastBackSlash(cFile.GetString());
		cdstr = cFile.GetName();
		cdstr.MakeLower();
		//SPEC OUT : 現在のファイル種類のまま、ディレクトリだけドロップされたものとする
		//	vpFindDlg->SetStrFile(cdstr.GetBuffer(), ui!=0);
		}
	cdstr = cFile.GetPath();
	cdstr.MakeLower();
	//vpFindDlg->SetStrPath(cdstr.GetBuffer());
	vpFindDlg->AddFindPathSpec(cdstr.GetBuffer());
	DragFinish(hDropInfo);
	// Find Dialog Open!
	((CFdiverView *)GetActiveView())->DoOnFind();
	//CFrameWnd::OnDropFiles(hDropInfo);
}
//"/G":Open find dlg.
//"/D":Direct find.
//"/K:string":find key string
//"/F:string":find file spec string
//"/P:string":find path string
//"/T[0/1]":find method index
//"/S[0/1]":find sub-directorys
//"/M[0/1]":find meta flg.
//"/C[0/1]":the search in the compress files flg.
LRESULT CMainFrame::OnMessageFindDlgOpen(WPARAM wParam, LPARAM lParam)
{
	CDFile cFile;
	int cparam = 0;
	bool bDlg=false, bDirect=false;
	char chSubDir=0, chMeta=0, chCompress=0, chMethod=0;
	CString strKey, strFileSpec, strPath;
	if (varyParams[0][0]!='/') {
		cFile  = varyParams[0];
		strPath = cFile.GetPath();
	}
	for(int i=0; i<varyParams.GetSize(); i++) {
		if (varyParams[i][0]=='/' && varyParams[i].GetLength()>1) {
			char ch=0;
			CString str;
			if (varyParams[i].GetLength()>3) {
				str = varyParams[i].Mid(3);
			}else if(varyParams[i].GetLength()>2) {
				ch = varyParams[i][2];
				if (ch<'0' && ch>'9')
					ch=0;
			}
			switch(varyParams[i][1]) {
			case 'G':
			case 'g':
				bDlg = true;
				break;
			case 'D':
			case 'd':
				bDirect = true;
				break;
			case 'K':
			case 'k':
				strKey = str;
				break;
			case 'F':
			case 'f':
				strFileSpec = str;
				break;
			case 'P':
			case 'p':
				strPath = str;
				break;
			case 'T':
			case 't':
				chMethod = ch;
				break;
			case 'S':
			case 's':
				chSubDir = ch;
				break;
			case 'M':
			case 'm':
				chMeta = ch;
				break;
			case 'C':
			case 'c':
				chCompress = ch;
				break;
			}
		}
	}

	if (chMethod != 0) {
		vpFindDlg->m_iSelForStrSpec = chMethod-'0';
		vpFindDlg->m_strSpec.m_iSel = vpFindDlg->m_iSelForStrSpec;
	}
	if (chSubDir != 0) {
		vpFindDlg->m_fSubDir = chSubDir=='0' ? FALSE:TRUE;
	}
	if (chMeta != 0) {
		vpFindDlg->m_fMetaChars = chMeta=='0' ? FALSE:TRUE;
	}
	if (chCompress != 0) {
		vpFindDlg->m_fArc = chCompress=='0' ? FALSE:TRUE;
	}
	//vpFindDlg->UpdateData(FALSE);

	if (!strKey.IsEmpty()) {
		vpFindDlg->AddFindStrSpec(strKey.GetBuffer(0));
	}
	if (!strFileSpec.IsEmpty()) {
		vpFindDlg->AddFindFileSpec(strFileSpec.GetBuffer(0));
	}
	if (!strPath.IsEmpty()) {
		strPath.MakeLower();
		vpFindDlg->AddFindPathSpec(strPath.GetBuffer(0));
	}
	if (bDirect) {
		// 検索文字列あり？
		if (vpFindDlg->FValidFindSpec()) {
			vpFindDlg->AddFindSpecs();
			vpFindList = ((CFdiverDoc *)GetActiveDocument())->m_pFindList;
			ASSERT(vpFindList);
			((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(TRUE);

			// ﾂｰﾙﾊﾞｰを更新する為、OnIdle()を呼び出す！
	//		CWinApp::OnIdle(0);
			// CDFilesオブジェクトの作成
			if (vpcFind->FInitFiles(vpFindDlg->GetFilePath(), vpFindDlg->GetFileSpec(), vpFindDlg->FSubDir(), vpFindDlg->FArc())) {
				if (vpFindOption->m_fIcon)
					((CFdiverApp *)AfxGetApp())->m_pMainWnd->ShowWindow(SW_MINIMIZE);
			}else{
				((CFdiverApp *)AfxGetApp())->FinishFind();
			}
		}
	}else
		((CFdiverView *)GetActiveView())->DoOnFind();
	return 0;
}

void CMainFrame::OnUpdateOptDragServer(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	if (vpFindOption)
		pCmdUI->SetCheck(vpFindOption->m_fDragServer);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: この位置にメッセージ ハンドラのコードを追加してください。
	if (nState==WA_ACTIVE || nState==WA_CLICKACTIVE)
		{
		CView *pView = GetActiveView();
		if (pView)
			pView->SetFocus();
		}
	
}

void CMainFrame::OnAppExtFromBtn()
{
	PostMessage(WM_CLOSE,(WPARAM)0,(LPARAM)0);
}


void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}
void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}
void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}
void CMainFrame::OnUpdateOptKeyentry(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}
void CMainFrame::OnOptKeyentry()
{
	CMetaInputDlg metaInputDlg;
	CString cstr;
	metaInputDlg.Initialize(&cstr, vpMetaStringArray, TRUE);
	metaInputDlg.DoModal();
}
void CMainFrame::SetPaneText(char *sz/*=NULL*/, int indicator/*=0*/)
{
	if (sz)
		m_wndStatusBar.SetPaneText(indicator, sz);
	else
		{
		m_wndStatusBar.SetPaneText(1, "");
		m_wndStatusBar.SetPaneText(2, "");
		m_wndStatusBar.SetPaneText(3, "");
		m_wndStatusBar.SetPaneText(4, "");
		m_wndStatusBar.SetPaneText(5, "");
		}
	m_wndStatusBar.UpdateWindow();
}
#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children from afxprv.h
BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle,
	CWnd* pParentWnd, CCreateContext* pContext)
{
	if (AfxGetApp()->m_pMainWnd->GetSafeHwnd())
		return CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle,
				pParentWnd, pContext);
	// only do this once
	//ASSERT_VALID_IDR(nIDResource);
	ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

	m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

	CString strFullString, strTitle;
	if (strFullString.LoadString(nIDResource))
		AfxExtractSubString(strTitle, strFullString, 0);    // first sub-string

	RECT rc;
	::SetRect(&rc, vpFindOption->m_left,vpFindOption->m_top,
	vpFindOption->m_width + vpFindOption->m_left,vpFindOption->m_hight+vpFindOption->m_top);
	//::SetRect(&rc, CW_USEDEFAULT,CW_USEDEFAULT,1,1);	// set minimam window
	//::SetRect(&rc, 0,0,0,0);	// set minimam window
	if (!Create(GetIconWndClass(dwDefaultStyle, nIDResource),
	  strTitle, dwDefaultStyle /*^ WS_VISIBLE*/, rc,
	  pParentWnd, MAKEINTRESOURCE(nIDResource), 0L, pContext))
		return FALSE;   // will self destruct on failure normally

	LoadAccelTable(MAKEINTRESOURCE(nIDResource));

	if (pContext == NULL)   // send initial update
		SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE);

	return TRUE;
}

LRESULT CMainFrame::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message==WM_ARCEXTRACT_MSG && WM_ARCEXTRACT_MSG!=NULL)
		{
		//0 : UNLHA32.DLL が該当ファイルの処理を開始することを表します。
		//1 : UNLHA32.DLL が該当ファイルの展開中であることを表します。
		//2 : UNLHA32.DLL が処理を終え，lpEis のメモリを開放しようとしていることを表します。
		MSG msg;
		switch(wParam)
			{
			case 0:
			case 1:
				if (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
					{
					if (msg.message==WM_KEYDOWN)
						{
						TranslateMessage(&msg);
						if (msg.wParam==VK_ESCAPE)
							{
							//検索中だったら検索を中止させる
							((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
							return 	1;//中止
							}
						DispatchMessage(&msg);
						}
					else if (msg.message==WM_CLOSE)
						{
						//((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
						//Eate!
						//検索中だったら検索を中止させる
						PostMessage(WM_KEYDOWN, VK_ESCAPE, 0);
						return 0;
						}			
					else
						{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
						}
					}
				break;
			//case 2:
			default:
				break;
			}
		return 	0;//続行
		}
	else
		return CFrameWnd::DefWindowProc( message, wParam, lParam );
}

void CMainFrame::OnMyHelpIndex() 
{
#ifdef HTML_HELP
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CString strFile = ((CFdiverApp *)AfxGetApp())->PGetDefaltPath();
	strFile += "\\FDiver_man.html";
	HINSTANCE hInst = ShellExecute(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), "open",
		strFile, NULL, NULL, SW_SHOWNORMAL);
	if ((UINT)hInst<=31) {
		if (::WinExec(strFile, SW_SHOWNORMAL)<=31) {
			CString str;
			str.LoadString(IDS_MSG_SHOW_MAN);
			str += "\n[";
			str += strFile;
			str += "]";
			AfxMessageBox(str.GetBuffer(0), MB_OK);
		}
	}
#else
	((CFdiverApp *)AfxGetApp())->OnMyHelpIndex();
	//WinHelp(0, HELP_FINDER);
#endif
}

void CMainFrame::OnViewToolbar() 
{
	vpFindOption->m_bToolBar = !vpFindOption->m_bToolBar;
	ShowControlBar(&m_wndToolBar, vpFindOption->m_bToolBar, FALSE);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if (vpFindOption)
		pCmdUI->SetCheck(vpFindOption->m_bToolBar);
}

void CMainFrame::OnViewStatusBar() 
{
	vpFindOption->m_bStatusBar = !vpFindOption->m_bStatusBar;
	ShowControlBar(&m_wndStatusBar, vpFindOption->m_bStatusBar, FALSE);
}

void CMainFrame::OnUpdateViewStatusBar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	if (vpFindOption)
		pCmdUI->SetCheck(vpFindOption->m_bStatusBar);
}

