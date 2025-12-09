/*    PortTool v2.2     EDSTRLI2.CPP          */

// edstrli2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "edstrli2.h"
#include "strindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdStrList2 ダイアログ

CEdStrList2::CEdStrList2(CWnd* pParent /*=NULL*/)
	: CChildDlg(CEdStrList2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEdStrList2)
	m_iSel = -1;
	m_pMetaStringArray = NULL;
	//}}AFX_DATA_INIT
}

void CEdStrList2::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);

	if (!pDX->m_bSaveAndValidate && ::IsWindow(m_combStr.GetSafeHwnd()))
		{ //CMetaStringArray
		m_combStr.ResetContent();
		if (m_pMetaStringArray)
			{
			for (int i=0; i<m_pMetaStringArray->GetSize(); i++)
				m_combStr.AddString(m_pMetaStringArray->PGetMetaString(i)->GetStrForLst().GetBuffer(0));
			}
		//m_btnChg.EnableWindow(m_iSel>= 0);
		}

	//{{AFX_DATA_MAP(CEdStrList2)
	DDX_Control(pDX, IDC_ESL_LIST, m_combStr);
	DDX_Control(pDX, IDC_ESL_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_ESL_UP, m_btnUp);
	DDX_Control(pDX, IDC_ESL_CHG, m_btnChg);
	DDX_LBIndex(pDX, IDC_ESL_LIST, m_iSel);
	//}}AFX_DATA_MAP

	m_btnChg.EnableWindow(m_iSel>=0);
	m_btnUp.EnableWindow(m_iSel>0);
	m_btnDown.EnableWindow(m_pMetaStringArray && m_iSel < m_pMetaStringArray->GetUpperBound());
}

