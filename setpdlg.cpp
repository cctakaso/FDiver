// setpdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\mdfc\dfile.h"
#include "setpdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);


/////////////////////////////////////////////////////////////////////////////
// CSetPathDlg dialog

//IMPLEMENT_DYNAMIC(CSetPathDlg, CFileDialog)

CSetPathDlg::CSetPathDlg(char *szPath, UINT idRes, UINT idResTitile) : CFileDialog(TRUE, NULL, _T("*.*"),
		NULL, _T("All Files (*.*)|*.*||"), NULL, 0, TRUE)
{
	//{{AFX_DATA_INIT(CSetPathDlg)
	//}}AFX_DATA_INIT
	if (szPath)
		m_strPaths = szPath;

	m_idRes = idRes;

	ASSERT(idResTitile>0);
	m_idResTitile = idResTitile;

#ifdef WIN32
	//#include <afximpl.h>  //afxData <- ::GetVersion()
	//extern AFX_DATA AUX_DATA afxData;
	//if (afxData.bWin4)
	// or
	// these codes from auxdata.cpp in mfc-source.
	DWORD dwVersion = ::GetVersion();
	m_bWin4 = (BYTE)dwVersion >= 4;
	if (m_bWin4)
		m_idRes = 0;	// Win95以上は３２ビット版では、オリジナルテンプレートを使わない。

#ifdef BUG20120112
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX)); // 必要あるのか?
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	BOOL bOsVersionInfoEx;
	if ((bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi)) == FALSE) {
		// Windows NT 4.0 SP5 以前と Windows 9x
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *)&osvi)) return;
	}
#endif

	// Windows XP 以降では GetNativeSystemInfo を、それ以外では GetSystemInfo を使う
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(SYSTEM_INFO)); // 必要あるのか?
	PGNSI pGNSI = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
	if (pGNSI)
		pGNSI(&si);
	else
		GetSystemInfo(&si);

#ifdef BUG20120112
	// Vista / 2008 / 7 / 2008 R2　とそれ以降
	m_bUperVista = (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osvi.dwMajorVersion >= 6);
#endif


#else
	m_bWin4 = FALSE;	// 16bitではいつもＦＡＬＳＥ
#endif
}


void CSetPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CFileDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPathDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetPathDlg, CFileDialog)
	//{{AFX_MSG_MAP(CSetPathDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSetPathDlg message handlers

void CSetPathDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

#ifdef BUG20120112
	if (m_bUperVista) {
#else
	if (vbUperVista) {
#endif
		m_strOutPath = GetMyFolderPath();
		if (m_strOutPath.IsEmpty())
			return;
	}else{
		if (m_bWin4)
			{
			//CDM_GETFOLDERPATH 
			//wParam = (WPARAM) cbBufSize; 
			//lParam = (LPARAM) (LPTSTR) lpszFolderBuf; 
			// Corresponding macro 
			if (CommDlg_OpenSave_GetFolderPath(GetSafeHwnd(), vz, sizeof(vz))>0)
				m_strPaths = vz;
			else
				return;
			}
		else
			m_strPaths = GetCurrentPath();

		AddLastBackSlash(&m_strPaths);
	}

	m_idRtn = IDOK;
	DefWindowProc(WM_COMMAND, IDCANCEL, (LONG) TRUE);

}

void CSetPathDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_idRtn = IDCANCEL;
	//PostMessage(WM_COMMAND, IDABORT, (LONG) TRUE);
	CFileDialog::OnCancel();
}

