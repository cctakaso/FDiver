#include "stdafx.h"
#include "fdiver.h"
#include "mdglibs.h"
#include "findopti.h"
#include "findlist.h"
#include "findlog.h"
extern CFindList *vpFindList;		// ŒŸõŒ‹‰ÊØ½Ä‚Ö‚ÌÎß²İÀ
extern CFindOption *vpFindOption;		// µÌß¼®İµÌŞ¼Şª¸Ä
/////////////////////////////////////////////////////////////////////////////
// MD. Global Function Library 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char vz[__MAX_PATH];		//==260

//Icons
//MB_ICONINFORMATION
//MB_ICONSTOP
//MB_ICONQUESTION
//MB_ICONEXCLAMATION
//Buttons
//MB_OK
//MB_OKCANCEL
//MB_YESNO
//MB_YESNOCANCEL
//MB_ABORTRETRYIGNORE
int BeepMessage(UINT uiMsg, UINT msgStyle/* = MB_ICONINFORMATION | MB_OK*/,  BOOL fBeep/* = TRUE*/, BOOL fMsg/*=TRUE*/, BOOL fLog/*=FALSE*/)
{
	CString cstr;
	cstr.LoadString(uiMsg);

	if (fLog)
		vpFindList->m_FindLog.AddLogLine(cstr.GetBuffer(0));
	if (fMsg)
		{
		if (fBeep)
			::MessageBeep(MB_ICONINFORMATION);
		return AfxMessageBox(cstr.GetBuffer(0), msgStyle);
		}

	return IDOK;
}
int Message(UINT uiMsg, UINT msgStyle/* = MB_ICONINFORMATION | MB_OK*/)
{
	return BeepMessage(uiMsg, msgStyle,  FALSE);
}

int BeepMessageLog(UINT uiMsg, UINT msgStyle/* = MB_ICONINFORMATION | MB_OK*/,  BOOL fBeep/* = TRUE*/)
{
	return BeepMessage(uiMsg, msgStyle, fBeep, !((CFdiverApp *)AfxGetApp())->GetFindDoingFlg() || !vpFindOption->m_fNoErrDsp, ((CFdiverApp *)AfxGetApp())->GetFindDoingFlg());
}

CString GetPartString(CString &strSrc, TCHAR ch)
{
	CString str,strT;
	try
	{
	while(TRUE)
		{
		int count = strSrc.Find(ch);
		if (count==-1)
			{
			str = strSrc;
			strSrc.Empty();
			break;
			}
		else if (count==0) 
			{
			strT = strSrc.Mid(1);
			strSrc = strT;
			continue;
			}
		else
			{
			str = strSrc.Left(count);			
			strT = strSrc.Mid(count+1);
			strSrc = strT;
			break;
			}
		}
	}
	catch(CException* e)
	{
		e->Delete();
	}
	return str;
}

CString GetPartString(CString &strSrc, char *sz)
{
	CString str,strT;
	if (sz==NULL || *sz=='\0')
		return str;
	int len=strlen(sz);
	try
	{
	while(TRUE)
		{
		int count = strSrc.FindOneOf(sz);
		if (count==-1)
			{
			str = strSrc;
			strSrc.Empty();
			break;
			}
		else if (count==0) 
			{
			strT = strSrc.Mid(len);
			strSrc = strT;
			continue;
			}
		else
			{
			str = strSrc.Left(count);			
			strT = strSrc.Mid(count+len);
			strSrc = strT;
			break;
			}
		}
	}
	catch(CException* e)
	{
		e->Delete();
	}
	return str;
}