BEGIN_MESSAGE_MAP(CEdStrList2, CChildDlg)
	//{{AFX_MSG_MAP(CEdStrList2)
	ON_BN_CLICKED(IDC_ESL_NEW, OnClickedEslNew)
	ON_BN_CLICKED(IDC_ESL_CHG, OnClickedEslChg)
	ON_BN_CLICKED(IDC_ESL_UP, OnClickedEslUp)
	ON_BN_CLICKED(IDC_ESL_DOWN, OnClickedEslDown)
	ON_LBN_SELCHANGE(IDC_ESL_LIST, OnSelchangeEslList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEdStrList2::Initialize(char *szTitle, BOOL fDontDelLastOne/*=FALSE*/)
{
	SetDlgItemText(IDC_ESL_NAME, szTitle);
	m_fDontDelLastOne = fDontDelLastOne;
}

BOOL CEdStrList2::UpdateData(CMetaStringArray *pMetaStringArray, int *piSel)
{
	if (piSel)
		m_iSel = *piSel;
	m_pMetaStringArray = pMetaStringArray;
	if (m_iSel==-1 && m_pMetaStringArray->GetSize()>0)
		m_iSel = 0;
	else if (m_iSel>m_pMetaStringArray->GetUpperBound())
		m_iSel = m_pMetaStringArray->GetUpperBound();
	return CChildDlg::UpdateData(FALSE);
}
BOOL CEdStrList2::RetrieveData(CMetaStringArray *&pMetaStringArray, int *piSel)
{
	CChildDlg::UpdateData(TRUE);
	pMetaStringArray = m_pMetaStringArray; //Pointerを取得する
	if (piSel)
		*piSel = m_iSel;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEdStrList2 メッセージハンドラ

BOOL CEdStrList2::OnInitDialog()
{
	CChildDlg::OnInitDialog();
	
	// TODO: この位置にその他の初期化用コードを追加してください。
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CEdStrList2::OnClickedEslNew()
{
	CInputStrDlg2 InputDlg2;
	CChildDlg::UpdateData(TRUE);
	// CMetaStringArray
	InputDlg2.SetInterface(m_iSel, m_pMetaStringArray);
	if (InputDlg2.DoModal())
		{
		m_iSel = InputDlg2.GetIndex();
		CChildDlg::UpdateData(FALSE);
		//Redraw All window
		InvalidateRect(NULL, FALSE);
		}
	
}

void CEdStrList2::OnClickedEslChg()
{
	CInputStrDlgChg2 InputDlgChg2;
	CChildDlg::UpdateData(TRUE);
	// CMetaStringArray
	InputDlgChg2.SetInterface(m_iSel, m_pMetaStringArray, m_fDontDelLastOne);
	if (InputDlgChg2.DoModal())
		{
		m_iSel = InputDlgChg2.GetIndex();
		CChildDlg::UpdateData(FALSE);
		//Redraw All window
		InvalidateRect(NULL, FALSE);
		}
	
}

void CEdStrList2::OnClickedEslUp()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
#ifdef NOTUSE	//MFC4.2では有効ではない
#ifdef COMBO
	if (!m_combStr.GetDroppedState())
		m_combStr.ShowDropDown(TRUE);
#endif//COMBO
#endif
	CMetaString *pMetaString = m_pMetaStringArray->PGetMetaString(m_iSel);
	m_pMetaStringArray->RemoveAt(m_iSel);
	m_pMetaStringArray->InsertAt(--m_iSel, pMetaString);
	CChildDlg::UpdateData(FALSE);
}

void CEdStrList2::OnClickedEslDown()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
#ifdef NOTUSE	//MFC4.2では有効ではない
#ifdef COMBO
	if (!m_combStr.GetDroppedState())
		m_combStr.ShowDropDown(TRUE);
#endif //COMBO
#endif
	CMetaString *pMetaString = m_pMetaStringArray->PGetMetaString(m_iSel);
	m_pMetaStringArray->RemoveAt(m_iSel);
	m_pMetaStringArray->InsertAt(++m_iSel, pMetaString);
	CChildDlg::UpdateData(FALSE);
}

void CEdStrList2::OnSelchangeEslList()
{
	CChildDlg::UpdateData(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlg2 ダイアログ

CInputStrDlg2::CInputStrDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputStrDlg2)
	m_cStrInput = "";
	m_cStrInput2 = "";
	//}}AFX_DATA_INIT
}

void CInputStrDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputStrDlg2)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_OF_STRFILE_BTN, m_btn2);
	DDX_Text(pDX, IDC_OF_STRFILE, m_cStrInput);
	DDX_Text(pDX, IDC_OF_STRFILE2, m_cStrInput2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputStrDlg2, CDialog)
	//{{AFX_MSG_MAP(CInputStrDlg2)
	ON_BN_CLICKED(IDC_OF_STRFILE_BTN, OnClickedOfStrfileBtn)
	ON_EN_UPDATE(IDC_OF_STRFILE, OnUpdateOfStrfile)
	//ON_EN_UPDATE(IDC_OF_STRFILE2, OnUpdateOfStrfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlg2 メッセージハンドラ

BOOL CInputStrDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	m_btnOk.EnableWindow(FALSE);
	m_btn2.EnableWindow(FALSE);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CInputStrDlg2::OnClickedOfStrfileBtn()
{
	UpdateData(TRUE);
	if ( (!m_cStrInput.IsEmpty() && m_pMetaStringArray->FValidNewTitle(m_cStrInput.GetBuffer(0), TRUE))&&
		 (m_pMetaStringArray->FValidKeyLogic(m_cStrInput2.GetBuffer(0)) ) )
		{
		CMetaString *pMetaString = new CMetaString;
		if (!pMetaString)
			{
			ASSERT(FALSE);
			return;
			}
		pMetaString->m_strTitle = m_cStrInput;
		pMetaString->m_strKey = m_cStrInput2;
		m_pMetaStringArray->InsertAt(m_iSel, pMetaString);
		EndDialog(TRUE);
		}
}

void CInputStrDlg2::OnOK()
{
	UpdateData(TRUE);
	if ( (!m_cStrInput.IsEmpty() && m_pMetaStringArray->FValidNewTitle(m_cStrInput.GetBuffer(0), TRUE))&&
		 (m_pMetaStringArray->FValidKeyLogic(m_cStrInput2.GetBuffer(0)) ) )
		{
		CMetaString *pMetaString = new CMetaString;
		if (!pMetaString)
			{
			ASSERT(FALSE);
			return;
			}
		pMetaString->m_strTitle = m_cStrInput;
		pMetaString->m_strKey = m_cStrInput2;
		m_pMetaStringArray->Add(pMetaString);
		m_iSel = m_pMetaStringArray->GetSize()-1;
		EndDialog(TRUE);
		}
}

