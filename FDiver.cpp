/*    PortTool v2.2     FDIVER.CPP          */

// Fdiver.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "Fdiver.h"
#include "mainfrm.h"
#include "fdivedoc.h"
#include "fdivevw.h"
#include "finddlg.h"
#include "ffile.h"
#include "grep.h"
#include "findopti.h"
#include "crejit.h"
//#include "findlist.h"
#include "optdlg.h"
#include "greppat.h"
#include "metastr.h"
#include "filetran.h"
#include "CDxdoc2txt.h"
#include "CDxdoc2txtEvents.h"
#include "profile.h"
#include "UserPath.h"

#define CREJIT
#ifndef CREJIT
//#include "timerdlg.h"
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global object.
CFindFile *vpcFind;
CGrep *vpcGrep;
CFindDlg *vpFindDlg;
COptionDlg *vpOptionDlg;
CFindOption *vpFindOption;
CKeyOutLogic *vpKeyOutLogic;
CMetaStringArray *vpMetaStringArray;
CFileTransArray *vpFileTransArray;

BOOL vfCloseApp=FALSE;	// ｱﾌﾟﾘｹｰｼｮﾝの終了ﾌﾗｸﾞ
CStringArray varyParams;


extern CFindList *vpFindList;
#ifndef BUG20120112
BOOL vbUperVista=FALSE;
#endif
#define	PRIVATE_PROFILE_NAME	"fdiver.ini"


/////////////////////////////////////////////////////////////////////////////
// CFdiverApp

BEGIN_MESSAGE_MAP(CFdiverApp, CWinApp)
	//{{AFX_MSG_MAP(CFdiverApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDR_OPT_FIND, OnOptFind)
	ON_COMMAND(IDR_ACT_TOPMOST, OnFTotop)
	ON_COMMAND(ID_MYHELP_INDEX, OnMyHelpIndex)
	ON_COMMAND(IDR_ACT_EDITER, OnActEditer)
	ON_COMMAND(IDR_ACT_CLONE, OnActClone)
	ON_COMMAND(IDR_OPT_ICON, OnOptIcon)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
#ifdef SHARWARE
	ON_COMMAND(IDR_CREJIT, OnCrejit)
#endif //SHARWARE
	ON_UPDATE_COMMAND_UI(IDR_CREJIT, OnUpdateCrejit)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// サーポートＵＲＬ
static char szSupportUrl[] = "http://hp.vector.co.jp/authors/VA052798";
static char szHelpUrl[] = "http://hp.vector.co.jp/authors/VA052798/fdiver";
void SuportUrlBrowse(HWND hwnd, BOOL fHelp) 
{
	HINSTANCE hInst;
	hInst = ShellExecute(hwnd, "open",
		fHelp ? szHelpUrl:szSupportUrl, NULL, NULL, SW_SHOWNORMAL);
	if ((UINT)hInst<=31) {
		if (::WinExec(szSupportUrl, SW_SHOWNORMAL)<=31) {
			if ((UINT)(hInst = ShellExecute(hwnd, NULL/*"open"*/,
				szSupportUrl, NULL, NULL, SW_SHOW))<=31)
				;
		}
	}
}




/////////////////////////////////////////////////////////////////////////////
// CFdiverApp クラスの構築

CFdiverApp::CFdiverApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CFdiverApp オブジェクト

CFdiverApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CFdiverApp クラスの初期化
int FindNextSpace(const CString &strIn)
{
	CString str = strIn;
	int pos;
	str.TrimLeft();
	if ((pos=str.Find(' '))>=0)
		pos += strIn.GetLength() - str.GetLength();
	return pos;
}

