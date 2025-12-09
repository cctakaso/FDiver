/*    PortTool v2.2     dbmpstr.h          */

/***********************************************************************************
-- Class Name: C D B m p S t r L i s t ／ C D B m p S t r C o m b o  c l a s s 
-- Description and Usage:
【機能概要】
　ＭＦＣのリストボックスクラスから派生させたこのクラスは、オーナードロウのリスト
　ボックスをより簡単に表示できるようにしたクラスです。

-- Notes:---------------------------------------------------------------------------
　94/9/2現在での不具合
	マウスダブルクリックなどの代わりに、キーボードでの操作ができません。

-- History:
		'94.8	- created		(M.Design)
**************************************************************************************/
//LISTBOX DEFINE
#undef this_class_id
#define this_class_id 0

#undef __DBMPSTR_H__

#if this_class_id==0
 #ifndef __DBMPSTRLIST_H__
  #define __DBMPSTRLIST_H__
 #else
  #define __DBMPSTR_H__
 #endif

#elif this_class_id==1
 #ifndef __DBMPSTRCOMBO_H__
  #define __DBMPSTRCOMBO_H__
 #else
  #define __DBMPSTR_H__
 #endif
#else
 #error そのようなクラスはサポートしていません。
#endif

#ifndef __DBMPSTR_H__

#include <afxwin.h>
#include <mbstring.h>
//#include "..\lib\dstring.h"
//#include "dstring.h"
#include "..\mdfc\dfileexp.h"
#include "lstent.h"
#include "HeaderCtrlEx.h"

#undef THIS_CLASS
#undef BASE_CLASS
#undef BMPSTR_RESETCONTENT
#undef BMPSTR_ADDSTRING
#undef BMPSTR_INSERTSTRING
#undef BMPSTR_DELETESTRING
#undef BMPSTR_GETITEMDATA
#undef BMPSTR_SETITEMDATA
#undef BMPSTR_GETCURSEL
#undef BMPSTR_SETITEMHEIGHT
#undef BMPSTR_ERR
#undef BMPSTR_ERRSPACE

#if this_class_id==0
 #define THIS_CLASS CDBmpStrList
 #define BASE_CLASS CListBox
 #define BMPSTR_RESETCONTENT	LB_RESETCONTENT	//DeleteAllItems()
 #define BMPSTR_ADDSTRING	LB_ADDSTRING	//InertItem(
 #define BMPSTR_INSERTSTRING	LB_INSERTSTRING	//
 #define BMPSTR_DELETESTRING	LB_DELETESTRING	//BOOL DeleteItem( int nItem );
 #define BMPSTR_GETITEMDATA	LB_GETITEMDATA	//DWORD GetItemData( int nItem );
 #define BMPSTR_SETITEMDATA	LB_SETITEMDATA	//BOOL SetItemData( int nItem, DWORD dwData );
 #define BMPSTR_GETCURSEL	LB_GETCURSEL	//UINT GetSelectedCount( ) const;int FindItem( LV_FINDINFO* pFindInfo, int nStart = -1 ) const;
 #define BMPSTR_SETITEMHEIGHT	LB_SETITEMHEIGHT	//
 #define BMPSTR_ERR			LB_ERR
 #define BMPSTR_ERRSPACE		LB_ERRSPACE
 #define BMPSTR_GETCOUNT	LB_GETCOUNT
#elif this_class_id==1
 #define THIS_CLASS CDBmpStrCombo
 #define BASE_CLASS CComboBox
 #define BMPSTR_RESETCONTENT	CB_RESETCONTENT
 #define BMPSTR_ADDSTRING	CB_ADDSTRING
 #define BMPSTR_INSERTSTRING	CB_INSERTSTRING
 #define BMPSTR_DELETESTRING	CB_DELETESTRING
 #define BMPSTR_GETITEMDATA	CB_GETITEMDATA
 #define BMPSTR_SETITEMDATA	CB_SETITEMDATA
 #define BMPSTR_GETCURSEL	CB_GETCURSEL
 #define BMPSTR_SETITEMHEIGHT	CB_SETITEMHEIGHT
 #define BMPSTR_ERR			CB_ERR
 #define BMPSTR_ERRSPACE		CB_ERRSPACE
 #define BMPSTR_GETCOUNT	CB_GETCOUNT
#else
 #error そのようなクラスはサポートしていません。
#endif

#ifndef BASE_CLASS
 #error クラスのベースとなるクラス CListBox or CComboBox を、指定してください。
#endif

#ifndef __DBMPSTR_COM_H__
#define __DBMPSTR_COM_H__

enum BSLIST_RESID_GROUP{
	small_group,
	midiam_group,
	large_group,
	max_group
};
// ビットマップリソースグループデータテーブル.
// BMP の高さとリソースＩＤが入る.
struct BSLIST_RESIDS{
	int iMaxHeight ;
	int resid ;
};
#endif //__DBMPSTR_COM_H__

