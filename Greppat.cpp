/*    PortTool v2.2     GREPPAT.CPP          */

// metachar.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "greppat.h"
#include "findopti.h"
#ifdef _DEBUG
#include "finddlg.h"
extern CFindDlg *vpFindDlg; // ﾌｧｲﾝﾄﾞﾀﾞｲｱﾛｸﾞ
//extern char vz[256];
#endif //_DEBUG

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFindOption *vpFindOption;
extern CMetaStringArray *vpMetaStringArray;

//ﾒﾀｷｬﾗｸﾀのｽﾀﾝﾀﾞｰﾄﾞﾀｲﾌﾟ（全て1byte文字）を定義
extern char METACHARSINI[MAX_METACHARS];


/********************************************
	CGrepPattern クラス
*********************************************/
CGrepPattern::CGrepPattern()
{
	m_pwSpecial = NULL;
	m_pwPattern = NULL;
}

CGrepPattern::~CGrepPattern()
{
	m_cstr.Empty();
	if (m_pwPattern)
		delete [] m_pwPattern;
	if (m_pwSpecial)
		delete [] m_pwSpecial;
}
void CGrepPattern::Initialize(char *sz)
{
	ASSERT(sz[0]!='\0');
	m_cstr = sz;
}
#ifdef _DEBUG
void CGrepPattern::Dump(CDumpContext& dc) const
{
	int i;
	dc << "\nCGrepPattern";
	dc << "\n m_cstr = " << m_cstr;
	dc << "\n m_cchBlockSize = " << m_cchBlockSize;
	dc << "\n m_cchPattern = " << m_cchPattern;
	dc << "\n m_dcpMatchAny = " << m_dcpMatchAny;
	dc << "\n m_iwMatchAnyPos = " << m_iwMatchAnyPos;
	BOOL fBytes = (vpFindDlg->m_strSpec.GetSelAttrData()->m_chPrefix==STRSPEC_ATTR_PREF_DBCS &&
					vpFindDlg->m_strSpec.GetSelAttrData()->m_fBytes);
	dc << "\n fBytes = " << fBytes;
    dc << "\n m_pwSpecial    = ";
	for (i=0; i<m_cchBlockSize; i++)
		{
		dc << m_pwSpecial[i] << " ";
		}
	for (i=0; i<(fBytes ? 4:2); i++)
		{
		dc << "\n m_pwPattern[" << i << "] = ";
		for (int j=i*m_cchBlockSize; j<(i+1)*m_cchBlockSize; j++)
			{
			//dc << (BYTE)(&m_pwPattern[i][j]) << " ";
			wsprintf((char*)vz,"%02x%02x ", *((BYTE *)(&((WORD *)m_pwPattern)[j])), *(((BYTE *)(&((WORD *)m_pwPattern)[j]))+1));
			dc << (char *)vz;
			}
		}
	for (i=0; i<(fBytes ? 4:2); i++)
		{
		dc << "\n m_pwPattern[" << i << "] = ";
		for (int j=i*m_cchBlockSize; j<(i+1)*m_cchBlockSize; j++)
			{
			//dc << (BYTE)(&m_pwPattern[i][j]) << " ";
			if (*(((BYTE *)(&((WORD *)m_pwPattern)[j]))+1)!=0)
				{
				vz[0]= ' ';
				vz[1]= *((BYTE *)(&((WORD *)m_pwPattern)[j]));
				vz[2]= *(((BYTE *)(&((WORD *)m_pwPattern)[j]))+1);
				vz[3]= ' ';
				vz[4]= ' ';
				vz[5]= '\0';
				}
			else if (*((BYTE *)(&((WORD *)m_pwPattern)[j]))<0x20)
				wsprintf((char*)vz,"%02x00 ", *((BYTE *)(&((WORD *)m_pwPattern)[j])));
			else
				wsprintf((char*)vz," %c00 ", *((BYTE *)(&((WORD *)m_pwPattern)[j])));
			dc << (char *)vz;
			}
		}

	//dc << "\n m_ = " << m_;
}
#endif //_DEBUG
/********************************************
	CKeyBlock クラス
*********************************************/
CKeyBlock::CKeyBlock()
{
	m_kbt = kbtDumy;
	m_pGrepPat = NULL;
}

CKeyBlock::~CKeyBlock()
{
	Clear();
}

void CKeyBlock::Clear()
{
	switch(m_kbt)
		{
		case kbtGrep:
			if (m_pGrepPat)
				delete m_pGrepPat;
			break;
		case kbtSubKeyIn:
			if (m_pSubKeyIn)
				delete m_pSubKeyIn;
			break;
		}
	m_kbt = kbtDumy;
	m_pGrepPat = NULL;
}

