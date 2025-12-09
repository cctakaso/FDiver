// FDiver.h : FDIVER アプリケーションのメイン ヘッダー ファイル
#ifndef _FDIVER_H__
#define _FDIVER_H__
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メインシンボル
#define _TAG_AUTOOPEN		//Default Tag Open
#define _TAG_TEXT
#include "tagfile.h"
#include "Splash.h"

extern BOOL svbDontCheckSemiFile;
/////////////////////////////////////////////////////////////////////////////
// CFdiverApp:
// このクラスの動作の定義に関しては Fdiver.cpp ファイルを参照してください。
//
#define WM_FINDDLG_OPEN	(WM_USER+10)

class CFdiverApp : public CWinApp
{
protected:
	BOOL m_fFindDoing;	// 検索中ﾌﾗｸﾞ(検索中止のﾌﾗｸﾞにも使われる)
	CString m_cstrDefPath; // アプリケーションファイルのあるパスをセット
public:
	CString GetDefaultPath();
	CFdiverApp();
	BOOL GetFindDoingFlg() {
		return m_fFindDoing; }
	void SetFindDoingFlg(BOOL f) {
		svbDontCheckSemiFile = m_fFindDoing = f; }
	char *PGetDefaltPath() {
		return m_cstrDefPath.GetBuffer(0); }
	void FinishFind();

#ifdef  _TAG_AUTOOPEN
	CTagFile m_cDefTagFile;	//default tag file.
#endif // _TAG_AUTOOPEN

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CFDiverApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount); // return TRUE if more idle processing
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CFdiverApp)
	afx_msg void OnAppAbout();
	afx_msg void OnOptFind();
	afx_msg void OnFTotop();
	afx_msg void OnMyHelpIndex();
	afx_msg void OnActEditer();
	afx_msg void OnActClone();
	afx_msg void OnOptIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnCrejit();
	afx_msg void OnUpdateCrejit(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DWORD m_dwSplashTime;
	CSplash m_splash;

};
/////////////////////////////////////////////////////////////////////////////

#endif// _FDIVER_H__
