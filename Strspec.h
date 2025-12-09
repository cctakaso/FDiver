/*    PortTool v2.2     strspec.h          */

// findopti.h : ƒwƒbƒ_[ ƒtƒ@ƒCƒ‹
#ifndef __STRSPEC_H_
#define __STRSPEC_H_

#include "strary2.h"
#include "..\mdfc\dstring.h"

//////Attrib
struct STRSPEC_ATTR
{
	char	m_chPrefix;
	BOOL	m_fCase;
	BOOL	m_fBytes;
	BOOL	m_fKata;
//	BOOL	m_fUmura;			//umura‚Ì‘ã‚è‚ÉWholeWord‚ğ“ü‚ê‚é
	BOOL	m_fMatchWholeWord;
	BOOL	m_fSpace;
	BOOL	m_fTab;
	BOOL	m_fLF;
	BOOL	m_fNoBreak;
	CString	m_strOthers;
};

#ifdef _DBCS
#define STRSPEC_ATTR_PREF_SBCS	'0'
#define STRSPEC_ATTR_PREF_DBCS	'1'
#define STRSPEC_ATTR_PREF_DEF	STRSPEC_ATTR_PREF_DBCS
#define STRSPEC_ATTR_PREF_UNDEF	STRSPEC_ATTR_PREF_SBCS
#else
#define STRSPEC_ATTR_PREF_SBCS	'0'
#define STRSPEC_ATTR_PREF_DEF	STRSPEC_ATTR_PREF_SBCS
#define STRSPEC_ATTR_PREF_UNDEF	STRSPEC_ATTR_PREF_DBCS
#endif //_DBCS

//ƒOƒ[ƒoƒ‹Eƒtƒ@ƒ“ƒNƒVƒ‡ƒ“ƒ‰ƒCƒuƒ‰ƒŠ
void AttrDataIni(STRSPEC_ATTR *pAttrData);
void AttrDataRetrive(CString *pStrAttr, STRSPEC_ATTR *pAttrData);
void AttrDataUpdate(CString *pStrAttr, STRSPEC_ATTR *pAttrData);

/////////////////////////////////////////////////////////////////////////////
// CStrSpec ƒ_ƒCƒAƒƒO
class CStrSpec
{
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
public:
	CStrSpec();// •W€‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^
	~CStrSpec() {
		ReadWriteProfile(FALSE); }

// ƒ_ƒCƒAƒƒO ƒf[ƒ^
	int m_iSel;
	CStringArray2	m_aryStr;	// •¶š—ñ´İÄØ°
	CStringArray2	m_aryAttr;	// ƒAƒgƒŠƒrƒ…[ƒg´İÄØ°

// ƒtƒ@ƒ“ƒNƒVƒ‡ƒ“
	void ReadWriteProfile(BOOL fRead);
	STRSPEC_ATTR *GetSelAttrData();	// Œ»İ‚ÌƒAƒgƒŠƒrƒ…[ƒgƒf[ƒ^‚ğæ“¾‚·‚é

protected:
	//protect‚Å‚ ‚é——R‚ÍAƒAƒbƒvƒf[ƒg‚·‚éƒ^ƒCƒ~ƒ“ƒO‚ğŠÖ”ƒR[ƒ‹‚É‚·‚éˆ×
	STRSPEC_ATTR m_attrData;
};


#endif //__STRSPEC_H_"