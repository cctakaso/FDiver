/* UNLHA.H, Micco, Oct.24,1995
** LH 2.02a
** Copyright (c) 1988-90 by ãgçËâhë◊  All rights reserved.
** UNLHA.DLL
** Copyright (c) 1995    by Micco.    All rights reserved.
*/


#if !defined(Unlha_H)
#define Unlha_H

#define UNLHA_VERSION	45

#ifndef FNAME_MAX
#define FNAME_MAX           128
#endif

#ifdef NOTUSE
#pragma option -a-
#endif
#pragma pack(1)

#ifndef ARC_DECSTRACT
#define ARC_DECSTRACT
typedef	HGLOBAL	HARC;

typedef struct {
	char			szFileName[FNAME_MAX + 1];
	UINT			uFlag;
	DWORD 			dwOriginalSize;
	DWORD 			dwCompressedSize;
	WORD			wRatio;
	WORD			wDate;
	WORD 			wTime;
	DWORD			dwCRC;
	char			szAttribute[5];
	char			szMode[8];
	UINT			uOSType;
}	INDIVIDUALINFO;

typedef INDIVIDUALINFO FAR *LPINDIVIDUALINFO;

typedef struct {
	char			szSourceFileName[FNAME_MAX + 1];
	char			szDestFileName[FNAME_MAX + 1];
	DWORD 			dwFileSize;
	DWORD			dwWriteSize;
}	EXTRACTINGINFO;

#endif

typedef struct {
	UINT			uTotalFiles;
	UINT			uCountInfoFiles;
	UINT			uErrorCount;
	LONG			lDiskSpace;
	HGLOBAL			hSubInfo;
}	LHALOCALINFO;

#pragma pack()
#ifdef NOTUSE
#pragma option -a.
#endif

#ifdef __cplusplus
extern "C" {
#endif

BOOL WINAPI _export UnlhaCheckArchive(LPCSTR _szFileName,
				const int _iMode);

int WINAPI _export Unlha(LPCSTR szCmdLine, LPSTR szOutput,
				const WORD wSize);
WORD WINAPI _export UnlhaGetVersion(VOID);
BOOL WINAPI _export UnlhaGetRunning(VOID);
BOOL WINAPI _export UnlhaGetBackGroundMode(VOID);
BOOL WINAPI _export UnlhaSetBackGroundMode(const BOOL BackGroundMode);
BOOL WINAPI _export UnlhaGetCursorMode(VOID);
BOOL WINAPI _export UnlhaSetCursorMode(const BOOL CursorMode);
WORD WINAPI _export UnlhaGetCursorInterval(VOID);
BOOL WINAPI _export UnlhaSetCursorInterval(const WORD Interval);
BOOL WINAPI _export UnlhaConfigDialog(const HWND _hwnd,
				LPSTR _lpszComBuffer, const int _iMode);
int WINAPI _export UnlhaGetFileCount(LPCSTR _szArcFile);
BOOL WINAPI _export UnlhaQueryFunctionList(const int _iFunction);

HARC WINAPI _export UnlhaOpenArchive(const HWND _hwnd,
				LPCSTR _szFileName, const DWORD _dwMode);
int WINAPI _export UnlhaCloseArchive(HARC _harc);
int WINAPI _export UnlhaFindFirst(HARC _harc, LPCSTR _szWildName,
				INDIVIDUALINFO FAR *_lpSubInfo);
int WINAPI _export UnlhaFindNext(HARC _harc,
				INDIVIDUALINFO FAR *_lpSubInfo);
int WINAPI _export UnlhaGetArcFileName(HARC _harc, LPSTR _lpBuffer,
				const int _nSize);
DWORD WINAPI _export UnlhaGetArcFileSize(HARC _harc);
DWORD WINAPI _export UnlhaGetArcOriginalSize(HARC _harc);
DWORD WINAPI _export UnlhaGetArcCompressedSize(HARC _harc);
WORD WINAPI _export UnlhaGetArcRatio(HARC _harc);
WORD WINAPI _export UnlhaGetArcDate(HARC _harc);
WORD WINAPI _export UnlhaGetArcTime(HARC _harc);
UINT WINAPI _export UnlhaGetArcOSType(HARC _harc);
int WINAPI _export UnlhaGetFileName(HARC _harc, LPSTR _lpBuffer,
				const int _nSize);
DWORD WINAPI _export UnlhaGetOriginalSize(HARC _harc);
DWORD WINAPI _export UnlhaGetCompressedSize(HARC _harc);
int WINAPI _export UnlhaGetMethod(HARC _harc, LPSTR _lpBuffer,
				const int _nSize);
WORD WINAPI _export UnlhaGetRatio(HARC _harc);
WORD WINAPI _export UnlhaGetDate(HARC _harc);
WORD WINAPI _export UnlhaGetTime(HARC _harc);
DWORD WINAPI _export UnlhaGetCRC(HARC _harc);
int WINAPI _export UnlhaGetAttribute(HARC _harc);
UINT WINAPI _export UnlhaGetOSType(HARC _harc);
BOOL WINAPI _export UnlhaSetOwnerWindow(HWND _hwnd);
BOOL WINAPI _export UnlhaClearOwnerWindow(VOID);

#ifdef __cplusplus
}
#endif

