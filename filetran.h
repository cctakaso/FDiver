// filetran.h : ヘッダー ファイル
//このクラスは、ファイル変換オブジェクトを管理するクラスである。
//変換先のパスを覚えておいて、もしも再度変換する場合は
//同一ファイルがすでに変換済みの場合は、変換しない。
//また変換したファイルを削除するなどの機能を有する
#ifndef __FILETRAN_H_
#define __FILETRAN_H_
#include "..\mdfc\dfileexp.h"
#include "filespec.h"
#include "dfilearc.h"



class CDFileCollect :public CDFileSpec
{
public:
	CDFileCollect():CDFileSpec(CDFileCollect::IDCH) {};
	CDFileCollect(const char* sz):CDFileSpec(sz, CDFileCollect::IDCH) {};
	~CDFileCollect() {};
	enum {IDCH = chTransSeparetor, IDCH2 = chSemi};

	int GetSize();
	CDString GetString(int iOffset, BOFFSET *poffset_first=NULL);
	const CDFileCollect& operator = ( const CDString& cstrSrc );
	const CDFileCollect& operator = ( const char *pstrSrc );
};


class CFileTrans;

typedef struct  {
	CFileTrans *pFileTrans;
	CDFile *pdFile;	// 一番元のファイル名->変換先のファイル名
	CDFile cdPath;	// 一番元のパス名
	CDFileCollect dFileCollectBefor;	//変換前の情報
	CDFileCollect dFileCollectAfter;	//変換後の情報
	BOOL fTrans;
	}TransData;
	//CListEntryの以下に対応している
	//CDFileExp *pcdFile;	// ﾊﾟｽ名またはﾌｧｲﾙ名(ﾌｧｲﾙｱﾄﾘﾋﾞｭｰﾄ有り)
	//CDString *pcdStr;	// 文書内容
	// pcdFile...変換前の情報、pcdStr....変換後の情報とする。
	// 変換ファイルの場合は、pcdFile------変換元ファイル名、
	//						 pcdStr-------変換先パス＋ファイル名
	// 圧縮ファイルの場合は、pcdFile------圧縮元ファイル名+'\'+圧縮内パス＋ファイル名、
	//						 pcdStr-------変換先パス＋ファイル名
	// 圧縮ファイル＋変換ファイルの場合は、２つのファイルが生成されるはず。
	//      pcdFile------圧縮元ファイル名+'\'+圧縮内パス＋ファイル名、
	//		pcdStr-------変換先パス＋ファイル名(1)＋';'+変換先パス＋ファイル名(2)
	// 圧縮ファイルの入れ子場合は、
	//      pcdFile------圧縮元ファイル名+'\'+圧縮内パス＋ファイル名(1)＋';'
	//					+圧縮元ファイル名+'\'+圧縮内パス＋ファイル名(2)..、
	//		pcdStr-------変換先パス＋ファイル名(1)＋';'+変換先パス＋ファイル名(2)...

class CFileTransForSearch
{
// コンストラクタ
public:
	CFileTransForSearch() {};	// 標準のコンストラクタ
	~CFileTransForSearch() {};
	// クラスの初期化
	void Initialize(TransData &tranData, BOOL fFindFileOnly, BOOL fActiveArc, CFindAttrs *pFindAttrs=NULL);


	BOOL FFirst(TransData &tranData);
	BOOL FNext(TransData &tranData);
protected:
	BOOL m_fFindFileOnly;
	BOOL m_fArcEnable; //ｱﾌﾟﾘｹｰｼｮﾝ側の圧縮ﾌｧｲﾙ内検索フラグ
	void InitTransData(TransData &tranData);
	BOOL FFirstLoop(TransData &tranData);

};


/////////////////////////////////////////////////////////////////////////////
// CFileTransArray
//CptrArrayの要素は、CFileTranオブジェクトを指す
class CFileTransArray :public CPtrArray
{
// コンストラクタ
public:
	CFileTransArray();	// 標準のコンストラクタ
	~CFileTransArray();

	BOOL FInitialize(char *szWorkPath);
	BOOL FInitScanData();

	void SetFindAttrs(CFindAttrs *pFindAttrs);

	void SetFindFileSpec(CDFileSpec *pFileCol);

	CFileTrans *GetFileTransObject(CDFile *pSrcFile, BOOL fArcEnable=TRUE);

	BOOL FDoTrans(TransData &tranData, BOOL fText=TRUE);
	BOOL FDoKftTrans(CString &str, EXT_TYPE type, BOOL bArc=FALSE);	//漢字変換
	
	BOOL FArcSupport();
	// サポートしているファイル拡張子か？
	BOOL FSupportExt(char *szExt, BOOL fArcEnable=TRUE);
	//BOOL FSupportExt(char *szExt);
	CDFileSpec GetSupportArcFileSpec();

	CDLLArray m_arypDll;	// Dllオブジェクト

	//BOOL m_fUserAbort;		// ファイル変換中ＤＬＬからのスキャンに
	//						// アボートを答えるためのフラグ
protected:
//	char *SzExtFromExt(EXT_TYPE ext) const;
	EXT_TYPE ExtFromSzExt(char *szExt);
	BOOL FIsArcExt(EXT_TYPE ext);
};

class CFileTrans : public CDFile
{
public:
	CFileTrans() {};
	~CFileTrans();
	
	//
	virtual BOOL FInitialize(EXT_TYPE ext, char *szFile);

	virtual BOOL FInitScanData() {
		return TRUE; }

	// 一番最初のファイル名を取り出す.
	virtual BOOL FFirst ( LPSTR szFileSpec = NULL ) {
		return TRUE; }

	// 次のファイル名を取り出す.
	virtual BOOL FNext ( LPSTR szFileSpec = NULL ) {
		return FALSE; }

	BOOL FDoTrans(TransData &tranData, BOOL fFindFileOnly=FALSE);
	// 指定ファイルを展開する
	virtual BOOL FDoTrans(char *szSrcFile, CString &cstrDes);

	// ファイル情報を取得する
	virtual FIND_DATA *PGetDta() {
		return NULL;/*元ファイルのデータを使わせる*/ };

	BOOL FIsArcType() {
		return 	(m_Ext >= EXT_ARCMIN) && (m_Ext >= EXT_ARCMAC); }

protected:
	EXT_TYPE m_Ext;
	CDLL *m_pDll;
	CFileScan m_pFileScan;
	CPtrArray m_arypFindData;
	CString m_cstrBasePath;	//後で削除するパス
	virtual void ResetContent();
};

class CFileTransArc : public CFileTrans
{
public:
	CFileTransArc() {};
	~CFileTransArc();

	//
	virtual BOOL FInitialize(EXT_TYPE ext, char *szFile);

	virtual BOOL FInitScanData();

	// 一番最初のファイル名を取り出す.
	virtual BOOL FFirst ( LPSTR szFileSpec = NULL );

	// 次のファイル名を取り出す.
	virtual BOOL FNext ( LPSTR szFileSpec = NULL );

	// 現在のセルポジションの格納ファイル情報を取得する
	virtual FIND_DATA *PGetDta();
protected:
	CPtrArray m_arypFindData;	// 格納ファイル情報のリスト
	int m_iSelFindData;			// 格納ファイル情報のセルポジション
	virtual void ResetContent();
};


#endif //! __FILETRAN_H_