BOOL ParseParam(CString &strCmd, CStringArray &aryParams)
{
	CString str = strCmd, strPart, strFile, strT;
	int pos_last;
	bool bFile=false;
	str.TrimLeft();
	str.TrimRight();
	if (str.IsEmpty())
		return FALSE;

	while(!str.IsEmpty()) {
		bool bFileParam = str[0]=='-' || str[0]=='/';
		//"/a /b"
		if ((pos_last=FindNextSpace(str))>=0) {
			strPart = str.Left(pos_last);
			str = str.Mid(pos_last);
			strT = str;
			strT.TrimLeft();
			if (!bFileParam) {
				strFile += strPart;
				if (!strT.IsEmpty() && (!(strT[0]=='-' || strT[0]=='/'))) {
					continue;
				}
			}
			str = strT;
		}else{
			strPart = str;
			str =""; //break!
		}
		strPart.TrimRight();
		if (!strPart.IsEmpty()) {
			if (strPart[0]=='-')
				*strPart.GetBuffer(0) = (char)'/';
			if (bFileParam)
				aryParams.SetAtGrow(aryParams.GetSize(), strPart);
			else
				strFile += strPart;
		}
	}
	if (!strFile.IsEmpty()) {
		bool bDblQ =  (strFile.GetLength()>1 &&
				strFile[0]=='"' && strFile[strFile.GetLength()-1]=='"');
		if (bDblQ) {
			CString str = strFile;
			strFile = str.Mid(1, strFile.GetLength()-2);
		}
		aryParams.InsertAt(0,strFile);
	}
	return TRUE;
}


BOOL CFdiverApp::InitInstance()
{
	SetDllDirectory("");	//remove current directory for search DLL pahts.
	AfxEnableControlContainer();
#if 0
	if (m_hPrevInstance)			 /* Other instances of app running? */
		{
		CString cstr;
		cstr.LoadString(IDR_MAINFRAME);
		HWND hWnd = ::FindWindow(NULL, cstr.GetBuffer(0));
		if (hWnd)
			{
			if (GetWindow(hWnd, GW_CHILD))
				{
				hWnd = GetWindow(hWnd, GW_CHILD);
				if (GetWindow(hWnd, GW_HWNDLAST))
					hWnd = GetWindow(hWnd, GW_HWNDLAST);
				}
			::SetActiveWindow(hWnd);
			}
		return FALSE;
		}
#endif //0

#if 0
#ifdef WIN32
#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif
#endif //WIN32
#endif

	SetDialogBkColor();        // ダイアログ背景色をグレーに設定します。

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたければ
	// 以下の特定の初期化ルーチンの中から不必要なものを削除してください。

	LoadStdProfileSettings();  // 標準 INI ファイルをロードします。(MRU を含む)

#ifdef BUG_20120112
	// アプリケーションファイルのあるパスをセット
	m_cstrDefPath = GetDefaultPath();

#ifdef BUG_20111218
	theProfile.SetProfile(PRIVATE_PROFILE_NAME, m_cstrDefPath);
#else
	CString strPath="";

	bool isAppDataLow = true;
	PWSTR pBuffer = NULL;
	HRESULT hr =SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, NULL, &pBuffer );
	if( SUCCEEDED( hr ) )
	{
		// いろいろ処理する
		strPath = pBuffer;
		// メモリを解放
		CoTaskMemFree( pBuffer );
	}	
	strPath += "\\webinter.net";

	if (!CheckPath(strPath.GetBuffer(0))) {
		if (!FCreateDirectory(strPath.GetBuffer(0))) {
			isAppDataLow = false;
		}
	}

	if (isAppDataLow) {
		theProfile.SetProfile(PRIVATE_PROFILE_NAME, strPath);
	}else{
		theProfile.SetProfile(PRIVATE_PROFILE_NAME, "");
	}


#endif
#else
#if 0
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX)); // 必要あるのか?
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	BOOL bOsVersionInfoEx;
	BOOL berror=false;
	if ((bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi)) == FALSE) {
		// Windows NT 4.0 SP5 以前と Windows 9x
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *)&osvi)) {
			berror = true;
		}
	}
	// Vista / 2008 / 7 / 2008 R2　とそれ以降
	if (berror)
		vbUperVista = false;
	else 
		vbUperVista = (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osvi.dwMajorVersion >= 6);
#endif

// バージョン情報の取得 
    OSVERSIONINFO OSver; 
    OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
    GetVersionEx(&OSver); 
 
    // もし Windows 6(Windows Vista/Windows Server 2008) 以降のバージョン?
    vbUperVista = OSver.dwMajorVersion >= 6; 