#define	UNPACK_CONFIG_MODE		1
#define PACK_CONFIG_MODE		2

#define	CHECKARCHIVE_RAPID		0
#define	CHECKARCHIVE_BASIC		1
#define	CHECKARCHIVE_FULLCRC	2

#if !defined(EXTRACT_FOUND_FILE)
/* MODE (for UnarjOpenArchive) */
#define M_INIT_FILE_USE			0x00000001L
#define M_REGARDLESS_INIT_FILE	0x00000002L
#define M_CHECK_ALL_PATH		0x00000100L
#define M_CHECK_FILENAME_ONLY	0x00000200L
#define M_USE_DRIVE_LETTER		0x00001000L
#define M_NOT_USE_DRIVE_LETTER	0x00002000L
#define M_ERROR_MESSAGE_ON		0x00400000L
#define M_ERROR_MESSAGE_OFF		0x00800000L

#define EXTRACT_FOUND_FILE		0x40000000L
#define EXTRACT_NAMED_FILE		0x80000000L
#endif /* EXTRACT_FOUND_FILE */

#if !defined(ISARC_FUNCTION_START)
#define ISARC_FUNCTION_START			0
#define ISARC							0
#define ISARC_GET_VERSION				1
#define ISARC_GET_CURSOR_INTERVAL		2
#define ISARC_SET_CURSOR_INTERVAL		3
#define ISARC_GET_BACK_GROUND_MODE		4
#define ISARC_SET_BACK_GROUND_MODE		5
#define ISARC_GET_CURSOR_MODE			6
#define ISARC_SET_CURSOR_MODE			7
#define ISARC_GET_RUNNING				8

#define ISARC_CHECK_ARCHIVE				16
#define ISARC_CONFIG_DIALOG				17
#define ISARC_GET_FILE_COUNT			18
#define ISARC_QUERY_FUNCTION_LIST		19
#define ISARC_HOUT						20
#define ISARC_STRUCTOUT					21
#define ISARC_GET_ARC_FILE_INFO			22

#define ISARC_OPEN_ARCHIVE				23
#define ISARC_CLOSE_ARCHIVE				24
#define ISARC_FIND_FIRST				25
#define ISARC_FIND_NEXT					26
#define ISARC_EXTRACT					27
#define ISARC_ADD						28
#define ISARC_MOVE						29
#define ISARC_DELETE					30

#define ISARC_GET_ARC_FILE_NAME			40
#define ISARC_GET_ARC_FILE_SIZE			41
#define ISARC_GET_ARC_ORIGINAL_SIZE		42
#define ISARC_GET_ARC_COMPRESSED_SIZE	43
#define ISARC_GET_ARC_RATIO				44
#define ISARC_GET_ARC_DATE				45
#define ISARC_GET_ARC_TIME				46
#define ISARC_GET_ARC_OS_TYPE			47
#define ISARC_GET_ARC_IS_SFX_FILE		48
#define ISARC_GET_FILE_NAME				57
#define ISARC_GET_ORIGINAL_SIZE			58
#define ISARC_GET_COMPRESSED_SIZE		59
#define ISARC_GET_RATIO					60
#define ISARC_GET_DATE					61
#define ISARC_GET_TIME					62
#define ISARC_GET_CRC					63
#define ISARC_GET_ATTRIBUTE				64
#define ISARC_GET_OS_TYPE				65
#define ISARC_GET_METHOD				66

#define ISARC_FUNCTION_END				66
#endif	/* ISARC_FUNCTION_START */

#ifndef FA_RDONLY
/* Attribute */
#define FA_RDONLY       0x01            /* Read only attribute */
#define FA_HIDDEN       0x02            /* Hidden file */
#define FA_SYSTEM       0x04            /* System file */
#define FA_LABEL        0x08            /* Volume label */
#define FA_DIREC        0x10            /* Directory */
#define FA_ARCH         0x20            /* Archive */
#endif

#ifndef ERROR_ARC_FILE_OPEN
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
#define ERROR_DIRECTORY			0x8012
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
#endif /* ERROR_ARC_FILE_OPEN */

#endif	/* Unlha_H */
