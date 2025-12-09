/*    PortTool v2.2     FDIVEDOC.CPP          */

// fdivedoc.cpp : CFdiverDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "version.h"
#include "Fdiver.h"
#include "finddlg.h"
#include "fdivedoc.h"
extern CFindDlg *vpFindDlg;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFdiverDoc

IMPLEMENT_DYNCREATE(CFdiverDoc, CDocument)

BEGIN_MESSAGE_MAP(CFdiverDoc, CDocument)
	//{{AFX_MSG_MAP(CFdiverDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFdiverDoc クラスの構築/消滅

CFdiverDoc::CFdiverDoc()
{
	// TODO: この位置に一回だけ構築用のコードを追加してください。
	m_pFindList = new CFindList;
}

CFdiverDoc::~CFdiverDoc()
{
	if (m_pFindList)
		delete m_pFindList;
}

BOOL CFdiverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFdiverDoc クラスのシリアライゼーション

void CFdiverDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		{
			// TODO:この位置に保存用のコードを追加してください。
		ar << (WORD)VERSION_NUM;
		}
	else
		{
		WORD verDoc;
		ar >> verDoc;
		if (verDoc <= NOSUP_VERSION_NUM)
			{
			BeepMessage(IDS_VERDOC_ERR);
			AfxThrowArchiveException(CArchiveException::badSchema);
			}
		if (verDoc > VERSION_NUM)
			{
			BeepMessage(IDS_VERDOC_ERR);
			AfxThrowArchiveException(CArchiveException::badSchema);
			}
			// TODO: この位置に読み込み用のコードを追加してください。
		}
	m_pFindList->Serialize(ar);
	//これから拡張されるかもしれないのであとでシリアライズする
	vpFindDlg->Serialize(ar);

	if (!ar.IsStoring())
		m_pFindList->ResetViewString(); // 検索ﾘｽﾄ表示へのｱｯﾌﾟﾃﾞｰﾄ
}


/////////////////////////////////////////////////////////////////////////////
// CFdiverDoc クラスの診断

#ifdef _DEBUG
void CFdiverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFdiverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFdiverDoc クラスのコマンド

void CFdiverDoc::OnFileSave() 
{
	CString newName=GetPathName();
//	newName.MakeLower();
	if (!newName.IsEmpty() && newName != ((CFdiverApp *)AfxGetApp())->m_cDefTagFile.GetBuffer())
		CDocument::OnFileSave();	// そのままセーブ
	else
		OnFileSaveAs();				// SaveAs()へ
}

void CFdiverDoc::OnFileSaveAs() 
{
	CString newName;
//	newName=GetPathName();
//	newName.MakeLower();
//	if (newName != ((CFdiverApp *)AfxGetApp())->m_cDefTagFile.GetBuffer())
//		{
//		CDocument::OnFileSaveAs();
//		return ;
//		}

	CDFile cdfile;
	if (!cdfile.SetUniqueName(vpFindDlg->GetStrBuffer(),"tax"))
		{
		CDocument::OnFileSaveAs();
		return ;
		}
	else
		newName = cdfile.GetFName();

	CDocTemplate* pTemplate = GetDocTemplate();

	if (!AfxGetApp()->DoPromptFileName(newName,
	  AFX_IDS_SAVEFILE, // : AFX_IDS_SAVEFILECOPY,
	  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
		return ;       // don't even try to save

	BeginWaitCursor();
	if (!OnSaveDocument(newName))
	{
		// be sure to delete the file
		TRY
		{
			CFile::Remove(newName);
		}
		CATCH_ALL(e)
		{
			TRACE0("Warning: failed to delete file after failed SaveAs\n");
		}
		END_CATCH_ALL
		EndWaitCursor();
		return ;
	}

	SetPathName(newName);
	ASSERT(m_strPathName == newName);       // must be set

	EndWaitCursor();
}