BOOL CKeyBlock::Initialize(KeyBlock_Type kbt, char *sz)
{
	ASSERT(kbt>=kbtGrep && kbt<=kbtDumy);
	Clear();
	switch(m_kbt=kbt)
		{
		case kbtGrep:
			m_pGrepPat = new CGrepPattern;
			if (!m_pGrepPat)
				return FALSE;
			m_pGrepPat->Initialize(sz);
			break;
		case kbtSubKeyIn:
			m_pSubKeyIn = new CKeyInLogic;
			if (!m_pSubKeyIn)
				return FALSE;
			if (m_pSubKeyIn->Initialize(sz)!=rlNutral)
				return FALSE;
			break;
		}
	return TRUE;
}
#ifdef _DEBUG
void CKeyBlock::Dump(CDumpContext& dc) const
{
	dc << "\nCKeyBlock";
	if (m_kbt==kbtGrep)
		{
		dc << "\n m_kbt = kbtGrep";
		dc << "\n ->";
		m_pGrepPat->Dump(dc);
		dc << "\n <-";
		}
	else if (m_kbt==kbtSubKeyIn)
		{
		dc << "\n m_kbt = kbtSubKeyIn";
		dc << "\n ->";
		m_pSubKeyIn->Dump(dc);
		dc << "\n <-";
		}
	else
		dc << "\n m_kbt = kbtDumy";
}
#endif //_DEBUG
/********************************************
	CKeyLogic クラス群
*********************************************/
/********************************************
	CKeyLogic 基本クラス
*********************************************/
void CKeyLogic::Clear()
{
	m_strKeyLogic.Empty();
	m_rl = rlNutral; // 結果格納バッファをイニシャライズ

	CKeyBlock *pKeyBlock;
	for (int i=0; i<=m_aryKeyBlock.GetUpperBound(); i++)
		{
		pKeyBlock = GetKeyBlock(i);
		delete pKeyBlock;
		}
	m_aryKeyBlock.RemoveAll();
	if (m_piKeyMatched)
		delete [] m_piKeyMatched;
	m_piKeyMatched = NULL;
}



// パターン内のワード文字列を与えて、ロジックパターンを作成してゆく
ReturnLogic CKeyLogic::SetLogicPatternForWord(MetaCharCheckFlag mf, char *pstr)
{
//	m_strKeyLogic
//	m_arystrPats
	ASSERT(mf==mfKeyOut || mf==mfKeyIn);
	CKeyBlock *pKeyBlock;
	KeyBlock_Type kbt;
	char *pstrF = pstr;
	CString cstrTok;
	char ch;
	STRSPEC_METACHARS *pmetaCharsData = &vpFindOption->m_metaChars.m_metaCharsData;

	for(; (ch = *pstr); pstr++)
		{
#ifdef _DBCS
		if (IsDBCSLeadByte (ch))
			{
			ASSERT ( IsDBCSTailByte(*(pstr+1)) ) ;
			cstrTok += ch;
			cstrTok += *(++pstr);
			}
		else
#endif //_DBCS
			{
			for(int i=0; i<MAX_METACHARS; i++)
				{
				if (pmetaCharsData->mfCheck[i]==mf && // チェック対象のみ
					(!(pstr>pstrF && *(pstr-1)==pmetaCharsData->str[mcPrefix][0])) &&
					strnicmp(pmetaCharsData->str[i].GetBuffer(0), (char *)pstr, pmetaCharsData->str[i].GetLength())==0)
					{
					if (!cstrTok.IsEmpty())
						{
						if ((pKeyBlock = new CKeyBlock)==NULL)
							return rlErr;
						m_aryKeyBlock.Add(pKeyBlock);
						if (mf==mfKeyOut && FCheckLogical(mfKeyIn/*default*/, cstrTok.GetBuffer(0)))
							kbt = kbtSubKeyIn; // サブキー=CKeyInLogic
						else
							kbt = kbtGrep;
						if (!pKeyBlock->Initialize(kbt, cstrTok.GetBuffer(0)))
								return rlErr;
						m_strKeyLogic += chNutral;
						}
					// dumy set
					if ((pKeyBlock = new CKeyBlock)==NULL)
						return rlErr;
					m_aryKeyBlock.Add(pKeyBlock);
					
					m_strKeyLogic += METACHARSINI[i];
					ch = 0;	//flg set
					cstrTok.Empty();
					pstr += (pmetaCharsData->str[i].GetLength() - 1);
					break;
					}
				}
			if (ch)
				cstrTok += ch;
			}
		}
	if (!cstrTok.IsEmpty())
		{
		if ((pKeyBlock = new CKeyBlock)==NULL)
			return rlErr;
		m_aryKeyBlock.Add(pKeyBlock);
		if (mf==mfKeyOut && FCheckLogical(mfKeyIn/*default*/, cstrTok.GetBuffer(0)))
			kbt = kbtSubKeyIn; // サブキー=CKeyInLogic
		else
			kbt = kbtGrep;
		if (!pKeyBlock->Initialize(kbt, cstrTok.GetBuffer(0)))
			return rlErr;
		m_strKeyLogic += chNutral;
		}
	// SXorの為のフラグ格納領域
	m_strSXorLogic = CString(chNutral,m_strKeyLogic.GetLength());
	if (m_piKeyMatched)
		delete [] m_piKeyMatched;
	m_piKeyMatched = new int[m_strKeyLogic.GetLength()+1];
	memset(m_piKeyMatched, (BYTE)0, sizeof(int)*(m_strKeyLogic.GetLength()+1));
	//takaso2010 delete
	//if (!m_piKeyMatched)
	//	rlErr;

	return rlNutral;
}