#if 0
	sprintf(vz,"dwMajorVersion=%d, dwMinorVersion=%d",(int)OSver.dwMajorVersion&0xff,(int)OSver.dwMinorVersion&0xff);
	MessageBox(NULL, vz, _T("バージョン情報 - Metastr.cpp"), MB_OK);

	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX)); // 必要あるのか?
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	BOOL bOsVersionInfoEx;
	BOOL berror=false;
	if ((bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi)) == FALSE) {
		// Windows NT 4.0 SP5 以前と Windows 9x
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *)&osvi)) {
			berror = true;
		}
	}
	// Vista / 2008 / 7 / 2008 R2　とそれ以降
	if (berror)
		vbUperVista = false;
	else 
		vbUperVista = (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osvi.dwMajorVersion >= 6);

	sprintf(vz,"dwMajorVersion=%d, dwMinorVersion=%d",(int)osvi.dwMajorVersion&0xff,(int)osvi.dwMinorVersion&0xff);
	MessageBox(NULL, vz, _T("バージョン情報 - fdiver.cpp"), MB_OK);
#endif 


	// アプリケーションファイルのあるパスをセット
	m_cstrDefPath = GetDefaultPath();

	if (vbUperVista) {
		bool isAppDataLow = true;
		HRESULT hr;
		HMODULE hLib;
		CString strPath="";
		
		hLib = LoadLibrary( _T( "shell32.dll" ) );
		if ( !hLib ) { return false; }
		typedef HRESULT ( WINAPI *FPSHGetKnownFolderPath )( const GUID&, DWORD, HANDLE, PWSTR * );
		FPSHGetKnownFolderPath func = reinterpret_cast<FPSHGetKnownFolderPath>( GetProcAddress( hLib, "SHGetKnownFolderPath" ) );
		if ( !func ) { FreeLibrary( hLib ); return false; }
		LPWSTR pstr = NULL;
		hr = ( *func )( FOLDERID_LocalAppDataLow, 0, NULL, &pstr );
		if ( FAILED( hr )) { FreeLibrary( hLib ); return false; }
		strPath =  pstr;
		FreeLibrary( hLib );

#if 0
		CString strPath="";

		bool isAppDataLow = true;
		PWSTR pBuffer = NULL;
		HRESULT hr =SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, NULL, &pBuffer );
		if( SUCCEEDED( hr ) )
		{
			// いろいろ処理する
			strPath = pBuffer;
			// メモリを解放
			CoTaskMemFree( pBuffer );
		}
#endif
		strPath += "\\webinter.net";

		if (!CheckPath(strPath.GetBuffer(0))) {
			if (!FCreateDirectory(strPath.GetBuffer(0))) {
				isAppDataLow = false;
			}
		}

		if (isAppDataLow) {
			theProfile.SetProfile(PRIVATE_PROFILE_NAME, strPath);
		}else{
			theProfile.SetProfile(PRIVATE_PROFILE_NAME, "");
		}

	}else{
		theProfile.SetProfile(PRIVATE_PROFILE_NAME, m_cstrDefPath);
	}
#endif

	// クレジットダイアログの表示
/**	if (m_splash.Create(NULL))
		{
		m_splash.ShowWindow(SW_SHOW);
		m_splash.UpdateWindow();
		m_splash.SetTimer(1, 500, NULL);
		m_dwSplashTime = ::GetCurrentTime();
		}
***/
#ifdef SHARWARE
	{
	CString cstr;
	CCrejit crejitDlg;
	switch(crejitDlg.FInitial())
		{
		case CRJ_ER_TIMERREQ:
			cstr.LoadString(IDS_CRJ_TIMERERR);
			AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP | MB_OK);
			return FALSE;
		case CRJ_ER_PASSWORD:
#ifdef PLEASE_TEMP_ID
			if (crejitDlg.DoModal()!=IDOK || crejitDlg.GetTmpID()->IsEmpty())
#else
			if (crejitDlg.DoModal()!=IDOK)
#endif
				return FALSE;
			break;
		//CRJ_ER_OK:
		default:
			break;
		}
	}
#endif //SHARWARE


