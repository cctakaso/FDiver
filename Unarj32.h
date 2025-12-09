/*
** UNARJ
** Copyright (c) 1990-93 by Robert K Jung.  All rights reserved.
**
** UNARJ32.H
** Windows DLL Version, Micco, Mar.21,1997
** Copyright (c) 1996-97 by Micco. All rights reserved.
*/

#if !defined(UNARJ32_H)
#define UNARJ32_H

#define UNARJ32_VERSION 10

#if !defined(FNAME_MAX32)
#define	FNAME_MAX32		512
#endif
#if !defined(COMMENT_MAX)
#define	COMMENT_MAX	2048
#endif

#if defined(__BORLANDC__)
#pragma option -a-
#else
#pragma pack(1)
#endif

#ifndef ARC_DECSTRACT
#define ARC_DECSTRACT
typedef	HGLOBAL	HARC;

typedef struct {
	DWORD 			dwOriginalSize;		/* ファイルのサイズ */
 	DWORD 			dwCompressedSize;	/* 圧縮後のサイズ */
	DWORD			dwCRC;				/* 格納ファイルのチェックサム */
	UINT			uFlag;				/* 処理結果 */
	UINT			uOSType;			/* 書庫作成に使われたＯＳ */
	WORD			wRatio;				/* 圧縮率 */
	WORD			wDate;				/* 格納ファイルの日付(DOS 形式) */
	WORD 			wTime;				/* 格納ファイルの時刻(〃) */
	char			szFileName[FNAME_MAX32 + 1];	/* 書庫名 */
	char			dummy1[3];
	char			szAttribute[8];		/* 格納ファイルの属性(書庫固有) */
	char			szMode[8];			/* 格納ファイルの格納モード(〃) */
}	INDIVIDUALINFO, *LPINDIVIDUALINFO;

#endif

typedef struct {
	UINT			uTotalFiles;
	UINT			uCountInfoFiles;
	UINT			uErrorCount;
	LONG			lDiskSpace;
	HGLOBAL			hSubInfo;
	char			szComment[COMMENT_MAX + 1];
	char			dummy[3];
}	LOCALINFO;

//#ifndef EXTRACTINGINFO
//typedef struct {
//	DWORD 			dwFileSize;		/* 格納ファイルのサイズ */
//	DWORD			dwWriteSize;	/* 書き込みサイズ */
//	char			szSourceFileName[FNAME_MAX32 + 1];	/* 格納ファイル名 */
//	char			dummy1[3];
//	char			szDestFileName[FNAME_MAX32 + 1];
//									/* 解凍先または圧縮元パス名 */
//	char			dummy[3];
//}	EXTRACTINGINFO, *LPEXTRACTINGINFO;
//#else
typedef EXTRACTINGINFO *LPEXTRACTINGINFO;
//#endif

//#ifndef EXTRACTINGINFOEX //Takaso
//typedef struct {
//	EXTRACTINGINFO exinfo;
//	DWORD dwCompressedSize;
//	DWORD dwCRC;
//	UINT  uOSType;
//	WORD  wRatio;
//	WORD  wDate;
//	WORD  wTime;
//	char  szAttribute[8];
//	char  szMode[8];
//} EXTRACTINGINFOEX, *LPEXTRACTINGINFOEX;
//#endif

#if !defined(__BORLANDC__)
#pragma pack()
#else
#pragma option -a.
#endif

#if !defined(__BORLANDC__)
#define	_export
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ### LHA.DLL Ver 1.1 と互換性のある API です。### */
WORD WINAPI _export UnarjGetVersion(VOID);

BOOL WINAPI _export UnarjGetRunning(VOID);

BOOL WINAPI _export UnarjGetBackGroundMode(VOID);
BOOL WINAPI _export UnarjSetBackGroundMode(const BOOL _bBackGroundMode);
BOOL WINAPI _export UnarjGetCursorMode(VOID);
BOOL WINAPI _export UnarjSetCursorMode(const BOOL _bCursorMode);
WORD WINAPI _export UnarjGetCursorInterval(VOID);
BOOL WINAPI _export UnarjSetCursorInterval(const WORD _uInterval);

int WINAPI _export Unarj(const HWND _hwnd, LPCSTR _szCmdLine,
						LPSTR _szOutput, const DWORD _wSize);

/* ###『統合アーカイバ API』共通の API です。### */
#if !defined(CHECKARCHIVE_RAPID)
#define	CHECKARCHIVE_RAPID		0	/* 簡易(最初の３ヘッダまで) */
#define	CHECKARCHIVE_BASIC		1	/* 標準(全てのヘッダ) */
#define	CHECKARCHIVE_FULLCRC	2	/* 完全(格納ファイルの CRC チェック) */

	/* 以下のフラグは上記と組み合わせて使用。*/
