/*    PortTool v2.2     METACHAD.CPP          */

// metachar.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
//#include "fdiver.h"
//#include "strspec.h"
#include "metachad.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaCharsDlg ダイアログ

CMetaCharsDlg::CMetaCharsDlg(CWnd* pParent /*=NULL*/)
	: CChildDlg(CMetaCharsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetaCharsDlg)
	//}}AFX_DATA_INIT
}

//void CMetaCharsDlg::Initialize(STRSPEC_METACHARS *pMetaCharsData)
//{
//	m_pmetaCharsOrg = pMetaCharsData;
//	MetaCharsDataCopy(pMetaCharsData, &m_metaCharsData);
//}

void CMetaCharsDlg::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaCharsDlg)
	DDX_Text(pDX, IDC_META_AND, m_metaCharsData.str[mcAnd]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcAnd], 3);
	DDX_Text(pDX, IDC_META_BLOCK_L, m_metaCharsData.str[mcBlaketL]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcBlaketL], 1);
	DDX_Text(pDX, IDC_META_BLOCK_R, m_metaCharsData.str[mcBlaketR]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcBlaketR], 1);
	DDX_Text(pDX, IDC_META_MATCHANY, m_metaCharsData.str[mcMatchAny]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcMatchAny], 1);
	DDX_Text(pDX, IDC_META_MATCHSTR, m_metaCharsData.str[mcMatchStr]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcMatchStr], 1);
	DDX_Text(pDX, IDC_META_NOT, m_metaCharsData.str[mcNot]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcNot], 3);
	DDX_Text(pDX, IDC_META_OR, m_metaCharsData.str[mcOr]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcOr], 3);
	DDX_Text(pDX, IDC_META_PREFIX, m_metaCharsData.str[mcPrefix]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcPrefix], 1);
	DDX_Text(pDX, IDC_META_XOR, m_metaCharsData.str[mcXor]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcXor], 3);
	DDX_Text(pDX, IDC_META_SBLOCK_L, m_metaCharsData.str[mcSBlaketL]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcSBlaketL], 1);
	DDX_Text(pDX, IDC_META_SBLOCK_R, m_metaCharsData.str[mcSBlaketR]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcSBlaketR], 1);
	DDX_Text(pDX, IDC_META_SOR, m_metaCharsData.str[mcSOr]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcSOr], 1);
	DDX_Text(pDX, IDC_META_SXOR, m_metaCharsData.str[mcSXor]);
	DDV_MaxChars(pDX, m_metaCharsData.str[mcSXor], 1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMetaCharsDlg, CChildDlg)
	//{{AFX_MSG_MAP(CMetaCharsDlg)
//	ON_EN_SETFOCUS(IDC_META_AND, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_BLOCK_L, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_BLOCK_R, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_MATCHANY, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_MATCHSTR, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_NOT, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_OR, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_PREFIX, OnSetfocusMeta)
//	ON_EN_SETFOCUS(IDC_META_XOR, OnSetfocusMeta)
	ON_BN_CLICKED(IDC_META_STNDARD, OnClickedMetaStndard)
	ON_BN_CLICKED(IDC_META_BASIC, OnClickedMetaBasic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaCharsDlg メッセージハンドラ

BOOL CMetaCharsDlg::OnInitDialog()
{
	CChildDlg::OnInitDialog();
	
	// TODO: この位置にその他の初期化用コードを追加してください。
	ShowWindow(SW_SHOW);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}
/*
void CMetaCharsDlg::OnSetfocusMeta()
{
	// TODO: この位置にコントロール通知ハンドラのコードを追加してください。
//resource.hの以下のIDは順列でなければならない
//IDS_META_MATCHANYに続く文字列リソースＩＤ
//IDC_META_MATCHANYに続くEditCtrリソースＩＤ
	ASSERT(GetFocus()->GetDlgCtrlID()>=IDC_META_MATCHANY);
	CString cstr;
	cstr.LoadString(IDS_META_MATCHANY+GetFocus()->GetDlgCtrlID()-IDC_META_MATCHANY);
	ASSERT(!cstr.IsEmpty());
	SetDlgItemText(IDC_META_INFO, cstr.GetBuffer(0));
}
*/
/*************************************************************************
-- Routine: BOOL COptionDlg2::RetriveData(CFindOption *pFindOption)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CFindOption *pFindOption - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CMetaCharsDlg::RetrieveData(CFindOption *pFindOption)
{
	//CChildDlg::UpdateData(TRUE);
	//pFindOption->m_optDispNum = m_optDispNum;
	//pFindOption->m_fDispDoc = m_fDispDoc;
	//pFindOption->m_fFile = m_fFile;
	//pFindOption->m_fDir = m_fDir;
	//pFindOption->m_fDragServer = m_fDragServer;
	if (!CChildDlg::UpdateData(TRUE)) //MAX文字数チェック
		return FALSE;				// CChildDlg::OnOK()でもチェックしてしまうのでここでリターンする
	UINT ui=0;
	if ((ui=MetaCharsDataCheck(&m_metaCharsData))!=0)
		{
//resource.hの以下のIDは順列でなければならない
//IDC_META_MATCHANYに続くEditCtrリソースＩＤ
/*
#define IDC_META_MATCHANY               287
#define IDC_META_MATCHSTR               288
#define IDC_META_AND                    289
#define IDC_META_OR                     290
#define IDC_META_XOR                    291
#define IDC_META_NOT                    292
#define IDC_META_BLOCK_L                293
#define IDC_META_BLOCK_R                294
#define IDC_META_PREFIX                 295
#define IDC_META_STNDARD                297
*/
		Message(IDS_PLEASE_INPUTCHAR);
		GetDlgItem(IDC_META_MATCHANY+ui-1)->SetFocus();
		return FALSE;
		}
	MetaCharsDataCopy(&m_metaCharsData, &pFindOption->m_metaChars.m_metaCharsData); // Update to Original
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CMetaCharsDlg::UpdateData(CFindOption *pFindOption)
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
BOOL CMetaCharsDlg::UpdateData(CFindOption *pFindOption)
{
//	m_optDispNum = pFindOption->m_optDispNum;
//	m_fDispDoc = pFindOption->m_fDispDoc;
//	m_fFile = pFindOption->m_fFile;
//	m_fDir = pFindOption->m_fDir;
//	m_fDragServer = pFindOption->m_fDragServer;
//	CChildDlg::UpdateData(FALSE);
	MetaCharsDataCopy(&pFindOption->m_metaChars.m_metaCharsData, &m_metaCharsData); // Update from Original
	CChildDlg::UpdateData(FALSE);
	return TRUE;
}


void CMetaCharsDlg::OnClickedMetaStndard()
{
	MetaCharsDataIni(&m_metaCharsData);
	CChildDlg::UpdateData(FALSE);
	GetDlgItem(IDC_META_MATCHANY)->SetFocus();
}

void CMetaCharsDlg::OnClickedMetaBasic()
{
	MetaCharsDataIni2(&m_metaCharsData);
	CChildDlg::UpdateData(FALSE);
	GetDlgItem(IDC_META_MATCHANY)->SetFocus();
}