#ifdef WIN32
	//FDiver32.hlpではなくFDiver.hlpにする。
	static TCHAR ssvHelpFilePath[__MAX_PATH];
	//warning C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//strcpy(ssvHelpFilePath, m_cstrDefPath.GetBuffer(0));
	strcpy_s(ssvHelpFilePath, sizeof(ssvHelpFilePath), m_cstrDefPath.GetBuffer(0));
	//ヘルプファイルの名前変更
	//warning C4996: 'strcat': This function or variable may be unsafe. Consider using strcat_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//strcat(ssvHelpFilePath, "\\fdiver.hlp");
	strcat_s(ssvHelpFilePath, sizeof(ssvHelpFilePath),"\\fdiver.hlp");

	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	free((void*)m_pszHelpFilePath);
	//Change the name of the .HLP file.
	//The CWinApp destructor will free the memory.
	m_pszHelpFilePath=_tcsdup(ssvHelpFilePath);

//	static TCHAR ssvHelpFilePath[__MAX_PATH];
//	strcpy(ssvHelpFilePath, m_cstrDefPath.GetBuffer(0));
//	strcat(ssvHelpFilePath, "\\fdiver.hlp");
//	m_pszHelpFilePath = ssvHelpFilePath;
#endif

#ifdef  _TAG_AUTOOPEN
	m_cDefTagFile.SetDefaultTagFile();
#endif // _TAG_AUTOOPEN

//	theProfile.SetProfile(PRIVATE_PROFILE_NAME, m_cstrDefPath);

	// 検索していないをｾｯﾄ
	SetFindDoingFlg(FALSE);

	// CFindOptionの生成
	vpFindOption = new CFindOption(); // this code must be hear!
	vpFindOption->ReadWriteProfile(TRUE);

	// COptionDlgの生成
	vpOptionDlg = new COptionDlg;
	vpOptionDlg->Initialize(vpFindOption);

	vpcFind = new CFindFile();
	// CGrepｵﾌﾞｼﾞｪｸﾄの生成
	vpcGrep= new CGrep();

	// CFindDialogの生成
	vpFindDlg = new CFindDlg();

	// CKeyOutLogicの生成
	vpKeyOutLogic = new CKeyOutLogic();

	// CMetaStringArrayの作成
	vpMetaStringArray = new CMetaStringArray();


	// アプリケーション用のドキュメント テンプレートを登録します。
	// ドキュメント テンプレートはドキュメント、フレーム ウィンドウとビュー
	// を結合するために機能します。

	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
			RUNTIME_CLASS(CFdiverDoc),
			RUNTIME_CLASS(CMainFrame),     // メイン SDI フレーム ウィンドウ
			RUNTIME_CLASS(CFdiverView)));



