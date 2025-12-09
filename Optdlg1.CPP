/*    PortTool v2.2     optdlg1.cpp          */

//optdlg1.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
//#include "stdlib.h"
//#include "Fdiver.h"
#include "optdlg1.h"
#include "version.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDlg1 ダイアログ

COptionDlg1::COptionDlg1(CWnd* pParent /*=NULL*/)
	: CChildDlg(COptionDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDlg1)
	m_pSubDlg = NULL;
	//}}AFX_DATA_INIT
}

COptionDlg1::~COptionDlg1()
{
	if (m_pSubDlg)
		delete m_pSubDlg;
}

void COptionDlg1::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);

//	m_pSubDlg->DoDataExchange(pDX);
//	if (!pDX->m_bSaveAndValidate && ::IsWindow(m_combStrFiles.GetSafeHwnd()))
//		{ //CStringArray
//		m_combStrFiles.ResetContent();
//		for (int i=0; i<m_aryStrFiles.GetSize(); i++)
//			m_combStrFiles.AddString(m_aryStrFiles[i].GetBuffer(0));
//		m_btnChgStrFiles.EnableWindow(m_iStrFiles >= 0);
//		}
//	DDV_MinMaxLong(pDX, m_lReadSize, (MIN_READBUFSIZE/1024), (MAX_READBUFSIZE/1024));
//	DDV_MinMaxLong(pDX, m_lReadSize, 123, 1233);

	//{{AFX_DATA_MAP(COptionDlg1)
	DDX_Control(pDX, IDC_OF_READSIZE, m_ceReadSize);
	DDX_Text(pDX, IDC_OF_READSIZE, m_lReadSize);
//	DDV_MinMaxLong(pDX, m_lReadSize, 123, 1233);
	DDV_MinMaxLong(pDX, m_lReadSize, (MIN_READBUFSIZE/1024), (MAX_READBUFSIZE/1024));
	DDX_Check(pDX, IDC_OF_SOUND, m_fSound);
	DDX_Check(pDX, IDC_OF_TOPWIN, m_fToTopWin);
	DDX_Check(pDX, IDC_OF_ICON, m_fIcon);
	DDX_Check(pDX, IDC_OF_METAHELP, m_fMetaHelp);
	DDX_Check(pDX, IDC_OF_NOERRDSP, m_fNoErrDsp);
	DDX_Text(pDX, IDC_OF_EXTRA_FILESPEC, m_strExtraFileSpec);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionDlg1, CChildDlg)
	//{{AFX_MSG_MAP(COptionDlg1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDlg1 メッセージハンドラ

BOOL COptionDlg1::OnInitDialog()
{
	CChildDlg::OnInitDialog();

	if (m_pSubDlg)
		delete m_pSubDlg;
	// サブダイアログの作成.
	m_pSubDlg = new CEdStrList(FALSE, this);
	// カレントアクティブサブダイアログのポインタセット

	// ベースになるダイアログの設定.
	// Create the actual CChildDlg controls offset by location
	// IDC_ANCHOR.
	m_pSubDlg->Create(IDC_ANCHOR);
	CString cstr;
	cstr.LoadString(IDS_OPT_FILE_ENTRY);
	m_pSubDlg->Initialize(cstr.GetBuffer(0));

	ShowWindow(SW_SHOW);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}
/*************************************************************************
-- Routine: BOOL COptionDlg1::RetriveData(CFindOption *pFindOption)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CFindOption *pFindOption - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL COptionDlg1::RetrieveData(CFindOption *pFindOption)
{
	if (!CChildDlg::UpdateData(TRUE))
		return FALSE;
/*
	if(m_lReadSize < (MIN_READBUFSIZE/1024) || m_lReadSize > (MAX_READBUFSIZE/1024))
		{
#ifdef WIN32
		BeepMessage(IDS_OPT_READSIZE32);
#else
		BeepMessage(IDS_OPT_READSIZE);
#endif //WIN32
		m_ceReadSize.SetSel(0,-1);
		m_ceReadSize.SetFocus();
		return FALSE;
		}
	else
		m_lReadSize *= 1024;
*/
	m_lReadSize *= 1024;

	pFindOption->m_lReadSize = m_lReadSize;
	pFindOption->m_fSound = m_fSound;
	pFindOption->m_fToTopWin = m_fToTopWin;
	pFindOption->m_fIcon = m_fIcon;
	pFindOption->m_fMetaHelp = m_fMetaHelp;
	pFindOption->m_fNoErrDsp = m_fNoErrDsp;
//	pFindOption->m_aryStrFiles = m_aryStrFiles;
	vExtraFileSpec = m_strExtraFileSpec;
	m_pSubDlg->RetrieveData(&pFindOption->m_aryStrFiles);
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL COptionDlg1::UpdateData(CFindOption *pFindOption)
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
BOOL COptionDlg1::UpdateData(CFindOption *pFindOption)
{
	m_lReadSize = pFindOption->m_lReadSize/1024;
	m_fSound = pFindOption->m_fSound;
	m_fToTopWin = pFindOption->m_fToTopWin;
	m_fIcon = pFindOption->m_fIcon;
	m_fMetaHelp = pFindOption->m_fMetaHelp;
	m_fNoErrDsp = pFindOption->m_fNoErrDsp;
	m_pSubDlg->UpdateData(&pFindOption->m_aryStrFiles);
	m_strExtraFileSpec = vExtraFileSpec;
//	m_aryStrFiles = pFindOption->m_aryStrFiles;
//	if (m_iStrFiles==-1 && m_aryStrFiles.GetSize()>0)
//		m_iStrFiles = 0;
//	m_btnChgStrFiles.EnableWindow(m_iStrFiles>=0);
	CChildDlg::UpdateData(FALSE);
	return TRUE;
}