// パターン内のワード文字列を与えて、ロジックパターンを作成してゆく
CString CKeyLogic::TransFromEntryMetaString(char *pstr, BOOL fFirst/*=FALSE*/, CMetaStringArray *pMetaStringArray/*=NULL*/)
{
	STRSPEC_METACHARS *pme = &vpFindOption->m_metaChars.m_metaCharsData;
	CString cstrBlaketL = pme->str[mcSBlaketL] + pme->str[mcSBlaketL];
	CString cstrBlaketR = pme->str[mcSBlaketR] + pme->str[mcSBlaketR];
	CString cstrTran;
	CString cstrTok;

	if (pMetaStringArray==NULL)
		pMetaStringArray = vpMetaStringArray;
	CDWordArray aryIndex;
	if (fFirst)
		aryIndex.RemoveAll();

	char *pch = pstr;
	char *pch2;
	int index;
	while(pch && *pch)
		{
		// 最後の'='は切り捨てる
		if ((pch2 = strstr(pch,cstrBlaketL.GetBuffer(0)))!=NULL)
			{
			*pch2 = '\0';
			cstrTran += pch;
			pch = pch2+2;
			if ((pch2 = strstr(pch,cstrBlaketR.GetBuffer(0)))!=NULL)
				{
				*pch2 = '\0';
				cstrTok = pMetaStringArray->GetKey(pch, &index);
				if (!cstrTok.IsEmpty())
					{
					// 無限ﾙｰﾌﾟにならない為のチェック
					for (int i=0; i<aryIndex.GetSize(); i++)
						{

/*    PortTool v2.2     1995/10/16    8:2          */
/*      Found   : (WORD)          */
/*      Issue   : ３２ビット値を不正にキャストしていないかチェックして下さい          */
/*      Suggest : 可能なら３２ビットデータに変更して下さい          */
/*      Help available, search for WORD in WinHelp file API32WH.HLP          */
						if (index==aryIndex[i])
							{
							TrowMacroException();
							}
						}
					aryIndex.Add(index); // EntryKeyのｲﾝﾃﾞｯｸｽをｾｰﾌﾞして再帰呼出を実行する
					cstrTran += pme->str[mcBlaketL];
					cstrTran += TransFromEntryMetaString(cstrTok.GetBuffer(0)); // 再帰呼出
					cstrTran += pme->str[mcBlaketR];
					aryIndex.RemoveAt(aryIndex.GetUpperBound()); // 再帰呼出から出たらEntryKeyのｲﾝﾃﾞｯｸｽを削除する
					}
				else					
					{
					//SPEC:無限ﾙｰﾌﾟにならない為に、Errにする
					//cstrTran += cstrBlaketL + pch + cstrBlaketR; //"[["を元に戻す
					TrowMacroException();
					}
				pch = pch2+2;
				}
			else
				{
				cstrTran += cstrBlaketL + pch;
				break;
				}
			}
		else
			{
			cstrTran += pch;
			break;
			}
		}
	return cstrTran;
}

BOOL CKeyLogic::FCheckLogical(MetaCharCheckFlag mf, char *pstr)
{
	return TRUE;	// for SXor対応！
//	m_strKeyLogic
//	m_arystrPats
	ASSERT(mf==mfKeyOut || mf==mfKeyIn);
	char *pstrF = pstr;
	char ch;
	STRSPEC_METACHARS *pmetaCharsData = &vpFindOption->m_metaChars.m_metaCharsData;
	for(; (ch = *pstr); pstr++)
		{
#ifdef _DBCS
		if (IsDBCSLeadByte (ch))
			{
			ASSERT ( IsDBCSTailByte(*(pstr+1)) ) ;
			++pstr;
			}
		else
#endif //_DBCS
			{
			for(int i=0; i<MAX_METACHARS; i++)
				{
				if (pmetaCharsData->mfCheck[i]==mf && // チェック対象のみ
					(!(pstr>pstrF && *(pstr-1)==pmetaCharsData->str[mcPrefix][0])) &&
					strnicmp(pmetaCharsData->str[i].GetBuffer(0), (char *)pstr, pmetaCharsData->str[i].GetLength())==0)
					{
					return TRUE;
					}
				}
			}
		}
	return FALSE;
}




void CKeyLogic::SetRlOne(ReturnLogic rl)
{
	ASSERT(m_strKeyLogic.GetLength()==m_aryKeyBlock.GetSize());
	ASSERT(m_indexLogic<m_strKeyLogic.GetLength());
	ASSERT(m_indexLogic<m_aryKeyBlock.GetSize());
	
	//ASSERT(GetSelKeyBlock()->m_kbt == kbtGrep);

	m_strKeyLogic.SetAt(m_indexLogic, CHFROMRL(rl));
}

