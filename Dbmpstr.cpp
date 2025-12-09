/*    PortTool v2.2     DBMPSTR.CPP          */

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
#include "stdafx.h"
#define DHEADER



#include "lstent.h"
#include "dbmpstr.h"
#include <mbstring.h>
// i.e. USE _fmemcpy
#include <memory.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// インプリメント
//IMPLEMENT_DYNAMIC ( THIS_CLASS, BASE_CLASS )
//#if this_class_id == 0
IMPLEMENT_DYNAMIC ( CDBmpStrList, CListBox )
// #elif this_class_id == 1
//IMPLEMENT_DYNAMIC ( CDBmpStrCombo, CComboBox )
//#else
// #error クラスなし
//#endif

#define ITEM_ADJUST	(3)
#define BMP_HIGHT	16
#define BMP_WIDTH_ADJUST	5/4


BEGIN_MESSAGE_MAP( CDBmpStrList, CListBox )
	//{{AFX_MSG_MAP(CDBmpStrList)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

	//ON_WM_CTLCOLOR()

/*************************************************************************
-- Routine: CDBmpStrList::CDBmpStrList () : BASE_CLASS()
-- Description and Usage:
		コンストラクタ。構造体の初期化を行います。
-- Arguments:
		なし。
-- Returns:
        なし。
-- Notes:
-- History:
		'94.8	- created		(M.Design)
*************************************************************************/
CDBmpStrList::CDBmpStrList () : BASE_CLASS()
{
	m_pEntryArray = new CListEntryArray;
	ASSERT(m_pEntryArray);
	m_iHeight = m_iHeight_back = 1;		//リスト高さ
	m_iResID = 0;		//使用するリソースID
	m_iFontHeight = 0;
#ifdef WIN32
	m_phbmRes[0] = NULL;
	m_phbmRes[1] = NULL;
#endif
	m_iResHeight = 0;
	m_frColor = GetSysColor(COLOR_WINDOWTEXT);
	m_bkColor = GetSysColor(COLOR_WINDOW);
	m_ratioBetweenLine = 0;
}

BOOL CDBmpStrList::PreCreateWindow(CREATESTRUCT& cs)
{

	return(CListBox::PreCreateWindow(cs));
}
/*************************************************************************
-- Routine: CDBmpStrList::CDBmpStrList () : Serialize(CArchive& ar)
-- Description and Usage:
		シリアライズ
-- Arguments:
		なし。
-- Returns:
        なし。
-- Notes:
-- History:
		'95.10	- created		(M.Design)
*************************************************************************/
void CDBmpStrList::Serialize(CArchive& ar)
{
	if (!ar.IsStoring())
		{
		BASE_CLASS::ResetContent();
		}
	m_pEntryArray->Serialize(ar);
}
/*************************************************************************
-- Routine:BOOL CDBmpStrList::Create ( DWORD dwStyle, const RECT& rect,
				CWnd* pParentWnd, UINT nID,	int nHeight,
				struct BSLIST_RESIDS * bsl_resids, size_ent entrys, HFONT hfont)
-- Description and Usage:
			リストボックスを作成、初期化します.
-- Arguments:
			DWORD dwStyle					 - リストボックスのスタイル.
			const RECT& rect				 - リストボックスの RECT.
			CWnd* pParentWnd				 - 親ウィンドウハンドル.
			UINT  nID						 - 作成するリストボックスの ID.
			struct BSLIST_RESIDS *bsl_resids	 - ﾘｿｰｽIDﾃｰﾌﾞﾙﾎﾟｲﾝﾀ
			int   entrys					 - ﾘｿｰｽIDﾃｰﾌﾞﾙのｴﾝﾄﾘｰ数
			int   nHeight					 - 作成するリストボックスの１項目の高さ.
-- Rurns:
			TRUE  - リストボックスの作成、初期化に成功.
			FALSE - 　　　　　　　　作成に失敗.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
BOOL CDBmpStrList::Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,	int nHeight,
			struct BSLIST_RESIDS *bsl_resids, int entrys, HFONT hfont)
{

	if (Create ( dwStyle, rect, pParentWnd, nID)==FALSE)
		return FALSE;
	Initial(bsl_resids, entrys, hfont, nHeight);

	return TRUE;
}

BOOL CDBmpStrList::Create ( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	TRACE ( "\n - CDBmpStrList::Create - " ) ;
	TRACE ( "OWNER DRAW のリストボックスを作成します." ) ;

	// リストボックスの作成.
#if this_class_id==0
	if (!CWnd::Create ( "LISTBOX", NULL, dwStyle | LBS_DISABLENOSCROLL | LBS_NOTIFY | WS_TABSTOP |
							/*LBS_WANTKEYBOARDINPUT |*/ LBS_OWNERDRAWFIXED, rect, pParentWnd, nID ) )
#elif this_class_id==1
	if (!CWnd::Create ( "COMBOBOX", NULL, dwStyle | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | WS_TABSTOP,
							rect, pParentWnd, nID ) )
