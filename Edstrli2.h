/*    PortTool v2.2     edstrli2.h          */

// edstrli2.h : ヘッダー ファイル
#ifndef __EDSTRLI2_H_
#define __EDSTRLI2_H_

#include "resource.h"
#include "..\mdfc\childdlg.h"
#include "metastr.h"

/////////////////////////////////////////////////////////////////////////////
// CEdStrList2 ダイアログ

class CEdStrList2 : public CChildDlg
{
// コンストラクタ
public:
	CEdStrList2(CWnd* pParent = NULL);	// 標準のコンストラクタ

	void Initialize(char *szTitle, BOOL fDontDelLastOne=FALSE);
	BOOL UpdateData(CMetaStringArray *paryStr, int *piSel=NULL);
	BOOL RetrieveData(CMetaStringArray *&paryStr, int *piSel=NULL);

// ダイアログ データ
	//{{AFX_DATA(CEdStrList2)
	enum { IDD = IDD_EDSTRLST2 };
	CListBox	m_combStr;
	CButton	m_btnDown;
	CButton	m_btnUp;
	CButton	m_btnChg;
	int		m_iSel;
	//}}AFX_DATA
	CMetaStringArray	*m_pMetaStringArray;	// 文字列配列
	BOOL m_fDontDelLastOne;		// 最終エントリー削除禁止フラグ

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CEdStrList2)
	afx_msg void OnClickedEslNew();
	afx_msg void OnClickedEslChg();
	afx_msg void OnClickedEslUp();
	afx_msg void OnClickedEslDown();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEslList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlg2 ダイアログ

class CInputStrDlg2 : public CDialog
{
// コンストラクタ
public:
	CInputStrDlg2(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInputStrDlg2)
	enum { IDD = IDD_INPUTSTRDLG_NEW2 };
	CButton	m_btnOk;
	CButton	m_btn2;
	CString	m_cStrInput;
	CString	m_cStrInput2;
	//}}AFX_DATA

	void SetInterface(int iSel, CMetaStringArray *paryStr) {
		m_iSel = iSel;
		m_pMetaStringArray = paryStr;
		}
	int GetIndex() {
		return m_iSel;
		}
// インプリメンテーション
protected:
	int m_iSel;
	CMetaStringArray *m_pMetaStringArray;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	//BOOL FEnableBtn2();
	//BOOL FEnableBtnOk();

	// メッセージマップ関数の生成
	//{{AFX_MSG(CInputStrDlg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedOfStrfileBtn();
	virtual void OnOK();
	afx_msg void OnUpdateOfStrfile();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlgChg2 ダイアログ
class CInputStrDlgChg2 : public CDialog
{
// コンストラクタ
public:
	CInputStrDlgChg2(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInputStrDlgChg2)
	enum { IDD = IDD_INPUTSTRDLG_CHG2 };
	CButton	m_btnOk;
	CButton	m_btn2;
	CString	m_cStrInput;
	CString	m_cStrInput2;
	//}}AFX_DATA

	void SetInterface(int iSel, CMetaStringArray *paryStr, BOOL fDontDelLastOne=FALSE) {
		m_iSel = iSel;
		m_pMetaStringArray = paryStr;
		m_fDontDelLastOne = fDontDelLastOne;
		}
	int GetIndex() {
		return m_iSel;
		}
// インプリメンテーション
protected:
	int m_iSel;
	CMetaStringArray *m_pMetaStringArray;
	BOOL m_fDontDelLastOne; //最後の１つを削除してはならないか？
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CInputStrDlgChg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateOfStrfile();
	afx_msg void OnClickedOfStrfileBtn();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //!__EDSTRLI2__H_
