// Colorlist.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "mdglibs.h"
#include "colorlist.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSel
CColorSel::CColorSel()
{
	m_id = -1;
	m_R = MAX_RorGorB;
	m_G = MAX_RorGorB;
	m_B = MAX_RorGorB;
}

void CColorSel::Initialize(CString &str)
{
	CString strId, strText, strR, strG, strB;
	strId = GetPartString(str, ',');
	strText = GetPartString(str, ',');
	strR = GetPartString(str, ',');
	strG = GetPartString(str, ',');
	strB = GetPartString(str, ',');
	Initialize(strId, strText, strR, strG, strB);
}

void CColorSel::Initialize(CString &strId, CString &strText,
		CString &strR, CString &strG, CString &strB)
{
	m_id = atol(strId);
	m_strText = strText;
	m_R = atoi(strR);
	m_G = atoi(strG);
	m_B = atoi(strB);
}

COLORREF CColorSel::GetColor()
{
	return RGB(m_R, m_G, m_B);
}

CString CColorSel::GetStringColor()
{
	return GetStringR() +","+ GetStringG() +","+ GetStringB();
}

void CColorSel::SetColor(COLORREF color)
{
	m_R = GetRValue(color);
	m_G = GetGValue(color);
	m_B = GetBValue(color);
}

CString CColorSel::GetStringId()
{
	CString str;
	str.Format(_T("%ld"),m_id);
	return str;
}
CString CColorSel::GetStringR()
{
	CString str;
	str.Format(_T("%d"),m_R);
	return str;
}
CString CColorSel::GetStringG()
{
	CString str;
	str.Format(_T("%d"),m_G);
	return str;
}
CString CColorSel::GetStringB()
{
	CString str;
	str.Format(_T("%d"),m_B);
	return str;
}


/////////////////////////////////////////////////////////////////////////////
// CColorListBox

IMPLEMENT_DYNCREATE(CColorListBox, CListBox)

BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
	//{{AFX_MSG_MAP(CColorListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListBox construction/destruction

CColorListBox::CColorListBox(): CListBox()
{
	m_heightItem=0;
}

CColorListBox::~CColorListBox()
{
}
/////////////////////////////////////////////////////////////////////////////

BOOL CColorListBox::AddColorItem(CColorSel &sel, BOOL fMemOnly)
{
	// リスト ボックスのアイテムを追加
	m_arySel.Add(sel);
	if (!fMemOnly && ::IsWindow(m_hWnd))
		AddString((LPCSTR)"");
		// Listbox は LBS_HASSTRINGS スタイルを持っていないので
		// 通常のリストボックスのストリングは RGB カラーを保存するために使用されます。
	return TRUE;
}

BOOL CColorListBox::AddColorItems()
{
	// リスト ボックスのアイテムを追加
	for (int i=0; i<m_arySel.GetSize(); i++)
		AddString((LPCSTR)"");
		// Listbox は LBS_HASSTRINGS スタイルを持っていないので
		// 通常のリストボックスのストリングは RGB カラーを保存するために使用されます。
	return TRUE;
}

void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	// すべてのアイテムは固定サイズです。
	// この処理を行うために LBS_OWNERDRAWVARIABLE を使わなければなりません。
	if (m_heightItem==0)
		{
		CDC* pDC = GetDC();
		CSize size = pDC->GetTextExtent(_T("Ｗ"));
		ReleaseDC(pDC);
		m_heightItem = size.cy * 3 /2;
		if (m_heightItem==0)
			m_heightItem = COLOR_ITEM_HEIGHT;
		}
	lpMIS->itemHeight = m_heightItem;
}

void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CRect rc, rcColor, rcText;
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	COLORREF cr = m_arySel[lpDIS->itemID].GetColor();
					//(COLORREF)lpDIS->itemData; // アイテム データ内の RGB
	BOOL fText = !m_arySel[lpDIS->itemID].m_strText.IsEmpty();

	rc = lpDIS->rcItem;

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
		{
		// 要求された色でカラー アイテムをペイントします。
		CBrush br(cr);
		rcColor = rc;
		if (fText)
			{
			rcColor.left++; rcColor.right--; rcColor.top++; rcColor.bottom--;
			rcColor.right = rcColor.left + rc.Height();
			}
		pDC->FillRect(&rcColor, &br);

		if (fText)
			{
			rcText = rc;
			rcText.left = rcColor.right + rcColor.Width()/2;
			rcText.bottom--;
			pDC->DrawText(m_arySel[lpDIS->itemID].m_strText, rcText, DT_LEFT | DT_SINGLELINE | DT_BOTTOM);
			}
		}

	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		// アイテムは選択されています - フレームをハイライト
		COLORREF crHilite = RGB(0,0,0);
		//COLORREF crHilite = RGB(255-GetRValue(cr),
		//				255-GetGValue(cr), 255-GetBValue(cr));
		CBrush br(crHilite);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}

	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
		// アイテムの選択は取り消されました -- フレームを削除
		COLORREF crHilite = RGB(255,255,255);
		//COLORREF crHilite = RGB(255-GetRValue(cr),
		//				255-GetGValue(cr), 255-GetBValue(cr));
		CBrush br(crHilite);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}
}


CColorSel *CColorListBox::GetSelData(int iSel)
{
	if (iSel==LB_ERR)
		{
		if (GetCount()==1)
			iSel = 0;
		else
			iSel = GetCurSel();
		}
	if (iSel==LB_ERR)
		return NULL;
	return &m_arySel[iSel];
}

void CColorListBox::SetColor(COLORREF color)
{
	if (::IsWindow(m_hWnd))
		ResetContent();
	m_arySel.RemoveAll();

	CColorSel sel;
	sel.SetColor(color);
	AddColorItem(sel);
}

COLORREF CColorListBox::GetColor(int iSel)
{
	if (iSel==LB_ERR)
		{
		if (GetCount()==1)
			iSel = 0;
		else
			iSel = GetCurSel();
		}
	if (iSel==LB_ERR)
		return RGB(0,0,0);

	CColorSel *pselData = GetSelData(iSel);
	if (pselData)
		return pselData->GetColor();
	else
		return RGB(0,0,0);
}
