// ColorDlg.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
#include "ColorDlg.h"
#include "fdiver.h"
#include "mdglibs.h"
#include "findopti.h"
#include "findlist.h"
#include "findlog.h"
extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CFindOption *vpFindOption;		// ｵﾌﾟｼｮﾝｵﾌﾞｼﾞｪｸﾄ

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorDlg ダイアログ

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlg::IDD, pParent)
	, m_ratioBetweenLine(0)
{
	m_ratioBetweenLine = 0;
	//{{AFX_DATA_INIT(CColorDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
	Initialize(TRUE);
}


void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_LST_COLOR, m_lstColors);
	DDX_Text(pDX, IDC_EDT_RATIO_BETWEEN_LINE, m_ratioBetweenLine);
	DDV_MinMaxInt(pDX, m_ratioBetweenLine, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	//{{AFX_MSG_MAP(CColorDlg)
	ON_LBN_DBLCLK(IDC_LST_COLOR, OnDblclkLstColor)
	ON_LBN_SELCHANGE(IDC_LST_COLOR, OnSelchangeLstColor)
	ON_BN_CLICKED(ID_CHANGE_COLOR, OnChangeColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorDlg メッセージ ハンドラ
BOOL CColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// コントロールのサブクラス化
	//VERIFY(m_lstColors.SubclassDlgItem(IDC_LST_COLOR, this));

	// リストボックスへ追加
	Initialize();
	m_lstColors.SetCurSel(0);
	OnSelchangeLstColor();

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CColorDlg::Initialize(BOOL fMemOnly)
{
	// リストボックスへ追加
	if (!fMemOnly)
		m_lstColors.ResetContent();
	CColorSel sel;
	CString str;
	str = "1,テキストカラー,";
	str += vpFindOption->m_strFrColor;
	sel.Initialize(str);
	m_lstColors.AddColorItem(sel, fMemOnly);
	str = "2,背景色,";
	str += vpFindOption->m_strBkColor;
	sel.Initialize(str);
	m_lstColors.AddColorItem(sel, fMemOnly);

	
	m_ratioBetweenLine = vpFindOption->m_ratioBetweenLine;

}

void CColorDlg::OnOK() 
{
	CColorSel *psel = GetSelData(0);
	if (!psel)
		goto Err;
	COLORREF frColor, bkColor;
	frColor = psel->GetColor();
	vpFindOption->m_strFrColor = psel->GetStringColor();

	psel = GetSelData(1);
	if (!psel)
		goto Err;
	bkColor = psel->GetColor();
	vpFindOption->m_strBkColor = psel->GetStringColor();
	
	UpdateData(TRUE);

	vpFindOption->m_ratioBetweenLine = m_ratioBetweenLine;

	vpFindList->SetColors(frColor, bkColor, m_ratioBetweenLine);

	CDialog::OnOK();
	return;
Err:
	Initialize();
	AfxMessageBox(_T("設定エラー：設定できませんでした。"));
}

void CColorDlg::OnCancel() 
{
	CDialog::OnCancel();
}


void CColorDlg::OnSelchangeLstColor()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (::IsWindow(m_btnOk.m_hWnd))
		m_btnOk.EnableWindow(m_lstColors.GetCurSel()!=LB_ERR);
}

void CColorDlg::OnDblclkLstColor() 
{
	OnChangeColor();
}

void CColorDlg::OnChangeColor() 
{
	// 最後の色を取得
	DWORD color;
	CColorSel *pselData = m_lstColors.GetSelData();
	if (pselData==NULL)
		return;
	color = pselData->GetColor();
	CColorDialog dlg(color);
	//dlg.m_cc.Flags = CC_ENABLEHOOK;
	if (dlg.DoModal()==IDOK)
		pselData->SetColor(dlg.GetColor());
}