#else
#error  エラーじゃ
#endif
		{
		TRACE ( "リストボックスの作成に失敗しました." ) ;
		ASSERT ( FALSE ) ;
		return ( FALSE ) ;
		}
	return TRUE;
}
/*************************************************************************
-- Routine: BOOL CDBmpStrList::Initial (struct BSLIST_RESIDS * bsl_resids,
				size_ent entrys, HFONT hfont=0, int nHeight=0)
-- Description and Usage:
			リストボックスを作成、初期化します.
-- Arguments:
			struct BSLIST_RESIDS *bsl_resids - ﾘｿｰｽIDﾃｰﾌﾞﾙﾎﾟｲﾝﾀ
			int   entrys					 - ﾘｿｰｽIDﾃｰﾌﾞﾙのｴﾝﾄﾘｰ数
			HFONT hfont						 - ﾌｫﾝﾄﾊﾝﾄﾞﾙ
			int   nHeight					 - 作成するリストボックスの１項目の高さ.
-- Rurns:
			TRUE  - リストボックスの初期化に成功.
			FALSE - 　　　　　　　　初期化に失敗.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
void CDBmpStrList::Initial(struct BSLIST_RESIDS *bsl_resids, int entrys,  HFONT hfont, int nHeight)
{
	int i;
	//initialize bitmap's resources.
#ifdef WIN32
	if (m_phbmRes[0])
		delete m_phbmRes[0];
	if (m_phbmRes[1])
		delete m_phbmRes[1];
#else
	if (m_iResID)
		{
		DeleteObject(m_phbmRes[0]) ;
		DeleteObject(m_phbmRes[1]) ;
		}
#endif

#ifndef WIN32
	if (m_dcMem.GetSafeHdc())
		m_dcMem.DeleteDC() ;
#endif

	// フォントの設定.
	if (hfont)
		{
		FSetFont ( hfont );
		m_iFontHeight=0;
		}

	// 高さが=0の場合は、ﾘｽﾄで使用されているﾌｫﾝﾄの高さを取得してｾｯﾄする
	if (nHeight==0)
		{
		m_iFontHeight = m_iHeight = GetFontHeight();
		}
	else
		m_iHeight = nHeight;

	if (m_iHeight<bsl_resids[0].iMaxHeight)
		m_iHeight = bsl_resids[0].iMaxHeight;

	m_iHeight_back = m_iHeight;
	m_iHeight = (m_iHeight_back * (100+m_ratioBetweenLine))/100;

	ASSERT(m_iHeight>0);
	// 項目の高さをセット.
	::SendMessage ( m_hWnd, BMPSTR_SETITEMHEIGHT, 0, MAKELPARAM ( m_iHeight, 0 ) ) ;
#if this_class_id==1	//コンボのｴﾃﾞｨｯﾄﾎﾞｯｸｽは、ﾘｽﾄ項目に比べて大きくしないと文字が入らないぞ！
	::SendMessage ( m_hWnd, BMPSTR_SETITEMHEIGHT, -1, MAKELPARAM ( m_iHeight+6, 0 ) ) ;
#endif

	// ビットマップリソースＩＤの選定
	for (i = 0 ; i<entrys; i++)
		{
		if ( m_iHeight <= bsl_resids[i].iMaxHeight )
			break ;
		}
	m_iResID = bsl_resids[i==entrys ? --i:i].resid;
	m_iResHeight = bsl_resids[i].iMaxHeight;
#ifdef WIN32
	m_phbmRes[0]=MyLoadBitmap(m_iResID, m_iResHeight, m_bkColor);
	ASSERT(m_phbmRes[0]);
	m_phbmRes[1]=MyLoadBitmap(m_iResID, m_iResHeight, GetSysColor(COLOR_HIGHLIGHT));
	ASSERT(m_phbmRes[1]);
#else
	m_phbmRes[0]=MyLoadBitmap(m_iResID, RGBToBGR(m_bkColor));
	ASSERT(m_phbmRes[0]);
	m_phbmRes[1]=MyLoadBitmap(m_iResID, RGBToBGR(GetSysColor(COLOR_HIGHLIGHT)));
	ASSERT(m_phbmRes[1]);

	// ビットマップ情報の設定
	CDC  *pDC;
	//BITMAP m_bm ;
	CBitmap cBmp ;
	int iOldDC;
	CBitmap* pOldBitmap;
	//CDC m_dcMem ;

	pDC = GetDC();
	if ( !m_dcMem.CreateCompatibleDC ( pDC ) )
		{
		TRACE ( "\nデバイスコンテキストが作成できません." ) ;
		ASSERT ( FALSE ) ;
		return ;
		}

	iOldDC = m_dcMem.SaveDC();
	cBmp.Attach(m_phbmRes[0]);
	pOldBitmap = m_dcMem.SelectObject ( &cBmp ) ;

	cBmp.GetObject ( sizeof(m_bm), &m_bm ) ;

	m_dcMem .SelectObject ( pOldBitmap ) ;
	m_dcMem.RestoreDC ( iOldDC ) ;
	cBmp.Detach();
	ReleaseDC(pDC);
#endif

}

void CDBmpStrList::SetColors(COLORREF frColor, COLORREF bkColor, int ratioBetweenLine, BOOL bUpdate)
{
	m_frColor = frColor;
	m_bkColor = bkColor;
	m_ratioBetweenLine = ratioBetweenLine;
	m_iHeight = (m_iHeight_back * (100+m_ratioBetweenLine))/100;

	ASSERT(m_iHeight>0);
	// 項目の高さをセット.
	::SendMessage ( m_hWnd, BMPSTR_SETITEMHEIGHT, 0, MAKELPARAM ( m_iHeight, 0 ) ) ;

	if (m_bkBrush.GetSafeHandle() )
		{
		VERIFY(SetClassLong(GetSafeHwnd(), GCL_HBRBACKGROUND, COLOR_WINDOW));
		m_bkBrush.DeleteObject();
		}
	if (GetSafeHwnd() && m_bkBrush.CreateSolidBrush(m_bkColor))
		SetClassLong(GetSafeHwnd(), GCL_HBRBACKGROUND, (long)m_bkBrush.GetSafeHandle());
		//VERIFY(SetClassLong(GetSafeHwnd(), GCL_HBRBACKGROUND, (long)m_bkBrush.GetSafeHandle()));
	if (bUpdate)
		{
		if (m_phbmRes[0])
			delete m_phbmRes[0];
		m_phbmRes[0]=MyLoadBitmap(m_iResID, m_iResHeight, m_bkColor);
		ASSERT(m_phbmRes[0]);
		Invalidate();
		UpdateWindow();
		}
}

#ifdef WIN32
CImageList *CDBmpStrList::MyLoadBitmap(int nID, int hight, COLORREF cr)
{
	CImageList *image = new CImageList;
	ASSERT(image);
	VERIFY(image->Create(nID, hight, 1, RGB(0,0,255)));
	image->SetBkColor(cr);
	return image;
}
#else
HBITMAP CDBmpStrList::MyLoadBitmap(int nID, DWORD rgbToUse)
{
  static int siOffset=0;
  HDC			hDC;
  HRSRC			h;

/*    PortTool v2.2     1995/10/16    7:57          */
/*      Found   : FAR          */
/*      Issue   : Win32 ではセグメントを用いません。従って FAR == NEAR == 指定なし！          */
  DWORD FAR		*p;
  LPSTR 		lpBits;
  HANDLE		hRes;
  HBITMAP		hBitmap;
  LPBITMAPINFOHEADER	lpBitmapInfo;

  h = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nID), RT_BITMAP);
  hRes = ::LoadResource(AfxGetApp()->m_hInstance, h);

  /* Lock the bitmap and get a pointer to the color table. */
  lpBitmapInfo = (LPBITMAPINFOHEADER)LockResource(hRes);

