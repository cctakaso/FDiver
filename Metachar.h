/*    PortTool v2.2     metachar.h          */

// metachar.h : ヘッダー ファイル
//

#ifndef __METACHAR_H_
#define __METACHAR_H_

#include "resource.h"
#include "strary2.h"
#include "..\mdfc\dstring.h"

#define chMatchAny      '?'
#define	chMatchStr		'*'
#define chAnd			'&'
#define chOr			'|'
#define chXor			'%'
#define chNot			'!'
#define chBlaketL		'('
#define chBlaketR		')'
#define	chPrefix		'\\'
#define chSBlaketL		'['
#define chSBlaketR		']'
#define chSOr			'|'
#define chSXor			'^'

enum MetaCharCheckFlag
{
	mfNon,
	mfKeyOut,
	mfKeyIn
};

enum MetaChar{
	mcMatchAny,
	mcMatchStr,
	mcAnd,
	mcOr,
	mcXor,
	mcNot,
	mcBlaketL,
	mcBlaketR,
	mcPrefix,
	mcSBlaketL,
	mcSBlaketR,
	mcSOr,
	mcSXor,
	MAX_METACHARS	//dumy
};
struct STRSPEC_METACHARS
{
	CString str[MAX_METACHARS];
	MetaCharCheckFlag mfCheck[MAX_METACHARS];
};

enum ReturnLogic
{
	rlErr=-1,		// 文法ｴﾗｰ || メモリエラー
	rlFalse=0,
	rlTrue,
	rlNutral
};
#define RLFROMCH(ch)	((ReturnLogic)(ch-'0'))
#define CHFROMRL(rl)	((char)(rl+'0'))
#define chFalse			CHFROMRL(rlFalse)
#define chTrue			CHFROMRL(rlTrue)
#define chNutral		CHFROMRL(rlNutral)

//グローバル・ファンクションライブラリ
void MetaCharsDataIni(STRSPEC_METACHARS *pMetaCharsData);
void MetaCharsDataIni2(STRSPEC_METACHARS *pMetaCharsData);
void MetaCharsDataCopy(STRSPEC_METACHARS *pSrc, STRSPEC_METACHARS *pDes);
int  MetaCharsDataCheck(STRSPEC_METACHARS *pMetaCharsData);
int  MetaCharsDataCheck(STRSPEC_METACHARS *pMetaCharsData, BOOL fUpdate);
// シンボルかどうか？
BOOL FSymboleCh(BYTE ch);

class CMetaChars
{
// コンストラクタ
public:
	CMetaChars();// 標準のコンストラクタ
	~CMetaChars() {
		ReadWriteProfile(FALSE); }

	STRSPEC_METACHARS m_metaCharsData;
protected:
	//protectである理由は、アップデートするタイミングを関数コールにする為
//	CKeyOutLogic m_keyOutLogic;			// サーチパターンロジック

	void ReadWriteProfile(BOOL fRead);
};

class CMacroException : public CException
{
	DECLARE_DYNAMIC(CMacroException)
public:
	enum {
		errMacSyntaxError,
	};
	int m_cause;
	CMacroException(int cause=CMacroException::errMacSyntaxError)
		{
		m_cause=cause;
		}
	void PASCAL ShowMessage();
};
void PASCAL TrowMacroException(int cause=CMacroException::errMacSyntaxError);
#define		MacroValidSyntax(f,p1)		((f) ? (void)0 : TrowMacroException(p1))

#endif // !__METACHAR_H_