void CInputStrDlg2::OnUpdateOfStrfile()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
	UpdateData(TRUE);
	m_btn2.EnableWindow(m_pMetaStringArray->GetSize()>0 && !m_cStrInput.IsEmpty() /*&& !m_cStrInput2.IsEmpty()*/);
	m_btnOk.EnableWindow(!m_cStrInput.IsEmpty()/* && !m_cStrInput2.IsEmpty()*/);
	UpdateData(FALSE);
}
void CInputStrDlg2::OnCancel()
{
	EndDialog(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlgChg2 ダイアログ

CInputStrDlgChg2::CInputStrDlgChg2(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputStrDlgChg2)
	m_cStrInput = "";
	m_cStrInput2 = "";
	//}}AFX_DATA_INIT
}

void CInputStrDlgChg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputStrDlgChg2)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_OF_STRFILE_BTN, m_btn2);
	DDX_Text(pDX, IDC_OF_STRFILE, m_cStrInput);
	DDX_Text(pDX, IDC_OF_STRFILE2, m_cStrInput2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputStrDlgChg2, CDialog)
	//{{AFX_MSG_MAP(CInputStrDlgChg2)
	ON_BN_CLICKED(IDC_OF_STRFILE_BTN, OnClickedOfStrfileBtn)
	ON_EN_UPDATE(IDC_OF_STRFILE, OnUpdateOfStrfile)
	//ON_EN_UPDATE(IDC_OF_STRFILE2, OnUpdateOfStrfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputStrDlgChg2 メッセージハンドラ

BOOL CInputStrDlgChg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	m_cStrInput = m_pMetaStringArray->PGetMetaString(m_iSel)->m_strTitle;
	m_cStrInput2 = m_pMetaStringArray->PGetMetaString(m_iSel)->m_strKey;
	UpdateData(FALSE);
	m_btn2.EnableWindow(!(m_fDontDelLastOne && m_pMetaStringArray->GetSize()==1));
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CInputStrDlgChg2::OnClickedOfStrfileBtn()
{
	UpdateData(TRUE);
	//CMetaStringArray
	if (m_fDontDelLastOne && m_pMetaStringArray->GetSize()==1)
		//AfxMessageBox("最後のエントリーを削除する事はできません。エントリーは少なくとも１つ以上必要です。");
		ASSERT(FALSE);
	else
		{
		delete m_pMetaStringArray->PGetMetaString(m_iSel);
		m_pMetaStringArray->RemoveAt(m_iSel);
		if (m_iSel >= m_pMetaStringArray->GetSize())
			m_iSel = m_pMetaStringArray->GetSize()-1;
		EndDialog(TRUE);
		}
}

void CInputStrDlgChg2::OnOK()
{
	// TODO: この位置にその他の検証用のコードを追加してください。
	UpdateData(TRUE);
	if ( (!m_cStrInput.IsEmpty() && m_pMetaStringArray->FValidNewTitle(m_cStrInput.GetBuffer(0), TRUE, m_iSel))&&
		 (m_pMetaStringArray->FValidKeyLogic(m_cStrInput2.GetBuffer(0)) ) )
		{
		m_pMetaStringArray->PGetMetaString(m_iSel)->m_strTitle = m_cStrInput;
		m_pMetaStringArray->PGetMetaString(m_iSel)->m_strKey = m_cStrInput2;
		EndDialog(TRUE);
		}
}


void CInputStrDlgChg2::OnUpdateOfStrfile()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
	UpdateData(TRUE);
	m_btnOk.EnableWindow(!m_cStrInput.IsEmpty() /*&& !m_cStrInput2.IsEmpty()*/);
	UpdateData(FALSE);
}

void CInputStrDlgChg2::OnCancel()
{
	EndDialog(FALSE);
}


