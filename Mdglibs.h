#ifndef __MDGLIBS_H_
#define __MDGLIBS_H_
/////////////////////////////////////////////////////////////////////////////
// MD. Global Function Library 

#include "..\MDFC\Dfile.h"
extern char vz[__MAX_PATH];

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
int BeepMessage(UINT uiMsg, UINT msgStyle = (MB_ICONINFORMATION | MB_OK), BOOL fBeep= TRUE, BOOL fMsg = TRUE, BOOL fLog=FALSE);
int Message(UINT uiMsg, UINT msgStyle = (MB_ICONINFORMATION | MB_OK));
int BeepMessageLog(UINT uiMsg, UINT msgStyle = (MB_ICONINFORMATION | MB_OK), BOOL fBeep= TRUE);
CString GetPartString(CString &strSrc, TCHAR ch);
CString GetPartString(CString &strSrc, char *sz);
#endif //!__MDGLIBS_H_
