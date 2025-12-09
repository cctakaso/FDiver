/*    PortTool v2.2     strspecd.h          */

// strspecd.h : ヘッダー ファイル
//
#ifndef __STRSPECD_H_
#define __STRSPECD_H_

#include "resource.h"
#include "..\mdfc\parentdl.h"
#include "strspec.h"
#include "edstratr.h"

#define	ER_OK		0		// 正常
#define	ER_MEMORY	1		// ﾒﾓﾘ確保に失敗しました。

#define SUBDLGS_NUM	2		// サブダイアログの数
#define FST_IDD_OF_SUBDLGS	IDD_STRSPEC_JPN	// 最初のサブダイアログＩＤＤ
	// 注意！それ以外のサブダイアログのIDDは、順にインクリメントされていなければならない。
// サブキャプション

/////////////////////////////////////////////////////////////////////////////
// CStrSpecDlg ダイアログ

class CStrSpecDlg : public CParentDlg
{
// コンストラクタ
public:
	CStrSpecDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CStrSpecDlg();


// ダイアログ データ
	//{{AFX_DATA(CStrSpecDlg)
	enum { IDD = IDD_STRSPEC };
		// 注意: ClassWizard はこの位置にデータメンバを追加します。
	//}}AFX_DATA

	// イニシャル関数
	void Initialize(CStrSpec *pStrSpec);

	void Selchange();
// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	CStrSpec *m_pStrSpecOrg;	// ﾌｧｲﾝﾄﾞｵﾌﾟｼｮﾝｵﾘｼﾞﾅﾙへのﾎﾟｲﾝﾀ
	CStrSpec *m_pStrSpec;		// ﾌｧｲﾝﾄﾞｵﾌﾟｼｮﾝ実体へのﾎﾟｲﾝﾀ
	// エディタブル・ストリング・リスト子ウィンドウ
	CEdStrAttr *m_pSubDlg2;

	virtual BOOL UpdateData(BOOL bSaveAndValidate=TRUE); 
	BOOL m_fChangeBefore;
	
	virtual BOOL SelchangeTab(int nSel);
	virtual int DrawCaption(CDC* pDC, int idTab, CRect rect);



	// メッセージマップ関数の生成
	//{{AFX_MSG(CStrSpecDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg LONG OnSelchangeEslList(UINT, LONG);
//	afx_msg void OnMetaChars();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //STRSPECD
