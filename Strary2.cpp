/*    PortTool v2.2     strary2.cpp          */

#include "stdafx.h"
#include "strary2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CStringArray2& CStringArray2::operator = ( CStringArray2 &src )
{
	RemoveAll();
	for (int i=0; i<src.GetSize(); i++)
		{
		Add(src[i].GetBuffer(0));
		}
	return *this;
}
