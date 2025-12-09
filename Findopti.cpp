/*    PortTool v2.2     FINDOPTI.CPP          */

//findopti.cpp : インプリメンテーション ファイル
//
#include "stdafx.h"
//#include "stdlib.h"
#include "Fdiver.h"
#include "findopti.h"
#include "..\mdfc\dfile.h"
#include "..\mdfc\ch.h"
#include "version.h"
#include "dfilearc.h"
#include "profile.h"

extern CFindOption *vpFindOption;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BMP_START_ADJUST	(5)
#define BMP_HIGHT	16
#define BMP_WIDTH_ADJUST	5/4
#define BMP_WIDTH	(BMP_START_ADJUST+BMP_HIGHT*BMP_WIDTH_ADJUST)

/////////////////////////////////////////////////////////////////////////////
// CFindOption ダイアログ

CFindOption::CFindOption()
{
//	ReadWriteProfile(TRUE);
//	if (m_lReadSize<MIN_READBUFSIZE || m_lReadSize>MAX_READBUFSIZE)
//		m_lReadSize = DEF_READBUFSIZE;
//	m_iDspListColum = DEF_DSPCOLUM;
//	if (m_optDispNum<1 || m_optDispNum>2)
//		m_optDispNum=1;
}

// プロファイルを読み書きする。
void CFindOption::ReadWriteProfile(BOOL fRead)
{
	int i;
	if (fRead)
		{
		m_fSound = theProfile.ReadInt("FindOption", "fSound", 1);		// default = Sound On
		m_fToTopWin = theProfile.ReadInt("FindOption", "fToTopWin", 1);	// default = To top window
		m_fIcon = theProfile.ReadInt("FindOption", "fIcon", 0);	// default = Not Icon
		m_fMetaHelp = theProfile.ReadInt("FindOption", "fMetaHelp", 1);	// default = yes
#ifdef WIN32
		m_fNoErrDsp = theProfile.ReadInt("FindOption", "fNoErrDsp", 1);	// default = yes
#else
		m_fNoErrDsp = theProfile.ReadInt("FindOption", "fNoErrDsp", 0);	// default = not
#endif //WIN32
		m_lReadSize = theProfile.ReadInt("FindOption", "iReadSize", 0) * 1024;
		CString cstrFTE="FindFileEnt";
		for (i=0; TRUE; i++)
			{
			_itoa_s(i, vz, sizeof(vz),10);
			CString cstr = theProfile.ReadString("FindOption", cstrFTE + vz , NULL);
			if (cstr.IsEmpty())
				break;
			m_aryStrFiles.Add(cstr.GetBuffer(0));
			}
#ifdef _JPN
		if (m_aryStrFiles.GetSize()==0)
			{
			m_aryStrFiles.Add("*.txt;*.ini");
			m_aryStrFiles.Add("*.wri;*.doc");
			m_aryStrFiles.Add("*.h;*.c;*.cpp");
			}
		for (i=0; i<m_aryStrFiles.GetSize(); i++) {
			if (m_aryStrFiles.GetAt(i)=="*.html;*.htm;*.shtml")
				break;
		}
		if (i>=m_aryStrFiles.GetSize())
			m_aryStrFiles.Add("*.html;*.htm;*.shtml");
#endif //_JPN
		cstrFTE="ExeParam";
		for (i=0; TRUE; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			CString cstr = theProfile.ReadString("FindOption", cstrFTE + vz , NULL);
			if (cstr.IsEmpty())
				break;
			m_aryStrExtnsions.Add(cstr.GetBuffer(0));
			}
		cstrFTE="KickApps";
		for (i=0; TRUE; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			CString cstr = theProfile.ReadString("FindOption", cstrFTE + vz , NULL);
			if (cstr.IsEmpty())
				break;
			m_aryStrKickApps.Add(cstr.GetBuffer(0));
			}
#ifdef _JPN
		if (GetExeParam("MINT.EXE").IsEmpty())
			m_aryStrExtnsions.Add("MINT.EXE /JB");
		if (GetExeParam("HIDEMARU.EXE").IsEmpty())
			m_aryStrExtnsions.Add("HIDEMARU.EXE /J");
		if (GetExeParam("WZEDITOR.EXE").IsEmpty())
			m_aryStrExtnsions.Add("WZEDITOR.EXE /J");
		if (GetExeParam("EMEDITOR.EXE").IsEmpty())
			m_aryStrExtnsions.Add("EMEDITOR.EXE /l ");
		if (GetExeParam("SAKURA.EXE").IsEmpty())
			m_aryStrExtnsions.Add("SAKURA.EXE -Y=");
		if (GetExeParam("MIW.EXE").IsEmpty())
			m_aryStrExtnsions.Add("MIW.EXE /+");//m_aryStrExtnsions.Add("MIW.EXE \\F(\\L)");
		if (GetExeParam("MKEDITOR.EXE").IsEmpty())
			m_aryStrExtnsions.Add("MKEDITOR.EXE /JL ");
		if (GetExeParam("K2EDITOR.EXE").IsEmpty())
			m_aryStrExtnsions.Add("K2EDITOR.EXE /J");
		if (GetExeParam("MERY.EXE").IsEmpty())
			m_aryStrExtnsions.Add("MERY.EXE /l ");
		if (GetExeParam("TERAPAD.EXE").IsEmpty())
			m_aryStrExtnsions.Add("TERAPAD.EXE /jl=");
		
#endif //_JPN
		m_strEditer = theProfile.ReadString("FindOption", "Editor" , NULL);
		if (m_strEditer=="")
			m_strEditer = theProfile.ReadString("FindOption", "Editer" , NULL);
		m_bCRIsNewLine = theProfile.ReadInt("FindOption", "bCRIsNewLine" , 1);
		m_fDir = theProfile.ReadInt("DispOption", "fDir", 1);
		m_fFile  = theProfile.ReadInt("DispOption", "fFile", 1);
		m_bKftTransFileView = theProfile.ReadInt("FindOption", "fKftTransFileView", 1);

		m_strNameHeader = _T("Name");
		m_strSizeHeader = _T("Size");
		m_strDateHeader = _T("Date");
		m_strAttrHeader = _T("Attr");
		m_strPathHeader = _T("Path");
		m_strLineHeader = _T("Line");
		m_strTextHeader = _T("Text");

/*		m_strNameHeader = _T("名前");// _T("Name");
		m_strSizeHeader = _T("サイズ");//_T("Size");
		m_strDateHeader = _T("更新日付");//_T("Date");
		m_strAttrHeader = _T("属性");//_T("Attr");
		m_strPathHeader = _T("パス");//_T("Path");
		m_strLineHeader = _T("行番号");//_T("Line");
		m_strTextHeader = _T("テキスト");//_T("Text");
*/
		m_cxDown  = theProfile.ReadInt("DispOption", "cxDown", BMP_WIDTH);
		m_cxTreePath  = theProfile.ReadInt("DispOption", "cxTreePath", BMP_WIDTH);
		m_cxTreeFile  = theProfile.ReadInt("DispOption", "cxTreeFile", BMP_WIDTH+BMP_HIGHT/2);
		m_cxTreeLine  = theProfile.ReadInt("DispOption", "cxTreeLine", BMP_WIDTH+BMP_HIGHT*3/2);

		m_cxListLine  = theProfile.ReadInt("DispOption", "cxListLine", BMP_WIDTH);

		m_cxPathPath  = theProfile.ReadInt("DispOption", "cxPathPath", BMP_WIDTH);
		m_cxPathLine  = theProfile.ReadInt("DispOption", "cxPathLine", BMP_WIDTH+BMP_HIGHT);

		m_cxFileFile  = theProfile.ReadInt("DispOption", "cxFileFile", BMP_WIDTH);
		m_cxFileLine  = theProfile.ReadInt("DispOption", "cxFileLine", BMP_WIDTH+BMP_HIGHT);

		m_cxName  = theProfile.ReadInt("DispOption", "cxName", BMP_WIDTH*7);
		m_cxSize = theProfile.ReadInt("DispOption", "cxSize", BMP_WIDTH*3);
		m_cxDate = theProfile.ReadInt("DispOption", "cxDate", BMP_WIDTH*4);
		m_cxAttr = theProfile.ReadInt("DispOption", "cxAttr", BMP_WIDTH*2);
		m_cxPath = theProfile.ReadInt("DispOption", "cxPath", BMP_WIDTH*5);
		m_cxLine = theProfile.ReadInt("DispOption", "cxLine", BMP_WIDTH*3/2);

		m_lfHeight = theProfile.ReadInt("DispOption", "lfHeight", 13);
		m_lfCharSet = theProfile.ReadInt("DispOption", "lfCharSet", SHIFTJIS_CHARSET);
		m_lfPitchAndFamily = theProfile.ReadInt("DispOption", "lfPitchAndFamily", 50);
		m_lfFaceName = theProfile.ReadString("DispOption", "lfFaceName", _T("ＭＳ Ｐゴシック"));
		m_strBkColor = theProfile.ReadString("DispOption", "bkColor", "255,255,255");//"192,192,192"
		m_strFrColor = theProfile.ReadString("DispOption", "frColor", "0,0,0");
		m_ratioBetweenLine = theProfile.ReadInt("DispOption", "ratioBetweenLine", 30);

		m_optDispNum = theProfile.ReadInt("FindOption", "OptDispNum", 1);	// default = Line number display
		m_fDispDoc = theProfile.ReadInt("FindOption", "fDispDoc", 1);	// default = Document display
		m_fDragServer = theProfile.ReadInt("FindOption", "fDragServer", 1);
		m_iMaxLines = theProfile.ReadInt("FindOption", "iMaxLines", DEF_DSPLINES);
		m_fDefTagAuto = theProfile.ReadInt("FindOption", "fDefTagAuto", 1);
		//m_optTime = theProfile.ReadInt("FindOption", "OptTime", 0);
		//CString strTime;
		//strTime = theProfile.ReadString("FindOption", "FromTime", NULL);
		//m_tFromTime = atol(strTime.GetBuffer(0));
		//strTime = theProfile.ReadString("FindOption", "GoTime", NULL);
		//m_tGoTime = atol(strTime.GetBuffer(0));

		m_fFTLha = theProfile.ReadInt("FindOption", "fFTLha", 1);
		m_fFTZip = theProfile.ReadInt("FindOption", "fFTZip", 1);
		m_fFTArj = theProfile.ReadInt("FindOption", "fFTArj", 1);
		m_fFTTar = theProfile.ReadInt("FindOption", "fFTTar", 1);
		m_fFTCab = theProfile.ReadInt("FindOption", "fFTCab", 1);
		m_fFTRar = theProfile.ReadInt("FindOption", "fFTRar", 1);
		//EntryPoint Arc
		m_fFTKft = theProfile.ReadInt("FindOption", "fFTKft", 1);
		m_fFTxdoc = theProfile.ReadInt("FindOption", "fFTxdoc", 1);
		m_optFTRemain = theProfile.ReadInt("FindOption", "optFTRemain", 0);
		m_strFTWorkPath = theProfile.ReadString("FindOption", "strFTWorkPath" , NULL);
		if (m_strFTWorkPath.IsEmpty() || !CheckPath(m_strFTWorkPath.GetBuffer(0)))
			{
			CDFile cdfile;
			cdfile.SetWinTmpFName("FDV");
			if (!cdfile.GetString()->IsEmpty())
				{
				//cdfile.Remove();
				m_strFTWorkPath = cdfile.GetPath();
				}
			else
				m_strFTWorkPath = ((CFdiverApp *)AfxGetApp())->PGetDefaltPath();
			RemoveLastBackSlash(&m_strFTWorkPath);
			}
		ASSERT(CheckPath(m_strFTWorkPath.GetBuffer(0)));
		//extern CDFileSpec vExtraFileSpec;//ワイルドカード指定時の除外ファイルスペック
		vExtraFileSpec = theProfile.ReadString("FindOption", "strExtraFileSpec" , "*.gif;*.jpg;*.jpeg;*.png;*.bmp;*.class");

		//General
		m_fTopMost = theProfile.ReadInt("General", "fAlwaysTop", 0);	// default = not always Top Must window
		m_left = theProfile.ReadInt("General", "left", (GetSystemMetrics(SM_CXSCREEN)-DEF_WIDTH) / 2);
		if (m_left >= GetSystemMetrics(SM_CXSCREEN))
			m_left = (GetSystemMetrics(SM_CXSCREEN)-DEF_WIDTH) / 2;
		m_top = theProfile.ReadInt("General", "top", (GetSystemMetrics(SM_CYSCREEN)-DEF_HIGHT) / 2);
		if (m_top >= GetSystemMetrics(SM_CYSCREEN))
			m_top = (GetSystemMetrics(SM_CYSCREEN)-DEF_HIGHT) / 2;
		m_width = theProfile.ReadInt("General", "width", DEF_WIDTH);
		m_hight = theProfile.ReadInt("General", "hight", DEF_HIGHT);
		m_bToolBar = theProfile.ReadInt("General", "ToolBar", TRUE);
		m_bHeaderBar = theProfile.ReadInt("General", "HeaderBar", TRUE);
		m_bStatusBar = theProfile.ReadInt("General", "StatusBar", TRUE);

		
		if (m_lReadSize<MIN_READBUFSIZE || m_lReadSize>MAX_READBUFSIZE)
			m_lReadSize = DEF_READBUFSIZE;
		m_iDspListColum = DEF_DSPCOLUM;
		if (m_optDispNum<1 || m_optDispNum>2)
			m_optDispNum=1;
		}
	else
		{
		theProfile.WriteInt("FindOption", "fSound", m_fSound);
		theProfile.WriteInt("FindOption", "fToTopWin", m_fToTopWin);
		theProfile.WriteInt("FindOption", "fIcon", m_fIcon);
		theProfile.WriteInt("FindOption", "fMetaHelp", m_fMetaHelp);
		theProfile.WriteInt("FindOption", "fNoErrDsp", m_fNoErrDsp);
		theProfile.WriteInt("FindOption", "iReadSize", (int)(m_lReadSize/1024) );
		CString cstrFTE="FindFileEnt";
		int i;
		for (i=0; i<m_aryStrFiles.GetSize();i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			theProfile.WriteString("FindOption", cstrFTE+vz, m_aryStrFiles[i]);
			}
		_itoa_s(i, vz, sizeof(vz), 10);
		theProfile.WriteString("FindOption", cstrFTE+vz, "");
		cstrFTE="ExeParam";
		for (i=0; i<m_aryStrExtnsions.GetSize();i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			theProfile.WriteString("FindOption", cstrFTE+vz, m_aryStrExtnsions[i]);
			}
		_itoa_s(i, vz, sizeof(vz), 10);
		theProfile.WriteString("FindOption", cstrFTE+vz, "");
		cstrFTE="KickApps";
		for (i=0; i<m_aryStrKickApps.GetSize();i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			theProfile.WriteString("FindOption", cstrFTE+vz, m_aryStrKickApps[i]);
			}
		_itoa_s(i, vz, sizeof(vz), 10);
		theProfile.WriteString("FindOption", cstrFTE+vz, "");

		theProfile.WriteString("FindOption", "Editor", m_strEditer);
		theProfile.WriteString("FindOption", "Editer", "");
		theProfile.WriteInt("FindOption", "bCRIsNewLine" , m_bCRIsNewLine);
		theProfile.WriteInt("FindOption", "fDir", m_fDir);
		theProfile.WriteInt("FindOption", "fFile", m_fFile);
		theProfile.WriteInt("FindOption", "fKftTransFileView", m_bKftTransFileView);

		theProfile.WriteInt("DispOption", "cxDown", m_cxDown);
		theProfile.WriteInt("DispOption", "cxTreePath", m_cxTreePath);
		theProfile.WriteInt("DispOption", "cxTreeFile", m_cxTreeFile);
		theProfile.WriteInt("DispOption", "cxTreeLine", m_cxTreeLine);

		theProfile.WriteInt("DispOption", "cxListLine", m_cxListLine);

		theProfile.WriteInt("DispOption", "cxPathPath", m_cxPathPath);
		theProfile.WriteInt("DispOption", "cxPathLine", m_cxPathLine);

		theProfile.WriteInt("DispOption", "cxFileFile", m_cxFileFile);
		theProfile.WriteInt("DispOption", "cxFileLine", m_cxFileLine);

		theProfile.WriteInt("DispOption", "cxName", m_cxName);
		theProfile.WriteInt("DispOption", "cxSize", m_cxSize);
		theProfile.WriteInt("DispOption", "cxDate", m_cxDate);
		theProfile.WriteInt("DispOption", "cxAttr", m_cxAttr);
		theProfile.WriteInt("DispOption", "cxPath", m_cxPath);
		theProfile.WriteInt("DispOption", "cxLine", m_cxLine);

		theProfile.WriteInt("DispOption", "lfHeight", m_lfHeight);
		theProfile.WriteInt("DispOption", "lfCharSet", m_lfCharSet);
		theProfile.WriteInt("DispOption", "lfPitchAndFamily", m_lfPitchAndFamily);
		theProfile.WriteString("DispOption", "lfFaceName", m_lfFaceName);
		theProfile.WriteString("DispOption", "bkColor", m_strBkColor);
		theProfile.WriteString("DispOption", "frColor", m_strFrColor);
		theProfile.WriteInt("DispOption", "ratioBetweenLine", m_ratioBetweenLine);


		theProfile.WriteInt("FindOption", "OptDispNum", m_optDispNum);
		theProfile.WriteInt("FindOption", "fDispDoc", m_fDispDoc);
		theProfile.WriteInt("FindOption", "fDragServer", m_fDragServer);
		theProfile.WriteInt("FindOption", "iMaxLines", m_iMaxLines);
		theProfile.WriteInt("FindOption", "fDefTagAuto", m_fDefTagAuto);
		//theProfile.WriteInt("FindOption", "OptTime", m_optTime);
		//char str[256];
		//_ltoa(m_tFromTime, str, 10); 
		//theProfile.WriteString("FindOption", "FromTime", str);
		//_ltoa(m_tGoTime, str, 10); 
		//theProfile.WriteString("FindOption", "GoTime", str);
		theProfile.WriteInt("FindOption", "fFTLha", m_fFTLha);
		theProfile.WriteInt("FindOption", "fFTZip", m_fFTZip);
		theProfile.WriteInt("FindOption", "fFTArj", m_fFTArj);
		theProfile.WriteInt("FindOption", "fFTTar", m_fFTTar);
		theProfile.WriteInt("FindOption", "fFTCab", m_fFTCab);
		theProfile.WriteInt("FindOption", "fFTRar", m_fFTRar);
		//EntryPoint Arc
		theProfile.WriteInt("FindOption", "fFTKft", m_fFTKft);
		theProfile.WriteInt("FindOption", "fFTxdoc", m_fFTxdoc);
		theProfile.WriteInt("FindOption", "optFTRemain", m_optFTRemain);
		theProfile.WriteString("FindOption", "strFTWorkPath", m_strFTWorkPath);
		theProfile.WriteString("FindOption", "strExtraFileSpec" , vExtraFileSpec);

		//General
		theProfile.WriteInt("General", "fAlwaysTop", m_fTopMost);
		theProfile.WriteInt("General", "left", m_left);
		theProfile.WriteInt("General", "top", m_top);
		theProfile.WriteInt("General", "width", m_width);
		theProfile.WriteInt("General", "hight", m_hight);
		theProfile.WriteInt("General", "ToolBar", m_bToolBar);
		theProfile.WriteInt("General", "HeaderBar", m_bHeaderBar);
		theProfile.WriteInt("General", "StatusBar", m_bStatusBar);
		}
}

