/*    PortTool v2.2     strspec.cpp          */

//strspec.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
#include "strspec.h"
#include "profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CStrSpec ダイアログ

CStrSpec::CStrSpec()
{
	ReadWriteProfile(TRUE);
}

// プロファイルを読み書きする。
void CStrSpec::ReadWriteProfile(BOOL fRead)
{
	CString CstrEntry;
	if (fRead)
		{
		CString cstr;
		m_iSel = theProfile.ReadInt("StrSpec", "FindStrSel", -1);
		if (m_iSel == -1)
			{
			m_iSel = 0;
			CString cstr;
			cstr.LoadString(IDS_STRSPEC_ENT1);
			m_aryStr.Add(cstr.GetBuffer(0));
#ifdef _JPN
			m_aryAttr.Add("110000000");
#else
			ASSERT(FALSE);
#endif
			cstr.LoadString(IDS_STRSPEC_ENT2);
			m_aryStr.Add(cstr.GetBuffer(0));
#ifdef _JPN
			m_aryAttr.Add("111001010");
#else
			ASSERT(FALSE);
#endif
			}
		else
			{
			CstrEntry="FindStrEnt";
			for (int i=0; TRUE; i++)
				{
				_itoa_s(i, vz, sizeof(vz), 10);
				cstr = theProfile.ReadString("StrSpec", CstrEntry + vz , NULL);
				if (cstr.IsEmpty())
					break;
				m_aryStr.Add(cstr.GetBuffer(0));
				}
			CstrEntry="FindStrAttr";
			for (int i=0; TRUE; i++)
				{
				_itoa_s(i, vz, sizeof(vz), 10);
				cstr = theProfile.ReadString("StrSpec", CstrEntry + vz , NULL);
				if (cstr.IsEmpty())
					break;
				m_aryAttr.Add(cstr.GetBuffer(0));
				}
			}
		}
	else
		{
		int i;
		theProfile.WriteInt("StrSpec", "FindStrSel", m_iSel);
		CstrEntry="FindStrEnt";
		for (i=0; i<m_aryStr.GetSize();i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			theProfile.WriteString("StrSpec", CstrEntry+vz, m_aryStr[i]);
			}
		_itoa_s(i, vz, sizeof(vz), 10);
		theProfile.WriteString("StrSpec", CstrEntry+vz, "");
		CstrEntry="FindStrAttr";
		for (i=0; i<m_aryAttr.GetSize();i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			theProfile.WriteString("StrSpec", CstrEntry+vz, m_aryAttr[i]);
			}
		_itoa_s(i, vz, sizeof(vz), 10);
		theProfile.WriteString("StrSpec", CstrEntry+vz, "");
		}
}

// 現在のアトリビュートデータを取得する
STRSPEC_ATTR *CStrSpec::GetSelAttrData()
{
	ASSERT(m_iSel>=0 && m_iSel<m_aryAttr.GetSize());
	AttrDataUpdate(&m_aryAttr[m_iSel], &m_attrData);
	return &m_attrData;
}



//グローバル・ファンクションライブラリ
void AttrDataIni(STRSPEC_ATTR *pAttrData)
{
	pAttrData->m_chPrefix = STRSPEC_ATTR_PREF_DEF;
	pAttrData->m_fCase = FALSE;
	pAttrData->m_fBytes = FALSE;
	pAttrData->m_fKata = FALSE;
	//pAttrData->m_fUmura = FALSE;
	pAttrData->m_fMatchWholeWord = FALSE;
	pAttrData->m_fSpace = FALSE;
	pAttrData->m_fTab = FALSE;
	pAttrData->m_fLF = FALSE;
	pAttrData->m_fNoBreak = FALSE;
	pAttrData->m_strOthers = "";
}
void AttrDataRetrive(CString *pStrAttr, STRSPEC_ATTR *pAttrData)
{
	*pStrAttr = pAttrData->m_chPrefix;
	*pStrAttr += pAttrData->m_fCase ? '1':'0';
	*pStrAttr += pAttrData->m_fBytes ? '1':'0';
	*pStrAttr += pAttrData->m_fKata ? '1':'0';
//	*pStrAttr += pAttrData->m_fUmura ? '1':'0';
	*pStrAttr += pAttrData->m_fMatchWholeWord ? '1':'0';
	*pStrAttr += pAttrData->m_fSpace ? '1':'0';
	*pStrAttr += pAttrData->m_fTab ? '1':'0';
	*pStrAttr += pAttrData->m_fLF ? '1':'0';
	*pStrAttr += pAttrData->m_fNoBreak ? '1':'0';
	*pStrAttr += pAttrData->m_strOthers;
}

void AttrDataUpdate(CString *pStrAttr, STRSPEC_ATTR *pAttrData)
{
	if (pStrAttr->GetLength()>=9)
		{
		pAttrData->m_chPrefix = (pStrAttr->GetAt(0));
		pAttrData->m_fCase = (pStrAttr->GetAt(1)=='1');
		pAttrData->m_fBytes = (pStrAttr->GetAt(2)=='1');
		pAttrData->m_fKata = (pStrAttr->GetAt(3)=='1');
//		pAttrData->m_fUmura = (pStrAttr->GetAt(4)=='1');
		pAttrData->m_fMatchWholeWord = (pStrAttr->GetAt(4)=='1');
		pAttrData->m_fSpace = (pStrAttr->GetAt(5)=='1');
		pAttrData->m_fTab = (pStrAttr->GetAt(6)=='1');
		pAttrData->m_fLF = (pStrAttr->GetAt(7)=='1');
		pAttrData->m_fNoBreak = (pStrAttr->GetAt(8)=='1');
		if (pStrAttr->GetLength()>9)
			pAttrData->m_strOthers = pStrAttr->Mid(9);
		}
}


