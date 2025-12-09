#ifndef __BUTTON_H__
#define __BUTTON_H__

//  Microsoft Visual C++ によって自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。


// このインターフェイスによって参照されるディスパッチ インターフェイス。
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CButton1 ラップ クラス

class CButton1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CButton1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x4a8c998f, 0x7713, 0x101b, { 0xa5, 0xa1, 0x4, 0x2, 0x1c, 0x0, 0x94, 0x2 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// アトリビュート
public:
	short GetBorderStyle();
	void SetBorderStyle(short);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	COleFont GetFont();
	void SetFont(LPDISPATCH);

// オペレーション
public:
	void AboutBox();
};

#endif // __BUTTON_H__