/*    PortTool v2.2     1995/10/16    7:57          */
/*      Found   : FAR          */
/*      Issue   : Win32 ではセグメントを用いません。従って FAR == NEAR == 指定なし！          */
  p = (DWORD FAR *)((LPSTR)(lpBitmapInfo) + lpBitmapInfo->biSize);

  /* Search for the Solid Blue entry and replace it with the current
   * background RGB.
   */
  if (siOffset==0)
  	{
  	while (TRUE)
      {
      	if (*p == 0x000000FF)	    // Solid Blue
		{
	  	*p = rgbToUse;
        break;
		}
      p++;
	  siOffset++;
      }
	}
  else
  	*(p+siOffset) = rgbToUse;
  UnlockResource(hRes);

  /* Now create the DIB. */
  lpBitmapInfo = (LPBITMAPINFOHEADER)LockResource(hRes);

  /* First skip over the header structure */
  lpBits = (LPSTR)(lpBitmapInfo + 1);

  /* Skip the color table entries, if any */
  lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);

  /* Create a color bitmap compatible with the display device */
  hDC = ::GetDC(NULL);
  hBitmap = CreateDIBitmap(hDC, lpBitmapInfo, (DWORD)CBM_INIT, lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS);
  ::ReleaseDC(NULL, hDC);

  GlobalUnlock(hRes);
  FreeResource(hRes);

  return(hBitmap);
}
DWORD CDBmpStrList::RGBToBGR(DWORD rgb)
{
  BYTE	    green;
  BYTE	    blue;


/*    PortTool v2.2     1995/10/16    7:57          */
/*      Found   : (WORD)          */
/*      Issue   : ３２ビット値を不正にキャストしていないかチェックして下さい          */
/*      Suggest : 可能なら３２ビットデータに変更して下さい          */
/*      Help available, search for WORD in WinHelp file API32WH.HLP          */
  green = (BYTE)((WORD)rgb >> 8);

/*    PortTool v2.2     1995/10/16    7:57          */
/*      Found   : HIWORD          */
/*      Issue   : HIWORD で扱う値が１６ビットなのか、３２ビットなのかチェックして下さい          */
  blue	= (BYTE)(HIWORD(rgb));
  return(RGB(blue, green, (BYTE)rgb));
}
#endif //WIN32

