// filetran.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "fdiver.h"
#include "filetrad.h"
#include "filetran.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CFileTransArray *vpFileTransArray;

/////////////////////////////////////////////////////////////////////////////
// CFileTransDlg ダイアログ

//EntryPoint Arc
CFileTransDlg::CFileTransDlg(CWnd* pParent /*=NULL*/)
	: CChildDlg(CFileTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileTransDlg)
	m_fLha = FALSE;
	m_fZip = FALSE;
	m_optRemain = 0;
	m_strWorkPath = _T("");
	m_fArj = FALSE;
	m_fTar = FALSE;
	m_fCab = FALSE;
	m_fRar = FALSE;
	m_fKft = FALSE;
	m_fxdoc = FALSE;
	//}}AFX_DATA_INIT
}


//EntryPoint Arc
void CFileTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CChildDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTransDlg)
	DDX_Check(pDX, IDC_FT_LHA, m_fLha);
	DDX_Check(pDX, IDC_FT_ZIP, m_fZip);
	DDX_Text(pDX, IDC_FT_WORKPATH, m_strWorkPath);
	DDX_Check(pDX, IDC_FT_ARJ, m_fArj);
	DDX_Check(pDX, IDC_FT_TAR, m_fTar);
	DDX_Check(pDX, IDC_FT_CAB, m_fCab);
	DDX_Check(pDX, IDC_FT_RAR, m_fRar);
	DDX_Check(pDX, IDC_FT_KFT, m_fKft);
	DDX_Check(pDX, IDC_FT_XDOC, m_fxdoc);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate)
		{
		m_optRemain = GetCheckedRadioButton(IDC_FT_NOREMAIN, IDC_FT_HITREMAIN)-IDC_FT_NOREMAIN;
		}
	else
		{
		CheckRadioButton(IDC_FT_NOREMAIN, IDC_FT_HITREMAIN, m_optRemain+IDC_FT_NOREMAIN);
		GetDlgItem(IDC_FT_LHA)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_LZH)->FActive());
		GetDlgItem(IDC_FT_ZIP)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_ZIP)->FActive());
		GetDlgItem(IDC_FT_ARJ)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_ARJ)->FActive());
		GetDlgItem(IDC_FT_TAR)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_TAR)->FActive());
		GetDlgItem(IDC_FT_CAB)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_CAB)->FActive());
		GetDlgItem(IDC_FT_RAR)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_RAR)->FActive());
//EntryPoint Arc
		GetDlgItem(IDC_FT_KFT)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_KFT)->FActive());
		GetDlgItem(IDC_FT_XDOC)->EnableWindow(vpFileTransArray->m_arypDll.PDll(EXT_XDOC)->FActive());
		}
}


BEGIN_MESSAGE_MAP(CFileTransDlg, CChildDlg)
	//{{AFX_MSG_MAP(CFileTransDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFileTransDlg メッセージ ハンドラ
BOOL CFileTransDlg::OnInitDialog()
{
	CChildDlg::OnInitDialog();
	ShowWindow(SW_SHOW);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}
/*************************************************************************
-- Routine: BOOL CFileTransDlg::RetriveData(CFindOption *pFindOption)
-- Description and Usage:
		 ダイアログ情報から、データに反映させます。
-- Arguments:
		CFindOption *pFindOption - 実ﾃﾞｰﾀ
-- Notes:
-- History:
		'95.2	- created		(M.Design)
*************************************************************************/
BOOL CFileTransDlg::RetrieveData(CFindOption *pFindOption)
{
	if (!CChildDlg::UpdateData(TRUE))
		return FALSE;
	if (!CheckPath(m_strWorkPath.GetBuffer(0)))
		{
		Message(IDS_INVAL_PATH);
		return FALSE;
		}
	pFindOption->m_fFTLha = m_fLha;
	pFindOption->m_fFTZip = m_fZip;
	pFindOption->m_fFTArj = m_fArj;
	pFindOption->m_fFTTar = m_fTar;
	pFindOption->m_fFTCab = m_fCab;
	pFindOption->m_fFTRar = m_fRar;
//EntryPoint Arc
	pFindOption->m_fFTKft = m_fKft;
	pFindOption->m_fFTxdoc = m_fxdoc;
	pFindOption->m_optFTRemain = m_optRemain;
	pFindOption->m_strFTWorkPath = m_strWorkPath;
	vpFileTransArray->FInitialize(pFindOption->m_strFTWorkPath.GetBuffer(0));
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CFileTransDlg::UpdateData(CFindOption *pFindOption)
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
BOOL CFileTransDlg::UpdateData(CFindOption *pFindOption)
{
	vpFileTransArray->FInitialize(pFindOption->m_strFTWorkPath.GetBuffer(0));
	m_fLha = pFindOption->m_fFTLha;
	m_fZip = pFindOption->m_fFTZip;
	m_fArj = pFindOption->m_fFTArj;
	m_fTar = pFindOption->m_fFTTar;
	m_fCab = pFindOption->m_fFTCab;
	m_fRar = pFindOption->m_fFTRar;
//EntryPoint Arc
	m_fKft = pFindOption->m_fFTKft;
	m_fxdoc = pFindOption->m_fFTxdoc;
	m_optRemain = pFindOption->m_optFTRemain;
	m_strWorkPath = pFindOption->m_strFTWorkPath;
	CChildDlg::UpdateData(FALSE);
	return TRUE;
}

