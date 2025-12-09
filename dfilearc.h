/***********************************************************************************
-- Class Name: C F i l e S c a n A r c  c l a s s
-- Description and Usage:
		アーカイブファイルを管理するクラス
-- Notes:---------------------------------------------------------------------------
	DLLの管理と、与えられたFIND_DATAをもとに圧縮ファイル内の
	検索および、指定ファイルの解凍を行う。
-- History:
		'95.11	- created		(M.Design)
**************************************************************************************/

#ifndef __DFILEARC_H__
#define __DFILEARC_H__

/////////////////////////////////////////////////////////////////////////////

#include "..\mdfc\dfile.h"

class CDLL : public CFileScan
{
public:
	CDLL() {
		m_ext =EXT_NON;
		m_hDll = NULL; }
	virtual ~CDLL() {
		FreeLib();
		};
	//ＤＬＬのﾁｪｯｸ等
	virtual BOOL FInitialize(EXT_TYPE at=EXT_NON, char *szBasePath=NULL, BOOL fActive=TRUE);

	BOOL FActive() {
		return m_hDll!=NULL;}

	virtual BOOL FActiveUpdate();

	//Ａｒｃファイルをセットする
	virtual BOOL FSetSrcFile(char *szArcFile);

	CDString *PGetSrcFile() {
		return m_dFileSrc.GetString(); }

	// 指定ファイルを展開する
	virtual int DoTrans(char *szSrcFile, CString &cstrDes, CString &cstrBasePath)=0;

	EXT_TYPE Getext() {
		return m_ext; }

	// 一番最初のファイル名を取り出す.
	virtual BOOL FFirst ( LPSTR szFileSpec, BOOL fFile) {
		return TRUE; }

	// 次のファイル名を取り出す.
	virtual BOOL FNext () {
		return FALSE; }
	CDFile *PGetDllFile() {
		return &m_dFileSrc; }
	HINSTANCE GetDll() {
		return m_hDll; }
protected:
	EXT_TYPE m_ext;					// 種別
	HINSTANCE m_hDll;			// ＤＬＬのハンドル
	CString m_cstrBasePath;			// 解凍先のﾍﾞｰｽパス
	CDFile m_dFileSrc;				// アーカイブファイル
	void FreeLib();
};

#ifdef WIN32
#include "Unlha32.h"
#include "Unzip32.h"
#include "Unarj32.h"
//#include "cabapi.h"
//EntryPoint Arc
#else
#include "Unlha.h"
#endif

typedef	WORD (WINAPI* DGetVersion)(VOID);
typedef	BOOL (WINAPI* DSetBackGroundMode)(const BOOL BackGroundMode);
typedef	BOOL (WINAPI* DSetCursorMode)(const BOOL CursorMode);
#ifdef WIN32
typedef	int (WINAPI* DArcCmd)(const HWND _hwnd, LPCSTR szCmdLine, LPSTR szOutput, const DWORD wSize);
#else
typedef	int (WINAPI* DArcCmd)(LPCSTR szCmdLine, LPSTR szOutput, const WORD wSize);
#endif //WIN32
typedef	BOOL (WINAPI* DCheckArchive)(LPCSTR _szFileName, const int _iMode);
typedef	HANDLE (WINAPI* DOpenArchive)(const HWND _hwnd, LPCSTR _szFileName,const DWORD _dwMode);
typedef	int (WINAPI* DCloseArchive)(HANDLE _harc);
typedef	int (WINAPI* DFindFirst)(HARC _harc, LPCSTR _szWildName, INDIVIDUALINFO *_lpSubInfo);
typedef	int (WINAPI* DFindNext)(HARC _harc, INDIVIDUALINFO *_lpSubInfo);
typedef BOOL (WINAPI *DSetOwnerWindow)(const HWND _hwnd);
typedef BOOL (WINAPI *DClearOwnerWindow)(VOID);
typedef BOOL (WINAPI *DGetRunning)(VOID);
//trans dll only.(unkanj.dll)
/*
typedef HANDLE (WINAPI* DOpenTran)(const HWND _hwnd, LPCSTR szCmdLine, LPSTR szOutput, const DWORD wSize, int *_prtn);
typedef unsigned int (WINAPI* DReadTran)(const HANDLE handle, void* lpBuf, UINT nCount, BOOL *pRtn);
typedef void (WINAPI *DCloseTran)(HANDLE handle);
typedef int (WINAPI *DGetType)(const HANDLE handle);
typedef BOOL (WINAPI *DIsEOFTran)(const HANDLE handle);
*/
#define WM_ARCEXTRACT_TXT	"wm_arcextract"

