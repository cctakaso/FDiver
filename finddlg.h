/*    PortTool v2.2     finddlg.h          */

// finddlg.h : ヘッダー ファイル
//
#include "..\mdfc\dfile.h"
#include "filespec.h"
#include "strspecd.h"
#define METASTRING

/////////////////////////////////////////////////////////////////////////////
// CFindDlg ダイアログ
#define WFD_COMBOENTRY	21	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列/ﾌｧｲﾙｽﾍﾟｯｸ配列数
class CFindDlg : public CDialog
{
	friend class CMainFrame;
// コンストラクタ
public:
	DECLARE_SERIAL(CFindDlg)

	CFindDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	//CFindDlg();	// ﾃﾞﾌｫﾙﾄコンストラクタ
	~CFindDlg();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o

	CFileSpecDlg m_fileSpecDlg;
	//CStrSpecDlg m_strSpecDlg;
// インプリメンテーション
	// 検索３要素の取得
	char *GetStrBuffer(){
		return m_cStr.GetBuffer(0); }
	CDFileSpec *GetFileSpec(){
		return &m_cFileSpec; }
	CDFile *GetFilePath(){
		return &m_cFilePath; }

	BOOL FSubDir(){
		return m_fSubDir; }
	BOOL FArc() {
		return m_fArc; }
	void ReadWriteProfile(BOOL fRead);
	BOOL FFindFileOnly() {
		return m_fFindFileOnly;
		}
	void SetStrFile(char *szFiles, BOOL fAdd=FALSE) {
		if (fAdd)
			{
			m_cStrFile += chSemi;
			m_cStrFile += szFiles;
			}
		else
			m_cStrFile = szFiles;
		}
	void AddFindPathSpec(char *sz, BOOL bAppend=FALSE);

// public data
	CStrSpec m_strSpec;
	CDFileSpec	m_cFileSpec;	// 検索ﾌｧｲﾙｽﾍﾟｯｸ
	CDFile		m_cFilePath;	// 検索パス
	int  m_optDispNum;		// 検索処理に位置処理を付加する＝行を意識して検索（固定）
	BOOL	m_fDispDoc;
	BOOL m_fOnDropBtn2;			// ﾄﾞﾛｯﾌﾟﾎﾞﾀﾝ2
	BOOL	m_fMetaChars;		// 正規表現ありなしフラグ
protected:
// ダイアログ データ
	//{{AFX_DATA(CFindDlg)
	enum { IDD = IDD_FIND };
	CComboBox	m_combStrSpec;
	CComboBox	m_comboPath;
	CComboBox	m_comboFile;
	CComboBox	m_comboStr;
	CString	m_cStr;			// 検索文字列
	CString	m_cStrFile;		// 検索ﾌｧｲﾙ
	CString	m_cStrPath;		// 検索パス
	BOOL	m_fSubDir;		// ｻﾌﾞﾃﾞｨﾚｸﾄﾘも検索するか
	int		m_iSelForStrSpec;
	BOOL	m_fArc;
	//}}AFX_DATA

	BOOL m_fFindFileOnly;	// ﾌｧｲﾙ名のみ検索か？

	CString	*m_pcStrComboStr[WFD_COMBOENTRY];	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
	CString	*m_pcStrComboFile[WFD_COMBOENTRY];	// ｺﾝﾎﾞﾎﾞｯｸｽﾌｧｲﾙｽﾍﾟｯｸ配列
	CString	*m_pcStrComboPath[WFD_COMBOENTRY];	// ｺﾝﾎﾞﾎﾞｯｸｽﾌｧｲﾙｽﾍﾟｯｸ配列

protected:
	// 検索を実行する
	BOOL FGoFind();
	// 検索する条件は整っているか
	BOOL FValidFindSpec();
	void AddFindSpecs();
	void AddFindStrSpec(char *sz);
	void AddFindFileSpec(char *sz);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	BOOL FIsMetaChars(CString &str);


	// メッセージマップ関数の生成
	//{{AFX_MSG(CFindDlg)
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedFSetpath();
	afx_msg void OnClickedFOption();
	afx_msg void OnClickedFPast();
	afx_msg void OnDropdownFFile();
	afx_msg void OnClickedFDrop();
	afx_msg void OnClickedFSetfilespec();
	afx_msg void OnClickedFSetstrspec();
	afx_msg void OnDestroy();
	afx_msg void OnClickedFMetaInput();
	afx_msg void OnDropdownFString();
	afx_msg void OnFSetmethodspec();
	afx_msg void OnSelendokFString();
	afx_msg void OnEditupdateFString();
	afx_msg void OnFSetpathFolder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
