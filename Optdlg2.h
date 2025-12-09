/*    PortTool v2.2     optdlg2.h          */

// optdlg2.h : ヘッダー ファイル
//
#ifndef __OPTDLG2_H_
#define __OPTDLG2_H_
//#include "dfile.h"
#include "..\mdfc\childdlg.h"
#include "resource.h"
#include "findopti.h"
/////////////////////////////////////////////////////////////////////////////
// COptionDlg2 ダイアログ
class COptionDlg2 : public CChildDlg
{
// コンストラクタ
public:
	COptionDlg2(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~COptionDlg2() {}

// ダイアログ データ
	//{{AFX_DATA(COptionDlg2)
	enum { IDD = IDD_DSPOPTION };
	CEdit	m_edMaxLines;
	BOOL	m_fDispDoc;
	int		m_optDispNum;
	BOOL	m_fFile;
	BOOL	m_fDir;
	int		m_optNum;
	BOOL	m_fNum;
	BOOL	m_fDragServer;
	int		m_iMaxLines;
	BOOL	m_fDefTagAuto;
	//}}AFX_DATA

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CFindOption *pFindOption);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CFindOption *pFindOption);


// インプリメンテーション
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(COptionDlg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedOfPosition();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // __OPTDLG2_H__
