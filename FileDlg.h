// FileDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CFileDlg ダイアログ

class CFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CFileDlg)

public:
	CFileDlg(BOOL bOpenFileDialog, // TRUE ならば FileOpen、 FALSE ならば FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CFileDlg)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
