// findlog.cpp : implementation file
//

#include "stdafx.h"
#include "..\mdfc\ch.h"
#include "fdiver.h"
#include "findlog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CFindLog, CDialog, 2)
/////////////////////////////////////////////////////////////////////////////
// CFindLog dialog


CFindLog::CFindLog(CWnd* pParent /*=NULL*/)
	: CDialog(CFindLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindLog)
	m_strLog = _T("");
	//}}AFX_DATA_INIT
}

void CFindLog::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_strLog;
	else
		ar >> m_strLog;
}

void CFindLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindLog)
	DDX_Control(pDX, IDC_FINDLOG_EDIT, m_edLog);
	DDX_Text(pDX, IDC_FINDLOG_EDIT, m_strLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindLog, CDialog)
	//{{AFX_MSG_MAP(CFindLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFindLog message handlers

BOOL CFindLog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindLog::AddLogString(char *sz, BOOL fFirstSpace/*=TRUE*/)
{
	if (fFirstSpace)
		m_strLog += chSpace;
	m_strLog += sz;
}

void CFindLog::AddLogLine(char *sz, BOOL fFirstSpace/*=TRUE*/)
{
	AddLogString(sz, fFirstSpace);
	m_strLog += "\r\n";
}
void CFindLog::ResetLog()
{
	m_strLog.Empty();
}

