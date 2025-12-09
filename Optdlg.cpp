/*    PortTool v2.2     optdlg.cpp          */

// optdlg.cpp : インプリメンテーション ファイル
//
//#include "childdlg.h"
//#include "string.h"
//#include "cwjtbl.h"

#include "stdafx.h"

#include "optdlg.h"
#include "optdlg1.h"
#include "optdlg2.h"
//#include "optdlg3.h"
#include "findlist.h"
#include "lstent.h"
#include "metachad.h"
#include "extensio.h"
#include "filetrad.h"
extern CFindList *vpFindList;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COptionDlg ダイアログ

//////////////////////////////////////////////////////////////////////////////
// コンストラクタ															 
//////////////////////////////////////////////////////////////////////////////
COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/):CParentDlg(COptionDlg::IDD, pParent)
{
	m_pFindOption = new CFindOption;
	ASSERT(m_pFindOption);
}


COptionDlg::~COptionDlg()
{
	if (m_pFindOption)
		delete m_pFindOption;
}



/////////////////////////////////////////////////////////////////////////////
// COptionDlg メッセージハンドラ
// 各タグの中にあるボタンを押しても、ここのメッセージマップに来る.
BEGIN_MESSAGE_MAP(COptionDlg, CParentDlg)
	//{{AFX_MSG_MAP(COptionDlg)

/*    PortTool v2.2     1995/10/16    8:8          */
/*      Found   : WM_VSCROLL          */
/*      Issue   : wParam/lParam の取り扱いに注意。詳細についてはテクニカルリファレンスをご覧下さい。          */
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// 初期設定
void COptionDlg::Initialize(CFindOption *pFindOption)
{
	ASSERT(pFindOption);
	m_pFindOptionOrg = pFindOption;
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDlg)
	//}}AFX_DATA_MAP
}