void CKeyLogic::SetFalseForAllNutral()
{
	for(int i=0; i<m_strKeyLogic.GetLength(); i++)
		{
		ReturnLogic rl = RLFROMCH(m_strKeyLogic[i]);
		if (rl==rlNutral)
			{
			// SXorフラグがchTrueならchTrueに、それ以外はchFalseにする
			if (m_strSXorLogic[i]==chTrue)
				m_strKeyLogic.SetAt(i, chTrue);
			else
				m_strKeyLogic.SetAt(i, chFalse);
			}
		}
	// SUBのCKeyLogic
	//for (int i=0; i<m_aryKeyBlock.GetSize(); i++)
	//	{
	//	if (GetKeyBlock(i)->m_kbt == kbtSubKeyIn)
	//		GetSubKeyLogic(i)->SetFalseForAllNutral();
	//	}
}
void CKeyLogic::SetNutralForAll()
{
	SetNutral();
	SetNutralForSub();
	m_strSXorLogic = CString(chNutral,m_strKeyLogic.GetLength());//SXorもリセット
}
void CKeyLogic::SetNutralForSub()
{
	// SUBのCKeyLogic
	for (int i=0; i<m_aryKeyBlock.GetSize(); i++)
		{
		if (GetKeyBlock(i)->m_kbt == kbtSubKeyIn)
			GetSubKeyLogic(i)->SetNutral();
		}
	m_indexLogic = m_strKeyLogic.GetLength(); //+1 for null taminate.
}
void CKeyLogic::SetNutral()
{
	char *ptok = m_strKeyLogic.GetBuffer(0);
	char tok;
	for(; (tok=*ptok) != '\0'; ptok++)
		{
		ReturnLogic rl = RLFROMCH(tok);
		if (rl==rlFalse || rl==rlTrue)
			*ptok = chNutral;
		}
	m_rl = rlNutral; // 結果格納バッファをイニシャライズ
	m_indexLogic = m_strKeyLogic.GetLength(); //+1 for null taminate.
}
void CKeyLogic::ResetBlockIndex()
{
	m_indexLogic = m_strKeyLogic.GetLength();	 //+1 for null taminate.

	// SUBのCKeyLogic
	for (int i=0; i<m_aryKeyBlock.GetSize(); i++)
		{
		if (GetKeyBlock(i)->m_kbt == kbtSubKeyIn)
			GetSubKeyLogic(i)->ResetBlockIndex();
		}
}

// m_strKeyLogicのロジックをチェックして、値を返す
ReturnLogic CKeyLogic::CheckLogic()
{
	// ﾆｭｰﾄﾗﾙでなければ計算しない
	if (m_rl != rlNutral)
		return m_rl;	//結果格納バッファの値をそのまま返す
	//m_strKeyLogicをチェックする
	TRY {
	advance(0);
	m_rl = term();
	if (m_tok != '\0')
		m_rl = rlErr;
	return m_rl;
	}
	CATCH(CMacroException, e)
		{
		if (m_rl != rlFalse)  // SXorでrlRがTRUEの場合を見つけた時以外
			m_rl = rlErr;
		}
	END_CATCH

	return m_rl;
}


ReturnLogic CKeyLogic::And(ReturnLogic rlL, ReturnLogic rlR)
{
	if (rlL == rlFalse || rlR == rlFalse)
		return rlFalse;
	if (rlL == rlNutral || rlR == rlNutral)
		return rlNutral;
	return (ReturnLogic)(rlL & rlR);
}
ReturnLogic CKeyLogic::Or(ReturnLogic rlL, ReturnLogic rlR/*=rlFalse*/)
{
	if (rlL == rlTrue || rlR == rlTrue)
		return rlTrue;
	if (rlL == rlFalse && rlR == rlFalse)
		return rlFalse;
	return rlNutral;
}
ReturnLogic CKeyLogic::Not(ReturnLogic rl)
{
	if (rl == rlNutral)
		return rlNutral;
	return (ReturnLogic)(!rl);
}

void CKeyLogic::advance(int next)
{
	if (next==0)
		{
		m_ptok = m_strKeyLogic.GetBuffer(0);
		ASSERT(m_ptok);
		}
	m_tok = *m_ptok++;
}
void CKeyLogic::eat(char ch)
{
	if (m_tok!=ch)
		TrowMacroException();
	advance();
}
/********************
ReturnLogic CKeyLogic::CheckSubLogic()
{
	int index = (m_ptok-1)-m_strKeyLogic.GetBuffer(0);
	ASSERT(index>=0 && index<m_strKeyLogic.GetLength());
	if (GetKeyBlock(index)->m_kbt != kbtSubKeyIn)
		return rlNutral;
	return GetSubKeyLogic(index)->CheckLogic();
}
********************/
#ifdef _DEBUG
void CKeyLogic::Dump(CDumpContext& dc) const
{
	int i;
	dc << "\n m_rl = " << (int)m_rl;
	dc << "\n m_strKeyLogic  = " << m_strKeyLogic;
	dc << "\n m_indexLogic = " << m_indexLogic;
	dc << "\n m_piKeyMatched = ";
	for (i=0; i<=m_strKeyLogic.GetLength(); i++)
		{
		dc << (int)m_piKeyMatched[i] << " ";
		}
	for (i=0; i<m_strKeyLogic.GetLength(); i++)
		{
		dc << "\n m_aryKeyBlock[" << i << "] = ";
		((CKeyBlock *)m_aryKeyBlock[i])->Dump(dc);
		}
}
#endif //_DEBUG


