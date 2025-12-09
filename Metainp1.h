/*    PortTool v2.2     metainp1.h          */

// metainp1.h : ヘッダー ファイル
#ifndef __METAINP1_H_
#define __METAINP1_H_
/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg1 ダイアログ
#include "resource.h"
#include "..\mdfc\childdlg.h"
#include "edstrli2.h"

class CMetaInputDlg1 : public CChildDlg
{
// コンストラクタ
public:
	CMetaInputDlg1(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CMetaInputDlg1();
// ダイアログ データ
	//{{AFX_DATA(CMetaInputDlg1)
	enum { IDD = IDD_META_INPUT1 };
	CEdit	m_edStr;
	CString	m_cstr;
	CButton	m_btnReplaceSel;
	//}}AFX_DATA

	// エディタブル・ストリング・リスト子ウィンドウ
	CEdStrList2 *m_pSubDlg;

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CString *pcstr, CMetaStringArray *pMetaStringArray);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CString *pcstr, CMetaStringArray *pMetaStringArray, BOOL fKeyEntryOnly=FALSE);

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CMetaInputDlg1)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedInput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //! __METAINP1_H_