void CFindOption::ResizeHeaderCx(int iZoom)
{
	//m_cxDown = div10plus(m_cxDown, iZoom, BMP_WIDTH);
	//m_cxTreePath = div10plus(m_cxTreePath, iZoom, BMP_WIDTH);
	//m_cxTreeFile = div10plus(m_cxTreeFile, iZoom, BMP_WIDTH+BMP_HIGHT/2);
	//m_cxTreeLine = div10plus(m_cxTreeLine, iZoom, BMP_WIDTH+BMP_HIGHT*3/2);
	//m_cxListLine = div10plus(m_cxListLine, iZoom, BMP_WIDTH);
	//m_cxPathPath = div10plus(m_cxPathPath, iZoom, BMP_WIDTH);
	//m_cxPathLine = div10plus(m_cxPathLine, iZoom, BMP_WIDTH+BMP_HIGHT);
	//m_cxFileFile = div10plus(m_cxFileFile, iZoom, BMP_WIDTH);
	//m_cxFileLine = div10plus(m_cxFileLine, iZoom, BMP_WIDTH+BMP_HIGHT);
	m_cxName = div10plus(m_cxName, iZoom, BMP_WIDTH*7);
	m_cxSize = div10plus(m_cxSize, iZoom, BMP_WIDTH*3);
	m_cxDate = div10plus(m_cxDate, iZoom, BMP_WIDTH*4);
	m_cxAttr = div10plus(m_cxAttr, iZoom, BMP_WIDTH*2);
	m_cxPath = div10plus(m_cxPath, iZoom, BMP_WIDTH*5);
	m_cxLine = div10plus(m_cxLine, iZoom, BMP_WIDTH*3/2);

}
int CFindOption::div10plus(int cxy, int iZoom, int default_cxy)
{
	cxy = cxy<1 ? 1:cxy;

	if (iZoom>0) //zoom in
		cxy += max((cxy*default_cxy)/(10*BMP_WIDTH*14),1);
	else {
		if (cxy>default_cxy)
			cxy -= max((cxy*default_cxy)/(10*BMP_WIDTH*14),1);
	}
	return cxy;
}


