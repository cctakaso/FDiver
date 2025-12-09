/*    PortTool v2.2     METACHAR.CPP          */

// metachar.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
//#include "fdiver.h"
//#include "strspec.h"
#include "metachar.h"
#include "findopti.h"
#include "profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFindOption *vpFindOption;


/////////////////////////////////////////////////////////////////////////////
// CMetaChars ダイアログ
#include "resource.h"

//ﾒﾀｷｬﾗｸﾀのｽﾀﾝﾀﾞｰﾄﾞﾀｲﾌﾟ（全て1byte文字）を定義
char METACHARSINI[MAX_METACHARS] =
{chMatchAny, chMatchStr, chAnd, chOr, chXor, chNot, chBlaketL, chBlaketR, chPrefix, chSBlaketL, chSBlaketR, chSOr, chSXor};
// ﾄｰｸﾝ切出しの際に参照する
//ﾒﾀｷｬﾗｸﾀのｽﾀﾝﾀﾞｰﾄﾞﾀｲﾌﾟでのｼﾝﾎﾞﾙﾁｪｯｸﾌﾗｸﾞを定義
const MetaCharCheckFlag METCINI_FCHKSET[MAX_METACHARS] =
{mfNon, mfNon, mfKeyOut, mfKeyOut, mfKeyOut, mfKeyOut, mfKeyOut, mfKeyOut, mfNon, mfKeyIn, mfKeyIn, mfKeyIn, mfKeyIn};
//ﾒﾀｷｬﾗｸﾀのﾍﾞｰｼｯｸﾀｲﾌﾟでのｼﾝﾎﾞﾙﾁｪｯｸﾌﾗｸﾞを定義
const MetaCharCheckFlag METCINI_FCHKSET2[MAX_METACHARS] =
{mfNon, mfNon, mfNon, mfNon, mfNon, mfNon, mfKeyOut, mfKeyOut, mfNon, mfKeyIn, mfKeyIn, mfKeyIn, mfKeyIn};
//書くﾒﾀｷｬﾗｸﾀの最大文字数を定義
const char METACHARS_MAXLEN[MAX_METACHARS] =
{1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1};

/////////////////////////////////////////////////////////////////////////////
// CMetaChars
CMetaChars::CMetaChars()
{
	ReadWriteProfile(TRUE);
}

// プロファイルを読み書きする。
void CMetaChars::ReadWriteProfile(BOOL fRead)
{
	CString CstrEntry;
	if (fRead)
		{
		CString cstr;
		// メタキャラクタの取り込み
		CstrEntry = "MetaChar";
		for (int i=0; i<MAX_METACHARS; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			m_metaCharsData.str[i] = theProfile.ReadString("FindOption", CstrEntry+vz, NULL);
			}
		MetaCharsDataCheck(&m_metaCharsData, TRUE/*update*/);
		}
	else
		{
		// メタキャラクタの書き込み
		CstrEntry = "MetaChar";
		for (int i=0; i<MAX_METACHARS; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			theProfile.WriteString("FindOption", CstrEntry+vz, m_metaCharsData.str[i].GetBuffer(0));
			}
		}
}