/*************************************************************************
-- Routine:BOOL CDBmpStrList::FSetFont ( HFONT hfont )
-- Description and Usage:
		リストボックスの表示で使うフォントの設定.
-- Arguments:
		HFONT hfont - リストボックスで使うフォントハンドル.
-- Returns:
		hfont が NULL でも、システムフォントが割り当てられるので、
														現在は TRUE のみ.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
BOOL CDBmpStrList::FSetFont ( HFONT hfont )
{
	::SendMessage ( m_hWnd, WM_SETFONT, (WPARAM)hfont, (WPARAM)TRUE ) ;
	return( TRUE ) ;
}

/*************************************************************************
-- Routine:void CDBmpStrList::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
-- Description and Usage:
		OWNER DRAW のリストボックスの作成時に、リストボックスの寸法を調べ
		るために、フレームワークから呼ばれる.
-- Arguments:
		LPMEASUREITEMSTRUCT lpMIS - MEASUREITEMSTRUCT 構造体. オーナー描画
		コントロールの寸法を WINDOWS に通知するときに使われます.
-- Returns:
		なし.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
void CDBmpStrList::MeasureItem ( LPMEASUREITEMSTRUCT lpMIS )
{
	ASSERT(m_iHeight>0);
	lpMIS->itemHeight = m_iHeight ;
}

/*************************************************************************
-- Routine:void CDBmpStrList::DrawItem(LPDRAWITEMSTRUCT lpDIS)
-- Description and Usage:
		OWNER DRAW スタイルをもつリストボックスに、視覚的変更のあった時に
		フレームワークから呼ばれる.	
-- Arguments:
		LPDRAWITEMSTRUCT lpDIS - DRAWITEMSTRUCT 構造体. オーナー描画
								 コントロールの描画方法をオーナーが判断
								 するために必要な情報を提供する.
-- Returns:
		なし.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
#define RESIZE_BUGFIX
void CDBmpStrList::DrawItem ( LPDRAWITEMSTRUCT lpDIS )
{
#ifdef RESIZE_BUGFIX // WM_SIZE時に、MoveWindow()から呼び出される為、FromHandle()のテンポラリマッパーがバグる
	CDC  cDC;
#else
	CDC* pDC;
#endif
	size_ent nIndex;
	CRect rc;
	int etBmp;	// EntryTypeOfBmp;	
	int tab;
	CString str[6];
	stCXALIGN itemData[6];
	int item, nItem, xPos;

	// ﾘｿｰｽの番号またはｴﾝﾄﾘｰ登録準備できていないか？
	if (m_iResID==0 || m_pEntryArray->m_bse==NULL)
		return;


	nIndex = lpDIS->itemData;

#ifdef _DEBUG		
//	TRACE ( "DrawItem - lpDIS->itemData=%d\n", nIndex) ;
#endif

	if (nIndex<0 || nIndex>=m_pEntryArray->m_wUseEntry)
		return;

	rc = &lpDIS->rcItem ;

	// リソースＩＤ、使用するビットマップの高さ
		
#ifdef RESIZE_BUGFIX // WM_SIZE時に、MoveWindow()から呼び出される為、FromHandle()のテンポラリマッパーがバグる
	cDC.Attach(lpDIS->hDC);
#else	
	pDC = CDC::FromHandle ( lpDIS->hDC ) ;
#endif


	if (lpDIS->itemState & ODS_SELECTED)
		{
		cDC.SetBkMode(OPAQUE);
		cDC.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
		cDC.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)) ;
		}
	else
		{
		cDC.SetBkMode(TRANSPARENT);
		cDC.SetTextColor(m_frColor);
		//cDC.FillRect(&rc , &m_bkBrush );
		//cDC.SetBkColor(m_bkColor) ;
		}
	

	if (lpDIS->itemAction == ODA_FOCUS)
		goto FocusOnly;

	/* Draw the black/white background. */
	if (cDC.GetBkColor()==::GetSysColor(COLOR_HIGHLIGHT))
		cDC.ExtTextOut(0, 0, ETO_OPAQUE,&rc, NULL, 0, NULL);
	else if (m_bkBrush.GetSafeHandle())
		cDC.FillRect(&rc , &m_bkBrush );

	etBmp = m_pEntryArray->GetEntryTypeOfBmp(nIndex);
	tab = m_pEntryArray->GetTabOfEntry(nIndex);
	//takaso2010
	CListEntry * pEntry = m_pEntryArray->GetEntry(nIndex);
	ASSERT(pEntry);

	// etBmp が 0 の時は birmap なし.
	memset(&itemData[0], 0, sizeof(itemData));
	int posstr = m_pEntryArray->GetEntryString(nIndex, str[1], str[2], str[3], str[4], str[5]);
	nItem = m_header.GetCxs(m_pEntryArray->GetEntryType(nIndex), itemData);
	xPos = rc.left + itemData[0].cx;

	if ( etBmp > 0  /*&& !(lpDIS->itemState & ODS_SELECTED)*/)
		{
		rc.left = xPos - BMP_HIGHT - ITEM_ADJUST;
		rc.right = rc.left + BMP_HIGHT;
		CPoint pt;
		pt.x = rc.left;
		pt.y = rc.top + ( ((unsigned int)( m_iHeight - BMP_HIGHT))>>1 );
		if (lpDIS->itemState & ODS_SELECTED)
			m_phbmRes[1]->Draw(&cDC, etBmp - 1, pt, ILD_NORMAL);
		else
			m_phbmRes[0]->Draw(&cDC, etBmp - 1, pt, ILD_NORMAL);
		}

	// テキストの表示
