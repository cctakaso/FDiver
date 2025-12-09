// FileDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "FDiver.h"
#include "FileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDlg

IMPLEMENT_DYNAMIC(CFileDlg, CFileDialog)

CFileDlg::CFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CFileDlg, CFileDialog)
	//{{AFX_MSG_MAP(CFileDlg)
		// メモ -  ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

