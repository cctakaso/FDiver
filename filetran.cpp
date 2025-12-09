/*    PortTool v2.2     FILETRAN.CPP          */
//filetran.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
#include "fdiver.h"
#include "mainfrm.h"
#include "filetran.h"
#include "findopti.h"
extern CFindOption *vpFindOption;		// ｵﾌﾟｼｮﾝｵﾌﾞｼﾞｪｸﾄ
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CFileTransArray *vpFileTransArray;


/////////////////////////////////////////////////////////////////////////////
// CDFileCollect
int CDFileCollect::GetSize()
{
	if (::GetAsyncKeyState(VK_CONTROL)&0x8000)
		return CDFileSpec_Base::GetSize();
	BOFFSET b;
	COFFSET cFind=0;
	int iOffset;

	if (IsEmpty())
		return 0;
	for (b=0, iOffset=0; (cFind=ScanFind (b, (WORD)GetChSep())) != (COFFSET)-1; iOffset++);
	if (iOffset<=0)
		for (b=0, iOffset=0; (cFind=ScanFind (b, (WORD)IDCH2)) != (COFFSET)-1; iOffset++);
	return iOffset+1;
}
CDString CDFileCollect::GetString(int iOffset, BOFFSET *poffset_first)
{
	if (::GetAsyncKeyState(VK_CONTROL)&0x8000)
		return CDFileSpec_Base::GetString(iOffset, poffset_first);
	BOFFSET b, b2;
	COFFSET cFind=0, cFind2=0;
	int iOffset2 = iOffset;
	for (b=0; iOffset>0 && (cFind=ScanFind (b, (WORD)GetChSep())) != (COFFSET)-1; iOffset--);
	for (b2=0; iOffset2>0 && (cFind2=ScanFind (b2, (WORD)IDCH2)) != (COFFSET)-1; iOffset2--);

	if (cFind2!=(COFFSET)-1 && (cFind==(COFFSET)-1 || cFind2 < cFind)) {
		cFind = cFind2;
		b = b2;
	}
	if (cFind==(COFFSET)-1)
		{
		CDString cdstr;
		return cdstr;	// ｴﾝﾄﾘｰなし
		}
	else
		{
		if (cFind!=0)
			cFind++;
		COFFSET cFindLim, cFindLim2;
		b2 = b;
		cFindLim=ScanFind (b, (WORD)GetChSep());
		cFindLim2=ScanFind (b2, (WORD)IDCH2);
		if (cFindLim2!=(COFFSET)-1 && (cFindLim==(COFFSET)-1 || cFindLim2 < cFindLim)) {
			cFindLim = cFindLim2;
			b = b2;
		}
		if (poffset_first)
			*poffset_first = b;
		if (cFindLim==(COFFSET)-1)
			return Mid(cFind);
		else
			return Mid(cFind, cFindLim-cFind);
		}
}
const CDFileCollect& CDFileCollect::operator = ( const CDString& cstrSrc )
{
	(*(CDString *)this) = cstrSrc.GetBuffer();
	return *this;
}


