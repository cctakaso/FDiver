/*    PortTool v2.2     fdivedoc.h          */

// Fdivedoc.h : CFdiverDoc クラスの宣言およびインターフェースの定義をします。
#ifndef __FDIVEDOC_H__
#define __FDIVEDOC_H__
//
/////////////////////////////////////////////////////////////////////////////
#include "findlist.h"
class CFdiverDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CFdiverDoc();
	DECLARE_DYNCREATE(CFdiverDoc)

// 属性
public:
	CFindList *m_pFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ

// オペレーション
public:

// インプリメンテーション
public:
	virtual ~CFdiverDoc();
	virtual void Serialize(CArchive& ar);	// ドキュメント I/O に対してオーバーライドされます。
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// メッセージ マップ関数の生成を行います。
protected:
	//{{AFX_MSG(CFdiverDoc)
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // __FDIVEDOC_H__
/////////////////////////////////////////////////////////////////////////////
