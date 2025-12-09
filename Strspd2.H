/*    PortTool v2.2     strspd2.h          */

// strspd2.h : ヘッダー ファイル
#ifndef __STRSPD2_H_
#define __STRSPD2_H_
#include "strspd1.h"
/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg2 ダイアログ

class CStrSpecDlg2 : public CStrSpecDlg1
{
// コンストラクタ
public:
	CStrSpecDlg2(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CStrSpecDlg2() {}

// ダイアログ データ
	//{{AFX_DATA(CStrSpecDlg2)
	enum { IDD = IDD_STRSPEC_US };
	//}}AFX_DATA

	// ダイアログ情報から、データに反映させます。
	virtual BOOL RetrieveData(CString *pStrAttr);


// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CStrSpecDlg2)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // __STRSPD2_H_
