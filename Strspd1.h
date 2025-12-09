/*    PortTool v2.2     strspd1.h          */

// strspd1.h : ヘッダー ファイル
#ifndef __STRSPD1_H_
#define __STRSPD1_H_
//#include "dfile.h"
#include "..\mdfc\childdlg.h"
#include "resource.h"
#include "strspec.h"
/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg1 ダイアログ

class CStrSpecDlg1 : public CChildDlg
{
// コンストラクタ
public:
	CStrSpecDlg1(CWnd* pParent = NULL);	// 標準のコンストラクタ
	CStrSpecDlg1(UINT id, CWnd* pParent);
	~CStrSpecDlg1() {}

// ダイアログ データ
	//{{AFX_DATA(CStrSpecDlg1)
	enum { IDD = IDD_STRSPEC_JPN };
/*	BOOL	m_fCase;
	BOOL	m_fBytes;
	BOOL	m_fKata;
	BOOL	m_fUmura;
	BOOL	m_fSpace;
	BOOL	m_fTab;
	BOOL	m_fLF;
	BOOL	m_fNoBreak;
	CString	m_strOthers;
*/
	STRSPEC_ATTR m_attrData;
	//}}AFX_DATA

	// ダイアログ情報から、データに反映させます。
	virtual BOOL RetrieveData(CString *pStrAttr);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CString *pStrAttr);

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CStrSpecDlg1)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateFsNoOtherEd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // __STRSPD1_H_
