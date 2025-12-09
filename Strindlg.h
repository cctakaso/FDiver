/*    PortTool v2.2     strindlg.h          */

// strInDlg.h : ヘッダー ファイル
//


/////////////////////////////////////////////////////////////////////////////
// CInputStrDlg ダイアログ

class CInputStrDlg : public CDialog
{
// コンストラクタ
public:
	CInputStrDlg(BOOL bRef=FALSE, CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInputStrDlg)
	enum { IDD = IDD_INPUTSTRDLG_NEW };
	CButton	m_btnRef;
	CButton	m_btnOk;
	CButton	m_btn2;
	CString	m_cStrInput;
	//}}AFX_DATA

	void SetInterface(int iSel, CStringArray *paryStr) {
		m_iSel = iSel;
		m_paryStr = paryStr;
		}
	int GetIndex() {
		return m_iSel;
		}
// インプリメンテーション
protected:
	int m_iSel;
	BOOL m_bRef;
	CStringArray *m_paryStr;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CInputStrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedOfStrfileBtn();
	virtual void OnOK();
	afx_msg void OnUpdateOfStrfile();
	virtual void OnCancel();
	afx_msg void OnRefBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlgChg ダイアログ
class CInputStrDlgChg : public CDialog
{
// コンストラクタ
public:
	CInputStrDlgChg(BOOL bRef=FALSE, CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInputStrDlgChg)
	enum { IDD = IDD_INPUTSTRDLG_CHG };
	CButton	m_btnRef;
	CButton	m_btnOk;
	CButton	m_btn2;
	CString	m_cStrInput;
	//}}AFX_DATA

	void SetInterface(int iSel, CStringArray *paryStr, BOOL fDontDelLastOne=FALSE) {
		m_iSel = iSel;
		m_paryStr = paryStr;
		m_fDontDelLastOne = fDontDelLastOne;
		}
	int GetIndex() {
		return m_iSel;
		}
// インプリメンテーション
protected:
	int m_iSel;
	BOOL m_bRef;
	CStringArray *m_paryStr;
	BOOL m_fDontDelLastOne; //最後の１つを削除してはならないか？
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CInputStrDlgChg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateOfStrfile();
	afx_msg void OnClickedOfStrfileBtn();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRefBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