#define DOTNUM_OF_OVER	(4)
#define CX_OVERDOT		(DOTNUM_OF_OVER*2+1)
	int itop = rc.top + (((unsigned int)(m_iHeight - m_iFontHeight))>>1);

	for (item=1; item<nItem; item++) {
		rc.left = rc.right + 2*ITEM_ADJUST;
		rc.right = rc.left + itemData[item].cx - 2*ITEM_ADJUST;

		BOOL bOver=FALSE;
		CString strTemp;
		CDString dstr = str[item];
		int pos,s, size, width;

		if (itemData[item].cx != DCX_MUGEN)
			for (pos=0, size=0, width=rc.Width(); pos<(int)dstr.GetLength(); pos++)
			{
			VERIFY(cDC.GetCharWidth(dstr.GetAt(pos), dstr.GetAt(pos),&s));
			size += s;
			if (size>width)
				{
				bOver = TRUE;
				break;
				}
			}
		if (bOver)
			for (pos=0, size=0, width=rc.Width()-CX_OVERDOT; pos<(int)dstr.GetLength(); pos++)
			{
			VERIFY(cDC.GetCharWidth(dstr.GetAt(pos), dstr.GetAt(pos),&s));
			size += s;
			if (size>width)
				{
				size -= s;
				strTemp = dstr.Left(pos);
				break;
				}
			}
		if (strTemp.IsEmpty())
			strTemp = str[item];

		if (bOver)
			{
			int xPixel;
			int yPixel = rc.top + m_iHeight - 4;
			if (itemData[item].align==CHeaderCtrlEx::right)
				xPos = rc.right - size -CX_OVERDOT;
			else
				xPos = rc.left;
			xPixel = xPos + size +1;
			for (pos=0; pos<DOTNUM_OF_OVER; pos++, xPixel+=2)
				cDC.SetPixel( xPixel, yPixel,
					(lpDIS->itemState & ODS_SELECTED) ?
						GetSysColor(COLOR_HIGHLIGHTTEXT):m_frColor);
			}
		else
			{
			if (itemData[item].align==CHeaderCtrlEx::right)
				xPos = rc.right - size;
			else
				xPos = rc.left;
			}

		//takaso2010
		CMarkFinds *pmark = pEntry->m_paryMark;
		int mark_count = pmark->GetSize();
		if (posstr>0 && item==posstr && mark_count>0) {
			CRect rcT = rc;
			int xPosT = xPos;
			cDC.ExtTextOut( xPos,
				itop,
				ETO_CLIPPED,
				&rc,
				strTemp,
				strTemp.GetLength() ,
				NULL );
			
			for (int j=0; j<mark_count; j++, xPosT=xPos, rcT=rc) {
				MARK_FIND mf = pmark->GetAt(j);
				CString strkey = strTemp.Mid(mf.pos, mf.len);
				if (mf.pos >0) {
					CString str = strTemp.Left(mf.pos);
					CSize siz = cDC.GetTextExtent(str);
					rcT.left+=siz.cx;//
					xPosT += siz.cx;
				}
				rcT.left++;//1dotづらす
				xPosT++;////1dotづらす
				if (lpDIS->itemState & ODS_SELECTED) {
					cDC.SetBkMode(TRANSPARENT);
				//	cDC.SetTextColor(m_frColor);
				//	cDC.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)) ;
				//}else {
				}
				cDC.ExtTextOut( xPosT,
					itop,
					ETO_CLIPPED,
					&rcT,
					strkey,
					strkey.GetLength() ,
					NULL );
			}
		}else{
			cDC.ExtTextOut( xPos,
				itop,
				ETO_CLIPPED,
				&rc,
				strTemp,
				strTemp.GetLength() ,
				NULL );
		}
	}

	if (lpDIS->itemState & ODS_FOCUS)