/********************************************
	CKeyInLogic 派生クラス
*********************************************/
// パターン全体の文字列を与えて、ロジックパターンを完成させる
ReturnLogic CKeyInLogic::Initialize(char *sz)
{
	ASSERT(sz[0]);
	// パターンロジックを空にｲﾆｼｬﾗｲｽﾞする
	Clear();

	if (SetLogicPatternForWord(mfKeyIn, sz)==rlErr)
		return rlErr;

	return CheckLogic();
}
BOOL CKeyInLogic::SetNextIndexLogic(int &cchMatched, BOOL fStr/*=FALSE*/)
{
	ASSERT(m_indexLogic>=0);
	

	if (m_indexLogic==0)
		return FALSE;
	ASSERT(m_indexLogic>0);

	char ch;	

	for (int i=m_indexLogic-1; i>=0; i--)
		{
		ch = m_strKeyLogic[i];
		if (FStrCh(ch))
			{
			// 以前のものがあるか？
			if (i<(m_strKeyLogic.GetLength()-1))
				{
				//直前のcchMatched>0のものを取得
				if (fStr)
					cchMatched = m_piKeyMatched[GetBeforStrIndex(i)];
				else
					cchMatched = m_piKeyMatched[GetBeforTrueIndex(i)];
				}
			else
				cchMatched = 0; //デフォルトは、B&Mで出てきたところから
			m_indexLogic = i;
			return TRUE;
			}
		else if (!fStr && ch==METACHARSINI[mcSOr] && m_strKeyLogic[m_indexLogic]==chTrue)
			{
			// 2[2|2
			for (i--; i>=0; i--)
				{
				// '['までスキップする
				if (m_strKeyLogic[i] == METACHARSINI[mcSBlaketL])
					break;
				}
			}
		}
	m_indexLogic = 0;
	if (fStr)
		cchMatched = m_piKeyMatched[GetBeforStrIndex(-1)];
	else
		cchMatched = m_piKeyMatched[GetBeforTrueIndex(-1)];
	return FALSE;
}
int CKeyInLogic::GetBeforStrIndex(int index)
{
	char ch;
	int i, j;
	//直前のcchMatched>0のものを取得
	for(i=index+1; i<m_strKeyLogic.GetLength(); i++)
		{
		ch = m_strKeyLogic[i];
		if (ch == METACHARSINI[mcSBlaketL])
			{
			int iCount=0;
			int iMin=0x0fff;
			int iStok;
			for(j=i+1; j<m_strKeyLogic.GetLength(); j++)
				{
				ch = m_strKeyLogic[j];
				if (ch == METACHARSINI[mcSBlaketR])
					{
					if (iMin==0x0fff || iCount==1) // "[x]abc","[^x]abc"である場合は、a位置のものを取得
						return GetBeforStrIndex(j);	//for "[x][ab]
					break;
					}
				else if (FStrCh(ch) && m_strKeyLogic[j]!=METACHARSINI[mcSXor])
					{
					iCount++;
					if (m_piKeyMatched[j]>0 && m_piKeyMatched[j]<iMin)
						{
						iMin = m_piKeyMatched[j];
						iStok = j;
						}
					}
				}
			ASSERT(iMin!=0x0fff);
			i = iStok;
			break;
			}
		else if (ch == METACHARSINI[mcSOr] ||
				ch == METACHARSINI[mcSXor])
			{
			for(j=i+1; j<m_strKeyLogic.GetLength(); j++)
				{
				if (m_strKeyLogic[j]==METACHARSINI[mcSBlaketR]) //もしも見つからなかったらcchMatched=0だ
					return GetBeforStrIndex(j);	//for "[x|x1][ab]
				}
			}
		else if (FStrIndex(i))
			break;
		}
	return i;	// not found is return m_strKeyLogic.GetLength() value.
}

int CKeyInLogic::GetBeforTrueIndex(int index)
{
	char ch;
	int i;
	//直前のcchMatched>0のものを取得
	for(i=index+1; i<m_strKeyLogic.GetLength(); i++)
		{
		ch = m_strKeyLogic[i];
//		if (ch == METACHARSINI[mcSOr] ||
//				ch == METACHARSINI[mcSXor])
//			{
//			for(j=i+1; j<m_strKeyLogic.GetLength(); j++)
//				{
//				if (m_strKeyLogic[j]==METACHARSINI[mcSBlaketR]) //もしも見つからなかったらcchMatched=0だ
//					return GetBeforTrueIndex(j);	//for "[x|x1][ab]
//				}
//			}
//		else
		if (m_strKeyLogic[i]==chTrue) //一番近いTrueを取得
			return i;
		}
	return i;	// not found is return m_strKeyLogic.GetLength() value.
}

BOOL CKeyLogic::FStrCh(char ch)
{
	ReturnLogic rl = RLFROMCH(ch);
	return (rl == rlNutral || rl == rlTrue || rl == rlFalse);
	//if (m_piKeyMatched[j]>0)
}

