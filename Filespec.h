/*    PortTool v2.2     filespec.h          */

// filespec.h : ヘッダー ファイル
//
#ifndef __FILESPEC_H_
#define __FILESPEC_H_

#include "resource.h"

enum EXTX_TYPE
{
	EXTX_NO=-1,
	EXTX_MIN=0,
	//microsoft
	EXTX_DOC=0,
	EXTX_DOCX,
	EXTX_XLS,
	EXTX_XLSX,
	EXTX_PPT,
	EXTX_PPTX,
	EXTX_WRI,
	//ジャストシステム
	EXTX_JAW,
	EXTX_JBW,
	EXTX_JFW,
	EXTX_JTD,
	//internet
	EXTX_PDF,
	EXTX_HTML,
	EXTX_EML,
	//OpenOffice
	EXTX_SXW,
	EXTX_SXC,
	EXTX_SXI,
	EXTX_SXD,
	//Open Document
	EXTX_ODT,
	EXTX_ODS,
	EXTX_ODP,
	EXTX_ODG,
	//Others
	EXTX_OAS,
	EXTX_BUN,
	EXTX_123,
	EXTX_RTF,

	EXTX_MAX
};

/////////////////////////////////////////////////////////////////////////////
// CFileSpecDlg ダイアログ

class CFileSpecDlg : public CDialog
{
// コンストラクタ
public:
	CFileSpecDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CFileSpecDlg() {
		ReadWriteProfile(FALSE); }

	void EnableTimeCtr(BOOL f);
//	BOOL FMatchAttr(BYTE b);
	// ﾊﾟﾗﾒｰﾀのｱﾄﾘﾋﾞｭｰﾄがｵﾌﾟｼｮﾝの内容に合致しているか
/*
#ifdef WIN32
	BOOL FMatchTimeAndAttr(FILETIME fileTime, DWORD b, char *sz) {
		return FMatchTime(fileTime) && FMatchAttr(b, sz); }
	BOOL FMatchTime(FILETIME fileTime);
	BOOL FMatchAttr(DWORD b, char *sz);
#else
	BOOL FMatchTimeAndAttr(unsigned short Date, unsigned short Time, BYTE b, char *sz) {
		return FMatchTime(Date, Time) && FMatchAttr(b, sz); }
	BOOL FMatchTime(unsigned short Date, unsigned short Time);
	BOOL FMatchAttr(BYTE b, char *sz);
#endif //WIN32
*/
	int GetIAttr();
	time_t GetFromTime();
	time_t GetGoTime();
	EXTX_TYPE CFileSpecDlg::ExtxFromSzExt(char *szExt);
// ダイアログ データ
	//{{AFX_DATA(CFileSpecDlg)
	enum { IDD = IDD_FILESPEC };
		// 注意: ClassWizard はこの位置にデータメンバを追加します。
	//}}AFX_DATA

	void ReadWriteProfile(BOOL fRead);

	int m_optTime;
	time_t m_tFromTime;
	time_t m_tGoTime;

//	BOOL	m_fAtr;
	//{{AFX_DATA(CFindDlg)
	BOOL	m_fHideFile;
	BOOL	m_fOtherFile;
	BOOL	m_fProgFile;
	BOOL	m_fDocFile;
	BOOL	m_fSysFile;

	//microsoft
	BOOL	m_fdoc;
	BOOL	m_fdocx;
	BOOL	m_fxls;
	BOOL	m_fxlsx;
	BOOL	m_fppt;
	BOOL	m_fpptx;
	BOOL	m_fwri;

	//ジャストシステム
	BOOL	m_fjaw;
	BOOL	m_fjbw;
	BOOL	m_fjfw;
	BOOL	m_fjtd;

	//internet
	BOOL	m_fpdf;
	BOOL	m_fhtml;
	BOOL	m_feml;

	//OpenOffice
	BOOL	m_fsxw;
	BOOL	m_fsxc;
	BOOL	m_fsxi;
	BOOL	m_fsxd;

	//Open Document
	BOOL	m_fodt;
	BOOL	m_fods;
	BOOL	m_fodp;
	BOOL	m_fodg;

	//Others
	BOOL	m_foas;
	BOOL	m_fbun;
	BOOL	m_f123;
	BOOL	m_frtf;


	CEdit	m_ceFromDay;
	CEdit	m_ceFromHour;
	CEdit	m_ceGoDay;
	CEdit	m_ceGoHour;
	CString	m_cstrFromDay;
	CString	m_cstrFromHour;
	CString	m_cstrGoDay;
	CString	m_cstrGoHour;
//	BOOL	m_fAtrRead;
//	BOOL	m_fAtrArchive;
//	BOOL	m_fAtrHiden;
//	BOOL	m_fAtrSystem;
//	BOOL	m_fAtrOther;
	//}}AFX_DATA

// インプリメンテーション

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	// for backup!
	void operator = ( CFileSpecDlg *pFileSpecDlg ) ;
	CFileSpecDlg *m_pFileSpecDlg;

	// メッセージマップ関数の生成
	//{{AFX_MSG(CFileSpecDlg)
	afx_msg void OnClickedOfNotime();
	afx_msg void OnClickedOfToday();
	afx_msg void OnClickedOfYesterday();
	afx_msg void OnClickedOfThisweek();
	afx_msg void OnClickedOfSetday();
	afx_msg void OnChangeTimeCtr();
	afx_msg void OnClickedFAtr();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //! __FILESPEC_H_