FocusOnly:
		cDC.DrawFocusRect(&rc);

	if (lpDIS->itemState & ODS_SELECTED)
		{
//		cDC.SetBkMode(TRANSPARENT);
		cDC.SetTextColor(m_frColor);
		cDC.SetBkColor(m_bkColor);
		}
	cDC.Detach();
}
/*************************************************************************
-- Routine:int CDBmpStrList::CompareItem ( LPCOMPAREITEMSTRUCT lpCIS )
-- Description and Usage:
		復元されたオーナー描画のリストボックスで、項目の相対位置を調べる
		ためにフレームワークから呼び出されます. 
-- Arguments:
		LPCOMPAREITEMSTRUCT lpCIS - COMPAREITEMSTRUCT 構造体. オーナー描画の
		コンボ ボックスまたはリスト ボックス内の2つの項目の、識別子とアプリ
		ケーション供給のデータを格納します.
-- Returns:
	   -1 - いま追加したデータの方が前.
		0 - 同じ.
		1 - いま追加したデータの方が後.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
int CDBmpStrList::CompareItem ( LPCOMPAREITEMSTRUCT lpCIS )
{
	return (size_ent)lpCIS->itemData1 - (size_ent)lpCIS->itemData2;
//	return _fmbscmp ( (const unsigned char FAR*)m_pEntryArray->m_bse[GetDataIndexFromItemData(lpCIS->itemData1)].pcdStr->GetBuffer(),
//				(const unsigned char FAR*)m_pEntryArray->m_bse[GetDataIndexFromItemData(lpCIS->itemData2)].pcdStr->GetBuffer() );
}
/*
	switch (m_SortType)
		{
		case ST_NAME:
			break;
		case ST_TYPE:
			break;
		case ST_SIZE:
			break;
		case ST_DATE:
			break;
		}
*/

/*************************************************************************
-- Routine:BOOL CDBmpStrList::FResetEntry ( 
							CListEntry* bsl_entry, size_ent entrys )
-- Description and Usage:
		リスト内の項目をすべて削除し、新しい項目を登録する.
-- Arguments:
		CListEntry* bsl_entry - 新しく登録する構造体.
		size_ent entrys            - 登録する構造体の数.
-- Returns:
		TRUE  - 成功.
		FALSE - 失敗.		
-- Notes:
-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
BOOL CDBmpStrList::FResetEntry ( CListEntry* bsl_entry, size_ent entrys )
{
	TRACE ( "\n - CDBmpStrList::FResetEntry - " ) ;

	size_ent i;
	int rtn=0;
	// ﾒﾓﾘの拡張
	if (!m_pEntryArray->FExpandEntry ( entrys))
		return ( FALSE ) ;
	
	// ﾊﾟﾗﾒｰﾀﾃﾞｰﾀのｺﾋﾟｰ
	// ::SendMessage(m_hWnd, , 0, 0);	// ﾘｽﾄをｱｯﾌﾟﾃﾞｰﾄしない。
	for (i=0; i<entrys; i++)
		{
		m_pEntryArray->m_bse[i] = bsl_entry[i];
		}

	// ﾘｽﾄｴﾝﾄﾘｰのﾘｾｯﾄ
	::SendMessage(m_hWnd, BMPSTR_RESETCONTENT, 0, 0);
	//DeleteAllItems();

	// ﾘｽﾄへの反映
	for (i = 0; i < entrys; i++ )
		{
		if (rtn=::SendMessage( m_hWnd, BMPSTR_ADDSTRING, 0, (LPARAM)i )<0)
			break;
		}
	return( rtn>=0 );
}


/*************************************************************************
-- Routine:int CDBmpStrList::AddString ( CListEntry *entry )
-- Description and Usage:
		リスト内の項目に、新しい項目を追加登録する.
-- Arguments:
		CListEntry *entry	- ｴﾝﾄﾘｰ構造体へのﾎﾟｲﾝﾀ
-- Returns:
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
int CDBmpStrList::AddString ( CListEntry *entry)
{
//	TRACE ( "\n - CDBmpStrList::AddString - " ) ;

	// ﾒﾓﾘの拡張
	if (!m_pEntryArray->FExpandEntry ( m_pEntryArray->m_wUseEntry +1 ))
		return ( BMPSTR_ERRSPACE ) ;
	
	// ﾊﾟﾗﾒｰﾀﾃﾞｰﾀのｺﾋﾟｰ
	// ::SendMessage(m_hWnd, , 0, 0);	// ﾘｽﾄをｱｯﾌﾟﾃﾞｰﾄしない。
	ASSERT(m_pEntryArray->m_wUseEntry>0);
	m_pEntryArray->m_bse[m_pEntryArray->m_wUseEntry-1] = *entry;

	// ﾘｽﾄへの反映
	return (int)::SendMessage( m_hWnd, BMPSTR_ADDSTRING, 0, (LPARAM)m_pEntryArray->m_wUseEntry-1 );
}
/*************************************************************************
-- Routine:int CDBmpStrList::DeleteString (int selFirst, int selCount)
-- Description and Usage:
		リスト内の項目を、複数削除する.
-- Arguments:
		int selFirst - 削除開始位置
		int selCount - 削除個数
-- Returns:
-- Notes:
-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
int CDBmpStrList::DeleteString (int selFirst, register int selCount )
{
	// ﾘｽﾄへの反映
	ASSERT(selCount>0);
	register int nCount;
	while (selCount--)
		{
		if ((nCount=(int)::SendMessage( m_hWnd, BMPSTR_DELETESTRING, selFirst, 0L ))==BMPSTR_ERR)
			return  nCount;
		}
	return nCount;
}
/*************************************************************************
-- Routine:int CDBmpStrList::ResetContent ()
-- Description and Usage:
		リスト内の項目をデータおよび表示上で全て削除する。
-- Arguments:
-- Returns:
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
void CDBmpStrList::ResetContent()
{
	m_pEntryArray->m_wUseEntry=0;  //使っているｴﾝﾄﾘｰ数だけをｸﾘｱ
//	m_pEntryArray->DeleteContent();	// 実体もｸﾘｱする
	BASE_CLASS::ResetContent();
/*
	CDC  *pDC;
	pDC = GetDC();
	OnEraseBkgnd(pDC);
	ReleaseDC(pDC);
*/
}