CString CFindOption::GetExeParam(char *szProg)
{
// szProg は、upper case でないといけない！！！！
	CDString cdstrProg = szProg;
	cdstrProg.MakeUpper();
	COFFSET c;

	if ((c=cdstrProg.Find((WORD)chDot))!=(COFFSET)(-1))
		cdstrProg = cdstrProg.Left(c);
	CDFile cdFile;
	CDString cdstr;
	for (int i=0; i<m_aryStrExtnsions.GetSize();i++)
		{
		_itoa_s(i, vz, sizeof(vz), 10);
		cdstr = m_aryStrExtnsions[i];

		if ((c=cdstr.Find((WORD)chSpace))!=(COFFSET)(-1))
			{
			cdFile = cdstr.Left(c);
			cdstr = cdFile.GetName();
			cdstr.MakeUpper();
			if (cdstr.ComparePrefix(cdstrProg.GetBuffer(0))==0)
				{
				cdstr = m_aryStrExtnsions[i];
				return cdstr.Mid(c);
				}
			}
		}
	return CDString();
}

BOOL CFindOption::GetCheckExtType(EXT_TYPE ext)
{
	switch(ext)
		{
		case EXT_LZH:
			return m_fFTLha;
		case EXT_ZIP:
			return m_fFTZip;
		case EXT_ARJ:
			return m_fFTArj;
		case EXT_TAR:
			return m_fFTTar;
		case EXT_CAB:
			return m_fFTCab;
		case EXT_RAR:
			return m_fFTRar;
		//EntryPoint Arc
		case EXT_KFT:
			return m_fFTKft && vpFindOption->m_bKftTransFileView;
		case EXT_XDOC:
			return m_fFTxdoc;
		default:
			ASSERT(FALSE);
		}
	return FALSE;
}
