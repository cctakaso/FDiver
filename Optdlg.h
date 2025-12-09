/*    PortTool v2.2     optdlg.h          */

// optdlg.h : ヘッダー ファイル
//

#ifndef __OPTDLG_H_
#define __OPTDLG_H_

#include "resource.h"
#include "..\mdfc\parentdl.h"
#include "findopti.h"

#define	ER_OK		0		// 正常
#define	ER_MEMORY	1		// ﾒﾓﾘ確保に失敗しました。

#ifdef WIN32
#define SUBDLGS_NUM	5		// サブダイアログの数
#else
#define SUBDLGS_NUM	4		// サブダイアログの数
#endif //WIN32
#define FST_IDD_OF_SUBDLGS	IDD_FINDOPTION	// 最初のサブダイアログＩＤＤ
#define FST_IDS_OF_SUBDLGS  IDS_DIBING
	// 注意！それ以外のサブダイアログのIDDは、順にインクリメントされていなければならない。
// サブキャプション


/////////////////////////////////////////////////////////////////////////////
// COptionDlg ダイアログ
class COptionDlg : public CParentDlg
{
public:
// コンストラクタ
	COptionDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~COptionDlg();						// Destructer


	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_OPTIONS };
	//}}AFX_DATA

	// イニシャル関数
	void Initialize(CFindOption *pFindOption);


	// ここでは使わない。
	// 現在のアクティブなダイアログへのポインタ（タグから呼び出されたダイアログ）.
	//UINT m_uIDDeepDlg;					// ID of currently active CDialog object
	//CDialog *m_pDeepDlg;				// Pointer to currently active CDialog object (as SETINP2, SETKAN, SETHKANA etc)

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(COptionDlg)
	public:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL


// インプリメンテーション
protected:
	CFindOption *m_pFindOptionOrg;	// ﾌｧｲﾝﾄﾞｵﾌﾟｼｮﾝｵﾘｼﾞﾅﾙへのﾎﾟｲﾝﾀ
	CFindOption *m_pFindOption;		// ﾌｧｲﾝﾄﾞｵﾌﾟｼｮﾝ実体へのﾎﾟｲﾝﾀ
	virtual BOOL UpdateData(BOOL bSaveAndValidate=TRUE); 
	
	virtual BOOL SelchangeTab(int nSel);
	virtual int DrawCaption(CDC* pDC, int idTab, CRect rect);


	// メッセージマップ関数の生成
	//{{AFX_MSG(COptionDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	// ｽﾋﾟﾝｺﾝﾄﾛｰﾙDLLﾗｲﾌﾞﾗﾘ
	//HINSTANCE m_hLibrary;

};
#endif // __OPTDLG_H_
