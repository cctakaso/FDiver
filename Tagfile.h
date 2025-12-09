/*    PortTool v2.2     tagfile.h          */

#ifdef _TAG //All this file
// tagfile.h : ヘッダー ファイル
//
#ifndef __TAGFILE_H__
#define __TAGFILE_H__

#ifndef __cplusplus
#error Magical Design Foundation Classes require C++ compilation (use a .cpp suffix)
#endif
#include "..\mdfc\dfile.h"
#define DEFAULT_TAG_FILENAME	"_auto_.tax" //must be lower
/////////////////////////////////////////////////////////////////////////////
// CTagFile ドキュメント

class CTagFile :public CDFile
{
protected:
	BOOL m_fModifyed;
public:
	CTagFile() {
		m_fModifyed=FALSE; }
	~CTagFile() {};
	void SetDefaultTagFile();
	void SetModifyed(BOOL f=TRUE) {
		m_fModifyed = f; }
	BOOL GetModifyed() {
		return m_fModifyed; }
};

#endif // __TAGFILE_H__
#endif //_TAG

