/*    PortTool v2.2     fdivevw.h          */

// FDivevw.h : CFdiverView クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////
class CFindList;
class CFdiverView : public CView
{
	friend class CFindList;
protected: // シリアライズ機能のみから作成します。
	CFdiverView();
	DECLARE_DYNCREATE(CFdiverView)
// 属性
public:
	CFdiverDoc* GetDocument();
protected:
	CFont m_font;
	LOGFONT	m_lf;
	CDLLDoc *m_pKftDll;
// オペレーション
public:
	void DoOnFind() {
		OnFind(); };
// インプリメンテーション
public:
	virtual ~CFdiverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	void SetFont(int iZoom);
// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CFdiverView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// メッセージ マップ関数の生成を行います。
protected:
	//{{AFX_MSG(CFdiverView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnFind();
	afx_msg void OnFindStop();
	afx_msg void OnFClearsel();
	afx_msg void OnActDispdoc();
	afx_msg void OnActDispdocedit();
	afx_msg void OnDspClosetodir();
	afx_msg void OnDspClosetofile();
	afx_msg void OnDspSortbydate();
	afx_msg void OnDspSortbyexp();
	afx_msg void OnDspSortbyname();
	afx_msg void OnDspSortbysize();
	afx_msg void OnOptDispbyfile();
	afx_msg void OnOptDispbypath();
	afx_msg void OnOptDisplist();
	afx_msg void OnOptDisptree();
	afx_msg void OnOptDragServer();
	afx_msg void OnUpdateActFind(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActFindstop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActClearsel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActDispdoc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActDispdocedit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspClosetodir(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspClosetofile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspSortbydate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspSortbyexp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspSortbyname(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspSortbysize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptDispbyfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptDispbypath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptDisplist(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptDisptree(CCmdUI* pCmdUI);
	afx_msg void OnOptDspfindlog();
	afx_msg void OnUpdateOptDspfindlog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDspListfont(CCmdUI* pCmdUI);
	afx_msg void OnDspListfont();
	afx_msg void OnUpdateViewHeaderbar(CCmdUI* pCmdUI);
	afx_msg void OnViewHeaderbar();
	afx_msg void OnUpdateActTagtext(CCmdUI* pCmdUI);
	afx_msg void OnActTagtext();
	afx_msg void OnUpdateDspColors(CCmdUI* pCmdUI);
	afx_msg void OnDspColors();
	afx_msg void OnUpdateDspOpenlist(CCmdUI* pCmdUI);
	afx_msg void OnDspOpenlist();
	afx_msg void OnUpdateActOrginal(CCmdUI* pCmdUI);
	afx_msg void OnActOrginal();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// fdivevw.cpp ファイルがデバッグ環境の時使用されます。
inline CFdiverDoc* CFdiverView::GetDocument()
   { return (CFdiverDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
