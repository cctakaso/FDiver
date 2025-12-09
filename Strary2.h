/*    PortTool v2.2     strary2.h          */

// strary2.h : ヘッダー ファイル
#ifndef __STRARY2_H_
#define __STRARY2_H_
/////////////////////////////////////////////////////////////////////////////
// CStringArray2 ダイアログ
class CStringArray2 : public CStringArray
{
public:
	CStringArray2() {};
	~CStringArray2() {};
	const CStringArray2& operator = ( CStringArray2 &src ) ;
};
#endif //__STRARY2_H_
