/*    PortTool v2.2     strspecd.cpp          */

// strspecd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "fdiver.h"
#include "strspecd.h"
#include "strspd1.h"
#include "strspd2.h"
#include "metachar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg ダイアログ

CStrSpecDlg::CStrSpecDlg(CWnd* pParent /*=NULL*/)
	: CParentDlg(CStrSpecDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrSpecDlg)
		// 注意: ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
	m_pStrSpec = new CStrSpec;
	ASSERT(m_pStrSpec);
	m_pSubDlg2 = NULL;
	m_fChangeBefore=TRUE;
}

CStrSpecDlg::~CStrSpecDlg()
{
	if (m_pStrSpec)
		delete m_pStrSpec;
	if (m_pSubDlg2)
		delete m_pSubDlg2;
}

void CStrSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrSpecDlg)
		// 注意: ClassWizard はこの位置に DDX と DDV の呼び出しコードを追加します。
	//}}AFX_DATA_MAP
}
#define WM_MYMESSAGE (WM_USER+1)
BEGIN_MESSAGE_MAP(CStrSpecDlg, CParentDlg)
	//{{AFX_MSG_MAP(CStrSpecDlg)
	ON_MESSAGE(WM_MYMESSAGE, OnSelchangeEslList)
//	ON_COMMAND(IDC_F_METACHARAS, OnMetaChars)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// 初期設定
void CStrSpecDlg::Initialize(CStrSpec *pStrSpec)
{
	ASSERT(pStrSpec);
	m_pStrSpecOrg = pStrSpec;
}


/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg メッセージハンドラ

BOOL CStrSpecDlg::OnInitDialog()
{

	// ｵﾘｼﾞﾅﾙから実ﾃﾞｰﾀへのｱｯﾌﾟﾃﾞｰﾄ
	*m_pStrSpec = *m_pStrSpecOrg;

	CParentDlg::OnInitDialog();
	CParentDlg::Initialize(IDC_ANCHOR3, SUBDLGS_NUM/*, TRUE*/);
	
	// TODO: この位置にその他の初期化用コードを追加してください。
	CenterWindow();

	ASSERT(m_pStrSpec->m_iSel<m_pStrSpec->m_aryAttr.GetSize() &&
		m_pStrSpec->m_iSel<m_pStrSpec->m_aryStr.GetSize());
	if (m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel].GetLength()==0 ||
	m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel].GetAt(0)==STRSPEC_ATTR_PREF_DEF)
		{
		// 最初に表示するタブの設定.
		m_uIDSubDlg = FST_IDD_OF_SUBDLGS;
		// サブダイアログの作成.
		m_pSubDlg = new CStrSpecDlg1(this);
		// カレントアクティブサブダイアログのポインタセット
		nActiveTab = 0;
		}
	else
		{
		// 最初に表示するタブの設定.
		m_uIDSubDlg = FST_IDD_OF_SUBDLGS+1;
		// サブダイアログの作成.
		m_pSubDlg = new CStrSpecDlg2(this);
		// カレントアクティブサブダイアログのポインタセット
		nActiveTab = 1;
		}

	// ベースになるダイアログの設定.
	// Create the actual CChildDlg controls offset by location
	// IDC_ANCHOR.
	m_pSubDlg->Create(IDC_ANCHOR3);


	// サブダイアログの作成.
	m_pSubDlg2 = new CEdStrAttr(this);//new CEdStrAttr(this);
	// カレントアクティブサブダイアログのポインタセット
	m_pSubDlg2->Create(IDC_ANCHOR2);

	CString cstr;
	cstr.LoadString(IDS_ENTRYNAME);

	m_pSubDlg2->Initialize(cstr.GetBuffer(0), TRUE/*最後のエントリーは消させない*/);
	// 初期化

//	m_pSubDlg2->UpdateData(&m_pStrSpec->m_aryStr, &m_pStrSpec->m_iSel);

	// Initialize the m_setdic structure before updating the controls the first time.
	// コントロールの初期化.
	UpdateData(FALSE);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}
//*****************************************************************
// Function:	CStrSpecDlg::UpdateData(BOOL bSaveAndValidate)
//*****************************************************************
BOOL CStrSpecDlg::UpdateData(BOOL bSaveAndValidate)
{

	if (m_fChangeBefore)
		{
		if (bSaveAndValidate)
			VERIFY(m_pSubDlg2->RetrieveData(&m_pStrSpec->m_aryStr, &m_pStrSpec->m_aryAttr, &m_pStrSpec->m_iSel));
		else
			VERIFY(m_pSubDlg2->UpdateData(&m_pStrSpec->m_aryStr, &m_pStrSpec->m_aryAttr, &m_pStrSpec->m_iSel));
		}

	ASSERT(m_pStrSpec->m_iSel>=0);
	// ダイアログのアップデート（タグの変更と、ボタンが押されて新しいダイアログを表示する）.
	// 表示するダイアログのポインタが入っていれば、それを表示する.
		// タブの切り替え.
		
		switch (m_uIDSubDlg)
		{
			case FST_IDD_OF_SUBDLGS:
				// 保存
				if (bSaveAndValidate) {
					return ((CStrSpecDlg1 *)m_pSubDlg)->RetrieveData(&m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel]);
				}
				else {
					return ((CStrSpecDlg1 *)m_pSubDlg)->UpdateData(&m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel]);
				}
				break;
			
			case (FST_IDD_OF_SUBDLGS +1):
				if (bSaveAndValidate) {
					return ((CStrSpecDlg2 *)m_pSubDlg)->RetrieveData(&m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel]);
				}
				else {
					return ((CStrSpecDlg2 *)m_pSubDlg)->UpdateData(&m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel]);
				}
				break;
		/* must be add point */
		}
	return CDialog::UpdateData(bSaveAndValidate);
}

