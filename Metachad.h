/*    PortTool v2.2     metachad.h          */

// metachar.h : ヘッダー ファイル
//

#ifndef __METACHARD_H_
#define __METACHARD_H_

#include "findopti.h"
#include "resource.h"
#include "..\mdfc\childdlg.h"
/////////////////////////////////////////////////////////////////////////////
// CMetaCharsDlg ダイアログ

class CMetaCharsDlg : public CChildDlg
{
// コンストラクタ
public:
	CMetaCharsDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

	//void Initialize(STRSPEC_METACHARS *pMetaCharsData);

// ダイアログ データ
	//{{AFX_DATA(CMetaCharsDlg)
	enum { IDD = IDD_META_CHARS };
//	CString	m_strAnd;
//	CString	m_strBlockLeft;
//	CString	m_strBlockRight;
//	CString	m_strMatchAny;
//	CString	m_strMatchStr;
//	CString	m_strNot;
//	CString	m_strOr;
//	CString	m_strPrefix;
//	CString	m_strXor;
	STRSPEC_METACHARS m_metaCharsData;
	//}}AFX_DATA

	// ダイアログ情報から、データに反映させます。
	BOOL RetrieveData(CFindOption *pFindOption);

	// データから、ダイアログ情報に反映させます。
	BOOL UpdateData(CFindOption *pFindOption);

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	STRSPEC_METACHARS *m_pmetaCharsOrg;
	// メッセージマップ関数の生成
	//{{AFX_MSG(CMetaCharsDlg)
	virtual BOOL OnInitDialog();
//	afx_msg void OnSetfocusMeta();
	//virtual void OnOK();
	afx_msg void OnClickedMetaStndard();
	afx_msg void OnClickedMetaBasic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // !__METACHARD_H_
