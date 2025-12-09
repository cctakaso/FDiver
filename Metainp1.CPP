/*    PortTool v2.2     metainp1.CPP          */
// metainp1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "fdiver.h"
#include "metastr.h"
#include "metainp1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg1 ダイアログ

CMetaInputDlg1::CMetaInputDlg1(CWnd* pParent /*=NULL*/)
	: CChildDlg(CMetaInputDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetaInputDlg1)
	m_pSubDlg = NULL;
	//}}AFX_DATA_INIT
}
CMetaInputDlg1::~CMetaInputDlg1()
{
	if (m_pSubDlg)
		delete m_pSubDlg;
}

void CMetaInputDlg1::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaInputDlg1)
	DDX_Control(pDX, IDC_F_STRING, m_edStr);
	DDX_Text(pDX, IDC_F_STRING, m_cstr);
	DDV_MaxChars(pDX, m_cstr, 256);
	DDX_Control(pDX, IDC_META_INPUT, m_btnReplaceSel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMetaInputDlg1, CChildDlg)
	//{{AFX_MSG_MAP(CMetaInputDlg1)
	ON_BN_CLICKED(IDC_META_INPUT, OnClickedInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMetaInputDlg1::OnInitDialog()
{
	CChildDlg::OnInitDialog();

	// サブダイアログの作成.
	if (m_pSubDlg)
		delete m_pSubDlg;
	m_pSubDlg = new CEdStrList2(this);
	// カレントアクティブサブダイアログのポインタセット

	// ベースになるダイアログの設定.
	// Create the actual CChildDlg controls offset by location
	// IDC_ANCHOR.
	m_pSubDlg->Create(IDC_ANCHOR);
	CString cstr;
	cstr.LoadString(IDS_META_TAB1);
	m_pSubDlg->Initialize(cstr.GetBuffer(0));

	ShowWindow(SW_SHOW);


	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

/*************************************************************************
-- Routine: BOOL CMetaInputDlg1::RetriveData(CString *pcstr, CMetaStringArray *pMetaStringArray)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CString *pcstr - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CMetaInputDlg1::RetrieveData(CString *pcstr, CMetaStringArray *pMetaStringArray)
{
	CChildDlg::UpdateData(TRUE);
	*pcstr = m_cstr;
	//m_pSubDlg->RetrieveData(pMetaStringArray);
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CMetaInputDlg1::UpdateData(CString *pcstr, CMetaStringArray *pMetaStringArray, BOOL fKeyEntryOnly=FALSE)
-- Description and Usage:
		データから、ダイアログ情報に反映させます。
-- Arguments:
		CString *pcstr - 実ﾃﾞｰﾀ
-- Returns:
		成功のときは TRUE を、失敗のときは FALSE を返します。
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CMetaInputDlg1::UpdateData(CString *pcstr, CMetaStringArray *pMetaStringArray, BOOL fKeyEntryOnly/*=FALSE*/)
{
	m_cstr = *pcstr;
	m_pSubDlg->UpdateData(pMetaStringArray);
	CChildDlg::UpdateData(FALSE);
	m_edStr.SetSel(0, -1);
	if (fKeyEntryOnly)
		{
		m_edStr.EnableWindow(FALSE);
		m_edStr.ShowWindow(SW_HIDE);
		m_btnReplaceSel.EnableWindow(FALSE);
		m_btnReplaceSel.ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_F_STRING_STATIC)->EnableWindow(FALSE);
		//SetDlgItemText(IDC_F_STRING_STATIC, "");
		}
	return TRUE;
}

void CMetaInputDlg1::OnClickedInput()
{
	CMetaStringArray *pMetaStringArray;
	CString cstr;
	int iSel;
	m_pSubDlg->RetrieveData(pMetaStringArray, &iSel);
	if (iSel>=0)
		{
		cstr = pMetaStringArray->PGetMetaString(iSel)->GetStrForTitle();
		m_edStr.ReplaceSel(cstr.GetBuffer(0));
		m_edStr.SetSel(0, -1);
		m_edStr.SetFocus();
		}
}
