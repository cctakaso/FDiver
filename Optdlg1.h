/*    PortTool v2.2     optdlg1.h          */

// optdlg1.h : ヘッダー ファイル
#ifndef __OPTDLG1_H_
#define __OPTDLG1_H_
//#include "dfile.h"
#include "findopti.h"
#include "resource.h"
#include "..\mdfc\childdlg.h"
#include "time.h"
#include "edstrlis.h"
/////////////////////////////////////////////////////////////////////////////
// COptionDlg1 ダイアログ
class COptionDlg1 : public CChildDlg
{
// コンストラクタ
public:
	COptionDlg1(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~COptionDlg1();

// ダイアログ データ
	//{{AFX_DATA(COptionDlg1)
	enum { IDD = IDD_FINDOPTION };
	CEdit	m_ceReadSize;
	long	m_lReadSize;
	BOOL	m_fSound;
	BOOL	m_fToTopWin;
	BOOL	m_fIcon;
	BOOL	m_fMetaHelp;
	BOOL	m_fNoErrDsp;
	CString	m_strExtraFileSpec;
//	CStringArray2 m_aryStrFiles;
	//}}AFX_DATA

	// エディタブル・ストリング・リスト子ウィンドウ
	CEdStrList *m_pSubDlg;

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CFindOption *pFindOption);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CFindOption *pFindOption);

// インプリメンテーション
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(COptionDlg1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // __OPTDLG1_H__
