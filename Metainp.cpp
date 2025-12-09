/*    PortTool v2.2     METAINP.CPP          */

// metainp.cpp : インプリメンテーション ファイル
//
//#include "childdlg.h"
//#include "string.h"
//#include "cwjtbl.h"

#include "stdafx.h"

#include "metainp.h"
#include "metainp1.h"
#include "metainp2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg ダイアログ

//////////////////////////////////////////////////////////////////////////////
// コンストラクタ															 
//////////////////////////////////////////////////////////////////////////////
CMetaInputDlg::CMetaInputDlg(CWnd* pParent /*=NULL*/):CParentDlg(CMetaInputDlg::IDD, pParent)
{
	m_pcstr = NULL;
	m_pMetaStringArray = NULL;
}


CMetaInputDlg::~CMetaInputDlg()
{
	if (m_pcstr)
		delete m_pcstr;
	if (m_pMetaStringArray)
		delete m_pMetaStringArray;
}


/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg メッセージハンドラ
// 各タグの中にあるボタンを押しても、ここのメッセージマップに来る.
BEGIN_MESSAGE_MAP(CMetaInputDlg, CParentDlg)
	//{{AFX_MSG_MAP(CMetaInputDlg)

/*    PortTool v2.2     1995/10/16    8:2          */
/*      Found   : WM_VSCROLL          */
/*      Issue   : wParam/lParam の取り扱いに注意。詳細についてはテクニカルリファレンスをご覧下さい。          */
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMetaInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaInputDlg)
	//}}AFX_DATA_MAP
}

// 初期設定
void CMetaInputDlg::Initialize(CString *pcstrOrg, CMetaStringArray *pMetaStringArrayOrg, BOOL fKeyEntryOnly/*=FALSE*/)
{
	ASSERT(pcstrOrg);
	ASSERT(pMetaStringArrayOrg);

	m_fKeyEntryOnly = fKeyEntryOnly;

	m_pcstr = new CString;
	ASSERT(m_pcstr);
	m_pMetaStringArray = new CMetaStringArray(pMetaStringArrayOrg);
	ASSERT(m_pMetaStringArray);


	m_pcstrOrg = pcstrOrg;
	m_pMetaStringArrayOrg = pMetaStringArrayOrg;
}

//***************************************************************
// Function :CMetaInputDlg::OnInitDialog()
// 
// Purpose:
// 		1) Initialize the main dialog box.
//		2) Fill the selection listbox.
//		3) Initialize the m_Setdic structure and
//		   Create the first ChildDlg.
//***************************************************************
BOOL CMetaInputDlg::OnInitDialog()
{
	// ｵﾘｼﾞﾅﾙから実ﾃﾞｰﾀへのｱｯﾌﾟﾃﾞｰﾄ
	*m_pcstr = *m_pcstrOrg;
	//*m_pMetaStringArray = *m_pMetaStringArrayOrg;

	CParentDlg::OnInitDialog();
	CParentDlg::Initialize(IDC_ANCHOR, SUBDLGS_NUM);
	
	// TODO: この位置にその他の初期化用コードを追加してください。
	CenterWindow();

	// 最初に表示するタブの設定.
	m_uIDSubDlg = FST_IDD_OF_SUBDLGS;		

	// サブダイアログの作成.
	m_pSubDlg = new CMetaInputDlg1(this);
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
// Function:	CMetaInputDlg::UpdateData(BOOL bSaveAndValidate)
//*****************************************************************
BOOL CMetaInputDlg::UpdateData(BOOL bSaveAndValidate)
{
	// ダイアログのアップデート（タグの変更と、ボタンが押されて新しいダイアログを表示する）.
	// 表示するダイアログのポインタが入っていれば、それを表示する.
		// タブの切り替え.
		switch (m_uIDSubDlg)
		{
			case FST_IDD_OF_SUBDLGS:
				// 保存
				if (bSaveAndValidate) {
					return ((CMetaInputDlg1 *)m_pSubDlg)->RetrieveData(m_pcstr, m_pMetaStringArray);
				}
				else {
					return ((CMetaInputDlg1 *)m_pSubDlg)->UpdateData(m_pcstr, m_pMetaStringArray, m_fKeyEntryOnly);
				}
				break;
			
			case (FST_IDD_OF_SUBDLGS +1):
				if (bSaveAndValidate) {
					return ((CMetaInputDlg2 *)m_pSubDlg)->RetrieveData(m_pcstr);
				}
				else {
					return ((CMetaInputDlg2 *)m_pSubDlg)->UpdateData(m_pcstr);
				}
				break;
			default:
				ASSERT(FALSE);
				break;
		/* must be add point */
		}
	return CDialog::UpdateData(bSaveAndValidate);
}

///////////////////////////////////////////////////////////////////////////////
// タグの変更.
///////////////////////////////////////////////////////////////////////////////

BOOL CMetaInputDlg::SelchangeTab(int nSel)
{
	// Get the current selection from the lisetbox
	// アクティブなタブの取得.
	//int nSel = nActiveTab;

	if (m_fKeyEntryOnly)
		return FALSE;

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
			m_pSubDlg = new CMetaInputDlg1(this);
			break;
		case (FST_IDD_OF_SUBDLGS +1):
			m_pSubDlg = new CMetaInputDlg2(this);
			break;
		default:
			ASSERT(FALSE);
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


void CMetaInputDlg::OnOK()
{
	if (UpdateData(TRUE))
		{
		*m_pMetaStringArrayOrg = *m_pMetaStringArray;	// ｵﾘｼﾞﾅﾙへのｱｯﾌﾟﾃﾞｰﾄ
		*m_pcstrOrg = *m_pcstr;
		CDialog::OnOK();
		}
}




int CMetaInputDlg::DrawCaption(CDC* pDC, int idTab, CRect rect)
{
	CPoint pt;			// Top-Left of the Tab
	CSize tExtent;
	CString cstr;

	if (m_fKeyEntryOnly && idTab==1)
		return 0;

	cstr.LoadString(IDS_META_TAB1 + idTab);
	int TabWidth = rect.Width();
	int lenCaption = cstr.GetLength();
	pt = rect.TopLeft();

/*    PortTool v2.2     1995/10/16    8:3          */
/*      Found   : GetTextExtent          */
/*      Issue   : ポータブルな GetTextExtentPoint に置き換わりました          */
//	WIN API:GetTextExtent()->GetTextExtentPoint32()だが、MFCはそのまま
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

