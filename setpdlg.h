// setpdlg.h : header file
//
#ifndef __SETPDLG_H__
#define __SETPDLG_H__
#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include "resource.h"
#endif //!__RESOURCE_H__
/////////////////////////////////////////////////////////////////////////////
// CSetPathDlg dialog
#ifndef BUG_20120112
extern BOOL vbUperVista;
#endif

class CSetPathDlg : public CFileDialog
{
//	DECLARE_DYNAMIC(CSetPathDlg)
// Construction
public:
	CSetPathDlg(char *szPath, UINT idRes, UINT idResTitile);

// Dialog Data
	//{{AFX_DATA(CSetPathDlg)
	//enum { IDD = IDD_PATH };
	//}}AFX_DATA
	virtual int DoModal();
	CString	m_strOutPath;

	char *GetPathBuffer() {
#ifdef BUG20120112
		return m_bUperVista ? m_strOutPath.GetBuffer(0):m_strPaths.GetBuffer(0); }
#else
		return vbUperVista ? m_strOutPath.GetBuffer(0):m_strPaths.GetBuffer(0); }
#endif

public:
// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CSetPathDlg)
	public:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnFileNameOK();
	//}}AFX_VIRTUAL

protected:
	CString	m_strPaths;
	UINT 	m_idRes;
	UINT	m_idResTitile;
	BOOL 	m_bWin4;
#ifndef BUG20120112
	BOOL	m_bUperVista;
#endif
	UINT	m_idRtn;
// Implementation
protected:
	CString GetMyFolderPath() const;

	// Generated message map functions
	//{{AFX_MSG(CSetPathDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //! __SETPDLG_H__
