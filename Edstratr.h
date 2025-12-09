/*    PortTool v2.2     edstratr.h          */

// edstratr.h : ヘッダー ファイル
//
#include "edstrlis.h"

/////////////////////////////////////////////////////////////////////////////
// CEdStrList ダイアログ

class CEdStrAttr : public CEdStrList
{
// コンストラクタ
public:
	CEdStrAttr(CWnd* pParent = NULL);	// 標準のコンストラクタ

	BOOL UpdateData(CStringArray2 *paryStr, CStringArray2 *paryAtr, int *piSel=NULL);
	BOOL UpdateData(CString *pcstr);
	BOOL RetrieveData(CStringArray2 *paryStr, CStringArray2 *paryAtr, int *piSel=NULL);

// ダイアログ データ
	//{{AFX_DATA(CEdStrList)
	enum { IDD = IDD_EDSTRLST };
	//}}AFX_DATA
	CStringArray2	m_aryAtr;	// アトリビュート配列
// インプリメンテーション
protected:
	// メッセージマップ関数の生成
	//{{AFX_MSG(CEdStrList)
	afx_msg void OnClickedEslNew();
	afx_msg void OnClickedEslChg();
	afx_msg void OnClickedEslUp();
	afx_msg void OnClickedEslDown();
	afx_msg void OnSelchangeEslList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
