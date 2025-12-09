/*    PortTool v2.2     lstent.h          */

#ifndef __LSTENT_H__
#define __LSTENT_H__

#include "malloc.h"
#include "..\mdfc\dfileexp.h"
#include "afxtempl.h"
#ifdef WIN32
typedef unsigned long	size_ent;
#else
typedef WORD	size_ent;
#endif


//takaso2010
//見つけた文字列の強調情報

typedef struct 
{
	int pos;	//見つけた文字列バイト位置
	int len;	//見つけた文字列バイト長
}MARK_FIND;

class CMarkFinds :public CArray<MARK_FIND>
{
	//DECLARE_DYNAMIC (CMarkFinds)
public:
	CMarkFinds() {
		CArray::CArray();
		};
	CMarkFinds(const CMarkFinds &src) {
		CArray::CArray();
		Copy(src); };

	~CMarkFinds() { };

};


class CListEntry
{
//	DECLARE_DYNAMIC (CListEntry)
public:

	CListEntry() {
		Initialize();
		};
	~CListEntry() {
		DeleteContent();
		};
	BOOL Initialize()
		{
		if ((pcdFile = new CDFileExp)==NULL)
			return FALSE;
		if ((pcdStr = new CDString)==NULL)
			return FALSE;
		//fOpen = FALSE;
		lLineNum = 0;
		dwHexNum = 0;
		//takaso2010
		if ((m_paryMark = new CMarkFinds)==NULL)
			return FALSE;
		return TRUE;
		}
	void DeleteContent()
		{
		if (pcdFile)
			{
			delete pcdFile;
			pcdFile = NULL;
			}
		if (pcdStr)
			{
			delete pcdStr;
			pcdStr = NULL;
			}
		if (m_paryMark)
			{
			delete m_paryMark;
			m_paryMark = NULL;
			}
		}
	// ﾌｧｲﾙｴﾝﾄﾘｰ(ﾊﾟｽまたはﾌｧｲﾙ)とﾄﾞｷｭﾒﾝﾄｴﾝﾄﾘｰを次のﾃﾞｰﾀで共有する。
	CDFileExp *pcdFile;	// ﾊﾟｽ名またはﾌｧｲﾙ名(ﾌｧｲﾙｱﾄﾘﾋﾞｭｰﾄ有り)
	CDString *pcdStr;	// 文書内容

	//takaso2010
	CMarkFinds *m_paryMark;
	//CArray<MARK_FIND, MARK_FIND&> m_aryMark;

	// pcdFile...変換前の情報、pcdStr....変換後の情報とする。
	// 変換ファイルの場合は、pcdFile------変換元パス＋ファイル名、
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
	union {
		BOOL fOpen;			// ｵｰﾌﾟﾝ状態か否か - ﾊﾟｽ名またはﾌｧｲﾙ名(ﾌｧｲﾙｱﾄﾘﾋﾞｭｰﾄ有り)
		long lLineNum;		// 番号(LineNum)   - 文書
		};
	union {
		size_ent nSortIndex;		// ｿｰﾄした時のｲﾝﾃﾞｯｸｽ(ﾊﾟｽまたはﾊﾟｽ内ﾌｧｲﾙでそれぞれ並ぶ)
		DWORD dwHexNum;		// 番号(HEX)
		};
		
	// ﾌｧｲﾙｴﾝﾄﾘｰのﾃﾞｰﾀﾘｾｯﾄ
	void ResetDataForFileEntry() {
		pcdStr->Empty();
		fOpen = TRUE;	//default is true!
		nSortIndex = (size_ent)-1;
		};

	// ﾄﾞｷｭﾒﾝﾄｴﾝﾄﾘｰのﾃﾞｰﾀﾘｾｯﾄ
	void ResetDataForDocEntry(DWORD dw=0) {
		pcdFile->GetString()->Empty();
		dwHexNum = dw;
		lLineNum = 0;
		//takaso2010 don't remove
		//m_paryMark->RemoveAll();
	};

	// エントリータイプを取得する
	int GetEntryType();

	// ビットマップタイプを取得する
	int GetEntryTypeOfBmp();
	
	// ｴﾝﾄﾘｰをｺﾋﾟｰする
	const CListEntry& operator = ( CListEntry &entrySrc );
};

enum LSTENT_TYPE {
	LSTENT_NORMAL,
	LSTENT_TXT,
	LSTENT_DOC
	};
// ソートタイプ
enum SORTTYPE {
	SORTTYPE_NO,	// ソートなし
	SORTTYPE_NAME,	// 名前ソート
	SORTTYPE_EXTENTION,	// 拡張子ソート
	SORTTYPE_SIZE,	// サイズソート
	SORTTYPE_DATE	// 日付ソート
};
class CListEntryArray :public CObject
{
protected:
	DECLARE_SERIAL(CListEntryArray)
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	//漢字コードマークアップを削除
	void KftTransFile(CDFile &cdfile, EXT_TYPE type, BOOL bArc=FALSE);
	//BOOL TrimMarkOfKftTransFile(CDFile &cdfile);
	EXT_TYPE TrimMarkOfKftTransFile(CDFile &cdfile);
	CString PickupMarkString(char *psz);

public:
	CListEntryArray() {
		Initialize();
		};
	~CListEntryArray() {
		DeleteContent();
		};

