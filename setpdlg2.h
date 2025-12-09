// setpdlg.h : header file
//
#ifndef __SETPDLG2_H__
#define __SETPDLG2_H__
#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include "resource.h"
#endif //!__RESOURCE_H__
/////////////////////////////////////////////////////////////////////////////
// CSetPathDlgForScan dialog
#include "setpdlg.h"

class CSetPathDlgForScan : public CSetPathDlg
{
//	DECLARE_DYNAMIC(CSetPathDlgForScan)
// Construction
public:
	CSetPathDlgForScan(char *szPath, int iTiteSearch);	// standard constructor
	int m_iTiteSearch;
// Dialog Data
	//{{AFX_DATA(CSetPathDlg)
	enum { IDD = IDD_PATH, IDCTITLE = IDS_PATHDLG_TITLE };
	BOOL m_fTiteSearch;
	//}}AFX_DATA

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CSetPathDlgForScan)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CSetPathDlgForScan)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //! __SETPDLG2_H__
