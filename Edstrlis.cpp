/*    PortTool v2.2     EDSTRLIS.CPP          */

// edstrlis.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "edstrlis.h"
#include "strindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdStrList ダイアログ

CEdStrList::CEdStrList(BOOL bRef/*=FALSE*/, CWnd* pParent /*=NULL*/)
	: CChildDlg(CEdStrList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEdStrList)
	m_bRef = bRef;
	m_iSel = -1;
	//}}AFX_DATA_INIT
}

void CEdStrList::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);

	if (!pDX->m_bSaveAndValidate && ::IsWindow(m_combStr.GetSafeHwnd()))
		{ //CStringArray
		m_combStr.ResetContent();
		for (int i=0; i<m_aryStr.GetSize(); i++)
			m_combStr.AddString(m_aryStr[i].GetBuffer(0));
		//m_btnChg.EnableWindow(m_iSel>= 0);
		}

	//{{AFX_DATA_MAP(CEdStrList)
	DDX_Control(pDX, IDC_ESL_LIST, m_combStr);
	DDX_Control(pDX, IDC_ESL_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_ESL_UP, m_btnUp);
	DDX_Control(pDX, IDC_ESL_CHG, m_btnChg);
	DDX_CBIndex(pDX, IDC_ESL_LIST, m_iSel);
	//}}AFX_DATA_MAP

	m_btnChg.EnableWindow(m_iSel>=0);
	m_btnUp.EnableWindow(m_iSel>0);
	m_btnDown.EnableWindow(m_iSel < m_aryStr.GetUpperBound());
}

BEGIN_MESSAGE_MAP(CEdStrList, CChildDlg)
	//{{AFX_MSG_MAP(CEdStrList)
	ON_BN_CLICKED(IDC_ESL_NEW, OnClickedEslNew)
	ON_BN_CLICKED(IDC_ESL_CHG, OnClickedEslChg)
	ON_BN_CLICKED(IDC_ESL_UP, OnClickedEslUp)
	ON_BN_CLICKED(IDC_ESL_DOWN, OnClickedEslDown)
	ON_CBN_SELCHANGE(IDC_ESL_LIST, OnSelchangeEslList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEdStrList::Initialize(char *szTitle, BOOL fDontDelLastOne/*=FALSE*/)
{
	SetDlgItemText(IDC_ESL_NAME, szTitle);
	m_fDontDelLastOne = fDontDelLastOne;
}

BOOL CEdStrList::UpdateData(CStringArray2 *paryStr, int *piSel)
{
	if (piSel)
		m_iSel = *piSel;
	m_aryStr = *paryStr;
	if (m_iSel==-1 && m_aryStr.GetSize()>0)
		m_iSel = 0;
	else if (m_iSel>m_aryStr.GetUpperBound())
		m_iSel = m_aryStr.GetUpperBound();
	return CChildDlg::UpdateData(FALSE);
}
BOOL CEdStrList::RetrieveData(CStringArray2 *paryStr, int *piSel)
{
	CChildDlg::UpdateData(TRUE);
	ASSERT(paryStr);
	*paryStr = m_aryStr;
	if (piSel)
		*piSel = m_iSel;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEdStrList メッセージハンドラ

BOOL CEdStrList::OnInitDialog()
{
	CChildDlg::OnInitDialog();
	
	// TODO: この位置にその他の初期化用コードを追加してください。
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CEdStrList::OnClickedEslNew()
{
	CInputStrDlg InputDlg(m_bRef);
	CChildDlg::UpdateData(TRUE);
	// CStringArray
	InputDlg.SetInterface(m_iSel, &m_aryStr);
	if (InputDlg.DoModal())
		{
		m_iSel = InputDlg.GetIndex();
		CChildDlg::UpdateData(FALSE);
		}
	
}

void CEdStrList::OnClickedEslChg()
{
	CInputStrDlgChg InputDlgChg(m_bRef);
	CChildDlg::UpdateData(TRUE);
	// CStringArray
	InputDlgChg.SetInterface(m_iSel, &m_aryStr, m_fDontDelLastOne);
	if (InputDlgChg.DoModal())
		{
		m_iSel = InputDlgChg.GetIndex();
		CChildDlg::UpdateData(FALSE);
		}
	
}

void CEdStrList::OnClickedEslUp()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
#ifdef NOTUSE	//MFC4.2では有効ではない
	if (!m_combStr.GetDroppedState())
		m_combStr.ShowDropDown(TRUE);
#endif
	CString cstr = m_aryStr[m_iSel];
	m_aryStr.RemoveAt(m_iSel);
	m_aryStr.InsertAt(--m_iSel, cstr.GetBuffer(0));
	CChildDlg::UpdateData(FALSE);
}

void CEdStrList::OnClickedEslDown()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
#ifdef NOTUSE	//MFC4.2では有効ではない
	if (!m_combStr.GetDroppedState())
		m_combStr.ShowDropDown(TRUE);
#endif
	CString cstr = m_aryStr[m_iSel];
	m_aryStr.RemoveAt(m_iSel);
	m_aryStr.InsertAt(++m_iSel, cstr.GetBuffer(0));
	CChildDlg::UpdateData(FALSE);
}

#define WM_MYMESSAGE (WM_USER+1)

void CEdStrList::OnSelchangeEslList()
{
	GetParent()->SendMessage(WM_MYMESSAGE, TRUE, 0L);		//Retrive Data
	CChildDlg::UpdateData(TRUE);
	GetParent()->SendMessage(WM_MYMESSAGE, FALSE, 0L);
}

