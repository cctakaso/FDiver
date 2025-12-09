// findlog.h : header file
//
#ifndef __FINDLOG_H_
#define __FINDLOG_H_

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CFindLog dialog

class CFindLog : public CDialog
{
	DECLARE_SERIAL(CFindLog)
// Construction
public:
	CFindLog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFindLog)
	enum { IDD = IDD_FINDLOG };
	CEdit	m_edLog;
	CString	m_strLog;
	//}}AFX_DATA

	void AddLogLine(char *sz, BOOL fFirstSpace=TRUE);
	void AddLogString(char *sz, BOOL fFirstSpace=TRUE);
	void ResetLog();
// Overrides
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindLog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //__FINDLOG_H_
