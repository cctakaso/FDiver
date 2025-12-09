/*    PortTool v2.2     metainp2.h          */

// metainp2.h : ヘッダー ファイル
#ifndef __METAINP2_H_
#define __METAINP2_H_
#include "resource.h"
#include "..\mdfc\childdlg.h"
/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg2 ダイアログ

class CMetaInputDlg2 : public CChildDlg
{
// コンストラクタ
public:
	CMetaInputDlg2(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CMetaInputDlg2() {};
// ダイアログ データ
	//{{AFX_DATA(CMetaInputDlg2)
	enum { IDD = IDD_META_INPUT2 };
	CEdit	m_edStr;
	CString	m_cstr;
	BOOL	m_fInput;
	//}}AFX_DATA

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CString *pcstr);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CString *pcstr);

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CMetaInputDlg2)
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickedMetaInput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //! __METAINP2_H_