	void DeleteContent();
	void Initialize();

	CListEntry far * m_bse ;	// ｴﾝﾄﾘｰﾊﾞｯﾌｧ
	size_ent m_wMaxEntry;	// ｴﾝﾄﾘｰﾊﾞｯﾌｧの最大ｴﾝﾄﾘｰ数
	size_ent m_wUseEntry ;	// ｴﾝﾄﾘｰﾊﾞｯﾌｧの使用ｴﾝﾄﾘｰ数
	SORTTYPE m_SortType;	// ｿｰﾄﾀｲﾌﾟ
	BOOL	m_bAsc;			// ｿｰﾄ方向
	int m_cxSbc;
//	int m_cxDbc;
//	int m_cxChars[256-0x20];

	// ｿｰﾄｲﾝﾃﾞｯｸｽの作成
	BOOL FMakeSortIndexOfPath(BOOL fFile);
	BOOL FMakeSortIndexFlat();

	// ﾌｧｲﾙのｿｰﾄｲﾝﾃﾞｯｸｽの作成
	BOOL FMakeSortIndexOfFile(size_ent nIndex);

	// ｿｰﾄｲﾝﾃﾞｯｸｽに従ってパスﾙを順次取得する
	size_ent GetPathIndex(size_ent keyIndex);

	// ｿｰﾄｲﾝﾃﾞｯｸｽに従ってあるパス以下のﾌｧｲﾙを順次取得する
	size_ent GetFileIndexInPath(size_ent nIndexPath, size_ent keyIndex);
	size_ent GetFileIndexFlat(size_ent keyIndex);

	// SortTypeに従って２つのﾌｧｲﾙｴﾝﾄﾘｰを比べる
	int CompareFileEntry(size_ent ent1, size_ent ent2);
	void ResetSort();

	// ｴﾝﾄﾘｰを拡張する
	BOOL FExpandEntry ( size_ent entrys );

	//takaso2010
	// エントリーを取得する
	CListEntry far *GetEntry(size_ent nIndex) {
		ASSERT(nIndex >= 0 && nIndex < m_wUseEntry);
		return &m_bse[nIndex]; }

	// ビットマップタイプを取得する
	int GetEntryTypeOfBmp(size_ent nIndex) {
		ASSERT(nIndex >= 0 && nIndex < m_wUseEntry);
		return m_bse[nIndex].GetEntryTypeOfBmp(); }
	
	// エントリータイプを取得する
	int GetEntryType(size_ent nIndex) {
		ASSERT(nIndex >= 0 && nIndex < m_wUseEntry);
		return m_bse[nIndex].GetEntryType(); }

	// エントリーのタブ位置を取得する
	int GetTabOfEntry(size_ent nIndex);

	//エントリー文字列を取得する
	//void GetEntryString(size_ent nIndex, CString &str1, CString &str2, CString &str3, CString &str4, CString &str5);
	int GetEntryString(size_ent nIndex, CString &str1, CString &str2, CString &str3, CString &str4, CString &str5);
	#ifdef _TAG_TEXT
	BOOL GetEntryStringForTagText(size_ent nIndex, CString &str);
	#endif

	// ファイル名を取得する
	CDString GetFName(size_ent nIndex, BOOL fNameOnly, LSTENT_TYPE iTranFile=LSTENT_NORMAL);
	CDString GetFName(size_ent nIndex, BOOL fNameOnly, CString& strPath);

	// ファイル名およびパスのあるエントリーにリストを遡る
	size_ent ScanBeforeFileOrPath(size_ent nIndex, register BOOL fPath);

	// ファイル名およびパスのあるエントリーにリストを遡る
	size_ent ScanAfterFileAndPath(size_ent nIndex);
	size_ent ScanAfterPath(size_ent nIndex);
	size_ent ScanAfterPath(size_ent nIndex, size_ent &entrys);

	// パラメータに従ってパスまたはファイルのｵｰﾌﾟﾝ状態を設定します。
	void MarkeFOpenOfFiles(BOOL fOpenPath, BOOL fOpenFile);
	// タブストップを取得する
	int GetTabPostion(CDC *pDC, int lenPath);
	// ｷｬﾗｸﾀ幅ﾃｰﾌﾞﾙを作成する
	void MakeCharWidthTbl(CDC *pDC);

	int MyGetTextExtentX(CDC *pDC, CDString *pcdStr);

};

#endif //__LSTENT_H__
