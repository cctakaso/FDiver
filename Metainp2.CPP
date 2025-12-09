/*    PortTool v2.2     metainp2.CPP          */

// metainp2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "fdiver.h"
#include "metainp2.h"
#include "findopti.h"
extern CFindOption *vpFindOption;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg2 ダイアログ

CMetaInputDlg2::CMetaInputDlg2(CWnd* pParent /*=NULL*/)
	: CChildDlg(CMetaInputDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetaInputDlg2)
	m_cstr = "";
	m_fInput = FALSE;
	//}}AFX_DATA_INIT
}

void CMetaInputDlg2::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaInputDlg2)
	DDX_Control(pDX, IDC_F_STRING, m_edStr);
	DDX_Text(pDX, IDC_F_STRING, m_cstr);
	DDV_MaxChars(pDX, m_cstr, 256);
	DDX_Check(pDX, IDC_META_INPUT, m_fInput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMetaInputDlg2, CChildDlg)
	//{{AFX_MSG_MAP(CMetaInputDlg2)
	ON_BN_CLICKED(IDC_META_INPUT, OnClickedMetaInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMetaInputDlg2::OnInitDialog()
{
	CChildDlg::OnInitDialog();

	ShowWindow(SW_SHOW);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

/*************************************************************************
-- Routine: BOOL CMetaInputDlg2::RetriveData(CString *pcstr)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CString *pcstr - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CMetaInputDlg2::RetrieveData(CString *pcstr)
{
	CChildDlg::UpdateData(TRUE);
	*pcstr = m_cstr;
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CMetaInputDlg2::UpdateData(CString *pcstr)
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
BOOL CMetaInputDlg2::UpdateData(CString *pcstr)
{
	m_cstr = *pcstr;
	CChildDlg::UpdateData(FALSE);
	m_edStr.SetSel(0, -1);
	m_edStr.SetFocus();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg2 メッセージハンドラ

BOOL CMetaInputDlg2::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
//resource.hの以下のIDは順列でなければならない
//IDS_META_MATCHANYに続く文字列リソースＩＤ
//IDC_META_MATCHANYに続くEditCtrリソースＩＤ

/*    PortTool v2.2     1995/10/16    8:3          */
/*      Found   : HIWORD          */
/*      Issue   : HIWORD で扱う値が１６ビットなのか、３２ビットなのかチェックして下さい          */
#ifdef WIN16_32
	if (DGetWmCommandCmd(wParam, lParam)==BN_CLICKED)
#else
	if (HIWORD(lParam)==BN_CLICKED)
#endif
		{
		if (wParam>=IDC_META_MATCHANY && wParam<=IDC_META_SXOR)
			{
			CChildDlg::UpdateData(TRUE);
			CString cstr;
			cstr.LoadString(IDS_META_MATCHANY+wParam-IDC_META_MATCHANY);
			ASSERT(!cstr.IsEmpty());
			SetDlgItemText(IDC_META_INFO, cstr.GetBuffer(0));
			if (m_fInput)
				{
				CString cstr;
				if (wParam == IDC_META_AND || wParam == IDC_META_OR || wParam == IDC_META_NOT ||
					wParam == IDC_META_XOR || wParam == IDC_META_BLOCK_L || wParam == IDC_META_BLOCK_R)
					{
					cstr = ' ';
					cstr += vpFindOption->m_metaChars.m_metaCharsData.str[wParam-IDC_META_MATCHANY].GetBuffer(0);
					cstr += ' ';
					}
				else
					cstr += vpFindOption->m_metaChars.m_metaCharsData.str[wParam-IDC_META_MATCHANY].GetBuffer(0);
				m_edStr.ReplaceSel(cstr.GetBuffer(0));
				}
			m_edStr.SetFocus();
			return TRUE;
			}
		}
	return CChildDlg::OnCommand(wParam, lParam);
}


void CMetaInputDlg2::OnClickedMetaInput()
{
	int nSt, nEn;
	CChildDlg::UpdateData(TRUE);	
	m_edStr.GetSel(nSt, nEn);
	if (nSt==0 && m_cstr.GetLength()==nEn) //全て選択中
		{
		m_edStr.SetSel(nEn, nEn);
		}
	m_edStr.SetFocus();
}