//	*
//
/*
enum SORTTYPE {
	ST_NAME,
	ST_TYPE,
	ST_SIZE,
	ST_DATE,
	};
*/
class CDBmpStrList:public CListBox
{

//#if this_class_id==0
	DECLARE_DYNAMIC ( CDBmpStrList )
//#elif this_class_id==1
//	DECLARE_DYNAMIC ( CDBmpStrCombo )
//#else
//    #error そのようなクラスはサポートしていません。
//#endif

#ifndef MAKEDWORD

#define MAKEDWORD(low, high)	((DWORD)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

protected:

	/* serialize-> */
	CListEntryArray *m_pEntryArray ;	// ｴﾝﾄﾘｰﾊﾞｯﾌｧ
	/* <-serialize */


	int m_iHeight ;		//リスト高さ
	int m_iHeight_back ;

	int m_iFontHeight;
	int m_iResID;		//使用するﾋﾞｯﾄﾏｯﾌﾟリソースID
	int m_iResHeight;
	COLORREF m_frColor;
	COLORREF m_bkColor;
	CBrush m_bkBrush;
	int m_ratioBetweenLine;

	// 現在のﾌｫﾝﾄの高さを取得する
	int GetFontHeight();


	// 選択セル番号から実データインデックスを取得する。
	size_ent GetDataIndexFromSel(size_ent sel);
	// 実データインデックスに対応する項目を選択状態にする
	BOOL SetSelFromDataIndex(size_ent sel);

	// 項目が選択されていないとき、-1 を返す.
	size_ent GetCurSelDataOffset();


#ifdef WIN32
	CImageList *MyLoadBitmap(int nID, int hight, COLORREF cr);
	CImageList *m_phbmRes[2];
#else
	HBITMAP MyLoadBitmap(int nID, DWORD rgbToUse);
	DWORD RGBToBGR(DWORD rgb);
	HBITMAP m_phbmRes[2];
	BITMAP m_bm;		// ﾋﾞｯﾄﾏｯﾌﾟｵﾌﾞｼﾞｪｸﾄ情報
	CDC m_dcMem ;		// ﾋﾞｯﾄﾏｯﾌﾟ用のﾒﾓﾘＤＣ
#endif
	CHeaderCtrlEx m_header;

public:

	CDBmpStrList() ;
	~CDBmpStrList() ;

	// リストボックスの作成
	// pParentWnd親ウィンドウの、rect矩形位置に子ウィンドウ番号nID、１つのエ
	// ントリの高さを、nHight、リストボックスで使う bitmap を bsl_resids に、
	// リスト自体のフォントを cfnt フォントにて作成するように登録.
	virtual BOOL Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int nHeight,
		struct BSLIST_RESIDS *bsl_resids, int entrys, HFONT hfont= NULL);
	// または、次の関数を続けて呼ぶ
	virtual BOOL Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void Initial(struct BSLIST_RESIDS *bsl_resids, int entrys, HFONT hfont=0, int nHeight=0);


	// 最初にエントリー用のバッファを確保しておく
	BOOL SetInitialMemory(size_ent entry){
		BOOL f=FExpandEntry(entry);
		m_pEntryArray->m_wUseEntry = 0;
		return f;
		}

	// インプリメンテーション




	// 現在選択中の種類を返す.
	int GetCurEntryType(void) ;//const ;

	// 現在選択中のエントリを返す。
	CListEntry GetCurEntry();

	// インデックス位置のエントリを返す.
	CListEntry GetEntry ( size_ent sel );

	// 使用するテーブルを新しくする.
	virtual BOOL FResetEntry ( CListEntry* bsl_entry, size_ent entorys ) ;
	
	// 項目を追加する
	virtual int AddString ( CListEntry* bsl_entry) ;
	
	// 項目を複数削除する
	int DeleteString (int selFirst, int selCount=1 );

	// データおよび表示項目を全て削除する。
	void ResetContent();

	// リスト自体で使用する、フォントハンドルを設定.
	// 設定なき場合は、システムフォントを使用.
	BOOL FSetFont ( HFONT hfont = NULL ) ;

	// 項目が選択されていないとき、-1 を返す.
	int GetCurSel() const ;

	// 文字列を探して、選択状態にする.
	//int SelectString ( int nStartAfter, LPCSTR lpszItem ) ;

	// 文字列を探す
	//int FindString ( int nStartAfter, LPCSTR lpszItem ) ;
	// 文字列をキーにして、項目のアプリケーション設定値を取得する。
	//void SetAppItemDataFromStr(char *sz, WORD wApp);
	
	// ｴﾝﾄﾘｰﾊﾞｯﾌｧへのﾎﾟｲﾝﾀ取得
	CListEntryArray *RenewEntryArray() {
		CListEntryArray *pOld = m_pEntryArray;
		m_pEntryArray = new CListEntryArray;
		return pOld;
		} ;

	void LayoutWindowRect(LPRECT lpClientRect, BOOL bShowHeader);
	void SetColors(COLORREF frColor, COLORREF bkColor, int ratioBetweenLine, BOOL bUpdate=TRUE);

	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CDBmpStrList)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnChildNotify ( UINT, WPARAM, LPARAM, LRESULT* ) ;
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

protected:
	// 登録ｴﾝﾄﾘｰを拡張する
	BOOL FExpandEntry ( size_ent entrys );

	//{{AFX_MSG(CDBmpStrList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor) ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

#endif //#ifndef __DBMPSTR_H__