#define CHECKARCHIVE_RECOVERY	4   /* 破損ヘッダを読み飛ばして処理 */
#define CHECKARCHIVE_SFX		8	/* SFX かどうかを返す */
#define CHECKARCHIVE_ALL		16	/* ファイルの最後まで検索する */
#endif

BOOL WINAPI _export UnarjCheckArchive(LPCSTR _szFileName, const int _iMode);

int WINAPI _export UnarjGetFileCount(LPCSTR _szArcFile);

#if !defined(UNPACK_CONFIG_MODE)
#define	UNPACK_CONFIG_MODE		1	/* 解凍系の設定 */
#define PACK_CONFIG_MODE		2	/* 圧縮系の設定 */
#endif

BOOL WINAPI _export UnarjConfigDialog(const HWND _hwnd, LPSTR _lpszComBuffer,
						const int _iMode);

#if !defined(ISARC_FUNCTION_START)
#define ISARC_FUNCTION_START			0
#define ISARC							0	/* Unlha */
#define ISARC_GET_VERSION				1	/* UnlhaGetVersion */
#define ISARC_GET_CURSOR_INTERVAL		2	/* UnlhaGetCursorInterval */
#define ISARC_SET_CURSOR_INTERVAL		3	/* UnlhaSetCursorInterval */
#define ISARC_GET_BACK_GROUND_MODE		4	/* UnlhaGetBackGroundMode */
#define ISARC_SET_BACK_GROUND_MODE		5	/* UnlhaSetBackGroundMode */
#define ISARC_GET_CURSOR_MODE			6	/* UnlhaGetCursorMode */
#define ISARC_SET_CURSOR_MODE			7	/* UnlhaSetCursorMode */
#define ISARC_GET_RUNNING				8	/* UnlhaGetRunning */

#define ISARC_CHECK_ARCHIVE				16	/* UnlhaCheckArchive */
#define ISARC_CONFIG_DIALOG				17	/* UnlhaConfigDialog */
#define ISARC_GET_FILE_COUNT			18	/* UnlhaGetFileCount */
#define ISARC_QUERY_FUNCTION_LIST		19	/* UnlhaQueryFunctionList */
#define ISARC_HOUT						20	/* (UnlhaHOut) */
#define ISARC_STRUCTOUT					21	/* (UnlhaStructOut) */
#define ISARC_GET_ARC_FILE_INFO			22	/* UnlhaGetArcFileInfo */

#define ISARC_OPEN_ARCHIVE				23	/* UnlhaOpenArchive */
#define ISARC_CLOSE_ARCHIVE				24	/* UnlhaCloseArchive */
#define ISARC_FIND_FIRST				25	/* UnlhaFindFirst */
#define ISARC_FIND_NEXT					26	/* UnlhaFindNext */
#define ISARC_EXTRACT					27	/* (UnlhaExtract) */
#define ISARC_ADD						28	/* (UnlhaAdd) */
#define ISARC_MOVE						29	/* (UnlhaMove) */
#define ISARC_DELETE					30	/* (UnlhaDelete) */

#define ISARC_GET_ARC_FILE_NAME			40	/* UnlhaGetArcFileName */
#define ISARC_GET_ARC_FILE_SIZE			41	/* UnlhaGetArcFileSize */
#define ISARC_GET_ARC_ORIGINAL_SIZE		42	/* UnlhaArcOriginalSize */
#define ISARC_GET_ARC_COMPRESSED_SIZE	43	/* UnlhaGetArcCompressedSize */
#define ISARC_GET_ARC_RATIO				44	/* UnlhaGetArcRatio */
#define ISARC_GET_ARC_DATE				45	/* UnlhaGetArcDate */
#define ISARC_GET_ARC_TIME				46	/* UnlhaGetArcTime */
#define ISARC_GET_ARC_OS_TYPE			47	/* UnlhaGetArcOSType */
#define ISARC_GET_ARC_IS_SFX_FILE		48	/* UnlhaGetArcIsSFXFile */
#define ISARC_GET_FILE_NAME				57	/* UnlhaGetFileName */
#define ISARC_GET_ORIGINAL_SIZE			58	/* UnlhaGetOriginalSize */
#define ISARC_GET_COMPRESSED_SIZE		59	/* UnlhaGetCompressedSize */
#define ISARC_GET_RATIO					60	/* UnlhaGetRatio */
#define ISARC_GET_DATE					61	/* UnlhaGetDate */
#define ISARC_GET_TIME					62	/* UnlhaGetTime */
#define ISARC_GET_CRC					63	/* UnlhaGetCRC */
#define ISARC_GET_ATTRIBUTE				64	/* UnlhaGetAttribute */
#define ISARC_GET_OS_TYPE				65	/* UnlhaGetOSType */
#define ISARC_GET_METHOD				66	/* UnlhaGetMethod */
#define ISARC_GET_WRITE_TIME			67	/* UnlhaGetWriteTime */
#define ISARC_GET_CREATE_TIME			68	/* UnlhaGetCreateTime */
#define ISARC_GET_ACCESS_TIME			69	/* UnlhaGetAccessTime */