void MetaCharsDataIni(STRSPEC_METACHARS *pMetaCharsData)
{
	for (int i=0; i<MAX_METACHARS; i++)
		pMetaCharsData->str[i] = METACHARSINI[i];
	pMetaCharsData->str[mcAnd] = "&&";
	pMetaCharsData->str[mcOr] = "||";
	ASSERT(sizeof(pMetaCharsData->mfCheck)==sizeof(METCINI_FCHKSET));
	memcpy(pMetaCharsData->mfCheck, METCINI_FCHKSET, sizeof(METCINI_FCHKSET));
}
void MetaCharsDataIni2(STRSPEC_METACHARS *pMetaCharsData)
{
	for (int i=0; i<MAX_METACHARS; i++)
		pMetaCharsData->str[i] = METACHARSINI[i];
	pMetaCharsData->str[mcAnd] = "AND";
	pMetaCharsData->str[mcOr] = "OR";
	pMetaCharsData->str[mcXor] = "XOR";
	pMetaCharsData->str[mcNot] = "NOT";
	ASSERT(sizeof(pMetaCharsData->mfCheck)==sizeof(METCINI_FCHKSET2));
	memcpy(pMetaCharsData->mfCheck, METCINI_FCHKSET2, sizeof(METCINI_FCHKSET2));
}
void MetaCharsDataCopy(STRSPEC_METACHARS *pSrc, STRSPEC_METACHARS *pDes)
{
	for (int i=0; i<MAX_METACHARS; i++)
		pDes->str[i] = pSrc->str[i];
}
int  MetaCharsDataCheck(STRSPEC_METACHARS *pMetaCharsData, BOOL fUpdate)
{
	int iRtn = MetaCharsDataCheck(pMetaCharsData);
	if (fUpdate && iRtn!=0)
		MetaCharsDataIni(pMetaCharsData);
	return iRtn;
}
int  MetaCharsDataCheck(STRSPEC_METACHARS *pMetaCharsData)
{
	BOFFSET bOffset;
	MetaCharCheckFlag mfCheck;
	CDString cdstr;
	int len;
	WORD wch;
	for (int i=0; i<MAX_METACHARS; i++)
		{
		cdstr = pMetaCharsData->str[i];
		len = cdstr.GetLength();
		if (len==0 || len > METACHARS_MAXLEN[i] || 
			(METACHARS_MAXLEN[i]==1 && !FSymboleCh((BYTE)cdstr.GetAt(0))) ) // 1文字の場合は、かならずシンボルにする
			return i+1;
		// ﾄｰｸﾝ切出しの際に参照する
		// ﾒﾀｷｬﾗｸﾀのｼﾝﾎﾞﾙﾁｪｯｸ
		pMetaCharsData->mfCheck[i] = mfCheck = METCINI_FCHKSET[i];
		if (METACHARS_MAXLEN[i]>1)	// １文字以上のﾒﾀｷｬﾗｸﾀをチェック対象にする
			continue;
		else
			{
			// 全てｼﾝﾎﾞﾙだったら、ﾌﾗｸﾞをONにする。
			for (bOffset=0; (wch = cdstr.ScanChar(bOffset)); )
				{
				if (!HighByte(wch))
					{
					if (FSymboleCh((BYTE)LowByte(wch)))
						continue;
					}
				mfCheck=mfNon;
				break;
				}
			pMetaCharsData->mfCheck[i] = mfCheck;
			}
		}
	return 0; //ﾁｪｯｸOKの時のみﾒﾀｷｬﾗｸﾀのｼﾝﾎﾞﾙﾁｪｯｸも全て終わっている
}

// シンボルかどうか？
BOOL FSymboleCh(BYTE ch)
{
	return ('!'<=ch && ch<='/') || 
			(':'<=ch && ch<='@') || 
			('['<=ch && ch<='`') || 
			('{'<=ch && ch<='~') || 
			('{'<=ch && ch<='~') || 
			('｢'<=ch && ch<='｣');
}


/************************************************************************/
/*		Functions in CMacroException class,								*/
/************************************************************************/
/*																		*/
/*		CMacroException													*/
/*																		*/
/************************************************************************/
// character strings to use for dumping CFileException
IMPLEMENT_DYNAMIC(CMacroException, CException);
void PASCAL TrowMacroException(int cause)
{
	THROW(new CMacroException(cause));
}
void PASCAL CMacroException::ShowMessage()
{
	static const UINT idCMacroExceptionCause[] =
		{
		IDS_META_RLERR,
		};

	int id=m_cause;
	if (id >= sizeof(idCMacroExceptionCause) / sizeof(UINT))
		id = 0; //set default
	Message(idCMacroExceptionCause[m_cause]);
}

