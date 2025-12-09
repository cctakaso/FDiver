// FDiverDoc.cpp : CFDiverDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "FDiver.h"

#include "FDiverDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFDiverDoc

IMPLEMENT_DYNCREATE(CFDiverDoc, CDocument)

BEGIN_MESSAGE_MAP(CFDiverDoc, CDocument)
	//{{AFX_MSG_MAP(CFDiverDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFDiverDoc クラスの構築/消滅

CFDiverDoc::CFDiverDoc()
{
	// TODO: この位置に１回だけ構築用のコードを追加してください。

}

CFDiverDoc::~CFDiverDoc()
{
}

BOOL CFDiverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFDiverDoc シリアライゼーション

void CFDiverDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFDiverDoc クラスの診断

#ifdef _DEBUG
void CFDiverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFDiverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFDiverDoc コマンド

