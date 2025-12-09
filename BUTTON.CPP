// Microsoft Visual C++ で自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。

#include "stdafx.h"
#include "button.h"

// このインターフェイスによって参照されるディスパッチ インターフェイス
#include "font.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButton1

IMPLEMENT_DYNCREATE(CButton1, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CButton1 プロパティ

short CButton1::GetBorderStyle()
{
	short result;
	GetProperty(DISPID_BORDERSTYLE, VT_I2, (void*)&result);
	return result;
}

void CButton1::SetBorderStyle(short propVal)
{
	SetProperty(DISPID_BORDERSTYLE, VT_I2, propVal);
}

CString CButton1::GetCaption()
{
	CString result;
	GetProperty(DISPID_CAPTION, VT_BSTR, (void*)&result);
	return result;
}

void CButton1::SetCaption(LPCTSTR propVal)
{
	SetProperty(DISPID_CAPTION, VT_BSTR, propVal);
}

BOOL CButton1::GetEnabled()
{
	BOOL result;
	GetProperty(DISPID_ENABLED, VT_BOOL, (void*)&result);
	return result;
}

void CButton1::SetEnabled(BOOL propVal)
{
	SetProperty(DISPID_ENABLED, VT_BOOL, propVal);
}

COleFont CButton1::GetFont()
{
	LPDISPATCH pDispatch;
	GetProperty(DISPID_FONT, VT_DISPATCH, (void*)&pDispatch);
	return COleFont(pDispatch);
}

void CButton1::SetFont(LPDISPATCH propVal)
{
	SetProperty(DISPID_FONT, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CButton1 オペレーション

void CButton1::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
