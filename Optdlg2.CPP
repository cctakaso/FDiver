/*    PortTool v2.2     optdlg2.cpp          */

//optdlg2.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
#include "optdlg2.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDlg2 ダイアログ

COptionDlg2::COptionDlg2(CWnd* pParent /*=NULL*/)
	: CChildDlg(COptionDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDlg2)
	m_optNum = -1;
	m_fNum = FALSE;
	m_iMaxLines = 0;
	m_fDefTagAuto = FALSE;
	//}}AFX_DATA_INIT
}


void COptionDlg2::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);
	if (!pDX->m_bSaveAndValidate)
		{
		m_fNum = m_optDispNum>0;
		m_optNum = m_optDispNum	-1;
		}
	//{{AFX_DATA_MAP(COptionDlg2)
	DDX_Control(pDX, IDC_OF_MAXLINES, m_edMaxLines);
	DDX_Check(pDX, IDC_OF_DISPDOC, m_fDispDoc);
	DDX_Check(pDX, IDC_OF_ATTR, m_fFile);
	DDX_Check(pDX, IDC_OF_DIR, m_fDir);
	DDX_Radio(pDX, IDC_OF_GYOUNUM, m_optNum);
	DDX_Check(pDX, IDC_OF_POSITION, m_fNum);
	DDX_Check(pDX, IDC_OF_DRAG_SERVER, m_fDragServer);
	DDX_Text(pDX, IDC_OF_MAXLINES, m_iMaxLines);
	DDV_MinMaxInt(pDX, m_iMaxLines, MIN_DSPLINES, MAX_DSPLINES);
	DDX_Check(pDX, IDC_DEFTAG_AUTO, m_fDefTagAuto);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate)
		{
		m_optDispNum = (m_fNum ? m_optNum+1:0);
		}
}

BEGIN_MESSAGE_MAP(COptionDlg2, CChildDlg)
	//{{AFX_MSG_MAP(COptionDlg2)
	ON_BN_CLICKED(IDC_OF_POSITION, OnClickedOfPosition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDlg2 メッセージハンドラ

BOOL COptionDlg2::OnInitDialog()
{
	CChildDlg::OnInitDialog();
	ShowWindow(SW_SHOW);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

/*************************************************************************
-- Routine: BOOL COptionDlg2::RetriveData(CFindOption *pFindOption)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CFindOption *pFindOption - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL COptionDlg2::RetrieveData(CFindOption *pFindOption)
{
	if (!CChildDlg::UpdateData(TRUE))
		return FALSE;
/*
	if (m_iMaxLines<MIN_DSPLINES || m_iMaxLines>MAX_DSPLINES)
		{
#ifdef WIN32
		Message(IDS_ERR_ENTRYVALUE_FORLIST32);
#else
		Message(IDS_ERR_ENTRYVALUE_FORLIST);
#endif //WIN32
		m_edMaxLines.SetSel(0,-1);
		m_edMaxLines.SetFocus();
		return FALSE;
		}
*/
	pFindOption->m_optDispNum = m_optDispNum;
	pFindOption->m_fDispDoc = m_fDispDoc;
	pFindOption->m_fFile = m_fFile;
	pFindOption->m_fDir = m_fDir;
	pFindOption->m_fDragServer = m_fDragServer;
	pFindOption->m_iMaxLines = m_iMaxLines;
	pFindOption->m_fDefTagAuto = m_fDefTagAuto;
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL COptionDlg2::UpdateData(CFindOption *pFindOption)
-- Description and Usage:
		データから、ダイアログ情報に反映させます。
-- Arguments:
		CFindOption *pFindOption - 実ﾃﾞｰﾀ
-- Returns:
		成功のときは TRUE を、失敗のときは FALSE を返します。
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL COptionDlg2::UpdateData(CFindOption *pFindOption)
{
	m_optDispNum = pFindOption->m_optDispNum;
	m_fDispDoc = pFindOption->m_fDispDoc;
	m_fFile = pFindOption->m_fFile;
	m_fDir = pFindOption->m_fDir;
	m_fDragServer = pFindOption->m_fDragServer;
	m_iMaxLines = pFindOption->m_iMaxLines;
	m_fDefTagAuto = pFindOption->m_fDefTagAuto;
	CChildDlg::UpdateData(FALSE);
	return TRUE;
}


void COptionDlg2::OnClickedOfPosition()
{
	CChildDlg::UpdateData(TRUE);
	GetDlgItem(IDC_OF_GYOUNUM)->EnableWindow(m_fNum);
	GetDlgItem(IDC_OF_BYTENUM)->EnableWindow(m_fNum);
	if (m_fNum)
		CheckRadioButton(IDC_OF_GYOUNUM, IDC_OF_BYTENUM, IDC_OF_GYOUNUM);
}
