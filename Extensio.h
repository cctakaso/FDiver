/*    PortTool v2.2     extensio.h          */

// extensio.h : ヘッダー ファイル
#ifndef __EXTENSIONS_H_
#define __EXTENSIONS_H_
//#include "dfile.h"
#include "findopti.h"
#include "resource.h"
#include "..\mdfc\childdlg.h"
#include "edstrlis.h"
/////////////////////////////////////////////////////////////////////////////
// CExtensionsDlg ダイアログ
class CExtensionsDlg : public CChildDlg
{
// コンストラクタ
public:
	CExtensionsDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CExtensionsDlg();

// ダイアログ データ
	//{{AFX_DATA(CExtensionsDlg)
	enum { IDD = IDD_EXTENSIONS };
	CButton	m_btnEditer;
	CEdit	m_edEditer;
	CString	m_strEditer;
	BOOL	m_bCRIsNewLine;
	//}}AFX_DATA

	// エディタブル・ストリング・リスト子ウィンドウ
	CEdStrList *m_pSubDlg;

	// エディタブル・ストリング・リスト子ウィンドウ
	CEdStrList *m_pSubDlgRef;

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CFindOption *pFindOption);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CFindOption *pFindOption);

// インプリメンテーション
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	// メッセージマップ関数の生成
	//{{AFX_MSG(CExtensionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditerBtn();
	afx_msg void OnChangeEditer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // __EXTENSIONS_H__
