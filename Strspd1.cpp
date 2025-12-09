/*    PortTool v2.2     strspd1.cpp          */

// strspd1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
//#include "fdiver.h"
#include "strspd1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg1 ダイアログ

CStrSpecDlg1::CStrSpecDlg1(CWnd* pParent /*=NULL*/)
	: CChildDlg(CStrSpecDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrSpecDlg1)
	AttrDataIni(&m_attrData);
	//}}AFX_DATA_INIT
}

CStrSpecDlg1::CStrSpecDlg1(UINT id, CWnd* pParent)
	: CChildDlg(id, pParent)
{
	//{{AFX_DATA_INIT(CStrSpecDlg1)
	AttrDataIni(&m_attrData);
	//}}AFX_DATA_INIT
}

void CStrSpecDlg1::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrSpecDlg1)
	DDX_Check(pDX, IDC_FS_IGN_CASE, m_attrData.m_fCase);
	DDX_Check(pDX, IDC_FS_IGNO_BYTES, m_attrData.m_fBytes);
	DDX_Check(pDX, IDC_FS_IGNO_KATA, m_attrData.m_fKata);
//	DDX_Check(pDX, IDC_FS_IGNO_UMURA, m_attrData.m_fUmura);
	DDX_Check(pDX, IDC_FS_IGNO_UMURA, m_attrData.m_fMatchWholeWord);
	DDX_Check(pDX, IDC_FS_NO_SPACE, m_attrData.m_fSpace);
	DDX_Check(pDX, IDC_FS_NO_TAB, m_attrData.m_fTab);
	DDX_Check(pDX, IDC_FS_NO_LF, m_attrData.m_fLF);
	DDX_Check(pDX, IDC_FS_NO_NOBRAK, m_attrData.m_fNoBreak);
	DDX_Text(pDX, IDC_FS_NO_OTHER_ED, m_attrData.m_strOthers);
	DDV_MaxChars(pDX, m_attrData.m_strOthers, 200);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStrSpecDlg1, CChildDlg)
	//{{AFX_MSG_MAP(CStrSpecDlg1)
	ON_EN_UPDATE(IDC_FS_NO_OTHER_ED, OnUpdateFsNoOtherEd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg1 メッセージハンドラ

BOOL CStrSpecDlg1::OnInitDialog()
{
	CChildDlg::OnInitDialog();
	ShowWindow(SW_SHOW);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

/*************************************************************************
-- Routine: BOOL CStrSpecDlg1::RetriveData(CString *pStrAttr)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CString *pStrAttr - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CStrSpecDlg1::RetrieveData(CString *pStrAttr)
{
	CChildDlg::UpdateData(TRUE);
#ifdef _DBCS
	m_attrData.m_chPrefix = STRSPEC_ATTR_PREF_DBCS;
#else	
	m_attrData.m_chPrefix = STRSPEC_ATTR_PREF_SBCS;
#endif
	AttrDataRetrive(pStrAttr, &m_attrData);
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CStrSpecDlg1::UpdateData(CString *pStrAttr)
-- Description and Usage:
		データから、ダイアログ情報に反映させます。
-- Arguments:
		CString *pStrAttr - 実ﾃﾞｰﾀ
-- Returns:
		成功のときは TRUE を、失敗のときは FALSE を返します。
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CStrSpecDlg1::UpdateData(CString *pStrAttr)
{
	AttrDataUpdate(pStrAttr, &m_attrData);
	CChildDlg::UpdateData(FALSE);
	return TRUE;
}


void CStrSpecDlg1::OnUpdateFsNoOtherEd()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
	
}