///////////////////////////////////////////////////////////////////////////////
// タグの変更.
///////////////////////////////////////////////////////////////////////////////

BOOL CStrSpecDlg::SelchangeTab(int nSel)
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
			m_pSubDlg = new CStrSpecDlg1(this);
			break;
		case (FST_IDD_OF_SUBDLGS +1):
			m_pSubDlg = new CStrSpecDlg2(this);
			break;
//		case (FST_IDD_OF_SUBDLGS +2):
//			m_pSubDlg = new CStrSpecDlg3(this);
//			break;
		/* must be add point */
		}

	// ダイアログ(タブ)の無効化.
	InvalidateRect(ivRect);
	// Create the new dialog box. Note that the create call is using a control ID.
	m_pSubDlg->Create(IDC_ANCHOR3);
	// Update the controls with the stored data.
	UpdateData(FALSE);
	nActiveTab = nSel;
	return TRUE;
}


void CStrSpecDlg::OnOK()
{
	if (UpdateData(TRUE))
		{
		*m_pStrSpecOrg = *m_pStrSpec;	// ｵﾘｼﾞﾅﾙへのｱｯﾌﾟﾃﾞｰﾄ
		CParentDlg::OnOK();
		}
}




int CStrSpecDlg::DrawCaption(CDC* pDC, int idTab, CRect rect)
{
	CPoint pt;			// Top-Left of the Tab
	CSize tExtent;
	CString cstr;

	cstr.LoadString(IDS_STRMODE_JPN + (UINT)idTab);
	int TabWidth = rect.Width();
	int lenCaption = cstr.GetLength();
	pt = rect.TopLeft();

/*    PortTool v2.2     1995/10/16    8:15          */
/*      Found   : GetTextExtent          */
/*      Issue   : ポータブルな GetTextExtentPoint に置き換わりました          */
//	MFCはそのまま
	tExtent = pDC->GetTextExtent(cstr.GetBuffer(0), lenCaption);



	if (TabWidth >= tExtent.cx )
		{
		CRect rc;
		//takaso2008
		CBrush *pbr = CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH));
		//CBrush *pbr = CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH));
		int base = 	TabHeight*3/5;
		pt.x += (TabWidth-tExtent.cx)/2;
		pt.y += TabHeight/4;

		//takaso2008
		pDC->SetBkMode(TRANSPARENT);


		pDC->TextOut(pt.x, pt.y, cstr);
		pt.x -=(base*5/4);
		rc.SetRect(pt.x, pt.y, pt.x + base, pt.y + base);
		pt.x += base/2;
		pt.y += base/2;
#if 0 //takaso2008
		pDC->Arc(&rc, pt, pt);
#endif
		if (idTab==nActiveTab)
			{
			base = (base/4==0) ? 1:base/4;
			rc.InflateRect(-base, -base);
#if 0 //takaso2008
			CBrush *pbr = CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH));
			CBrush *pbr = CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH));
			CBrush *pbrOld = pDC->SelectObject(pbr);
			pDC->Ellipse(&rc);
			pDC->SelectObject(pbrOld);
#endif
			}
		return tExtent.cx;
		}
	else
		return 0;
}

LONG CStrSpecDlg::OnSelchangeEslList(UINT wParam, LONG lParam)
{
	if (wParam==TRUE)
		{//切換前の設定の取得および保管
		m_fChangeBefore=FALSE;
		VERIFY(UpdateData(TRUE));	//Retrive Data
		m_fChangeBefore=TRUE;
		VERIFY(m_pSubDlg2->UpdateData(&m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel])); //Set Update Data
		return TRUE;
		}
	else
		{// 切換後の設定の取得
		VERIFY(m_pSubDlg2->RetrieveData(&m_pStrSpec->m_aryStr, &m_pStrSpec->m_aryAttr, &m_pStrSpec->m_iSel));
		int nSel = ((m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel].GetLength()==0 ||
		 m_pStrSpec->m_aryAttr[m_pStrSpec->m_iSel].GetAt(0)==STRSPEC_ATTR_PREF_DEF) ? 0:1);
		m_uIDSubDlg = nSel + FST_IDD_OF_SUBDLGS;
		if (m_pSubDlg)
			delete m_pSubDlg;
		switch (m_uIDSubDlg)
			{
			case FST_IDD_OF_SUBDLGS:
				m_pSubDlg = new CStrSpecDlg1(this);
				break;
			case (FST_IDD_OF_SUBDLGS +1):
				m_pSubDlg = new CStrSpecDlg2(this);
				break;
			/* must be add point */
			}

		// ダイアログ(タブ)の無効化.
		InvalidateRect(ivRect);
		// Create the new dialog box. Note that the create call is using a control ID.
		m_pSubDlg->Create(IDC_ANCHOR3);
		// Update the controls with the stored data.
		UpdateData(FALSE);
		nActiveTab = nSel;
		return TRUE;
		}
}
// 
//void CStrSpecDlg::OnMetaChars()
//{
//	CMetaCharsDlg metaCharsDlg;
//	metaCharsDlg.Initialize(m_pStrSpec->GetSelMetaCharsData());
//	metaCharsDlg.DoModal();
//}