#ifdef _TAG
	// DDE Execute open を使用可能にします。
	EnableShellOpen();
	RegisterShellFileTypes();

	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	OnFileNew();
	// メインウィンドウＺオーダー・サイズイニシャルセット

	ASSERT(m_pMainWnd);
	SetWindowPos(m_pMainWnd->GetSafeHwnd(),
		vpFindOption->m_fTopMost ? HWND_TOPMOST:HWND_NOTOPMOST,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
#ifdef NOTUSE
	RECT rc;
	::SetRect(&rc, vpFindOption->m_left,vpFindOption->m_top,
	vpFindOption->m_width ,vpFindOption->m_hight);
	SetWindowPos(m_pMainWnd->GetSafeHwnd(),
		vpFindOption->m_fTopMost ? HWND_TOPMOST:HWND_NOTOPMOST,
		rc.left,rc.top,rc.right,rc.bottom, SWP_SHOWWINDOW );
#endif //NOTUSE

//-->move
	// CFileTransArrayの作成(Must be Create Main Window at this point!)
	//vpFileTransArray = new CFileTransArray();
	//vpFileTransArray->FInitialize(vpFindOption->m_strFTWorkPath.GetBuffer(0));


	CDFile cdOpenFile;
	bool bAutoFindDlgOpen = false;
	if (m_lpCmdLine[0] != '\0')
		{
		// create main window
		/*CMainFrame* pMainFrame = new CMainFrame;
		if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
			return FALSE;
		m_pMainWnd = pMainFrame;
		((CMainFrame*)m_pMainWnd)->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();
		*/
		// open an existing document
	//	cdOpenFile = m_lpCmdLine;
		CString str = m_lpCmdLine;//cdOpenFile.GetBuffer();
		ParseParam(str, varyParams);
		if (varyParams[0][0]!='/')
			cdOpenFile = varyParams[0];
		if (stricmp(cdOpenFile.GetBufferExtention(), "tax")!=0) {
			cdOpenFile = m_cDefTagFile;
			bAutoFindDlgOpen = true;
		}
		m_cDefTagFile.SetModifyed();
		}
	else if (vpFindOption->m_fDefTagAuto) {
		cdOpenFile = m_cDefTagFile;
		m_cDefTagFile.SetModifyed();
	}


	ASSERT(m_pMainWnd);
	((CMainFrame*)m_pMainWnd)->ShowWindow(SW_SHOW);


	// CFileTransArrayの作成(Must be Create Main Window at this point!)
	vpFileTransArray = new CFileTransArray();
	vpFileTransArray->FInitialize(vpFindOption->m_strFTWorkPath.GetBuffer(0));

	m_pMainWnd->UpdateWindow();


	if (vpFindList)
		vpFindList->ResetHeaderType(TRUE);
	if (!cdOpenFile.GetString()->IsEmpty() && cdOpenFile.FExistRealFile())
		OpenDocumentFile(cdOpenFile.GetBuffer());
	if (m_lpCmdLine[0] == '\0')
		{
		CString strTitle;
		VERIFY(strTitle.LoadString(AFX_IDS_APP_TITLE));
		m_pMainWnd->SetWindowText(strTitle);
		}


#else //!_TAG->
	CString strTitle;
	VERIFY(strTitle.LoadString(AFX_IDS_APP_TITLE));
	m_pMainWnd->SetWindowText(strTitle);

	OnFileNew();

	// メインウィンドウＺオーダー・サイズイニシャルセット
	ASSERT(m_pMainWnd);
	SetWindowPos(m_pMainWnd->GetSafeHwnd(),
		vpFindOption->m_fTopMost ? HWND_TOPMOST:HWND_NOTOPMOST,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
#endif //_TAG

// delte cods
//		vpFindOption->m_fTopMost ? HWND_TOPMOST:HWND_NOTOPMOST,
//		vpFindOption->m_left,vpFindOption->m_top,
//		vpFindOption->m_width,vpFindOption->m_hight, 0 /*| SWP_NOMOVE*/ /*| SWP_NOSIZE*/);
//	m_pMainWnd->ShowWindow(SW_SHOW);


	// Drag & Drop Accept
	m_pMainWnd->DragAcceptFiles(); //default prameter = TRUE


	if (bAutoFindDlgOpen) {
		m_pMainWnd->PostMessage(WM_FINDDLG_OPEN, 0,0);
	}

	
	return TRUE;
}

int CFdiverApp::ExitInstance()
{
//#ifdef _DEBUG
//	AfxMessageBox("CFdiverApp::ExitInstance() call Ok!");
//#endif //_DEBUG

	if (vpFileTransArray)
		delete vpFileTransArray;

	if (vpcFind)
		delete vpcFind;

	if (vpcGrep)
		delete vpcGrep;

	// CFindDialogの終了
	if (vpFindDlg)
		delete vpFindDlg;

	if (vpOptionDlg)
		delete vpOptionDlg;

	// CFindOptionの終了
	if (vpFindOption) {
		vpFindOption->ReadWriteProfile(FALSE);
		delete vpFindOption;
	}

	// CFindOptionの終了
	if (vpKeyOutLogic)
		delete vpKeyOutLogic;

	// CMetaStringArrayの終了
	if (vpMetaStringArray)
		delete vpMetaStringArray;

	SaveStdProfileSettings();

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// App About が使用する CAboutDlg クラスのダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnBtnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを起動する App コマンド
void CFdiverApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFdiverApp のコマンド
void CFdiverApp::FinishFind()
{
#ifdef ICON_FLASH
	m_pMainWnd->FlashWindow(TRUE);
/*    PortTool v2.2     1995/10/16    8:0          */
/*      Found   : SetClassWord          */
/*      Issue   : Win32 で３２ビットになった値については SetClassLong を使用して下さい          */
	SetClassWord(m_pMainWnd->GetSafeHwnd(), GCW_HICON, (WORD)LoadIcon(IDR_MAINFRAME));
	m_pMainWnd->FlashWindow(TRUE);
#endif //ICON_FLASH
	SetFindDoingFlg(FALSE);
	if (m_pMainWnd->IsIconic())
		{
		if (vpFindOption->m_fIcon)
			m_pMainWnd->ShowWindow(SW_RESTORE);
#ifdef ICON_FLASH
		else
			m_pMainWnd->FlashWindow(TRUE);
#endif //ICON_FLASH
		}
	//ドキュメントパスへ	だめだったら、アプリのパスへ
	CDFile cdFile = ((CMainFrame *)m_pMainWnd)->GetActiveDocument()->GetPathName();
	if (!SetCurrentPath(cdFile.GetPath().GetBuffer())) //ドキュメントパスへ
		SetCurrentPath(GetDefaultPath().GetBuffer(0));// デフォルトのパスへ戻す
}

BOOL CFdiverApp::OnIdle(LONG lCount) // return TRUE if more idle processing
{
#ifndef NOSEARCH_ONIDLE

	BOOL bMore = CWinApp::OnIdle(lCount);

	// then do our work
	if (m_splash.m_hWnd != NULL)
	{
		if (::GetCurrentTime() - m_dwSplashTime > 3000)
		{
			// timeout expired, destroy the splash window
			m_splash.DestroyWindow();

			m_pMainWnd->UpdateWindow();

	//		if (m_fEnableShowMenuPal && 
	//			!((CMainFrame *)m_pMainWnd)->m_fShowMenuPal)
	//			((CMainFrame *)m_pMainWnd)->DoMenuPal();


			// NOTE: don't set bResult to FALSE,
			//  CWinApp::OnIdle may have returned TRUE

		}
		else
		{
			// check again later...
			bMore = TRUE;
		}
		return bMore;
	}

	if (m_fFindDoing)
		{
		if (vpFindDlg->FFindFileOnly())
			vpcFind->StartScan(NULL, NULL, NULL);
		else
			{
			int iPatternLength;
			if ((iPatternLength=vpcGrep->Init(vpcFind))!=NULL)
				vpcFind->StartScan(vpcGrep->GetEngin(), vpFindOption->m_lReadSize, iPatternLength);
			}
		m_cDefTagFile.SetModifyed();
		FinishFind();
		}
#endif //!NOSEARCH_ONIDLE
	bMore |= CWinApp::OnIdle(lCount);

	return bMore;
}


BOOL CFdiverApp::PreTranslateMessage(MSG* pMsg)
{
	BOOL bResult = CWinApp::PreTranslateMessage(pMsg);

	if (m_splash.m_hWnd != NULL &&
		(pMsg->message == WM_KEYDOWN ||
		 pMsg->message == WM_SYSKEYDOWN ||
		 pMsg->message == WM_LBUTTONDOWN ||
		 pMsg->message == WM_RBUTTONDOWN ||
		 pMsg->message == WM_MBUTTONDOWN ||
		 pMsg->message == WM_NCLBUTTONDOWN ||
		 pMsg->message == WM_NCRBUTTONDOWN ||
		 pMsg->message == WM_NCMBUTTONDOWN))
	{
		m_splash.DestroyWindow();
		m_pMainWnd->UpdateWindow();
	}

	return bResult;
}

//void CFdiverApp::OnActChgpath()
//{
//	CDString cdstr = GetPathFromDlg();	
//	if (!cdstr.IsEmpty())
//		vpFindDlg->m_cStrPath = cdstr;
//}

void CFdiverApp::OnOptFind()
{
	vpOptionDlg->DoModal();
}


void CFdiverApp::OnFTotop()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
//	m_pMainWnd->SetWindowPos(
//		(vpFindOption->m_fTopMost = !vpFindOption->m_fTopMost) ?
//		 &m_pMainWnd->wndTopMost:&m_pMainWnd->wndNoTopMost,0,0,0,0,
//		 SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(m_pMainWnd->GetSafeHwnd(),
		(vpFindOption->m_fTopMost = !vpFindOption->m_fTopMost) ?
		 HWND_TOPMOST:HWND_NOTOPMOST,0,0,0,0,
		 SWP_NOMOVE | SWP_NOSIZE);
}