/*************************************************************************
-- Routine:CDBmpStrList::~CDBmpStrList()
-- Description and Usage:
		リストボックスの破棄、使用していたフォントの破棄、
		使用していた構造体領域の破棄.
-- Arguments:
		なし.
-- Returns:
		なし.
-- Notes:

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
CDBmpStrList::~CDBmpStrList()
{
	if (m_pEntryArray)
		delete m_pEntryArray;
#ifdef WIN32
	if (m_phbmRes[0])
		delete m_phbmRes[0];
	if (m_phbmRes[1])
		delete m_phbmRes[1];
#else
	if (m_iResID)
		{
		DeleteObject(m_phbmRes[0]) ;
		DeleteObject(m_phbmRes[1]) ;
		}
	if (m_dcMem.GetSafeHdc())
		m_dcMem.DeleteDC() ;
#endif

	if (m_bkBrush.GetSafeHandle())
		m_bkBrush.DeleteObject();
}


/*************************************************************************
-- Routine:int CDBmpStrList::GetCurEntryType(void) const
-- Description and Usage:
		現在選択中の種類を返す.
-- Arguments:
		なし.
-- Returns:
		フォントの種類の例 ( enum BSLIST_TYPE )
				1(FT_TRUETYPE) - TrueType FONT
				0(FT_PRINTER)  - Printer  FONT
			   -1(FT_OTHERS)   - OTHER    FONT
-- Notes:												   makeprocinstance

-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
int CDBmpStrList::GetCurEntryType(void) //const
{
	TRACE ( "\n - CDBmpStrList::GetCurEntryType - " ) ;

	size_ent nIndex = GetCurSelDataOffset() ;

	if ( nIndex == (size_ent)-1 )
		return ( -1 ) ;

	int iTmp = m_pEntryArray->GetEntryType(nIndex);

	return ( iTmp ) ;
}		


/*************************************************************************
-- Routine:CListEntry CDBmpStrList::GetCurEntry()
-- Description and Usage:
		現在選択中のエントリ（構造体）を返す.

-- Arguments:
		なし.
-- Returns:
		CListEntry - カーソル位置の構造体情報.
		（フォント種類、フォント名など）
-- Notes:
		
-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
CListEntry CDBmpStrList::GetCurEntry()
{
	TRACE ( "\n - CDBmpStrList::GetCurEntry - " ) ;
	CListEntry bsl ;
	size_ent nIndex = GetCurSelDataOffset() ;
	
	if ( nIndex != (size_ent)-1 )
		bsl = m_pEntryArray->m_bse[nIndex];
	return ( bsl ) ;
}



/*************************************************************************
-- Routine:CListEntry CDBmpStrList::GetEntry ( int sel )
-- Description and Usage:
		インデックス位置のエントリを返す.
-- Arguments:
		int sel - 取得したいインデックス.
-- Returns:
		CListEntry - カーソル位置の構造体情報.
		（フォント種類、フォント名など）
-- Notes:
		
-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
CListEntry CDBmpStrList::GetEntry ( size_ent sel ) 
{
	TRACE ( "\n - CDBmpStrList::GetEntry - " ) ;
	CListEntry bsl ;
    size_ent selT = GetDataIndexFromSel(sel);
	if (selT != (size_ent)-1)
		bsl = (CListEntry)m_pEntryArray->m_bse[selT] ;
	return ( bsl ) ;
}

/*************************************************************************
-- Routine:struct int GetCurSel() const
-- Description and Usage:
		選択中のエントリを返す.
-- Arguments:
		なし.
-- Returns:
		カーソル位置のインデックス.
-- Notes:
		
-- History:
		'94.7	- created		(M.Design)
*************************************************************************/
int CDBmpStrList::GetCurSel() const
{
	//TRACE ( "\n - CDBmpStrList::GetCurSel - " ) ;
	return ( (int)::SendMessage ( m_hWnd, BMPSTR_GETCURSEL, 0, 0L ) ) ;
}


