/*    PortTool v2.2     edstrlis.h          */

// edstrlis.h : ƒwƒbƒ_[ ƒtƒ@ƒCƒ‹
#ifndef __EDSTRLIS_H_
#define __EDSTRLIS_H_

#include "resource.h"
#include "childdlg.h"
#include "strary2.h"

/////////////////////////////////////////////////////////////////////////////
// CEdStrList ƒ_ƒCƒAƒƒO

class CEdStrList : public CChildDlg
{
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
public:
	CEdStrList(CWnd* pParent = NULL);	// •W€‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^

	void Initialize(char *szTitle, BOOL fDontDelLastOne=FALSE);
	BOOL UpdateData(CStringArray2 *paryStr, int *piSel=NULL);
	BOOL RetrieveData(CStringArray2 *paryStr, int *piSel=NULL);

// ƒ_ƒCƒAƒƒO ƒf[ƒ^
	//{{AFX_DATA(CEdStrList)
	enum { IDD = IDD_EDSTRLST };
	CComboBox	m_combStr;
	CButton	m_btnDown;
	CButton	m_btnUp;
	CButton	m_btnChg;
	int		m_iSel;
	//}}AFX_DATA
	CStringArray2	m_aryStr;	// •¶š—ñ”z—ñ
	BOOL m_fDontDelLastOne;		// ÅIƒGƒ“ƒgƒŠ[íœ‹Ö~ƒtƒ‰ƒO

// ƒCƒ“ƒvƒŠƒƒ“ƒe[ƒVƒ‡ƒ“
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ƒTƒ|[ƒg

	// ƒƒbƒZ[ƒWƒ}ƒbƒvŠÖ”‚Ì¶¬
	//{{AFX_MSG(CEdStrList)
	afx_msg void OnClickedEslNew();
	afx_msg void OnClickedEslChg();
	afx_msg void OnClickedEslUp();
	afx_msg void OnClickedEslDown();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEslList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //!__EDSTRLIS__H_