/*    PortTool v2.2     metastr.h          */

// metastr.h : ヘッダー ファイル
#ifndef __METASTR_H_
#define __METASTR_H_

#include "strary2.h"
/////////////////////////////////////////////////////////////////////////////
// CMetaString
class CMetaString
{
// コンストラクタ
public:
	CMetaString() {};	// 標準のコンストラクタ
	~CMetaString() {}

	CString GetStrForLst();
	CString GetStrForTitle();

	CString m_strTitle;
	CString m_strKey;
	const CMetaString& operator = ( CMetaString &src );
};

/////////////////////////////////////////////////////////////////////////////
// CMetaStringArray
#define METAINI_FILENAME	"METASTR.INI"
class CMetaStringArray :public CPtrArray
{
// コンストラクタ
public:
	CMetaStringArray();	// 標準のコンストラクタ
	CMetaStringArray(CMetaStringArray *pMetaString);
	~CMetaStringArray();

	CMetaString *PGetMetaString(int i) {
		ASSERT(i>=0 && i<GetSize());
		return (CMetaString *)GetAt(i);
		};
	BOOL FValidNewTitle(char *sz, BOOL fMsg=FALSE, int iSel=-1);
	BOOL FValidKeyLogic(char *sz);
	const CString GetKey(char *sz, int *pIndex=NULL);
	CString		m_strIniFile;
	const CMetaStringArray& operator = ( CMetaStringArray &src );
protected:
	void ReadWriteProfile(BOOL fRead);
	void SetIniFile();
};

#endif //! __METASTR_H_