ReturnLogic CKeyInLogic::term()
{
	ReturnLogic rl = fact();
	while(m_tok != '\0')
		{
		if (m_tok==METACHARSINI[mcSBlaketL])
			{
			advance();
			// "12[3
			if ( *m_ptok==METACHARSINI[mcSBlaketR])
				{
				if (FStrCh(*(m_ptok-1)))
					advance();
				else
					TrowMacroException();
				}
			else
				rl = And(rl, term());
			eat(METACHARSINI[mcSBlaketR]);
			}
		else if (m_tok==METACHARSINI[mcSBlaketR])
			{
			// "12[3]2
			//advance();
			//if (m_tok == '\0')
			//	break;
			//rl = And(rl, term());
			break; // return up!
			}
		else if (m_tok==METACHARSINI[mcSOr])
			{
			advance();
			rl = Or(rl, fact());
			}
		else if (m_tok==METACHARSINI[mcSXor])
			{
			advance();
			rl = Xor(rl, fact());
			}
		else
			{
			ASSERT(*(m_ptok-2)==METACHARSINI[mcSBlaketR]);
			rl = And(rl, fact());
			}
		}
	return rl;
}
ReturnLogic CKeyInLogic::fact()
{
	ReturnLogic rl;

	if (m_tok==METACHARSINI[mcSBlaketL])
		{
		advance();
		rl = term();
		eat(METACHARSINI[mcSBlaketR]);
		}
	else if (m_tok==METACHARSINI[mcSOr])
		{
		advance();
		rl = Or(fact());
		}
	else if (m_tok==METACHARSINI[mcSXor])
		{
		advance();
		rl = Xor(fact());
		}
	else if (m_tok=='\0')
		{
		TrowMacroException();
		}
	else
		{
		rl = RLFROMCH(m_tok);
		if (rl!=rlFalse && rl!=rlTrue && rl!=rlNutral)
			{
			TrowMacroException();
			}
/*****	if (rl == rlNutral)
			{
			switch(rl = CheckSubLogic())
				{
				case rlErr:
					TrowMacroException();
					break;
				case rlTrue:
				//case rlFalse: SubKeyからCKeyOutLogicにセットするのは、rlTrueだけとする。
				//case rlNutral:
					*(m_ptok-1) = CHFROMRL(rl);
					break;
				}
			}
**********/
		advance();
		}
	return rl;
}
ReturnLogic CKeyInLogic::Xor(ReturnLogic rlL, ReturnLogic rlR)
{
	switch(rlR)
		{
		case rlTrue: //rlR is must be to check first!
			m_rl = rlFalse;
			TrowMacroException();
			return rlFalse; //for compiler
			break;
		case rlFalse:
			return rlL;
			break;
		default: //rlNutral
			return rlNutral;
			break;
		}
}
ReturnLogic CKeyInLogic::Xor(ReturnLogic rlR)
{
	if (rlR==rlTrue)
		{
		m_rl = rlFalse;
		TrowMacroException();
		}
	return Not(rlR);
}
#ifdef _DEBUG
void CKeyInLogic::Dump(CDumpContext& dc) const
{
	dc << "\nCKeyInLogic";
	CKeyLogic::Dump(dc);
}
#endif //_DEBUG
/********************************************
	CKeyOutLogic 派生クラス
*********************************************/
// パターン全体の文字列を与えて、ロジックパターンを完成させる
BOOL CKeyOutLogic::Initialize(char *sz, BOOL bMsg)
{
	ASSERT(sz[0]);
	// パターンロジックを空にｲﾆｼｬﾗｲｽﾞする
	Clear();

	CString cstrWord = sz;
	CDString cdstr;
	TRY {
	cdstr = TransFromEntryMetaString(cstrWord.GetBuffer(0), TRUE);
	}
	CATCH(CMacroException, e)
		{
		delete e;
		if (bMsg) {
			ASSERT(cdstr.IsEmpty());
			Message(IDS_ERR_METASTRENTRY_LOOP);
		}
		return FALSE;
		}
	END_CATCH

	ReturnLogic rl=rlNutral;
	UINT ui;
	BOFFSET boffset;
	// key out check!
	for(boffset=0; ;)
		{
		cstrWord = cdstr.ScanWord(boffset);
		if (cstrWord.IsEmpty())
			break;
		if (SetLogicPatternForWord(mfKeyOut, (char *)cstrWord.GetBuffer(0))==rlErr)
			{
			rl = rlErr;
			break;
			}
		}

	switch(rl==rlNutral ? CheckLogic():rl)
		{
		case rlErr:
			ui = IDS_META_RLERR;
			break;
		case rlFalse:
			ui = IDS_META_RLFALSE;
			break;
		case rlTrue:
			ui = IDS_META_RLTRUE;
			break;
		default:
			ui = 0;
			break;
		}
	if (ui!=0)
		{
		if (bMsg)
			Message(ui);
		return FALSE;
		}
	return TRUE;
}