#define ISARC_FUNCTION_END				69
#endif	/* ISARC_FUNCTION_START */

BOOL WINAPI _export UnarjQueryFunctionList(const int _iFunction);

#ifndef WM_ARCEXTRACT
#define	WM_ARCEXTRACT	"wm_arcextract"

#define	ARCEXTRACT_BEGIN		0	/* 該当ファイルの処理の開始 */
#define	ARCEXTRACT_INPROCESS	1	/* 該当ファイルの展開中 */
#define	ARCEXTRACT_END			2	/* 処理終了、関連メモリを開放 */
#define ARCEXTRACT_OPEN			3	/* 該当書庫の処理の開始 */
#define ARCEXTRACT_COPY			4	/* ワークファイルの書き戻し */

WINAPI _export UnarjSetOwnerWindow(const HWND _hwnd);
BOOL WINAPI _export UnarjClearOwnerWindow(VOID);

typedef BOOL CALLBACK ARCHIVERPROC(HWND _hwnd, UINT _uMsg,
						UINT _nState, LPEXTRACTINGINFOEX _lpEis);
typedef ARCHIVERPROC *LPARCHIVERPROC;

BOOL WINAPI _export UnarjSetOwnerWindowEx(HWND _hwnd,
		LPARCHIVERPROC _lpArcProc);
BOOL WINAPI _export UnarjKillOwnerWindowEx(HWND _hwnd);
#endif

/* OpenArchive 系 API です。 */

#if !defined(EXTRACT_FOUND_FILE)
/* MODE (for UnarjOpenArchive) */
#define M_INIT_FILE_USE			0x00000001L	/* レジストリの設定を使用 */
#define M_REGARDLESS_INIT_FILE	0x00000002L	/* 〃 を使用しない */
#define M_NOT_USE_TIME_STAMP	0x00000008L
#define M_EXTRACT_REPLACE_FILE	0x00000010L
#define M_EXTRACT_NEW_FILE		0x00000020L
#define M_EXTRACT_UPDATE_FILE	0x00000040L
#define M_CHECK_ALL_PATH		0x00000100L	/* 厳格なファイル名サーチ */
#define M_CHECK_FILENAME_ONLY	0x00000200L	/* 〃を行わない */
#define M_CHECK_DISK_SIZE		0x00000400L
#define M_REGARDLESS_DISK_SIZE	0x00000800L
#define M_USE_DRIVE_LETTER		0x00001000L	/* ドライブ名から格納 */
#define M_NOT_USE_DRIVE_LETTER	0x00002000L	/* 〃 を格納しない */
#define M_INQUIRE_DIRECTORY		0x00004000L
#define M_NOT_INQUIRE_DIRECTORY 0x00008000L
#define M_INQUIRE_WRITE			0x00010000L
#define M_NOT_INQUIRE_WRITE		0x00020000L
#define M_CHECK_READONLY		0x00040000L
#define M_REGARDLESS_READONLY	0x00080000L
#define M_REGARD_E_COMMAND		0x00100000L
#define M_REGARD_X_COMMAND		0x00200000L
#define M_ERROR_MESSAGE_ON		0x00400000L	/* エラーメッセージを表示 */
#define M_ERROR_MESSAGE_OFF		0x00800000L	/* 〃を表示しない */
#define M_BAR_WINDOW_ON			0x01000000L
#define M_BAR_WINDOW_OFF		0x02000000L
#define M_CHECK_PATH			0x04000000L
#define M_RECOVERY_ON			0x08000000L /* 破損ヘッダの読み飛ばし */

#define M_MAKE_INDEX_FILE		0x10000000L
#define M_NOT_MAKE_INDEX_FILE	0x20000000L
#define EXTRACT_FOUND_FILE		0x40000000L	/* 検索されたファイルを解凍 */
#define EXTRACT_NAMED_FILE		0x80000000L	/* 指定したファイルを解凍 */
#endif /* EXTRACT_FOUND_FILE */

HARC WINAPI _export UnarjOpenArchive(const HWND _hwnd, LPCSTR _szFileName,
							const DWORD _dwMode);
int WINAPI _export UnarjCloseArchive(HARC _harc);
int WINAPI _export UnarjFindFirst(HARC _harc, LPCSTR _szWildName,
							INDIVIDUALINFO *_lpSubInfo);
int WINAPI _export UnarjFindNext(HARC _harc, INDIVIDUALINFO *_lpSubInfo);
int WINAPI _export UnarjGetArcFileName(HARC _harc, LPSTR _lpBuffer,
							const int _nSize);
