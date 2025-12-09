/*    PortTool v2.2     EXTENSIO.CPP          */

//optdlg1.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
//#include "stdlib.h"
//#include "Fdiver.h"
#include "extensio.h"
//#include "strindlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtensionsDlg ダイアログ

CExtensionsDlg::CExtensionsDlg(CWnd* pParent /*=NULL*/)
	: CChildDlg(CExtensionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtensionsDlg)
	m_strEditer = _T("");
	m_bCRIsNewLine = FALSE;
	//}}AFX_DATA_INIT
}

CExtensionsDlg::~CExtensionsDlg()
{
	if (m_pSubDlg)
		delete m_pSubDlg;
	if (m_pSubDlgRef)
		delete m_pSubDlgRef;
}

void CExtensionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);

//	m_pSubDlg->DoDataExchange(pDX);
//	if (!pDX->m_bSaveAndValidate && ::IsWindow(m_combStrFiles.GetSafeHwnd()))
//		{ //CStringArray
//		m_combStrFiles.ResetContent();
//		for (int i=0; i<m_aryStrExtnsions.GetSize(); i++)
//			m_combStrFiles.AddString(m_aryStrExtnsions[i].GetBuffer(0));
//		m_btnChgStrFiles.EnableWindow(m_iStrFiles >= 0);
//		}

	//{{AFX_DATA_MAP(CExtensionsDlg)
	DDX_Control(pDX, IDC_REF_BTN, m_btnEditer);
	DDX_Control(pDX, IDC_EDITER, m_edEditer);
	DDX_Text(pDX, IDC_EDITER, m_strEditer);
	DDX_Check(pDX, IDC_CHKCR_EDITER, m_bCRIsNewLine);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtensionsDlg, CChildDlg)
	//{{AFX_MSG_MAP(CExtensionsDlg)
	ON_BN_CLICKED(IDC_REF_BTN, OnEditerBtn)
	ON_EN_CHANGE(IDC_EDITER, OnChangeEditer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtensionsDlg メッセージハンドラ

BOOL CExtensionsDlg::OnInitDialog()
{
	CChildDlg::OnInitDialog();

	// サブダイアログの作成.
	m_pSubDlg = new CEdStrList(FALSE, this);
	m_pSubDlgRef = new CEdStrList(TRUE, this);
	// カレントアクティブサブダイアログのポインタセット

	// ベースになるダイアログの設定.
	// Create the actual CChildDlg controls offset by location
	// IDC_ANCHOR.
	CString cstr;
	m_pSubDlg->Create(IDC_ANCHOR);
	cstr.LoadString(IDS_EXECUTE);
	m_pSubDlg->Initialize(cstr.GetBuffer(0));

	m_pSubDlgRef->Create(IDC_ANCHOR2);
	cstr.LoadString(IDS_KICK_APPS);
	m_pSubDlgRef->Initialize(cstr.GetBuffer(0));

	ShowWindow(SW_SHOW);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}
/*************************************************************************
-- Routine: BOOL CExtensionsDlg::RetriveData(CFindOption *pFindOption)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CFindOption *pFindOption - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CExtensionsDlg::RetrieveData(CFindOption *pFindOption)
{
	CChildDlg::UpdateData(TRUE);
	m_pSubDlg->RetrieveData(&pFindOption->m_aryStrExtnsions);
	m_pSubDlgRef->RetrieveData(&pFindOption->m_aryStrKickApps);
	pFindOption->m_strEditer = m_strEditer;
	pFindOption->m_bCRIsNewLine = m_bCRIsNewLine;
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CExtensionsDlg::UpdateData(CFindOption *pFindOption)
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
BOOL CExtensionsDlg::UpdateData(CFindOption *pFindOption)
{
	m_pSubDlg->UpdateData(&pFindOption->m_aryStrExtnsions);
	m_pSubDlgRef->UpdateData(&pFindOption->m_aryStrKickApps);
	m_strEditer = pFindOption->m_strEditer;
	m_bCRIsNewLine = pFindOption->m_bCRIsNewLine;
	CChildDlg::UpdateData(FALSE);
	return TRUE;
}


void CExtensionsDlg::OnEditerBtn() 
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください
	CFileDialog dlg(TRUE, _T("exe"), m_strEditer, //NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("ｱﾌﾟﾘｹｰｼｮﾝ (*.exe)|*.exe|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
		{
		m_strEditer = dlg.GetPathName(); 
		}
	CChildDlg::UpdateData(FALSE);
}

void CExtensionsDlg::OnChangeEditer() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで EM_SETEVENTMASK
	// メッセージをコントロールへ送るために CChildDlg::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CChildDlg::UpdateData(TRUE);
	CString str;
	str = m_strEditer;
	str.MakeUpper();
	m_bCRIsNewLine = (str.FindOneOf(_T("HIDEMARU"))>=0);
	CChildDlg::UpdateData(FALSE);
}
