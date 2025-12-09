/*    PortTool v2.2     metainp.h          */

// metainp.h : ヘッダー ファイル
//

#ifndef __METAINP_H_
#define __METAINP_H_

#include "resource.h"
#include "..\mdfc\parentdl.h"
#include "metastr.h"
#include "metainp1.h"
#include "metainp2.h"

#define	ER_OK		0		// 正常
#define	ER_MEMORY	1		// ﾒﾓﾘ確保に失敗しました。

#define SUBDLGS_NUM	2		// サブダイアログの数
#undef FST_IDD_OF_SUBDLGS
#define FST_IDD_OF_SUBDLGS	IDD_META_INPUT1	// 最初のサブダイアログＩＤＤ
	// 注意！それ以外のサブダイアログのIDDは、順にインクリメントされていなければならない。
// サブキャプション


/////////////////////////////////////////////////////////////////////////////
// CMetaInputDlg ダイアログ
class CMetaInputDlg : public CParentDlg
{
public:
// コンストラクタ
	CMetaInputDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CMetaInputDlg();						// Destructer


	//{{AFX_DATA(CMetaInputDlg)
	enum { IDD = IDD_META_INPUT };
	//}}AFX_DATA

	// イニシャル関数
	void Initialize(CString *pcstrOrg, CMetaStringArray *pMetaStringArray, BOOL fKeyEntryOnly=FALSE);


	BOOL m_fKeyEntryOnly;		//keyword entry only
	// ここでは使わない。
	// 現在のアクティブなダイアログへのポインタ（タグから呼び出されたダイアログ）.
	//UINT m_uIDDeepDlg;					// ID of currently active CDialog object
	//CDialog *m_pDeepDlg;				// Pointer to currently active CDialog object (as SETINP2, SETKAN, SETHKANA etc)

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CMetaInputDlg)
	public:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CString *m_pcstrOrg;			// ｷｰﾜｰﾄﾞ･ｵﾘｼﾞﾅﾙへのﾎﾟｲﾝﾀ
	CString *m_pcstr;					// ｷｰﾜｰﾄﾞ･ﾃﾝﾎﾟﾗﾘ
	CMetaStringArray *m_pMetaStringArrayOrg;		// ﾒﾀｽﾄﾘﾝｸﾞ･ｵﾘｼﾞﾅﾙへのﾎﾟｲﾝﾀ
	CMetaStringArray *m_pMetaStringArray;		// ﾒﾀｽﾄﾘﾝｸﾞ･ﾃﾝﾎﾟﾗﾘ
	virtual BOOL UpdateData(BOOL bSaveAndValidate=TRUE); 
	
	virtual BOOL SelchangeTab(int nSel);
	virtual int DrawCaption(CDC* pDC, int idTab, CRect rect);


	// メッセージマップ関数の生成
	//{{AFX_MSG(CMetaInputDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	// ｽﾋﾟﾝｺﾝﾄﾛｰﾙDLLﾗｲﾌﾞﾗﾘ
	//HINSTANCE m_hLibrary;

};
#endif // __METAINP_H_
