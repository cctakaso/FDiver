/* PortTool v2.2 edstrlis.h */

// edstrlis.h : ヘッダー ファイル
#ifndef __EDSTRLIS_H_
#define __EDSTRLIS_H_

#include "resource.h"
#include "..\mdfc\childdlg.h"
#include "strary2.h"

/////////////////////////////////////////////////////////////////////////////
// CEdStrList ダイアログ

class CEdStrList : public CChildDlg
{
// コンストラクタ
public:
	CEdStrList(BOOL bRef=FALSE, CWnd* pParent = NULL);	// 標準のコンストラクタ

	void Initialize(char *szTitle, BOOL fDontDelLastOne=FALSE);
	BOOL UpdateData(CStringArray2 *paryStr, int *piSel=NULL);
	BOOL RetrieveData(CStringArray2 *paryStr, int *piSel=NULL);

// ダイアログ データ
	//{{AFX_DATA(CEdStrList)
	enum { IDD = IDD_EDSTRLST };
	CComboBox	m_combStr;
	CButton	m_btnDown;
	CButton	m_btnUp;
	CButton	m_btnChg;
	int		m_iSel;
	//}}AFX_DATA
	CStringArray2	m_aryStr;	// 文字列配列
	BOOL m_fDontDelLastOne;		// 最終エントリー削除禁止フラグ

protected:
	BOOL m_bRef;
// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CEdStrList)
	afx_msg void OnClickedEslNew();
	afx_msg void OnClickedEslChg();
	afx_msg void OnClickedEslUp();
	afx_msg void OnClickedEslDown();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEslList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //!__EDSTRLIS__H_・