BOOL CSetPathDlg::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CSetPathDlg::DoModal()
{
	ASSERT(m_idResTitile>0);

	// ダイアログタイトルの設定
	CString cstrTitle;
	cstrTitle.LoadString(m_idResTitile);
	m_ofn.lpstrTitle = cstrTitle;//title;

	// オープン時のパス設定
	m_ofn.hInstance	= AfxGetInstanceHandle() ;				// ｳｨﾝﾄﾞｩ･ﾊﾝﾄﾞﾙ
	CString cStrPath;
	if (m_strPaths.IsEmpty())
		m_strPaths = GetCurrentPath();
	cStrPath = m_strPaths;
	RemoveLastBackSlash(&cStrPath);
	m_ofn.lpstrInitialDir = cStrPath;					// 最初のﾌｧｲﾙ･ﾃﾞｨﾚｸﾄﾘを示す文字列ｱﾄﾞﾚｽ


	// 既存のﾊﾟｽ名のみ入力,読込み専用ﾁｪｯｸBOX非表示;

#ifdef BUG20120112
	if (m_bUperVista) 
#else
	if (vbUperVista) 
#endif
		m_ofn.Flags |= OFN_ENABLEHOOK | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT;
	else
		m_ofn.Flags |= OFN_ENABLEHOOK | OFN_NOVALIDATE | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT;

	if (m_idRes>0)
		{
		m_ofn.lpTemplateName = MAKEINTRESOURCE(m_idRes);
		m_ofn.Flags |= OFN_ENABLETEMPLATE;
		}
	// append the "*.*" all files filter
	//m_ofn.nMaxCustFilter = NULL;
//	m_ofn.lpstrFilter			= NULL ;								// ﾌｨﾙﾀを示す文字列のﾍﾟｱを含むﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ
//	m_ofn.lpstrCustomFilter	= NULL ;								// ﾌｨﾙﾀを示すﾕｰｻﾞｰ定義文字列のﾍﾟｱを含むﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ
//	m_ofn.nMaxCustFilter		= 0L ;									// lpstrCustomFilterが識別するﾊﾞｯﾌｧ･ｻｲｽﾞ
//	m_ofn.nFilterIndex			= 0L ;									// lpstrFilterが指すﾊﾞｯﾌｧへのｲﾝﾃﾞｨｯｸｽ
//	m_ofn.lpstrFileTitle	= vz;								// 選択ﾌｧｲﾙのﾀｲﾄﾙ受取りﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ
//	m_ofn.nMaxFileTitle		= sizeof(vz);									// lpstrFileTitleﾊﾞｯﾌｧにｺﾋﾟｰされる最大文字列ｻｲｽﾞ
//	m_ofn.nFileOffset			= 0 ;									// ﾊﾟｽ先頭からlpstrFileが指すﾌｧｲﾙ名までの
//	m_ofn.nFileExtension		= 0 ;									// ﾊﾟｽ先頭からlpstrFileが指すﾌｧｲﾙ名拡張子までの
//	m_ofn.lpstrDefExt			= NULL ;								// ﾃﾞﾌｫﾙﾄ拡張子を格納するﾊﾞｯﾌｧ･ｱﾄﾞﾚｽ
//	m_ofn.lCustData			= NULL ;								// lpfnHookが指すﾌｯｸ関数にｼｽﾃﾑが渡す（未使用）
	//m_ofn.lpstrFilter = NULL;//strFilter;
	//m_ofn.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	//m_ofn.lpfnHook = _MyCommDlgProc;


	m_idRtn = IDOK;
	m_strPaths.Empty();



#ifdef BUG20120112
	if (m_bUperVista) {
#else
	if (vbUperVista) {
#endif
		const int c_cMaxFiles = 100;
		const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
		m_strPaths = _T("希望ﾊﾟｽに移動。");
		m_ofn.lpstrFile = m_strPaths.GetBuffer(c_cbBuffSize);
		m_ofn.nMaxFile = c_cMaxFiles;
	}

	//BOOL bRet = CFileDialog::DoModal() == IDOK ? TRUE : FALSE;
	CFileDialog::DoModal();

	if ((m_idRtn==IDOK) /*&& m_strPaths.IsEmpty()*/)
		{
#ifdef BUG20120112
		if (m_bUperVista) {
#else
		if (vbUperVista) {
#endif
			if (!m_strOutPath.IsEmpty())
				AddLastBackSlash(&m_strOutPath);
			else {
				//m_idRtn = IDCANCEL;
				m_strOutPath = GetMyFolderPath();
				AddLastBackSlash(&m_strOutPath);
			}
		}else{
			m_strPaths = GetPathName();
			int pos = m_strPaths.ReverseFind('\\');
			if (pos!=-1)
				{
				m_strPaths = m_strPaths.Left(pos);
				if (!m_strPaths.IsEmpty())
					AddLastBackSlash(&m_strPaths);
				else
					m_idRtn = IDCANCEL;
				}
			else
				m_idRtn = IDCANCEL;
		}
	}
	return m_idRtn==IDOK;
}





CString CSetPathDlg::GetMyFolderPath() const
{
#ifdef BUG20120112
	ASSERT(m_bUperVista);
#else
	ASSERT(vbUperVista);
#endif
	CString strResult;

#ifdef BUG20120112
	if (m_bUperVista)
#else
	if (vbUperVista)
#endif
	{
		IShellItem *psiResult;
		HRESULT hr = (static_cast<IFileDialog*>(m_pIFileDialog))->GetFolder(&psiResult);
		if (SUCCEEDED(hr))
		{
			LPWSTR wcFolderPath = NULL;
			hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &wcFolderPath);
			if (SUCCEEDED(hr))
			{
				strResult = wcFolderPath;
				CoTaskMemFree(wcFolderPath);
			}
			psiResult->Release();
		}
	}
	else
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(m_ofn.Flags & OFN_EXPLORER);

		if (GetParent()->SendMessage(CDM_GETFOLDERPATH, (WPARAM)MAX_PATH, (LPARAM)strResult.GetBuffer(MAX_PATH)) < 0)
			strResult.Empty();
		else
			strResult.ReleaseBuffer();
	}
	
	return strResult;
}

BOOL CSetPathDlg::OnFileNameOK()
{
#ifdef BUG20120112
	if (m_bUperVista) {
#else
	if (vbUperVista) {
#endif
		return CFileDialog::OnFileNameOK();
	}
	return 0;
}
