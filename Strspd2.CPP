/*    PortTool v2.2     STRSPD2.CPP          */

// strspd2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
//#include "fdiver.h"
#include "strspd2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg2 ダイアログ

CStrSpecDlg2::CStrSpecDlg2(CWnd* pParent /*=NULL*/)
	: CStrSpecDlg1(CStrSpecDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrSpecDlg2)
	//}}AFX_DATA_INIT
}

void CStrSpecDlg2::DoDataExchange(CDataExchange* pDX)
{
	CStrSpecDlg1::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrSpecDlg2)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStrSpecDlg2, CStrSpecDlg1)
	//{{AFX_MSG_MAP(CStrSpecDlg2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg2 メッセージハンドラ


/*************************************************************************
-- Routine: BOOL CStrSpecDlg2::RetriveData(CString *pStrAttr)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CString *pStrAttr - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CStrSpecDlg2::RetrieveData(CString *pStrAttr)
{
	CChildDlg::UpdateData(TRUE);
	m_attrData.m_chPrefix = STRSPEC_ATTR_PREF_SBCS;
	AttrDataRetrive(pStrAttr, &m_attrData);
	return TRUE;
}