void CFdiverApp::OnMyHelpIndex()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	SuportUrlBrowse(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), TRUE);


//	CWinApp::OnHelpIndex();
//	if (vpFindOption->m_fTopMost)
//		{
//		HWND hWnd=FindWindow("MS_WINHELP","Fdiver");
//		if (hWnd)
//			SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
//		}
}



void CFdiverApp::OnActEditer()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	CDFile cdfile;
//	HINSTANCE hInst;

	if (!vpFindOption->m_strEditer.IsEmpty())
		{
		//CString str;
		//CDFile strPath;
		//strPath =vpFindOption->m_strEditer;
		//str = strPath.GetPath();
		//strPath = _T("\"")+str+_T("\"");
		//str = _T("\"")+vpFindOption->m_strEditer+_T("\"");
		//hInst=FindExecutable(str, strPath.GetBuffer(), vz);
		//cdfile = vz;
		CString str;
		str= _T("\"")+vpFindOption->m_strEditer+_T("\"");
		cdfile = str;
		}
	else
		cdfile = "notepad.exe";

	if (::WinExec(cdfile.GetBuffer(), SW_SHOWNORMAL)<32)
		{
		cdfile = "notepad.exe";
		if (::WinExec(cdfile.GetBuffer(), SW_SHOWNORMAL)<32)
			{
			CString cstr;
			cstr.LoadString(IDS_ACTEDITER_ERR);
			AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP | MB_OK);
			}
		}
}