extern UINT WM_ARCEXTRACT_MSG;

#include "..\Unkanj\unkanj.h"

class CDLLArc : public CDLL
{
public:
	CDLLArc() {
		m_FindData.hFindHandle=NULL; }
	virtual ~CDLLArc() {};

	virtual BOOL FInitialize(EXT_TYPE at=EXT_NON, char *szBasePath=NULL, BOOL fActive=TRUE);

	//ソースファイルをセットする
	virtual BOOL FSetSrcFile(char *szArcFile);

	//CDString *PGetSrcFile() {
	//	return m_dFileSrc.GetString(); }

	// 一番最初のファイル名を取り出す.
	virtual BOOL FFirst ( LPSTR szFileSpec, BOOL fFile);
	// 次のファイル名を取り出す.
	virtual BOOL FNext () ;

	// 指定ファイルを展開する
	virtual int DoTrans(char *szSrcFile, CString &cstrDes, CString &cstrBasePath);
protected:
	INDIVIDUALINFO 	m_ArcInfo;		// アーカイブ・インフォメーション

	// 通常ファイルと同様にFIND_DATAへのファイル情報への
	BOOL SaveAndChkAttr();
	// 一番最初のファイル名を取り出す.
	BOOL FFirst ( LPSTR szFileSpec);

#ifdef NOTUSE
	BOOL m_fDir;
#endif //NOTUSE
	DGetVersion GetVersion;
	DSetBackGroundMode SetBackGroundMode;
	DSetCursorMode SetCursorMode;
	DArcCmd ArcCmd;
	DCheckArchive CheckArchive;
	DOpenArchive OpenArchive;
	DCloseArchive CloseArchive;
	DFindFirst FindFirst;
	DFindNext FindNext;
	DSetOwnerWindow SetOwnerWindow;
	DClearOwnerWindow ClearOwnerWindow;
	DGetRunning GetRunning;
private:
	CString		m_strAttr;
};


class CDLLDoc : public CDLL
{
#define UNKANJI_SUB_DIR	("UNKANJI")
#define XDOC_SUB_DIR	("XDOC")
public:
	CDLLDoc();
	virtual ~CDLLDoc();

	//ＤＬＬのﾁｪｯｸ等
	virtual BOOL FInitialize(EXT_TYPE at=EXT_NON, char *szBasePath=NULL, BOOL fActive=TRUE);

	// 指定ファイルを展開する
	int DoTrans(char *szSrcFile, CString &cstrDes, CString &cstrBasePath);
	BOOL DoOpenTran(char *szSrcFile);
	unsigned int DoReadTran(void* lpBuf, UINT nCount, int *pRtn=NULL);
	void DoCloseTran();
	CString DoGetType();
	BOOL DoIsEOFTran();
protected:
	HANDLE m_handle;
	DGetVersion GetVersion;
	DArcCmd ArcCmd;
	DOpen OpenTran;
	DRead ReadTran;
	DClose CloseTran;

	DSetBackGroundMode SetBackGroundMode;
	DSetOwnerWindow SetOwnerWindow;
	//DClearOwnerWindow ClearOwnerWindow;
	DGetRunning GetRunning;

	DGetType GetType;
	DIsEOF	IsEOFTran;
};

class CDLLArray :public CPtrArray
{
public:
	CDLLArray() {};
	virtual ~CDLLArray();

	BOOL FInitialize(char *szWorkPath);
	void SetFindAttrs(CFindAttrs *pFindAttrs);
	void SetFindFileSpec(CDFileSpec *pFileCol);

	CDLL *PDll(EXT_TYPE ext);

	BOOL FActiveAndCheck(EXT_TYPE ext);
protected:

};


#endif // __DFILEARC_H__

