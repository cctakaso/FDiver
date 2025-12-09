/*    PortTool v2.2     findopti.h          */

// findopti.h : ヘッダー ファイル
#ifndef __FINDOPTI_H_
#define __FINDOPTI_H_

#include "time.h"
#include "strary2.h"
#include "metachar.h"
#include "..\mdfc\dfile.h"



/////////////////////////////////////////////////////////////////////////////
// CFindOption ダイアログ
class CFindOption
{
// コンストラクタ
public:
	CFindOption();	// 標準のコンストラクタ
	~CFindOption() {};
		//ReadWriteProfile(FALSE); }

// ダイアログ データ
	BOOL	m_fSound;
	BOOL	m_fToTopWin;
	BOOL	m_fIcon;
	BOOL	m_fMetaHelp;
	BOOL	m_fNoErrDsp;
	long	m_lReadSize;
	CStringArray2	m_aryStrFiles;	// ファイル種別ｴﾝﾄﾘｰ
	CStringArray2	m_aryStrExtnsions;	// 起動プログラムパラメータｴﾝﾄﾘｰ
	CStringArray2	m_aryStrKickApps;	//起動ｱﾌﾟﾘｹｰｼｮﾝ群
	CString	m_strEditer;	//エディタパス
	BOOL	m_bCRIsNewLine;

	BOOL	m_bKftTransFileView;	//漢字ｺｰﾄﾞ変換ｵﾘｼﾞﾅﾙﾌｧｲﾙを開くか否か
	BOOL	m_fDir;
	BOOL	m_fFile;
	CString	m_strLineHeader;
	CString	m_strNameHeader;
	CString	m_strSizeHeader;
	CString	m_strDateHeader;
	CString	m_strAttrHeader;
	CString	m_strPathHeader;
	CString	m_strTextHeader;
	int		m_cxDown;
	int		m_cxTreePath;
	int		m_cxTreeFile;
	int		m_cxTreeLine;
	int		m_cxListLine;
	int		m_cxPathPath;
	int		m_cxPathLine;
	int		m_cxFileFile;
	int		m_cxFileLine;
	int		m_cxName;
	int		m_cxSize;
	int		m_cxDate;
	int		m_cxAttr;
	int		m_cxPath;
	int		m_cxLine;

	int		m_lfHeight;
	int		m_lfCharSet;
	int		m_lfPitchAndFamily;
	CString	m_lfFaceName;
	CString m_strBkColor;
	CString m_strFrColor;

	int		m_optDispNum;
	BOOL	m_fDispDoc;
	int		m_iDspListColum;	// 検索結果ﾘｽﾄ表示桁数
	int		m_iMaxLines;
	BOOL	m_fDragServer;
	BOOL	m_fDefTagAuto;

	BOOL	m_fTopMost;			// 最上位ウィンドウ位置を保持する
	int		m_left;				// ウィンドウleft
	int		m_top;				// ウィンドウtop
	int		m_width;			// ウィンドウ幅
	int		m_hight;			// ウィンドウ高さ
	BOOL	m_bToolBar;			// Show Tool bar 
	BOOL	m_bHeaderBar;		// Show Header bar 
	BOOL	m_bStatusBar;		// Show Status bar 

	BOOL	m_fFTLha;
	BOOL	m_fFTZip;
	BOOL	m_fFTArj;
	BOOL	m_fFTTar;
	BOOL	m_fFTCab;
	BOOL	m_fFTRar;
	//EntryPoint Arc
	BOOL	m_fFTKft;
	BOOL	m_fFTxdoc;
	int		m_optFTRemain;
	CString	m_strFTWorkPath;

	CMetaChars m_metaChars;

	int m_ratioBetweenLine;

	void ReadWriteProfile(BOOL fRead);

	CString GetExeParam(char *szProg);	// 指定プログラムの起動パラメータを得る

	BOOL GetCheckExtType(EXT_TYPE ext);

	void ResizeHeaderCx(int iZoom);
	int div10plus(int cxy, int iZoom, int default_cxy);

};

#endif //FINDOPTI