DWORD WINAPI _export UnarjGetArcFileSize(HARC _harc);
DWORD WINAPI _export UnarjGetArcOriginalSize(HARC _harc);
DWORD WINAPI _export UnarjGetArcCompressedSize(HARC _harc);
WORD WINAPI _export UnarjGetArcRatio(HARC _harc);
WORD WINAPI _export UnarjGetArcDate(HARC _harc);
WORD WINAPI _export UnarjGetArcTime(HARC _harc);
UINT WINAPI _export UnarjGetArcOSType(HARC _harc);
int WINAPI _export UnarjIsSFXFile(HARC _harc);
int WINAPI _export UnarjGetFileName(HARC _harc, LPSTR _lpBuffer,
							const int _nSize);
int WINAPI _export UnarjGetMethod(HARC _harc, LPSTR _lpBuffer,
							const int _nSize);
DWORD WINAPI _export UnarjGetOriginalSize(HARC _harc);
DWORD WINAPI _export UnarjGetCompressedSize(HARC _harc);
WORD WINAPI _export UnarjGetRatio(HARC _harc);
WORD WINAPI _export UnarjGetDate(HARC _harc);
WORD WINAPI _export UnarjGetTime(HARC _harc);
DWORD WINAPI _export UnarjGetCRC(HARC _harc);
int WINAPI _export UnarjGetAttribute(HARC _harc);
UINT WINAPI _export UnarjGetOSType(HARC _harc);

#ifdef __cplusplus
}
#endif

#ifndef FA_RDONLY
/* Attribute */
#define FA_RDONLY       0x01            /* 書き込み保護属性 */
#define FA_HIDDEN       0x02            /* 隠し属性 */
#define FA_SYSTEM       0x04            /* システム属性 */
#define FA_LABEL        0x08            /* ボリューム・ラベル */
#define FA_DIREC        0x10            /* ディレクトリ */
#define FA_ARCH         0x20            /* アーカイブ属性 */
#endif

#if !defined(ERROR_START)
#define ERROR_START				0x8000
/* WARNING */
#define ERROR_DISK_SPACE		0x8005
#define ERROR_READ_ONLY			0x8006
#define ERROR_USER_SKIP			0x8007
#define ERROR_UNKNOWN_TYPE		0x8008
#define ERROR_METHOD			0x8009
#define ERROR_PASSWORD_FILE		0x800A
#define ERROR_VERSION			0x800B
#define ERROR_FILE_CRC			0x800C
#define ERROR_FILE_OPEN			0x800D
#define ERROR_MORE_FRESH		0x800E
#define ERROR_NOT_EXIST			0x800F
#define ERROR_ALREADY_EXIST		0x8010

#define ERROR_TOO_MANY_FILES	0x8011

/* ERROR */
#define ERROR_MAKEDIRECTORY		0x8012
#define ERROR_CANNOT_WRITE		0x8013
#define ERROR_HUFFMAN_CODE		0x8014
#define ERROR_COMMENT_HEADER	0x8015
#define ERROR_HEADER_CRC		0x8016
#define ERROR_HEADER_BROKEN		0x8017
#define ERROR_ARC_FILE_OPEN		0x8018
#define ERROR_NOT_ARC_FILE		0x8019
#define ERROR_CANNOT_READ		0x801A
#define ERROR_FILE_STYLE		0x801B
#define ERROR_COMMAND_NAME		0x801C
#define ERROR_MORE_HEAP_MEMORY	0x801D
#define ERROR_ENOUGH_MEMORY		0x801E
#if !defined(ERROR_ALREADY_RUNNING)
#define ERROR_ALREADY_RUNNING	0x801F
#endif
#define ERROR_USER_CANCEL		0x8020
#define ERROR_HARC_ISNOT_OPENED	0x8021
#define ERROR_NOT_SEARCH_MODE	0x8022
#define ERROR_NOT_SUPPORT		0x8023
#define ERROR_TIME_STAMP		0x8024
#define ERROR_TMP_OPEN			0x8025
#define ERROR_LONG_FILE_NAME	0x8026
#define ERROR_ARC_READ_ONLY		0x8027
#define ERROR_SAME_NAME_FILE	0x8028
#define ERROR_NOT_FIND_ARC_FILE 0x8029
#define ERROR_RESPONSE_READ		0x802A
#define ERROR_NOT_FILENAME		0x802B
#define ERROR_TMP_COPY			0x802C

#ifndef	ERROR_END	//takaso
//#define ERROR_END	ERROR_NOT_FILENAME
#define ERROR_END	ERROR_TMP_COPY
#endif
#endif /* ERROR_START */

/* ### UNARJ32.DLL 独自の API です。### */
WORD WINAPI _export UnarjGetSubVersion(VOID);

#endif	/* UNARJ32_H */
