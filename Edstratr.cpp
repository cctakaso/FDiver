/*    PortTool v2.2     EDSTRATR.CPP          */

// edstrlis.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "edstratr.h"
#include "strindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_MYMESSAGE (WM_USER+1)

/////////////////////////////////////////////////////////////////////////////
// CEdStrAttr ダイアログ

CEdStrAttr::CEdStrAttr(CWnd* pParent /*=NULL*/):CEdStrList(FALSE, pParent)
{
	
	//{{AFX_DATA_INIT(CEdStrAttr)
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CEdStrAttr, CEdStrList)
	//{{AFX_MSG_MAP(CEdStrAttr)
	ON_BN_CLICKED(IDC_ESL_NEW, OnClickedEslNew)
	ON_BN_CLICKED(IDC_ESL_CHG, OnClickedEslChg)
	ON_BN_CLICKED(IDC_ESL_UP, OnClickedEslUp)
	ON_BN_CLICKED(IDC_ESL_DOWN, OnClickedEslDown)
	ON_CBN_SELCHANGE(IDC_ESL_LIST, OnSelchangeEslList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CEdStrAttr::UpdateData(CStringArray2 *paryStr, CStringArray2 *paryAtr, int *piSel)
{
	m_aryAtr = *paryAtr;
	ASSERT(paryStr->GetSize()==paryAtr->GetSize());
	return CEdStrList::UpdateData(paryStr, piSel);
}
BOOL CEdStrAttr::UpdateData(CString *pStrAttr)
{ //アトリビュートのみアップデート
	ASSERT(pStrAttr);
	ASSERT(m_iSel<m_aryStr.GetSize());
	m_aryAtr[m_iSel] = *pStrAttr;
	return TRUE;
}
BOOL CEdStrAttr::RetrieveData(CStringArray2 *paryStr, CStringArray2 *paryAtr, int *piSel)
{
	ASSERT(m_aryStr.GetSize()==m_aryAtr.GetSize());
	CEdStrList::RetrieveData(paryStr, piSel);
	ASSERT(paryAtr);
	*paryAtr = m_aryAtr;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEdStrAttr メッセージハンドラ


void CEdStrAttr::OnClickedEslNew()
{
	CChildDlg::UpdateData(TRUE);
	//切換前のデータの保持
	GetParent()->SendMessage(WM_MYMESSAGE, TRUE, 0L);
	CInputStrDlg InputDlg;
	InputDlg.SetInterface(m_iSel, &m_aryStr);
	if (InputDlg.DoModal())
		{
		m_iSel = InputDlg.GetIndex();
		if (m_iSel==m_aryStr.GetUpperBound())
			{//Add
			m_aryAtr.Add("");
			}
		else
			{//Insert
			m_aryAtr.InsertAt(m_iSel, "");
			}
		CChildDlg::UpdateData(FALSE);
		//新規エントリー切換後のデータの表示
		GetParent()->SendMessage(WM_MYMESSAGE, FALSE, 0L);
		}
	
}

void CEdStrAttr::OnClickedEslChg()
{
	CChildDlg::UpdateData(TRUE);
	//切換前のデータの保持
	GetParent()->SendMessage(WM_MYMESSAGE, TRUE, 0L);
	CInputStrDlgChg InputDlgChg;
	// CStringArray
	int iSize = m_aryStr.GetSize();
	InputDlgChg.SetInterface(m_iSel, &m_aryStr, m_fDontDelLastOne);
	if (InputDlgChg.DoModal())
		{
		if (m_aryStr.GetSize()<iSize)
			m_aryAtr.RemoveAt(m_iSel);
		m_iSel = InputDlgChg.GetIndex();
		CChildDlg::UpdateData(FALSE);
		//新規エントリー切換後のデータの表示
		GetParent()->SendMessage(WM_MYMESSAGE, FALSE, 0L);
		}
}

void CEdStrAttr::OnClickedEslUp()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
#ifdef NOTUSE	//MFC4.2では有効ではない
	if (!m_combStr.GetDroppedState())
		m_combStr.ShowDropDown(TRUE);
#endif
	CString cstr = m_aryStr[m_iSel];
	m_aryStr.RemoveAt(m_iSel);
	m_aryStr.InsertAt(m_iSel-1, cstr.GetBuffer(0));
	cstr = m_aryAtr[m_iSel];
	m_aryAtr.RemoveAt(m_iSel);
	m_aryAtr.InsertAt(--m_iSel, cstr.GetBuffer(0));
	CChildDlg::UpdateData(FALSE);
}

void CEdStrAttr::OnClickedEslDown()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
#ifdef NOTUSE	//MFC4.2では有効ではない
	if (!m_combStr.GetDroppedState())
		m_combStr.ShowDropDown(TRUE);
#endif
	CString cstr = m_aryStr[m_iSel];
	m_aryStr.RemoveAt(m_iSel);
	m_aryStr.InsertAt(m_iSel+1, cstr.GetBuffer(0));
	cstr = m_aryAtr[m_iSel];
	m_aryAtr.RemoveAt(m_iSel);
	m_aryAtr.InsertAt(++m_iSel, cstr.GetBuffer(0));
	CChildDlg::UpdateData(FALSE);
}

void CEdStrAttr::OnSelchangeEslList()
{
	//切換前のデータの保持
	GetParent()->SendMessage(WM_MYMESSAGE, TRUE, 0L);
//	CChildDlg::UpdateData(TRUE);
	//切換後のデータの表示
	GetParent()->SendMessage(WM_MYMESSAGE, FALSE, 0L);
}

