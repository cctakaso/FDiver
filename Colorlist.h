#include "afxtempl.h"

#ifndef __COLORLIST_H__
#define __COLORLIST_H__
/////////////////////////////////////////////////////////////////////////////
// カスタム リスト ボックス - 色を含む
#define COLOR_ITEM_HEIGHT   (20)
#define MAX_RorGorB		(255)
class CColorSel
{
public:
	CColorSel();
	~CColorSel() {};
	void Initialize(CString &str);
	void Initialize(CString &strId, CString &strText,
		CString &strR, CString &strG, CString &strB);
	COLORREF GetColor();
	CString GetStringColor();
	void SetColor(COLORREF color);

	CString GetStringId();
	CString GetStringR();
	CString GetStringG();
	CString GetStringB();


	long m_id;
	CString m_strText;
	BYTE m_R;
	BYTE m_G;
	BYTE m_B;
};


class CColorListBox : public CListBox
{
public:
	CColorListBox();
	DECLARE_DYNCREATE(CColorListBox)
	virtual ~CColorListBox();
// オペレーション
	BOOL AddColorItems();
	BOOL AddColorItem(CColorSel &sel, BOOL fMemOnly=FALSE);
	CColorSel *GetSelData(int iSel=LB_ERR);
	void SetColor(COLORREF color);
	COLORREF GetColor(int iSel=LB_ERR);
	int GetArySize() {
		return m_arySel.GetSize(); }
// Overrides
	//virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListBox)
	protected:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	//}}AFX_VIRTUAL

// Implementation

// Generated message map functions
protected:
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//{{AFX_MSG(CColorListBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//
protected:
	int m_heightItem;
	CArray<CColorSel,CColorSel> m_arySel;
};

#endif //#ifndef __COLORLIST_H__