void CFdiverApp::OnActClone()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	CDFile cdfile;
//	HINSTANCE hInst;

	GetModuleFileName(m_hInstance, (char *)vz, sizeof(vz));

	cdfile = vz;

	if (::WinExec(cdfile.GetBuffer(), SW_SHOWNORMAL)<32)
		{
		CString cstr;
		cstr.LoadString(IDS_ACTEDITER_ERR);
		AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP | MB_OK);
		}
}

void CFdiverApp::OnOptIcon()
{
	// TODO: この位置にコマンド ハンドラのコードを追加してください。
	vpFindOption->m_fIcon = !vpFindOption->m_fIcon;
	
}


/*
void CFdiverApp::OnSetFocus(CWnd* pOldWnd)
{
	CWinApp::OnSetFocus(pOldWnd);
	vpFindList->SetFocus();
}
*/
// アプリケーションファイルのあるパスをセット
CString CFdiverApp::GetDefaultPath()
{
#if BUG20120112
	CString str = UserPath::myDocuments().c_str();
	return str;
#if 0
	GetModuleFileName(m_hInstance, (char *)vz, sizeof(vz));
	CDString cdstr = (char *)vz;
	if (cdstr.IsEmpty())
		{
		ASSERT(FALSE);
		return cdstr;
		}
	int i = cdstr.ReverseFind('\\');
	if (i<0)
		{
		ASSERT(FALSE);
		cdstr.Empty();
		return cdstr;
		}
	return cdstr.Left(i);
#endif
#else
	if (vbUperVista) {
		CString str = UserPath::myDocuments().c_str();
		return str;
	}else{
		GetModuleFileName(m_hInstance, (char *)vz, sizeof(vz));
		CDString cdstr = (char *)vz;
		if (cdstr.IsEmpty())
			{
			ASSERT(FALSE);
			return cdstr;
			}
		int i = cdstr.ReverseFind('\\');
		if (i<0)
			{
			ASSERT(FALSE);
			cdstr.Empty();
			return cdstr;
			}
		return cdstr.Left(i);
	}
#endif
}
void CFdiverApp::OnFileOpen()
{
	CString newName;
	if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
	  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		return; // open cancelled

	CDocument *pDoc=((CMainFrame *)m_pMainWnd)->GetActiveDocument();
	if (newName==pDoc->GetPathName())
		pDoc->SetPathName("");	// 再オープン
	OpenDocumentFile(newName);
		// if returns NULL, the user has already been alerted
}

#ifdef SHARWARE
void CFdiverApp::OnCrejit() 
{
	// TODO: Add your command handler code here
	CCrejit crejitDlg;
	crejitDlg.DoModal();
}
#endif //SHARWARE
void CFdiverApp::OnUpdateCrejit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef SHARWARE
	pCmdUI->Enable(!GetFindDoingFlg());
#else
	pCmdUI->Enable(FALSE);
#endif //SHARWARE
}


void CAboutDlg::OnBtnBrowse() 
{
	SuportUrlBrowse(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), FALSE);
}
