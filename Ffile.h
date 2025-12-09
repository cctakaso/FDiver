/*    PortTool v2.2     ffile.h          */

#ifndef __FFILE_H__
#define __FFILE_H__

#ifndef __cplusplus
#error Magical Design Foundation Classes require C++ compilation (use a .cpp suffix)
#endif

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"        // Target version control
#include "..\mdfc\dfile.h"
#include <direct.h>
#include "lstent.h"
#include "filetran.h"
#define MATCHANY //?や*を有効にする、リードする方法を256戻るようにする。


class CGrepEngin;

class CFindFile
{
protected:
	
	BOOL m_fSubDir;
	BOOL m_fArcEnable;
	CDFileSpec *m_pFileSpec;
	CDFile *m_pFilePath;
	char *m_pszForFindList;		// 
	CDFile m_dFileSrc;				// アーカイブファイル
	CString m_strReadBack;

	HGLOBAL m_hReadBuff;
	BYTE far *m_lpReadBuff;	// ﾘｰﾄﾞﾊﾞｯﾌｧ先頭ﾎﾟｲﾝﾀ
	BYTE far *m_lpReadBuff_back;	// ﾘｰﾄﾞﾊﾞｯﾌｧ先頭ﾎﾟｲﾝﾀ　バックアップ
	EXT_TYPE m_ext_type;

	long m_lSeek;		// 実際のﾌｧｲﾙｼｰｸ位置
	long m_lReadSize;	// 実際のﾌｧｲﾙﾘｰﾄﾞｻｲｽﾞ
	long m_lReadBuffSize;	// ﾘｰﾄﾞﾊﾞｯﾌｧｻｲｽﾞ
	int m_iPatternLength;	// 検索ﾊﾟﾀｰﾝｻｲｽﾞ
	CDFile *m_pReadFile;	// 見つけたﾌｧｲﾙ(現在ｽｷｬﾝﾘｰﾄﾞ中のﾌｧｲﾙ)
	CFileScan	*m_pFileScan;
	//FIND_DATA *m_pDTA;			// 見つけたﾌｧｲﾙのDTA
	long m_lSeekLineBefor;	// 直前の見つけた行の先頭ｼｰｸ位置
	long m_lLineBefor;			// 直前の見つけた行番号
#ifdef MATCHANY
	long m_lOffScanStBuff;	// ﾘｰﾄﾞﾊﾞｯﾌｧのﾊﾟﾀｰﾝﾏｯﾁﾝｸﾞを開始するｽｷｬﾝﾎﾟｲﾝﾀを指すｵﾌｾｯﾄを格納する
	long m_lLineScanStBuff;			// ﾘｰﾄﾞﾊﾞｯﾌｧのﾊﾟﾀｰﾝﾏｯﾁﾝｸﾞを開始するｽｷｬﾝﾎﾟｲﾝﾀでの行番号
#endif
	CGrepEngin *m_pcGrepEngin;	// ｸﾞﾚｯﾌﾟｴﾝｼﾞﾝ
	CFileTransForSearch m_FileTransForSearch;

	// ｶﾚﾝﾄﾃﾞｨﾚｸﾄﾘをﾄﾞﾚｲﾌﾞ付きで変更します。
	//BOOL SetCurrentDirectory(LPSTR lpPath);

	// 検索された項目を再度絞り込み検索または、実ディスクを検索するか切り分ける。
	BOOL SearchFilesDiskOrList(char * szPath);
	// ファイルスペックに従って指定パスのファイルを、見つける。(再帰呼び出し関数)
	BOOL SearchFilesDisk(char * szPath);
	// ファイルスペックに従ってリストのファイルを、見つける。
	BOOL SearchFilesList(CListEntryArray *pEntryArray);

	// ﾘｰﾄﾞﾊﾞｯﾌｧ等のｸﾘｰﾝﾅｯﾌﾟ
	void CleanUpForRead();

	//漢字ｺｰﾄﾞ変換マーク
	void MarkKftTransFile();

public:
	CDLLDoc *m_pKftDll;	//漢字フィルターDLLポインタ

public:
	
	CFindFile();

	~CFindFile();

	// ディレクトリの中で最初のファイル
	// セット:CFindFile::SearchFiles()
	// リセット：CFindList::FAddList()
	BOOL m_fFirstFileOfDir;

	TransData m_TranData;

	char *GetFindFileBuffer() {
		return m_pReadFile->GetBuffer(); }

	// ファイル名を取得する
	CDFile *GetFindFile() {
		return m_pReadFile;
		}
	BOOL FFirstRead() {
		return m_lOffScanStBuff==0; }
	BOOL FLastRead() {
		return m_lReadSize != m_lReadBuffSize-1; }
	long GetReadSize() {
		return m_lReadSize; }
	long GetSeekLineBefor() { //takaso2010
		return m_lSeekLineBefor; }

	FIND_DATA *PGetDta() {
		return m_pFileScan->PGetDta(); }

	// ファイルスペックをイニシャルセットする。
	BOOL FInitFiles(CDFile *pcFilePath, CDFileSpec *pcFileSpec, BOOL fSubDir, BOOL fArc);

	// ファイルスペックに従ってファイルを、見つける。
	int StartScan(CGrepEngin *pcEngin, long lReadSize, int iPatternLength);
	
	// 見つけたﾌｧｲﾙを読み込む為の初期処理
	BOOL FInitRead(long readsize, int iPatternLength);

	// ﾌｧｲﾙ読込みの初期処理
	int SetReadFile(char *szFile);

	// 読込みﾌｧｲﾙのｸﾛｰｽﾞ
	void CloseReadFile();

	// ﾌｧｲﾙの順次読込み
	long ReadBuffer();

	// ﾘｰﾄﾞﾊﾞｯﾌｧへのﾎﾟｲﾝﾀを取得する
	BYTE far *GetBuffer() const {
		return m_lpReadBuff; }
	
	// 実際のﾌｧｲﾙｼｰｸ位置
	long GetSeek() const {
		return m_lSeek; }

	// 実際のﾌｧｲﾙﾘｰﾄﾞｻｲｽﾞ
	long GetReadSize() const {
		return m_lReadSize; }

	// ﾗｲﾝ情報取得
	BYTE far *GetLineInfo(long lSeekFind, long cchMatched, long *plLine);

#ifdef MATCHANY
	// ﾘｰﾄﾞﾊﾞｯﾌｧのﾊﾟﾀｰﾝﾏｯﾁﾝｸﾞを開始するｽｷｬﾝﾎﾟｲﾝﾀを指すｵﾌｾｯﾄを格納する
	long GetOffSetOfScanStart()	{
		return m_lOffScanStBuff; }
#endif

};


#endif //__FFILE_H__,
