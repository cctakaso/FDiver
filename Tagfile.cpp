/*    PortTool v2.2     tagfile.cpp          */

// tagfile.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#ifdef _TAG //All this file
#include "fdiver.h"
#include "tagfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTagFile


/////////////////////////////////////////////////////////////////////////////
// CTagFile コマンド
void CTagFile::SetDefaultTagFile()
{
	SetPath(((CFdiverApp *)AfxGetApp())->PGetDefaltPath());
	SetName(DEFAULT_TAG_FILENAME);
//	m_cDStrFName.MakeLower();
}
#endif //_TAG