const CDFileCollect& CDFileCollect::operator = ( const char *pstrSrc )
{
	(*(CDString *)this) = pstrSrc;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CFileTransForSearch
// How To Use:
void CFileTransForSearch::Initialize(TransData &tranData, BOOL fFindFileOnly, BOOL fArcEnable, CFindAttrs *pFindAttrs/*=NULL*/)
{
	InitTransData(tranData);
	// DLLのファイルスキャンの条件イニシャル
	if (pFindAttrs)
		vpFileTransArray->SetFindAttrs(pFindAttrs);
	// 圧縮ﾌｧｲﾙが保持している格納ﾌｧｲﾙインデックスをイニシャライズする
	vpFileTransArray->FInitScanData();
	m_fFindFileOnly = fFindFileOnly;
	m_fArcEnable = fArcEnable;
}
void CFileTransForSearch::InitTransData(TransData &tranData)
{
	tranData.fTrans = FALSE;
	tranData.dFileCollectBefor = "";
	tranData.dFileCollectAfter = "";
}

BOOL CFileTransForSearch::FFirst(TransData &tranData)
{
	tranData.pFileTrans=NULL;
	InitTransData(tranData);
	// 元のパス名のセット-ここでセットしてしまう
	tranData.cdPath = tranData.pdFile->GetPath();
	switch (FFirstLoop(tranData))
		{
		case 1:
			tranData.fTrans = TRUE;
			//thlow
		case 0:
			return TRUE;
			break;
		default:
			break;
		}
	return FALSE;
}


int CFileTransForSearch::FFirstLoop(TransData &tranData)
{
// 変換対象ファイルでない->0
// 変換した->1
// 圧縮格納ファイルに希望のファイルがないとかエラー->-1;
	CFileTrans *pFileTrans;
	if (pFileTrans = vpFileTransArray->GetFileTransObject(tranData.pdFile, m_fArcEnable))
		{
		if (tranData.pFileTrans==NULL)
			tranData.pFileTrans = pFileTrans;		// 一番元の圧縮ファイル名へのポインタ
		// この書庫で、現在のセル位置の格納ﾌｧｲﾙは、また書庫であるか？
		FIND_DATA *pFindData = pFileTrans->PGetDta();
		CDFile cdFile;
		if (pFindData)
			cdFile = pFindData->srFD.cFileName;
		if (pFindData && vpFileTransArray->FSupportExt(cdFile.GetBufferExtention(), m_fArcEnable))
			{
			// 圧縮ﾌｧｲﾙの場合
			// ﾃﾞｰﾀのｾｰﾌﾞ
			CDFile cdFileBack =  *tranData.pdFile;
			CDFileCollect dFileCollectBBack = tranData.dFileCollectBefor;
			CDFileCollect dFileCollectABack = tranData.dFileCollectAfter;
			if (pFileTrans->FDoTrans(tranData, m_fFindFileOnly))
				{
				// 圧縮ファイルの入れ子対応
				if (FFirstLoop(tranData)>=0)
					{
					//case 0://入れ子じゃないよ
					//case 1://入れ子で変換した
				 	return 1; //一度は変換したよ
					}
				else
					{
					//case -1:
					//入れ子だったのだけど変換できなかった
					//次をスキャンする
					// 見つからない場合は、元にもどして
					*tranData.pdFile = cdFileBack;
					tranData.dFileCollectBefor = dFileCollectBBack;
					tranData.dFileCollectAfter = dFileCollectABack;
					goto NextScan;
					}
				}
			else
				if (!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
					return -1;
			//変換できなかった
			}
		else
NextScan:
			{
			// ﾃﾞｰﾀのｾｰﾌﾞ
			CDFile cdFileBack =  *tranData.pdFile;
			CDFileCollect dFileCollectBBack = tranData.dFileCollectBefor;
			CDFileCollect dFileCollectABack = tranData.dFileCollectAfter;
			while (pFileTrans->FNext())
				{
				if (pFileTrans->FDoTrans(tranData, m_fFindFileOnly))
					{
					// 圧縮ファイルの入れ子対応
					if (FFirstLoop(tranData)>=0)
						{
						//case 0://入れ子じゃないよ
						//case 1://入れ子で変換した
						return 1; //一度は変換したよ
						}
					//case -1:
					//入れ子だったのだけど変換できなかった
					//次をスキャンする
					}
				else
					if (!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
						return -1;
				}
			// 見つからない場合は、元にもどして
			*tranData.pdFile = cdFileBack;
			tranData.dFileCollectBefor = dFileCollectBBack;
			tranData.dFileCollectAfter = dFileCollectABack;
			return -1;	//変換すべきものだったけどヒットしない
			}
		return -1;	//変換すべきものだったけどヒットしない
		}
	else
		return 0;	//変換すべきﾌｧｲﾙじゃない

	ASSERT(FALSE);
	return FALSE;
}
                                 
BOOL CFileTransForSearch::FNext(TransData &tranData)
{
	//もとのﾌｧｲﾙﾄﾗﾝｽｵﾌﾞｼﾞｪｸﾄはあるか？
	if (tranData.pFileTrans==NULL)
		return FALSE;
	InitTransData(tranData);
	//tranData.pdFileに一番元のファイルがまたｾｯﾄしてあることが必要！！！
	switch (FFirstLoop(tranData))
		{
		case 1:
			tranData.fTrans = TRUE;
			//thlow
		case 0:
			return TRUE;
			break;
		default:
			break;
		}
	return FALSE;
}




/////////////////////////////////////////////////////////////////////////////
// CFileTransArray
CFileTransArray::CFileTransArray()	// 標準のコンストラクタ
{
//	m_fUserAbort = FALSE;
}

CFileTransArray::~CFileTransArray()
{
	for (int i=0; i<GetSize();i++)
		delete ((CFileTrans *)GetAt(i));
}

/*
char *CFileTransArray::SzExtFromExt(EXT_TYPE ext) const
{
	ASSERT(ext<EXT_MAX);
	return szEXT_TYPE[(int)ext];
}
*/
EXT_TYPE CFileTransArray::ExtFromSzExt(char *szExt)
{
	CString cstr = szExt;
	cstr.MakeLower();
	for (int i=0; i<=EXT_ARCMAC; i++) {
		for (int k=0; szEXT_TYPE[i][k][0]!='\0'; k++) {
			if (cstr == szEXT_TYPE[i][k])
			return (EXT_TYPE)i;
		}
	}

	return EXT_MAX;
}

BOOL CFileTransArray::FIsArcExt(EXT_TYPE ext)
{
	return (ext>=EXT_ARCMIN) && (ext<=EXT_ARCMAC);
}


//一つでも現在サポートしているアーカイバがあるか？
BOOL CFileTransArray::FArcSupport()
{
	for (int i=EXT_ARCMIN; i<=EXT_ARCMAC; i++)
		{
		if (m_arypDll.FActiveAndCheck((EXT_TYPE)i))
			return TRUE;
		}
	return FALSE;
}

CDFileSpec CFileTransArray::GetSupportArcFileSpec()
{
	CDFileSpec cdFileSpec;
	for (int i=EXT_ARCMIN; i<=EXT_ARCMAC; i++){
		if (m_arypDll.FActiveAndCheck((EXT_TYPE)i))	{
			for (int k=0; szEXT_TYPE[i][k][0]!='\0'; k++) {
				CString cstr = "*.";
				cstr += szEXT_TYPE[i][k];
				cdFileSpec.AddString(cstr.GetBuffer(0));
			}
		}
	}
	return cdFileSpec;
}

BOOL CFileTransArray::FSupportExt(char *szExt, BOOL fArcEnable)
{
#ifdef WIN32
	EXT_TYPE et = ExtFromSzExt(szExt);
	BOOL fIsArc = FIsArcExt(et);
	if (et<EXT_ARCMIN  ||  et>EXT_ARCMAC)
		return FALSE;
	return m_arypDll.FActiveAndCheck(et) && (!fIsArc || (fIsArc && fArcEnable));
#else
	return FALSE;
#endif //WIN32
}


BOOL CFileTransArray::FInitialize(char *szWorkPath)
{
	return m_arypDll.FInitialize(szWorkPath);
}

BOOL CFileTransArray::FInitScanData()
{
	for (int i=0; i<GetSize(); i++)
		{
		((CFileTrans *)GetAt(i))->FInitScanData();
		}
	return TRUE;
}

void CFileTransArray::SetFindAttrs(CFindAttrs *pFindAttrs)
{
	m_arypDll.SetFindAttrs(pFindAttrs);
}

void CFileTransArray::SetFindFileSpec(CDFileSpec *pFileSpec)
{
	m_arypDll.SetFindFileSpec(pFileSpec);
}

CFileTrans *CFileTransArray::GetFileTransObject(CDFile *pSrcFile, BOOL fArcEnable /*=TRUE*/)
{
	//変換元ファイル名をcheck
	if (!FSupportExt(pSrcFile->GetBufferExtention(), fArcEnable))
		return NULL;	//ﾄﾗﾝｽﾚｰﾄ対象ファイルじゃない。

	//登録すみファイルにあるか？
	for (int i=0; i<GetSize(); i++)
		{
		// ファイル名の比較
		if (*((CFileTrans *)GetAt(i))->GetString() == *pSrcFile->GetString())
			return (CFileTrans *)GetAt(i);					//あったよ！
		}

	//ファイルタイプにあわせてCFileTransオブジェクトを作成する
	EXT_TYPE ext;
	CFileTrans *pFileTrans;
	switch (ext=ExtFromSzExt(pSrcFile->GetBufferExtention()))
		{
		case EXT_LZH:
		case EXT_ZIP:
		case EXT_ARJ:
		case EXT_TAR:
		case EXT_CAB:
		case EXT_RAR:
//EntryPoint Arc
			pFileTrans = new CFileTransArc();
			break;
//		case EXT_KFT:
//			pFileTrans = new CFileTransArc();
//			break;
		default:
			ASSERT(FALSE);
			return NULL;		//no support file type!
			break;
		}
	//変換元(圧縮)ファイル名セット
	if (!pFileTrans->FInitialize(ext, pSrcFile->GetBuffer()))
		{
		delete pFileTrans;
		return NULL;
		}
	Add(pFileTrans);					//array add
	return pFileTrans;
}

// 漢字を変換する
BOOL CFileTransArray::FDoKftTrans(CString &str, EXT_TYPE type, BOOL bArc)
{
	CDLLDoc *pDll = (CDLLDoc*)m_arypDll.PDll(type);
	if (pDll && m_arypDll.FActiveAndCheck(type)) {
		CDFile dfile;
		CString cstrBasePath;
		dfile = str;
		pDll->FSetSrcFile(str.GetBuffer(0));
		if (pDll->DoTrans(bArc ? str.GetBuffer(0):str.Mid(dfile.GetDrvLen()).GetBuffer(0), str, cstrBasePath)==0) {
			return TRUE;
		}
	}
	return FALSE;
}

// 既存のtranDataにしたがって最終ファイルを取得する
BOOL CFileTransArray::FDoTrans(TransData &tranData, BOOL fText/*=TRUE*/)
{
//IN :tarnData.cdPath..................ソースファイルのパス
//IN :tarnData.dFileCollectBefor.......ソースファイルコレクション
//IN :fText............................最終テキストファイルの取得
//OUT:tarnData.dFileCollectAfter.......ディストリビュートファイルコレクション
// 変換した->TRUE
// 変換できない->FALSE;
	int iSelMac = tranData.dFileCollectBefor.GetSize()-1;
	ASSERT(iSelMac>=1);
	tranData.pdFile->SetPath(tranData.cdPath.GetBuffer());
	tranData.pdFile->SetName(tranData.dFileCollectBefor.GetString(0).GetBuffer(0));
	for (int iSel=1; iSel<=iSelMac; iSel++)
		{
		CFileTrans *pFileTrans;
		if (pFileTrans = GetFileTransObject(tranData.pdFile))
			{
			if (!fText && iSel == iSelMac && pFileTrans->FIsArcType())
				return TRUE;	//ドキュメント
			CString cstrFile = tranData.dFileCollectBefor.GetString(iSel);
			if (pFileTrans->FFirst(cstrFile.GetBuffer(0)))
				{
				CString cstrDes;
				if (pFileTrans->FDoTrans(cstrFile.GetBuffer(0), cstrDes))
					{
					//変換したファイル名
					tranData.dFileCollectAfter.SetString(iSel-1, cstrDes.GetBuffer(0));
					*tranData.pdFile = cstrDes;
					continue;
					}
				}
			}
		return FALSE; //見つからないまたは、途中で変換できない
		}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CFileTrans
CFileTrans::~CFileTrans()
{
	ResetContent();
}

void CFileTrans::ResetContent()
{
	//ディレクトリ以下の展開ファイルを全部削除する
	if (!m_cstrBasePath.IsEmpty()) {
		CDFile dfile(m_cstrBasePath);
		RemoveAllDir(dfile.GetPath().GetBuffer(0), FALSE);	//no prompt
	}
}



BOOL CFileTrans::FInitialize(EXT_TYPE ext, char *szFile)
{
	//関連ＤＬＬオブジェクトへのポインタをセット
	ASSERT(ext>EXT_NON);
	ASSERT(szFile && *szFile);
	m_Ext = ext;
	SetFName(szFile);
	m_pDll = vpFileTransArray->m_arypDll.PDll(m_Ext);
	if (!m_pDll)
		return FALSE;
	ASSERT(m_pDll);
	//ソースファイルが正しいかどうかチェックする
	return m_pDll->FSetSrcFile(GetBuffer());
}

BOOL CFileTrans::FDoTrans(TransData &tranData, BOOL fFindFileOnly/*=FALSE*/)
{
	char *szFindFile = PGetDta()->srFD.cFileName;

	if (fFindFileOnly)
		{
		CDFile cdFile = szFindFile;
		if (!FIsArcExtention(cdFile.GetBufferExtention()))
			{
			//最終変換ファイル名
			*tranData.pdFile = szFindFile;
			//圧縮ファイル+';'+圧縮ファイル内ﾃﾞｨﾚｸﾄﾘ+ファイル名
			CDFile cdFileSrc;
			if (tranData.dFileCollectBefor.IsEmpty())
				tranData.dFileCollectBefor.AddString(GetName().GetBuffer());
			tranData.dFileCollectBefor.AddString(szFindFile);
			//変換したファイル名
			//なし
			return TRUE;
			}
		}

	CString cstrDes;
	if (FDoTrans(szFindFile, cstrDes))
		{
		//最終変換ファイル名
		*tranData.pdFile = cstrDes.GetBuffer(0);
		//圧縮ファイル+';'+圧縮ファイル内ﾃﾞｨﾚｸﾄﾘ+ファイル名
		CDFile cdFileSrc;
		if (tranData.dFileCollectBefor.IsEmpty())
			tranData.dFileCollectBefor.AddString(GetName().GetBuffer());
		tranData.dFileCollectBefor.AddString(szFindFile);
		//変換したファイル名
		tranData.dFileCollectAfter.AddString(cstrDes);
		return TRUE;
		}
	return FALSE;
}
// 指定ファイルを展開する
BOOL CFileTrans::FDoTrans(char *szSrcFile, CString &cstrDes)
{
	if (m_pDll && m_pDll->FSetSrcFile(GetBuffer()))	//元ファイルを指定する
		return m_pDll->DoTrans(szSrcFile, cstrDes, m_cstrBasePath)==0;
	else
		return FALSE;
}

CFileTransArc::~CFileTransArc()
{
	ResetContent();
}

void CFileTransArc::ResetContent()
{
	//格納ファイルの情報を削除する
	for (int i=0; i<m_arypFindData.GetSize(); i++)
		delete ((FIND_DATA *)m_arypFindData.GetAt(i));
}

BOOL CFileTransArc::FInitialize(EXT_TYPE ext, char *szFile)
{
	if (!CFileTrans::FInitialize(ext, szFile))
		return FALSE;
    // 最初に全格納ファイルのリストを作成する
	//ステータスバーの表示	
	CString cstrMsg;
	cstrMsg = m_pDll->PGetDllFile()->GetName().GetBuffer();
	//cstrMsg.MakeLower();
	cstrMsg += " Scan....";
	((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));

    ResetContent();

    FIND_DATA *pFindData;
    if (m_pDll->FFirst(szStarDotStar, TRUE/*this is not work this parameter now!*/))
		{
		do {
			//見つけたファイルの情報を格納する
			pFindData = new FIND_DATA;
			m_pDll->PopData(pFindData);
			m_arypFindData.Add(pFindData);
			}while(m_pDll->FNext());
		}

	return FInitScanData();
}

BOOL CFileTransArc::FInitScanData()
{
	m_iSelFindData = -1;	//格納ファイル情報のセルポジションの初期化
	return TRUE;
}


// 一番最初のファイル名を取り出す.
BOOL CFileTransArc::FFirst ( LPSTR szFileSpec /*=NULL*/) 
{
	//if (szFileSpec==NULL)
	//	{
	//	//格納ファイル情報のセルポジションの初期化
	//	m_iSelFindData = -1;
	//	}
	return FNext(szFileSpec);
}


// 次のファイル名を取り出す.
BOOL CFileTransArc::FNext ( LPSTR szFileSpec /*=NULL*/)
{
	if (szFileSpec==NULL)
		{
		//セットしてある条件に従う
		//最後までスキャンしたなら最初に戻す
		if (m_iSelFindData==m_arypFindData.GetSize())
			m_iSelFindData = -1;
		while ((++m_iSelFindData)<m_arypFindData.GetSize())
			{
			if (m_pDll->FCheckAttrsMatch((FIND_DATA *)m_arypFindData.GetAt(m_iSelFindData)))
				return TRUE;
			}
		}
	else
		{
		//セットしてる条件には従わず szFileSpecにのみ従う、１ﾌｧｲﾙのみ検索
		CString cstr;
		CString cstrSpec = szFileSpec;
		cstrSpec.MakeLower();
		int iSelFindData = -1;
		while ((++iSelFindData)<m_arypFindData.GetSize())
			{
			cstr = (char *)((FIND_DATA *)m_arypFindData.GetAt(iSelFindData))->srFD.cFileName;
			cstr.MakeLower();
			if (cstr==cstrSpec)
				return TRUE;
			}
		}
	return FALSE;
}

// 現在のセルポジションの格納ファイル情報を取得する
FIND_DATA *CFileTransArc::PGetDta() 
{
	if (m_iSelFindData<0 || m_iSelFindData>=m_arypFindData.GetSize())
		return NULL;	//エントリーがない
	return (FIND_DATA *)m_arypFindData.GetAt(m_iSelFindData);
}
