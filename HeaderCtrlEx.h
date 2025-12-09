// HeaderCtrlEx.h : ヘッダー ファイル
//
#ifndef __HEADERCTRLEX_H__
#define __HEADERCTRLEX_H__
/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx ウィンドウ
#define HEADERITEM_NUM	(6)
typedef struct {
	int cx;
	int	align;
	}stCXALIGN;
#define DCX_MUGEN	(5000)

class CHeaderCtrlEx : public CHeaderCtrl
{
// コンストラクション
public:
	CHeaderCtrlEx();

// アトリビュート
public:
	enum {
		left,
		center,
		right
		};
	int		m_cxs[HEADERITEM_NUM];
protected:
	CFont m_font;
	CFont *m_pfontOld;
	CBitmap	m_bmpTree;
	CBitmap	m_bmpLine;
	CBitmap	m_bmpPath;
	CBitmap	m_bmpFile;
	CBitmap	m_bmpDown;
	
	BOOL	m_fDir;
	BOOL	m_fFile;
	int		m_et;

// オペレーション
public:
	void ResetHeaderType(int et=-1, bool bForceChange=false);
	int GetCxs(int et, stCXALIGN *pInt);
// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CHeaderCtrlEx)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CHeaderCtrlEx();

	// 生成されたメッセージ マップ関数
protected:
	int SetCxs();
	void InsertItem(int cx, const CString &str);
	void RemoveItems(int nUppder=0);
	//{{AFX_MSG(CHeaderCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif //__HEADERCTRLEX_H__