/*************************************************************************
-- Routine:BOOL CDBmpStrList::OnChildNotify(UINT message, WPARAM,
										LPARAM lParam, LRESULT* pLResult)

-- Description and Usage:
		リストボックスにメッセージが post された時に呼ばれる.
-- Arguments:
		UINT message	  - メッセージ.
		WPARAM			  - WPARAM (受取拒否？）.
		LPARAM lParam	  - LPARAM.
		LRESULT* pLResult - 

-- Returns:
		なにか処理をした - TRUE.
		処理なし		 - FALSE.

-- Notes:

-- History:
		'94.8	- created		(M.Design)
*************************************************************************/
BOOL CDBmpStrList::OnChildNotify ( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult )
{
	//if (uMessage==WM_CTLCOLOR )
	return( BASE_CLASS::OnChildNotify(message, wParam, lParam, pLResult)) ;
}



// protected functions
// 指定されたﾌｫﾝﾄの高さを取得する
int CDBmpStrList::GetFontHeight()
{
//	CDC  *pDC;
//	pDC = GetDC();
//	TEXTMETRIC tm;
//	pDC->GetTextMetrics(&tm);
//	int iHeight =  abs(tm.tmHeight)+abs(tm.tmInternalLeading);
//	ReleaseDC(pDC);
//	return iHeight;
//
	CFont *pFont;
	HFONT hFont;
	if (m_hWnd && (pFont = GetFont()) && (hFont=(HFONT)pFont->GetSafeHandle()))
		{
		LOGFONT logfont;
		VERIFY(GetObject(hFont, sizeof(LOGFONT), &logfont)>0);
		return abs(logfont.lfHeight);
		}
	else
		return HIWORD(::GetDialogBaseUnits());
}

// 選択セル番号から実データインデックスを取得する。
size_ent CDBmpStrList::GetDataIndexFromSel(size_ent sel)
{
	if (sel == (size_ent)-1)
		return (size_ent)-1;
	DWORD dw = (DWORD)::SendMessage ( m_hWnd, BMPSTR_GETITEMDATA, sel, 0 );
	return (size_ent)dw;
}

BOOL CDBmpStrList::SetSelFromDataIndex(size_ent sel)
{
	DWORD dwCount = (DWORD)::SendMessage ( m_hWnd, BMPSTR_GETCOUNT, 0, 0 );
	for (DWORD dw=0; dw<dwCount; dw++)
		{
		DWORD dwData = (DWORD)::SendMessage ( m_hWnd, BMPSTR_GETITEMDATA, dw, 0 );
		if ((size_ent)dwData == sel)
			{
			return SetCurSel(dw)!=BMPSTR_ERR;
			}
		}
	return FALSE;
}

// 項目が選択されていないとき、-1 を返す.
size_ent CDBmpStrList::GetCurSelDataOffset()
{
	return GetDataIndexFromSel(GetCurSel());
}


// - dbmpstrl.cpp -


int CDBmpStrList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	CRect rc;
	rc.SetRectEmpty();
	m_header.Create(HDS_BUTTONS | HDS_HORZ | CCS_TOP | WS_CHILD | WS_VISIBLE,
					rc, this->GetParent(), 2);
	//m_header.Layout();
	return 0;
}

void CDBmpStrList::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	CListBox ::CalcWindowRect(lpClientRect, nAdjustType);
}

void CDBmpStrList::LayoutWindowRect(LPRECT lpClientRect, BOOL bShowHeader)
{
	ASSERT(lpClientRect);

	ShowWindow(SW_HIDE);
	m_header.ShowWindow(SW_HIDE);
	CRect rc = *lpClientRect;
	if (bShowHeader)
		{
#ifdef HEADER_BOTTOM
		rc.top = rc.bottom - BMP_HIGHT;
		m_header.MoveWindow(&rc);
		rc = *lpClientRect;
		rc.bottom -= BMP_HIGHT;
#else
		rc.bottom = rc.top + BMP_HIGHT;
		m_header.MoveWindow(&rc);
		rc = *lpClientRect;
		rc.top += BMP_HIGHT;
#endif
		}
	MoveWindow(&rc, FALSE);
	m_header.ShowWindow(bShowHeader ? SW_SHOWNA:SW_HIDE);
	ShowWindow ( SW_SHOWNA ) ;
}

BOOL CDBmpStrList::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (m_bkBrush.GetSafeHandle())
		{
		CRect rc ;
		GetClientRect(&rc);
		pDC->FillRect(&rc , &m_bkBrush );
		return 1;
		}
	else
		return CListBox ::OnEraseBkgnd(pDC);
}



//HBRUSH CDBmpStrList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
HBRUSH CDBmpStrList::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr;
	if (!(hbr = (HBRUSH)m_bkBrush.GetSafeHandle()))
		hbr = (HBRUSH)GetSysColor(COLOR_WINDOW);//CListBox ::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}
