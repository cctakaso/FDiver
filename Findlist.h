/*    PortTool v2.2     findlist.h          */

/***********************************************************************************
-- Class Name: C F i n d L i s t   c l a s s 
-- Description and Usage:
【機能概要】
	

-- Notes:---------------------------------------------------------------------------
-- History:
		'94.8	- created		(M.Design)
**************************************************************************************/
#ifndef __FINDLIST_H__
#define __FINDLIST_H__
#include "dbmpstr.h"
#include "ffile.h"
#include "lstent.h"
#include "metachar.h"
#include "findlog.h"
class CFindList:public CDBmpStrList//CListBox
{
	DECLARE_DYNCREATE(CFindList)
protected:
	long m_lLineBefor;
	CDString m_cStrLstBefor;
	CListEntry m_LstEntry;
	// 項目を追加する
	virtual int AddString ( CListEntry* bsl_entry) ;
	BOOL AddStringToMemOnly ( CListEntry* bsl_entry );
	int m_OptOfViewString;
	BOOL m_fStopScroll;
	size_ent m_wTmpEntry;	//ﾃﾝﾎﾟﾗﾘｶｳﾝﾀ
	CDFile m_dTmpFileTxt;	// ﾃﾝﾎﾟﾗﾘTxtﾌｧｲﾙ
	//takaso2010
	CListEntry *m_pLstEntry_save;
public:
	CFindList();
	~CFindList();

//	virtual BOOL Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int nHeight,
//		struct BSLIST_RESIDS *bsl_resids, int entrys, HFONT hfont= NULL);
	// または、次の関数を続けて呼ぶ
//	virtual BOOL Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	CFindLog m_FindLog;
	DWORD m_wFileCount;	// file counter
	DWORD m_wFoundDirs;	// found counter
	DWORD m_wFoundFiles;	// found counter
 	DWORD m_wFoundCount;	// found counter
	//size_ent m_wFileCount;	// file counter
	//size_ent m_wFoundDirs;	// found counter
	//size_ent m_wFoundFiles;	// found counter
 	//size_ent m_wFoundCount;	// found counter
	
	//漢字コード変換マーク"*"の為に、ファイル名エントリーへのポインタを保存しておく
	DWORD m_wLastFileListEntry;
	CListEntry *GetLastFileListEntry() {
		return m_wLastFileListEntry>=0 ? &m_pEntryArray->m_bse[m_wLastFileListEntry]:NULL; }
	CListEntry *GetSelListEntry() {
		size_ent nIndex = GetDataIndexFromSel(GetCurSel());
		return (nIndex==(size_ent)-1) ? NULL:&m_pEntryArray->m_bse[nIndex]; }

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	// ﾒﾓﾘｴﾝﾄﾘｰ数を取得します
	size_ent GetMemEntrys() {
		return m_pEntryArray->m_wUseEntry; }

	// 検索結果ﾘｽﾄへの追加(ﾃﾞｨﾚｸﾄﾘ＆ﾌｧｲﾙ)
	BOOL FAddList(CFindFile *pFindFile, ReturnLogic rl=rlTrue);
	// 検索結果ﾘｽﾄへの追加(位置&文書)
	BOOL FAddList(CFindFile *pFindFile, long lMatchFirst, long cchMatched, BYTE far *lpchDoc, ReturnLogic rl=rlTrue);
	// ﾃﾝﾎﾟﾗﾘｴﾝﾄﾘｰ配列から最後のｴﾝﾄﾘｰのみを破棄する
	void DeleteLastOneOfList();
	// ﾃﾝﾎﾟﾗﾘｴﾝﾄﾘｰ配列から実データへｱｯﾌﾟﾃﾞｰﾄして、ﾃﾝﾎﾟﾗﾘを破棄する
	BOOL FAddListFromTempList(CFindFile *pFindFile, ReturnLogic rl);

	//新しい表示ｵﾌﾟｼｮﾝに従って表示し直します。
	int ResetViewString (BOOL bSel=FALSE);

	// 項目をCListに、追加します。
	int ViewString (size_ent nIndex, BOOL fCheckOpen, int insPos=-1);
	
	BOOL AddString();
	// AddString()のﾒﾓﾘにだけ追加するﾊﾞｰｼﾞｮﾝ
	BOOL AddStringToMemOnly();
	// AddString()のListBoxにだけ追加するﾊﾞｰｼﾞｮﾝ
	BOOL AddStringToLstBoxOnly(int indexAppend);

	void ResetContent();
	void ResetList();
	void ResetSort() {
		m_pEntryArray->ResetSort(); }
	BOOL OnChildNotify ( UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT* pLResult );
	BOOL FMachBefor(char *sz, long lLine);
	// ディスプレイタイプをセットします

	void OpenDocument(BOOL fEditer);
	void OpenDocumentByApp(char *szExe);
	void OpenDocument(LPCSTR lpszFileName, long lLine=0, DWORD dwHexNum=0, BOOL fEditer=TRUE, char *szExe = NULL);

	SORTTYPE GetSortType() {
		return m_pEntryArray->m_SortType; }
	void SortList(SORTTYPE st);
	void ListInPathOrFile(BOOL bOpenPath, BOOL bOpenFile);
	void EnterListItem(BOOL fEditer, UINT nChar=0);

	BOOL IsSelectedFile();
	BOOL IsSelectedLine();

	void ResetHeaderType(BOOL bReset=FALSE);
	void ResetHeaderCx() {
		m_header.ResetHeaderType(-1, true);
	}

	#ifdef _TAG_TEXT
	void WriteTagText(CStdioFile &file);
	#endif

// メッセージ マップ関数の生成を行います。
	//{{AFX_MSG(CFindList)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnActDispdocedit();
	afx_msg void OnActDispdoc();
	afx_msg void OnOpenFolder();
	afx_msg void OnEditCopy1();
	afx_msg void OnEditRefFile();
	afx_msg void OnUpdateActDispdocedit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActDispdoc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRefFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDellFile(CCmdUI* pCmdUI);
	afx_msg void OnEditDellFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
typedef struct {
	int wSize;	//Size of data structure(16bit and 32bit support)
	POINT ptMousePos;	//Point of mouse cursor
	BOOL fInNonClientArea;	//Window's non-client area
#ifdef WIN32
	BOOL fUnicode;		// Are the pathnames in Unicode?
#endif //WIN32

/*    PortTool v2.2     1995/10/16    8:21          */
/*      Found   : FAR          */
/*      Issue   : Win32 ではセグメントを用いません。従って FAR == NEAR == 指定なし！          */
}DROPFILESTRUCT, FAR *LPDROPFILESTRUCT;

// Drag server Single file version.
BOOL DragServerForSingleFile(HWND hWnd, CListEntryArray *pEntryArray, size_ent nIndex, BOOL fCtrKey);
// Drop-file struct memory block create function
HDROP DragCreateFiles(LPPOINT lpptMousePos, BOOL fInNonClientArea);
// Append file name to Drop-file struct memory block function
HDROP DragAppendFile(HGLOBAL hDrop, LPCSTR szPathname);

#endif //__FINDLIST_H__
