// setpdlg2.cpp : implementation file
//

#include "stdafx.h"
#include "setpdlg2.h"
#include "..\mdfc\dfile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//IMPLEMENT_DYNAMIC(CSetPathDlgForScan, CSetPathDlg)

/////////////////////////////////////////////////////////////////////////////
// CSetPathDlgForScan dialog
BEGIN_MESSAGE_MAP(CSetPathDlgForScan, CSetPathDlg)
	//{{AFX_MSG_MAP(CSetPathDlgForScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSetPathDlgForScan::DoDataExchange(CDataExchange* pDX)
{
	CSetPathDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPathDlgForScan)
	//}}AFX_DATA_MAP
	if (!m_bWin4)
		DDX_Check(pDX, IDC_F_TITESEARCH, m_fTiteSearch);
}

/////////////////////////////////////////////////////////////////////////////
// CSetPathDlgForScan message handlers
CSetPathDlgForScan::CSetPathDlgForScan(char *szPath, int iTiteSearch): CSetPathDlg(szPath, CSetPathDlgForScan::IDD, CSetPathDlgForScan::IDCTITLE)
{
	m_iTiteSearch = iTiteSearch;
}


void CSetPathDlgForScan::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if (!m_bWin4 && m_fTiteSearch)
		{
		CString cstrTite;
		cstrTite.LoadString(IDS_TITESEARCH);
		m_strPaths = cstrTite.GetBuffer(0);
		m_idRtn = IDOK;
		//CFileDialog::OnOK();
		//PostMessage(WM_COMMAND, IDCANCEL, (LONG) TRUE);
		DefWindowProc(WM_COMMAND, IDCANCEL, (LONG) TRUE);
		//DestroyWindow();
		}
	else
		CSetPathDlg::OnOK();
	//CFileDialog::OnOK();
}

BOOL CSetPathDlgForScan::OnInitDialog() 
{
	CSetPathDlg::OnInitDialog();
	
	if (m_iTiteSearch>=0)
		m_fTiteSearch = m_iTiteSearch;
	else
		{
		m_fTiteSearch = FALSE;
		if (!m_bWin4)
			GetDlgItem(IDC_F_TITESEARCH)->EnableWindow(FALSE);
		}
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