ScanLogic CKeyOutLogic::ScanStrNext(CGrepPattern *&pGrepPattern, int &cchMatched, BOOL ffirst/*takaso2010*/)
{
//return value:
//slNextBlock: cchMatchedはクリアされている事
//slNextPat:   cchMatchedは加算されている事

	// 現在m_indexLogicが指しているCKeyBlockごとの処理
	
	//一番最初だったら、CKeyOutLogicのインデックスをイニシャルセット
	if (ffirst)/*takaso2010*/
		{
		ResetBlockIndex();
		GetSelGrepPatternFlow(pGrepPattern);
		return slNextBlock;
		}
	ScanLogic sl;

	ASSERT(GetSelKeyBlock()->m_kbt != kbtDumy); //ダミーではない
	if (GetSelKeyBlock()->m_kbt == kbtGrep) // グレップである場合
		{
		SetSelCchMatched(cchMatched);	// 現在のcchMatchedセット
		cchMatched = 0;			// クリアする
		if (SetNextIndexLogicSimple())
			{
			GetSelGrepPatternFlow(pGrepPattern);
			sl = slNextBlock;
			}
		else
			sl = slEndBlock;
		}
	else
		{
		ASSERT( GetSelKeyBlock()->m_kbt ==  kbtSubKeyIn );
		GetSelSubKeyLogic()->SetSelCchMatched(cchMatched);	// CKeyInLogicで、現在のcchMatchedセット
		if (GetSelSubKeyLogic()->SetNextIndexLogic(cchMatched, TRUE))
			{
			sl = GetSelGrepPatternFlow(pGrepPattern);
			ASSERT(sl==slNextPat);
			// ここでだけ、cchMatchedは加算されている
			}
		else
			{
			SetSelCchMatched(cchMatched);	// CKeyOutLogicで、ｻﾌﾞｷｰのcchMatchedをセット
			cchMatched = 0;			// クリアする
			if (SetNextIndexLogicSimple())
				{
				GetSelGrepPatternFlow(pGrepPattern);
				sl = slNextBlock;
				}
			else
				sl = slEndBlock;
			}
		}
	return sl;
}

ScanLogic CKeyLogic::GetSelGrepPatternFlow(CGrepPattern *&pGrepPattern)
{
	InitSelToStr();

	// 現在m_indexLogicが指しているKeyBlockのGrepPatを取得する
	
	//一番最初だったら、CKeyOutLogicのインデックスをイニシャルセット
	ASSERT(GetSelKeyBlock()->m_kbt != kbtDumy); //ダミーではない

	if (GetSelKeyBlock()->m_kbt == kbtGrep) // グレップである場合
		{
		pGrepPattern = GetSelGrepPattern();
		return slNextBlock;
		}
	else
		{
		ASSERT( GetSelKeyBlock()->m_kbt ==  kbtSubKeyIn );
		GetSelSubKeyLogic()->InitSelToStr();
		pGrepPattern = GetSelSubKeyLogic()->GetSelGrepPattern();
		return slNextPat;
		}
	return slNextPat; //for compiler!
}
void CKeyLogic::InitSelToStr()
{
	if (m_indexLogic==m_strKeyLogic.GetLength())
		VERIFY(SetNextIndexLogicSimple());
}


int CKeyOutLogic::GetMinMatchedForGrep()
{
	int iMin=0x0fff;
	for (int i=0; i<m_strKeyLogic.GetLength(); i++)
		{
		// 	BOOL FStrIndex(i)-->m_piKeyMatched[i]>0 for speed!
		if (m_piKeyMatched[i]>0 && m_piKeyMatched[i]<iMin)
	 		iMin = m_piKeyMatched[i];
		}

	if (iMin==0x0fff) {	//takaso2010
		iMin=0;
	}
	return iMin;
}

void CKeyOutLogic::ScanPatternFirst(CGrepPattern *&pGrepPattern)
{
	SetNutralForSub();
	GetSelGrepPatternFlow(pGrepPattern);
}

BOOL CKeyOutLogic::FResetSXorIndexLogic(int index)
{
	ASSERT(index>=0 && index<m_strKeyLogic.GetLength());
	if (m_strSXorLogic[index]==chTrue)
		{
		m_strSXorLogic.SetAt(index, chNutral);
		return TRUE;
		}
	return FALSE;
}

