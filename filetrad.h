// filetrad.h : ヘッダー ファイル
//
#ifndef __FILETRAD_H_
#define __FILETRAD_H_

/////////////////////////////////////////////////////////////////////////////
// CFileTransDlg ダイアログ
#include "..\mdfc\childdlg.h"
#include "resource.h"
#include "findopti.h"

class CFileTransDlg : public CChildDlg
{
// コンストラクション
public:
	CFileTransDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

//EntryPoint Arc

// ダイアログ データ
	//{{AFX_DATA(CFileTransDlg)
	enum { IDD = IDD_FILETRANS };
	BOOL	m_fLha;
	BOOL	m_fZip;
	int		m_optRemain;
	CString	m_strWorkPath;
	BOOL	m_fArj;
	BOOL	m_fTar;
	BOOL	m_fCab;
	BOOL	m_fRar;
	BOOL	m_fKft;
	BOOL	m_fxdoc;
	//}}AFX_DATA

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CFindOption *pFindOption);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CFindOption *pFindOption);

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CFileTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFileTransDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //__FILETRAD_H_
