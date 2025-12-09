#ifndef __FONT_H__
#define __FONT_H__

//  Microsoft Visual C++ によって自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。

/////////////////////////////////////////////////////////////////////////////
// COleFont ラップ クラス

class COleFont : public COleDispatchDriver
{
public:
	COleFont() {}		// COleDispatchDriver デフォルト コンストラクション
	COleFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COleFont(const COleFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// アトリビュート
public:
	CString GetName();
	void SetName(LPCTSTR);
	CY GetSize();
	void SetSize(const CY&);
	BOOL GetBold();
	void SetBold(BOOL);
	BOOL GetItalic();
	void SetItalic(BOOL);
	BOOL GetUnderline();
	void SetUnderline(BOOL);
	BOOL GetStrikethrough();
	void SetStrikethrough(BOOL);
	short GetWeight();
	void SetWeight(short);
	short GetCharset();
	void SetCharset(short);

// オペレーション
public:
};

#endif // __FONT_H__