ScanLogic CKeyOutLogic::ScanPatternNext(CGrepPattern *&pGrepPattern , ReturnLogic rlIn,  int &cchMatched, ReturnLogic &rlLine/*この行は追加するか？*/, ReturnLogic &rlLogic)
{
	ASSERT(m_strKeyLogic.GetLength()==m_aryKeyBlock.GetSize());
	ASSERT(m_indexLogic<m_strKeyLogic.GetLength());
	ASSERT(m_indexLogic<m_aryKeyBlock.GetSize());
	

	//一番最初だったら、CKeyOutLogicのインデックスをイニシャルセット
	ScanLogic sl;

	ASSERT(GetSelKeyBlock()->m_kbt != kbtDumy); //ダミーではない
	if (GetSelKeyBlock()->m_kbt == kbtGrep) // グレップである場合
		{
		if ((rlLine = rlIn)==rlTrue) //見つけた行は追加するかどうかは、rlInに同じである。
			{	// 見つけたならば、ｷｰﾛｼﾞｯｸｽﾄﾘﾝｸﾞに、結果をｾｯﾄ
			SetRlOne(rlIn);
			SetSelCchMatched(cchMatched);	// 現在のcchMatchedセット
			}
		cchMatched = 0;			// クリアする
		if ((rlLogic=CheckLogic())==rlFalse) //rlFalse時のみslFalseLogicで、処理を中断する
			return slFalseLogic;
		if (SetNextIndexLogicSimple())
			{
			GetSelGrepPatternFlow(pGrepPattern);
			sl = slNextBlock;
			}
		else
			sl = slEndBlock;
		}
	else
		{
RepeatKeyIn:
		ASSERT( GetSelKeyBlock()->m_kbt ==  kbtSubKeyIn );
		if (rlIn==rlNutral)
			GetSelSubKeyLogic()->SetRlOne(rlFalse); 	// ｻﾌﾞｷｰﾌﾞﾛｯｸの中のｷｰﾛｼﾞｯｸｽﾄﾘﾝｸﾞに、結果をｾｯﾄ
		else
			GetSelSubKeyLogic()->SetRlOne(rlIn); 	// ｻﾌﾞｷｰﾌﾞﾛｯｸの中のｷｰﾛｼﾞｯｸｽﾄﾘﾝｸﾞに、結果をｾｯﾄ
		if (rlIn == rlTrue)
			GetSelSubKeyLogic()->SetSelCchMatched(cchMatched);	// CKeyInLogicで、現在のcchMatchedセット
		rlLine = GetSelSubKeyLogic()->CheckLogic(); //ｻﾌﾞｷｰﾌﾞﾛｯｸの結果を取得
		if (rlLine==rlNutral && GetSelSubKeyLogic()->SetNextIndexLogic(cchMatched))
			{//ｻﾌﾞｷｰﾌﾞﾛｯｸの結果が決まっていないで、まだﾊﾟﾀｰﾝが有る場合
			sl = GetSelGrepPatternFlow(pGrepPattern);
			ASSERT(sl==slNextPat);
			if (rlIn == rlNutral)
				goto RepeatKeyIn;
			// ここでだけ、cchMatchedは加算されている
			}
		else
			{
			ASSERT(rlLine == rlTrue || rlLine == rlFalse);
			if (rlLine==rlTrue)
				{	// 見つけたならば、ｷｰﾛｼﾞｯｸｽﾄﾘﾝｸﾞに、SXorがない場合は、結果をｾｯﾄ
				BOOL fSXor = FALSE;
				char *ptok = GetSelSubKeyLogic()->GetLogicBuffer();
				char tok;
				for(; !fSXor && (tok=*ptok) != '\0'; ptok++)
					{
					if (tok==METACHARSINI[mcSXor])
						fSXor = TRUE;
					}
				if (fSXor && m_strSXorLogic[m_indexLogic]!=chTrue)
					m_strSXorLogic.SetAt(m_indexLogic, chTrue);
				else
					{
					SetRlOne(rlLine);
					SetSelCchMatched(cchMatched);	// 現在のcchMatchedセット
					}
				}
			cchMatched = 0;			// クリアする
			if ((rlLogic=CheckLogic())==rlFalse) //rlFalse時のみslFalseLogicで、処理を中断する
				return slFalseLogic;
			if (SetNextIndexLogicSimple())
				{
				GetSelGrepPatternFlow(pGrepPattern);
				sl = slNextBlock;
				}
			else
				sl = slEndBlock;
			}
		}
	return sl;
}

BOOL CKeyLogic::SetNextIndexLogicSimple()
{
	if (m_indexLogic==0)
		return FALSE;
	ASSERT(m_indexLogic>0);


	for (int i=m_indexLogic-1; i>=0; i--)
		{
		if (FStrIndex(i))
			{
			m_indexLogic = i;
			return TRUE;
			}
		}
	m_indexLogic = 0;
	return FALSE;
}

ReturnLogic CKeyOutLogic::term()
{
	ReturnLogic rl = fact();
	while(m_tok != '\0')
		{
		if (m_tok==METACHARSINI[mcAnd])
			{
			advance();
			rl = And(rl, fact());
			}
		else if (m_tok==METACHARSINI[mcOr])
			{
			advance();
			rl = Or(rl, fact());
			}
		else if (m_tok==METACHARSINI[mcXor])
			{
			advance();
			rl = Xor(rl, fact());
			}
		else
			break;
		}
	return rl;
}

ReturnLogic CKeyOutLogic::fact()
{
	ReturnLogic rl;

	if (m_tok==METACHARSINI[mcBlaketL])
		{
		advance();
		rl = term();
		eat(METACHARSINI[mcBlaketR]);
		}
	else if (m_tok==METACHARSINI[mcNot])
		{
		advance();
		rl = Not(fact());
		}
	else if (m_tok=='\0')
		{
		TrowMacroException();
		}
	else
		{
		rl = RLFROMCH(m_tok);
		if (rl!=rlFalse && rl!=rlTrue && rl!=rlNutral)
			{
			TrowMacroException();
			}
/*****	if (rl == rlNutral)
			{
			switch(rl = CheckSubLogic())
				{
				case rlErr:
					TrowMacroException();
					break;
				case rlTrue:
					*(m_ptok-1) = CHFROMRL(rl);
					break;
				}
			}
***************/
		advance();
		}
	return rl;
}
ReturnLogic CKeyOutLogic::Xor(ReturnLogic rlL, ReturnLogic rlR)
{
	if (rlL == rlNutral || rlR == rlNutral)
		return rlNutral;
	return (ReturnLogic)(rlL ^ rlR);
}
#ifdef _DEBUG
void CKeyOutLogic::Dump(CDumpContext& dc) const
{
	dc << "\nCKeyOutLogic";
	CKeyLogic::Dump(dc);
}
#endif //_DEBUG