//***************************************************************
// Function :COptionDlg::OnInitDialog()
// 
// Purpose:
// 		1) Initialize the main dialog box.
//		2) Fill the selection listbox.
//		3) Initialize the m_Setdic structure and
//		   Create the first ChildDlg.
//***************************************************************
BOOL COptionDlg::OnInitDialog()
{
	// ｵﾘｼﾞﾅﾙから実ﾃﾞｰﾀへのｱｯﾌﾟﾃﾞｰﾄ
	*m_pFindOption = *m_pFindOptionOrg;
	CParentDlg::OnInitDialog();
	CParentDlg::Initialize(IDC_ANCHOR, SUBDLGS_NUM);
	
	// TODO: この位置にその他の初期化用コードを追加してください。
	//CenterWindow();

	// 最初に表示するタブの設定.
	m_uIDSubDlg = FST_IDD_OF_SUBDLGS;		

	// サブダイアログの作成.
	m_pSubDlg = new COptionDlg1(this);
	// カレントアクティブサブダイアログのポインタセット


	// ベースになるダイアログの設定.
	// Create the actual CChildDlg controls offset by location
	// IDC_ANCHOR.
	m_pSubDlg->Create(IDC_ANCHOR);

	// Initialize the m_setdic structure before updating the controls the first time.
	// コントロールの初期化.
	UpdateData(FALSE);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

//*****************************************************************
// Function:	COptionDlg::UpdateData(BOOL bSaveAndValidate)
//*****************************************************************
BOOL COptionDlg::UpdateData(BOOL bSaveAndValidate)
{
	// ダイアログのアップデート（タグの変更と、ボタンが押されて新しいダイアログを表示する）.
	// 表示するダイアログのポインタが入っていれば、それを表示する.
		// タブの切り替え.
		switch (m_uIDSubDlg)
		{
			case FST_IDD_OF_SUBDLGS:
				// 保存
				if (bSaveAndValidate) {
					return ((COptionDlg1 *)m_pSubDlg)->RetrieveData(m_pFindOption);
				}
				else {
					return ((COptionDlg1 *)m_pSubDlg)->UpdateData(m_pFindOption);
				}
				break;
			
			case (FST_IDD_OF_SUBDLGS +1):
				if (bSaveAndValidate) {
					return ((COptionDlg2 *)m_pSubDlg)->RetrieveData(m_pFindOption);
				}
				else {
					return ((COptionDlg2 *)m_pSubDlg)->UpdateData(m_pFindOption);
				}
				break;
			case (FST_IDD_OF_SUBDLGS +2):
				if (bSaveAndValidate) {
					return ((CExtensionsDlg *)m_pSubDlg)->RetrieveData(m_pFindOption);
				}
				else {
					return ((CExtensionsDlg *)m_pSubDlg)->UpdateData(m_pFindOption);
				}
				break;
			case (FST_IDD_OF_SUBDLGS +3):
				if (bSaveAndValidate) {
					return ((CMetaCharsDlg *)m_pSubDlg)->RetrieveData(m_pFindOption);
				}
				else {
					return ((CMetaCharsDlg *)m_pSubDlg)->UpdateData(m_pFindOption);
				}
				break;
			case (FST_IDD_OF_SUBDLGS +4):
				if (bSaveAndValidate) {
					return ((CFileTransDlg *)m_pSubDlg)->RetrieveData(m_pFindOption);
				}
				else {
					return ((CFileTransDlg *)m_pSubDlg)->UpdateData(m_pFindOption);
				}
				break;
		/* must be add point */
		}
	return CDialog::UpdateData(bSaveAndValidate);
}

///////////////////////////////////////////////////////////////////////////////
// タグの変更.
///////////////////////////////////////////////////////////////////////////////

BOOL COptionDlg::SelchangeTab(int nSel)
{
	// Get the current selection from the lisetbox
	// アクティブなタブの取得.
	//int nSel = nActiveTab;

	// Just in case there isn't one, don't do anything.
	if (nSel == -1)
		return FALSE;

	// If we are already on the current selection, don't bother deleting and re-creating the ChildDlg.
	// 現在表示されている所と同じなら帰る.
	if (m_uIDSubDlg == (UINT) nSel + FST_IDD_OF_SUBDLGS)
		return FALSE;

	// Call UpdateData to Retrieve the information from the current set of ChildDlg controls.
	// If UpdateData doesn't work then something is seriously wrong!!
	// 表示の一新.
	if (!UpdateData(TRUE))
		{
		return FALSE;
		}
	// The IDs of the child dialogs have been conveniently chosen to be in numeric sequence.
	// That is, IDD_SETDIC == 101, IDD_SETINP == 102, IDD_SETTRN == 103, 
	// IDD_SETMRK == 104, IDD_SETSTYL == 105.
	// This way, we can simply determine the child dialog selected by retrieving the listbox
	// selection (0-5) and adding that to IDD_SETDIC.
	m_uIDSubDlg = nSel + FST_IDD_OF_SUBDLGS;
	if (m_pSubDlg)
		delete m_pSubDlg;
	switch (m_uIDSubDlg)
		{
		case FST_IDD_OF_SUBDLGS:
			m_pSubDlg = new COptionDlg1(this);
			break;
		case (FST_IDD_OF_SUBDLGS +1):
			m_pSubDlg = new COptionDlg2(this);
			break;
		case (FST_IDD_OF_SUBDLGS +2):
			m_pSubDlg = new CExtensionsDlg(this);
			break;
		case (FST_IDD_OF_SUBDLGS +3):
			m_pSubDlg = new CMetaCharsDlg(this);
			break;
		case (FST_IDD_OF_SUBDLGS +4):
			m_pSubDlg = new CFileTransDlg(this);
			break;
		/* must be add point */
		}

	// ダイアログ(タブ)の無効化.
	InvalidateRect(ivRect);
	// Create the new dialog box. Note that the create call is using a control ID.
	m_pSubDlg->Create(IDC_ANCHOR);
	// Update the controls with the stored data.
	UpdateData(FALSE);
	nActiveTab = nSel;
	return TRUE;
}


void COptionDlg::OnOK()
{
	if (UpdateData(TRUE))
		{
		*m_pFindOptionOrg = *m_pFindOption;	// ｵﾘｼﾞﾅﾙへのｱｯﾌﾟﾃﾞｰﾄ
		if (vpFindList)
			vpFindList->ResetViewString(TRUE); // 検索ﾘｽﾄ表示へのｱｯﾌﾟﾃﾞｰﾄ
		CDialog::OnOK();
		}
}




int COptionDlg::DrawCaption(CDC* pDC, int idTab, CRect rect)
{
	CPoint pt;			// Top-Left of the Tab
	CSize tExtent;
	CString cstr;

	cstr.LoadString(FST_IDS_OF_SUBDLGS + idTab);
	int TabWidth = rect.Width();
	int lenCaption = cstr.GetLength();
	pt = rect.TopLeft();

/*    PortTool v2.2     1995/10/16    8:9          */
/*      Found   : GetTextExtent          */
/*      Issue   : ポータブルな GetTextExtentPoint に置き換わりました          */
//	WINAPI:GetTextExtent()->GetTextExtenPosion32()だが、MFCはそのまま
	tExtent = pDC->GetTextExtent(cstr.GetBuffer(0), lenCaption);
	if (TabWidth >= tExtent.cx )
		{
		//takaso2008
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(pt.x + (TabWidth-tExtent.cx)/2, pt.y + TabHeight/4, cstr.GetBuffer(0));
		return tExtent.cx;
		}
	else
		return 0;
}

