// MainFrm.h : CMainFrame クラスの宣言およびインターフェイスの定義をします。
/////////////////////////////////////////////////////////////////////////////
//#include "mytoolba.h"
//#include "mystatus.h"
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
protected: // シリアライズ機能のみから作成します。
	DECLARE_DYNCREATE(CMainFrame)

// コントロール バー用メンバ
	CStatusBar	m_wndStatusBar;
//	CMyStatusBar	m_wndStatusBar;
	CToolBar	m_wndToolBar;

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	public:
// メッセージ マップ関数の生成を行います。
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateOptFind(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFinditems(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchfiles(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFinddoing(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnUpdateActTopmost(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpIndex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActEditer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActClone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptIcon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnUpdateOptDragServer(CCmdUI* pCmdUI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnAppExtFromBtn();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnOptKeyentry();
	afx_msg void OnUpdateOptKeyentry(CCmdUI* pCmdUI);
	afx_msg void OnMyHelpIndex();
	afx_msg LRESULT OnMessageFindDlgOpen(WPARAM wParam, LPARAM lParam);
	afx_msg void OnViewToolbar();
	afx_msg void OnUpdateViewToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewStatusBar();
	afx_msg void OnUpdateViewStatusBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// 属性
public:

// オペレーション
public:
	void SetPaneText(char *sz=NULL, int indicator=0);
	CString GetPaneText(int indicator=0) {
		return m_wndStatusBar.GetPaneText(indicator);
	}

// インプリメンテーション
public:
	virtual ~CMainFrame();
//	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL LoadFrame(UINT nIDResource,
				DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
				CWnd* pParentWnd = NULL,
				CCreateContext* pContext = NULL);
	virtual LRESULT DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam );
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
	CStatusBar *GetStatusBar() {
		return &m_wndStatusBar; }

};

/////////////////////////////////////////////////////////////////////////////
