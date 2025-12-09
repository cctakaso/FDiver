/*    PortTool v2.2     strindlg.cpp          */

// strInDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "fdiver.h"
#include "strInDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlg ダイアログ

CInputStrDlg::CInputStrDlg(BOOL bRef/*=FALSE*/, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputStrDlg)
	m_bRef = bRef;
	m_cStrInput = "";
	//}}AFX_DATA_INIT
}

void CInputStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputStrDlg)
	DDX_Control(pDX, IDC_REF_BTN, m_btnRef);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_OF_STRFILE_BTN, m_btn2);
	DDX_Text(pDX, IDC_OF_STRFILE, m_cStrInput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputStrDlg, CDialog)
	//{{AFX_MSG_MAP(CInputStrDlg)
	ON_BN_CLICKED(IDC_OF_STRFILE_BTN, OnClickedOfStrfileBtn)
	ON_EN_UPDATE(IDC_OF_STRFILE, OnUpdateOfStrfile)
	ON_BN_CLICKED(IDC_REF_BTN, OnRefBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlg メッセージハンドラ

BOOL CInputStrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	m_btnOk.EnableWindow(FALSE);
	m_btn2.EnableWindow(FALSE);
	m_btnRef.ShowWindow(m_bRef ? SW_SHOW:SW_HIDE);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CInputStrDlg::OnClickedOfStrfileBtn()
{
	UpdateData(TRUE);
	if (!m_cStrInput.IsEmpty())
		m_paryStr->InsertAt(m_iSel, m_cStrInput.GetBuffer(0));
	EndDialog(TRUE);
}

void CInputStrDlg::OnOK()
{
	UpdateData(TRUE);
	if (!m_cStrInput.IsEmpty())
		m_paryStr->Add(m_cStrInput.GetBuffer(0));
	m_iSel = m_paryStr->GetSize()-1;
	EndDialog(TRUE);
}

void CInputStrDlg::OnUpdateOfStrfile()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
	UpdateData(TRUE);
	m_btnOk.EnableWindow(!m_cStrInput.IsEmpty());
	m_btn2.EnableWindow(m_paryStr->GetSize()>0 && !m_cStrInput.IsEmpty());
	UpdateData(FALSE);
}
void CInputStrDlg::OnCancel()
{
	EndDialog(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlgChg ダイアログ

CInputStrDlgChg::CInputStrDlgChg(BOOL bRef/*=FALSE*/, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputStrDlgChg)
	m_bRef = bRef;
	m_cStrInput = "";
	//}}AFX_DATA_INIT
}

void CInputStrDlgChg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputStrDlgChg)
	DDX_Control(pDX, IDC_REF_BTN, m_btnRef);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_OF_STRFILE_BTN, m_btn2);
	DDX_Text(pDX, IDC_OF_STRFILE, m_cStrInput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputStrDlgChg, CDialog)
	//{{AFX_MSG_MAP(CInputStrDlgChg)
	ON_EN_UPDATE(IDC_OF_STRFILE, OnUpdateOfStrfile)
	ON_BN_CLICKED(IDC_OF_STRFILE_BTN, OnClickedOfStrfileBtn)
	ON_BN_CLICKED(IDC_REF_BTN, OnRefBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlgChg メッセージハンドラ

BOOL CInputStrDlgChg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	m_cStrInput = m_paryStr->GetAt(m_iSel);
	UpdateData(FALSE);
	m_btn2.EnableWindow(!(m_fDontDelLastOne && m_paryStr->GetSize()==1));
	m_btnRef.ShowWindow(m_bRef ? SW_SHOW:SW_HIDE);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CInputStrDlgChg::OnClickedOfStrfileBtn()
{
	UpdateData(TRUE);
	//CStringArray
	if (m_fDontDelLastOne && m_paryStr->GetSize()==1)
		//AfxMessageBox("最後のエントリーを削除する事はできません。エントリーは少なくとも１つ以上必要です。");
		ASSERT(FALSE);
	else
		{
		m_paryStr->RemoveAt(m_iSel);
		if (m_iSel >= m_paryStr->GetSize())
			m_iSel = m_paryStr->GetSize()-1;
		EndDialog(TRUE);
		}
}

void CInputStrDlgChg::OnOK()
{
	// TODO: この位置にその他の検証用のコードを追加してください。
	UpdateData(TRUE);
	if (!m_cStrInput.IsEmpty())
		m_paryStr->SetAt(m_iSel, m_cStrInput.GetBuffer(0));
	EndDialog(TRUE);
}


void CInputStrDlgChg::OnUpdateOfStrfile()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
	UpdateData(TRUE);
	m_btnOk.EnableWindow(!m_cStrInput.IsEmpty());
	UpdateData(FALSE);
}

void CInputStrDlgChg::OnCancel()
{
	EndDialog(FALSE);
}


void CInputStrDlgChg::OnRefBtn() 
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください
	CFileDialog dlg(TRUE, _T("exe"), m_cStrInput, //NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("ｱﾌﾟﾘｹｰｼｮﾝ (*.exe)|*.exe|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
		{
		m_cStrInput = dlg.GetPathName(); 
		UpdateData(FALSE);
		OnUpdateOfStrfile();
		}
}

void CInputStrDlg::OnRefBtn() 
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください
	CFileDialog dlg(TRUE, _T("exe"), m_cStrInput, //NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("ｱﾌﾟﾘｹｰｼｮﾝ (*.exe)|*.exe|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
		{
		m_cStrInput = dlg.GetPathName(); 
		UpdateData(FALSE);
		OnUpdateOfStrfile();
		}
}
