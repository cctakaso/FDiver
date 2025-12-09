/*    PortTool v2.2     DFILEEXP.CPP          */

#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <exception>
#include <io.h>
#include <iostream>
#include <fstream>
#include <locale.h>

#include "fdiver.h"
#include "..\mdfc\ch.h"
#include "mainfrm.h"
#include "findopti.h"
#include "dfilearc.h"
#include "findlist.h"
#include "CDxdoc2txt.h"

using namespace std ;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFindOption *vpFindOption;
extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ

UINT WM_ARCEXTRACT_MSG=NULL;
//#define NEED_ZIP32J_IZIP32J //UNZIP32.DLL　ZIP32J.DLL　IZIP32J.DLL

char *szDllFileName[] = {
#ifdef WIN32
	"UNLHA32.DLL",
	#ifdef NEED_ZIP32J_IZIP32J
		"ZIP32J.DLL",//"UNZIP32.DLL",
	#else
		"UNZIP32.DLL",
	#endif
	"UNARJ32J.DLL",
	"TAR32.DLL",
	"CAB32.DLL",
	"UNRAR32.DLL",
	//EntryPoint Arc
	"UNKANJ.DLL",
	"xdoc2txt.exe", //takaso2010
#else
	"UNLHA.DUM",//"UNLHA.DLL",
	"ZIP32J.DLL",//"UNZIP32.DLL",
	"UNARJ.DUM",//"UNARJ.DLL",
	"UNKANJ32.DUM",
#endif
	};
char *szArcFuncLst[][14] = {
//	"UNLHA32.DLL",
	{"UnlhaGetVersion",
	"UnlhaSetBackGroundMode",
	"UnlhaSetCursorMode",
	"Unlha",
	"UnlhaCheckArchive",
	"UnlhaOpenArchive",
	"UnlhaCloseArchive",
	"UnlhaFindFirst",
	"UnlhaFindNext",
	"UnlhaSetOwnerWindow",
	"UnlhaClearOwnerWindow",
	"UnlhaGetRunning",
	NULL,
	NULL,
	},
//	"ZIP32J.DLL",//"UNZIP32.DLL",
	{
#ifdef NEED_ZIP32J_IZIP32J
	"ZipGetVersion",
#else
	"UnZipGetVersion",
#endif
	"UnZipSetBackGroundMode",
	"UnZipSetCursorMode",
	"UnZip",
	"UnZipCheckArchive",
	"UnZipOpenArchive",
	"UnZipCloseArchive",
	"UnZipFindFirst",
	"UnZipFindNext",
	"UnZipSetOwnerWindow",
	"UnZipClearOwnerWindow",
#ifdef NEED_ZIP32J_IZIP32J
	"ZipGetRunning",
#else
	"UnZipGetRunning",
#endif
	NULL,
	NULL,
	},
//	"UNARJ32J.DLL",
	{"UnarjGetVersion",
	"UnarjSetBackGroundMode",
	"UnarjSetCursorMode",
	"Unarj",
	"UnarjCheckArchive",
	"UnarjOpenArchive",
	"UnarjCloseArchive",
	"UnarjFindFirst",
	"UnarjFindNext",
	"UnarjSetOwnerWindow",
	"UnarjClearOwnerWindow",
	"UnarjGetRunning",
	NULL,
	NULL,
	},
//	"TAR32.DLL",
	{"TarGetVersion",
	"TarSetBackGroundMode",
	"TarSetCursorMode",
	"Tar",
	"TarCheckArchive",
	"TarOpenArchive",
	"TarCloseArchive",
	"TarFindFirst",
	"TarFindNext",
	"TarSetOwnerWindow",
	"TarClearOwnerWindow",
	"TarGetRunning",
	NULL,
	NULL,
	},
//	"CAB32.DLL",
	{"CabGetVersion",
	"CabSetBackGroundMode",
	"CabSetCursorMode",
	"Cab",
	"CabCheckArchive",
	"CabOpenArchive",
	"CabCloseArchive",
	"CabFindFirst",
	"CabFindNext",
	"CabSetOwnerWindow",
	"CabClearOwnerWindow",
	"CabGetRunning",
	NULL,
	NULL,
	},
//	"UNRAR32.DLL",
	{"RarGetVersion",
	"RarSetBackGroundMode",
	"RarSetCursorMode",
	"Rar",
	"RarCheckArchive",
	"RarOpenArchive",
	"RarCloseArchive",
	"RarFindFirst",
	"RarFindNext",
	"RarSetOwnerWindow",
	"RarClearOwnerWindow",
	"RarGetRunning",
	NULL,
	NULL,
	},
//EntryPoint Arc

//	"UNKANJ32.DLL",
	{"ccGetVersion",
	"ccSetBackGroundMode",
	"ccSetCursorMode",
	"ccCommand",
	"ccOpen",
	"ccRead",
	"ccClose",
	NULL,
	NULL,
	"ccSetOwnerWindow",
	NULL, //"ccClearOwnerWindow",
	"ccGetRunning",
	"ccGetType",
	"ccIsEOF"
	},
//takaso2010
//	"xdoc2txt.exe",
	{NULL,
	NULL,
	NULL,
	"ccCommand",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, //"ccClearOwnerWindow",
	NULL,
	NULL,
	NULL,
	}
};
char *szArcCmdLst[] = {
//	"e -p -a1 -r0 -m1 -n2 -f1 -s1 -jn1 -gd0 \"-w1",
	"e -p -a1 -r0 -m1 -n1 -f1 -s1 -jn1 -gd0 \"-w1",
		//e:ディレクトリを有効として解凍しない
		//-p:ファイル名の検索を厳密に
		//
		//	  　すべてのファイルを合致させる目的で "*.*" を指定する場合には
		//  "-p" スイッチは使用すべきではありません。"-p" スイッチが指定され
		//  ていると  "*.*" は「パス名を持たない全てのファイル」を意味します。
		//  サブディレクトリを持つディレクトリパスを合致させるには，"-p2" ス
		//  イッチを使います。このスイッチは，UNLHA32.DLL が，指定されたワイ
		//  ルド名ではなく，パス名の最初の部分だけが合致するか調べます。例え
		//  ば，あなたの書庫が TC と言う名前の  TURBO C++ のディレクトリを含
		//  んでいるとき，INCLUDE サブディレクトリをサブディレクトリ
		//  INCLUDE\SYS と共に展開したいとしたら，次の命令が使えます。

		//-a1:全てのファイルがそのままの属性で解凍
		//-r0:非再帰モード(パス名で指定されたファイルだけを凍結・解凍します。)
		//-m1:問い合わせを行わず、問い合わせにたいして、すべて「Y」が入力された
		//    ものとして処理を続けます。
		//	  更新日時の照合を行い、書庫内のファイルの方が新しければファイル
		// 	  を更新します。
		//-n2:ooo..... という表示を抑制します。
		//------> -n1:	n[0|1]:
		//	  ファイル名の表示も抑制します
		//-f1:ディスク残量のチェックを抑止。
		//-s1:最新のファイルが存在のスキップメッセージの制御
		//-jn1:新ﾌｧｲﾙのみ解凍
		//-gd0:余分なﾃﾞｰﾀの削除の抑制
		//-w1<作業ディレクトリ名>] 作業用ディレクトリの指定<-----must be last!!!!!!!!!
		////-jf1:ルート記号の削除
#ifdef NEED_ZIP32J_IZIP32J
	"-qq --i",//"e -p -a1 -r0 -m1 -n2",
#else
	"-qq --i",//"e -p -a1 -r0 -m1 -n2",
#endif
		//     -i   解凍状況の表示ダイアログを出す。
        //  禁止するには --i と指定してください。
		//     -q  出来るだけ余計な情報は表示しない。
		//     -qq さらに「静か」
	//arj
	"e -i -y -p",
		//	i[-|+]: 展開状況ダイアログ表示の抑止  [-i-]
		//y[-|+]: すべての質問に yes と仮定  [-y-]
		//	p[-|+|1]: 全パス名で合致  [-p-]
	//Tar
	//"--check-all-path=1 --display-dialog=0 -xfRo",
	"--display-dialog=0 --check-all-path=1 -xfRo",
	//"xfRo",
        //-x      (eXtract) アーカイブ中のファイルを取り出します。file... 
        //n       (no message) t コマンド実行時に、出力を抑えます。
        //        例えば tgz ,taz ,tar ファイルの整合性チェックに使います。
        //o PATH  (extract to) x コマンド実行時に、展開をPATH の下に行います。
        //        PATHは、末尾の '/', '\'に応じて内部で'/'を付加して処理しま
        //        す。以下の例では、c:/gnu というサブディレクトリが存在しな
        //        ければ、勝手に作成して作業を続けます。

        //        指定の形式は、次の通りです。
        //            tar xvaf GCC242.TGZ -o c:/gnu
        //          or
        //            tar xvafo GCC242.TGZ c:/gnu
                    
        //        また、DLL版では、
        //           tar xvaf GCC242.TGZ c:/gnu/
        //        のようにも指定できます。[DLLのみ]
		//-R
 		//	overwrite Read Only file
 		//   Example)
 		//    for backup  : -cfz9AHUS filename.tgz -s filename.sec
		//        for list    : -tvfU filename.tgz
		//        for restore : -xfU2R filename.tgz -s filename.sec
		//	[DLLのみ]
		//--check-all-path=[0|1]
		//	ファイル名検索時に厳密にパス名にマッチするようにチェック
		//	するかどうか、パス名を含めてチェックするときは1を、パス名を
		//	含まないファイル名のみマッチするか調べるときは0を指定する。
		//	1を指定すると、*.*でアーカイバ中のすべてのファイルにマッチ
		//	せず、一番上のディレクトリのファイルのみにマッチする。
		//	デフォルトは0。[DLLのみ]
			
		//--display-dialog=[0|1]
		//	圧縮/展開中に状況表示ダイアログを表示するかどうか。
		//	表示しないと何が起こっているのかわからないので不安になるかも
		//	しれない。表示すると多少動作が遅くなるかもしれない。
		//	1に設定すると表示する。デフォルトは1。[DLLのみ]
	//Cab
	"-x -i -o",
	  //x: キャビネット内のファイルを展開
	  //  i: サイレントモード
	  //  o: 無条件に上書き解凍
	  //  w: 正規表現を利用
	//Rar
	"-x -o -s",
     //-x  書庫のファイルを解凍
	 //   書庫から１個以上のファイルをカレントディレクトリまたは指定された
	  //ディレクトリに解凍します。
     //-o  すでにファイルが存在しても、ユーザーに問い合わせることなく上書
     //    きします。
     //-s  filespec の比較を厳密に行います。
     //    -s が指定されると、UNRAR32.DLL はフルパスでの一致を試みます。
     //    -s が指定されず、filespec が '\' および '/' を含まない場合、
     //    UNRAR32.DLL は書庫に格納されたファイル名からディレクトリを除い
     //    た部分との一致を試みます。
     //    filespec が '\' または '/' を含む場合は、-s の指定の如何に関わ
     //    らずフルパスでの一致を試みます。
     //-x  書庫のファイルを解凍
//EntryPoint Arc
	"t -s",
	//xdoc2txt
	"-n -f", //2013.03/04 takaso -n add.
	};
// CABAPI.H      Kuniaki Miyauchi
#define CABAPI_VERSION	84
#define UNRAR32_VERSION 5

int iSupportVersion[] = {
#ifdef WIN32
	UNLHA32_VERSION,
#else
	UNLHA_VERSION,
#endif
#ifdef NEED_ZIP32J_IZIP32J
	24,
#else
	97, //UNZIP32_VERSION,
#endif
	UNARJ32_VERSION,
	53,	//tar
	CABAPI_VERSION,
	UNRAR32_VERSION,
	UNKANJ_VERSION,
	0,//takaso2010
	};

/*************************************************************************
*************************************************************************/
void CDLL::FreeLib()
{
	if (m_hDll) {
		if (m_ext==EXT_XDOC){
			delete (CDxdoc2txt *)m_hDll;
		}else{
			FreeLibrary (m_hDll);
		}
	}
	m_hDll = NULL;
}

BOOL CDLL::FInitialize(EXT_TYPE ext/*=EXT_NON*/, char *szBasePath/*=NULL*/, BOOL fActive/*=TRUE*/)
{
	// ｄｌｌタイプセット
	if (ext != EXT_NON)
		m_ext =ext;
	ASSERT(m_ext!=EXT_NON);

	// アーカイブファイルのセーブと解凍用フォルダのセット
	// 起動時にセットされる。途中で変えてもだめ！！！！!
	if (m_cstrBasePath.IsEmpty() && szBasePath!=NULL)
		m_cstrBasePath = szBasePath;
	RemoveLastBackSlash(&m_cstrBasePath);

	ASSERT(!m_cstrBasePath.IsEmpty( ));


	// ＡｒｃＤＬＬのリ・ロード
	if (!fActive)
		{
//		if (m_hDll)
//			{
//			FreeLibrary (m_hDll);
//			m_hDll = NULL;
//			}
		return FALSE;	//アクティブでなくする
		}

	if (!m_hDll) {
		if (ext==EXT_XDOC){
			if ((m_hDll = (HINSTANCE) new CDxdoc2txt())==NULL)
				return FALSE;
			if (!((CDxdoc2txt *)m_hDll)->Create(NULL, NULL, 0,
						CRect(0,0,0,0), AfxGetMainWnd(), 10)) {
				delete (CDxdoc2txt * )m_hDll;
				m_hDll = NULL;	//takaso 4.21
				return FALSE;
			}
		}else{
			if ((m_hDll = LoadLibrary (szDllFileName[m_ext]))==NULL ){
#ifdef WIN32
#ifdef _DEBUG
				DWORD dw = GetLastError();
#endif
#endif
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CDLL::FActiveUpdate()
{
	if (!FActive())
		return FInitialize();
	return TRUE;
}

//ソースファイルをセットする
BOOL CDLL::FSetSrcFile(char *szSrcFile)
{
	if (!FActive())
		return FALSE;
	ASSERT(m_ext!=EXT_NON && m_hDll!=NULL);
	ASSERT(szSrcFile);
	m_dFileSrc = szSrcFile;
	if (!m_dFileSrc.FExistRealFile())	//存在するか？
		return FALSE;
	return TRUE;
}

/*************************************************************************
*************************************************************************/
CDLLDoc::CDLLDoc()
{
	m_handle=NULL;
}
CDLLDoc::~CDLLDoc()
{
	if (m_handle) {
		DoCloseTran();
	}
	//変換したﾌｧｲﾙを削除しておく！
	AddLastBackSlash(&m_cstrBasePath);
	m_cstrBasePath += (m_ext==EXT_XDOC ? XDOC_SUB_DIR:UNKANJI_SUB_DIR);//m_dFileSrc.GetName();
	if (!m_cstrBasePath.IsEmpty())
		RemoveAllDir(m_cstrBasePath.GetBuffer(0), FALSE);	//no prompt
}
BOOL CDLLDoc::FInitialize(EXT_TYPE ext/*=EXT_NON*/, char *szBasePath/*=NULL*/, BOOL fActive/*=TRUE*/)
{
	if (CDLL::FInitialize(ext, szBasePath, fActive) == FALSE)
		return FALSE;

	if (WM_ARCEXTRACT_MSG==NULL)
		{
		//WM_ARCEXTRACT_MSGの登録
		WM_ARCEXTRACT_MSG=::RegisterWindowMessage(WM_ARCEXTRACT_TXT);
		if (WM_ARCEXTRACT_MSG==0)
			return FALSE;
		}
	if (ext==EXT_XDOC) {
		return TRUE;
	}else{
		// チェックバージョン＆サポートファンクション
		GetVersion = (DGetVersion)GetProcAddress (m_hDll, szArcFuncLst[m_ext][0]);
		SetBackGroundMode = (DSetBackGroundMode)GetProcAddress (m_hDll, szArcFuncLst[m_ext][1]);
		ArcCmd = (DArcCmd)GetProcAddress (m_hDll, szArcFuncLst[m_ext][3]);
		SetOwnerWindow	= (DSetOwnerWindow)GetProcAddress(m_hDll, szArcFuncLst[m_ext][9]);
		OpenTran	= (DOpen)GetProcAddress(m_hDll, szArcFuncLst[m_ext][4]);
		ReadTran	= (DRead)GetProcAddress(m_hDll, szArcFuncLst[m_ext][5]);
		CloseTran	= (DClose)GetProcAddress(m_hDll, szArcFuncLst[m_ext][6]);
		//ClearOwnerWindow = (DClearOwnerWindow)GetProcAddress(m_hDll, szArcFuncLst[m_ext][10]);
		GetRunning	= (DGetRunning)GetProcAddress(m_hDll, szArcFuncLst[m_ext][11]);
		GetType = (DGetType)GetProcAddress(m_hDll, szArcFuncLst[m_ext][12]);
		IsEOFTran = (DIsEOF)GetProcAddress(m_hDll, szArcFuncLst[m_ext][13]);
	}

	if (!(GetVersion && ArcCmd && OpenTran && ReadTran && CloseTran &&
		SetBackGroundMode && GetRunning && SetOwnerWindow &&
		GetType && IsEOFTran))
		goto FREE_LIB;
	if ((GetVersion)()<iSupportVersion[m_ext])
		goto FREE_LIB;
	// 解凍されたパス付きファイル名のイニシャルエンプティー
//	(SetOwnerWindow)(AfxGetMainWnd()->GetSafeHwnd());
	return TRUE;
FREE_LIB:
	FreeLib();
	return FALSE;
}

//takaso2008
void widen(const std::string &src, std::wstring &dest) {
    setlocale(LC_ALL, "Japanese_Japan.932");
#ifdef BUG20120117
	wchar_t *wcs = new wchar_t[src.length() + 1];
	size_t returnValue;
	mbstowcs_s(&returnValue, wcs, src.length() + 1, src.c_str(), _TRUNCATE );
#else
	//wchar_t *wcs = new wchar_t[src.length() + 1];
	wchar_t *wcs = new wchar_t[(src.length() + 1)*2];
	//warning C4996: 'mbstowcs': This function or variable may be unsafe. Consider using mbstowcs_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	mbstowcs(wcs, src.c_str(), src.length() + 1);
#endif
	dest = wcs;
	delete [] wcs;
}

int CDLLDoc::DoTrans(char *szSrcFile, CString &cstrDes, CString &cstrBasePath)
{
	int iRtn;
	if (!FActive())
		return -1;	//NG!!!
	ASSERT(!m_dFileSrc.GetString()->IsEmpty());
	
	// 解凍されたパス付きファイル名の作成
	//パス付きソースファイルなら、そのパスにUNKANJI_SUB_DIRサブディレクトリを付ける
	//パスなしソースファイルなら、テンポラリにUNKANJI_SUB_DIRサブディレクトリを付ける
	CDFile cdfile = szSrcFile;
	if (cdfile.FExistDir()) {
		if (cdfile.FExistDrv()) {
			cstrDes = cdfile.GetPath();
			AddLastBackSlash(&cstrDes);
			cstrDes += (m_ext==EXT_XDOC ? XDOC_SUB_DIR:UNKANJI_SUB_DIR);//m_dFileSrc.GetName();
		} else {
			cstrDes = m_cstrBasePath;
			AddLastBackSlash(&cstrDes);
			cstrDes += (m_ext==EXT_XDOC ? XDOC_SUB_DIR:UNKANJI_SUB_DIR);//m_dFileSrc.GetName();
			//if (cdfile.GetDir().GetAt(0)!=chBackSlash)
			WORD wh = cdfile.GetString()->GetAt(0);
			if (wh!=(WORD)chBackSlash && wh!=(WORD)chSlash)
				AddLastBackSlash(&cstrDes);
			cstrDes += cdfile.GetDir();
		}
	} else {
		cstrDes = m_cstrBasePath;
		AddLastBackSlash(&cstrDes);
		cstrDes += (m_ext==EXT_XDOC ? XDOC_SUB_DIR:UNKANJI_SUB_DIR);//m_dFileSrc.GetName();
	}
	AddLastBackSlash(&cstrDes);
	cstrBasePath = cstrDes.GetBuffer(0);
	cstrDes +=	cdfile.GetName();//名前はソースと同じとする。
	
	
	CDFile cdfileDes = cstrDes;
	
	//ファイルが既にあるかないかのチェック
	// "-m1"オプションがそれをやってくれるはずがやってくれない
	//ので以下のコードを復活する
	if (cdfileDes.FExistRealFile())
		return 0;//OK

	//ステータスバーの表示	
	CString cstr;
	CString cstrMsg = ((CMainFrame *)AfxGetMainWnd())->GetPaneText();
	if (cstrMsg.Find("...OK")==-1) {
		cstrMsg = m_dFileSrc.GetName().GetBuffer();
//		cstrMsg += chTransSeparetor;
//		cstrMsg += cdfile.GetName();
////		cstrMsg.MakeLower();
		cstrMsg += chSpace;
	}else
		cstrMsg += " / ";
	cstr.LoadString(m_ext==EXT_XDOC ? IDS_XDOC_TRANS:IDS_KFT_TRANS);
	cstrMsg += cstr;
	cstrMsg += "...";

	((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));

	if (m_ext==EXT_XDOC) {
		CString str;
		((CDxdoc2txt *)GetDll())->Convert(m_dFileSrc.GetBuffer(), &str); //szArcFuncLst[m_ext][5]
		char *psz = str.GetBuffer();
		if (!str.IsEmpty()) {
			fstream fout;
			int filenamelen = cdfileDes.GetName().GetLength();

			string st(cdfileDes.GetBuffer());
			wstring ws;
			widen(st,ws);

			iRtn = 0;

			while( !str.IsEmpty() && iRtn==0) {
				fout.clear();
				//fout.open( strDesFileName.c_str(), ios::out | ios::trunc | ios::binary, filebuf::sh_none);
				fout.open( (wchar_t *)ws.c_str(), ios::out | ios::trunc | ios::binary);
				if (!fout.is_open()) {
					CString strT;
					if (cdfileDes.GetFName().GetLength() > filenamelen)
						strT= cdfileDes.GetPath();
					else
						strT = GetCurrentPath();
					if (FCreateDirectory(strT.GetBuffer()))
						continue;
					iRtn = -1;
				}
				break;
			}
			fout.write((const char *)psz, str.GetLength());
			if (fout.is_open()) {
				fout.flush();
				fout.close();
			}
		}
		iRtn = 0;	//ok
	}else{
		//コマンドラインの作成
		CString cstrCmd;
		cstrCmd = szArcCmdLst[m_ext];

		cstrCmd += chSpace;

		// ソースファイル
		cstrCmd += '\"';
		cstrCmd += m_dFileSrc.GetBuffer();
		cstrCmd += '\"';
		cstrCmd += chSpace;
		// ディスティネーションファイルの指定
		cstrCmd += '\"';
		cstrCmd += cdfileDes.GetBuffer();
		cstrCmd += '\"';

		// 解凍されたパス付きファイル名のイニシャルエンプティー
	//	(ClearOwnerWindow)();
	//	if (!(SetOwnerWindow)(AfxGetMainWnd()->GetSafeHwnd()))
	//		goto ERR;
		VERIFY((SetBackGroundMode)(FALSE));//タスクを占有
	//	if (!WaitEndRunning())
	//		return -1;			//User Abort!

		TRACE(cstrCmd.GetBuffer(0));
		TRACE("\r\n");
		iRtn = (ArcCmd)(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), cstrCmd.GetBuffer(0), vz, sizeof(vz));
	}
	if (iRtn==0)
		{
		cstrMsg +="OK";
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));
		return iRtn;
		}
	((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
	return -1;
}


BOOL CDLLDoc::DoOpenTran(char *szSrcFile)
{
	int rtn;

	if (m_ext==EXT_XDOC)
		return TRUE;


	if (!FActive())
		return -1;	//NG!!!
	ASSERT(!m_dFileSrc.GetString()->IsEmpty());

	if (m_handle)
		DoCloseTran();

	//ステータスバーの表示
//	CString cstr;
//	CString cstrMsg;
//	cstrMsg = m_dFileSrc.GetName().GetBuffer();
//	cstrMsg.MakeLower();
//	cstrMsg += chSpace;
//	cstr.LoadString(IDS_KFT_TRANS);
//	cstrMsg += cstr;
//	cstrMsg += "...";

//	((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));

	//コマンドラインの作成
	CString cstrCmd;
	cstrCmd = szArcCmdLst[m_ext];

	cstrCmd += chSpace;
	// アーカイブファイル
	cstrCmd += '\"';
	cstrCmd += m_dFileSrc.GetBuffer();
	cstrCmd += '\"';

	// 解凍されたパス付きファイル名のイニシャルエンプティー
//	(ClearOwnerWindow)();
//	if (!(SetOwnerWindow)(AfxGetMainWnd()->GetSafeHwnd()))
//		goto ERR;
	VERIFY((SetBackGroundMode)(TRUE));//タスクを占有しない
//	if (!WaitEndRunning())
//		return -1;			//User Abort!
	TRACE(cstrCmd.GetBuffer(0));
	TRACE("\r\n");
	m_handle = (OpenTran)(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), cstrCmd.GetBuffer(0), vz, sizeof(vz), &rtn);
	if (m_handle!=NULL)
		return TRUE;
	((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
	return FALSE;
}

unsigned int CDLLDoc::DoReadTran(void* lpBuf, UINT nCount, int *pRtn)
{
	if (!FActive())
		return -1;	//NG!!!
	ASSERT(m_ext!=EXT_XDOC);
	ASSERT(m_handle);
	return (ReadTran)(m_handle, lpBuf, nCount, pRtn);
}

void CDLLDoc::DoCloseTran()
{

	if (!FActive())
		return;	//NG!!!
	if (m_ext==EXT_XDOC){
		m_handle = NULL;
		return ;
	}
	ASSERT(m_handle);
	(CloseTran)(m_handle);
	m_handle = NULL;
}

CString CDLLDoc::DoGetType()
{
	CString str;
	if (!FActive())
		return str;	//NG!!!

	if (m_ext==EXT_XDOC) {
		str = m_dFileSrc.GetBufferExtention();
		str.MakeLower();
		return str;
	}
	ASSERT(m_handle);
	int type =  (GetType)(m_handle);
	switch(type) {
		case kt_jis:
			str = "jis";
			break;
		case kt_euc:
			str = "euc";
			break;
		case kt_utf8:
			str = "utf";
			break;
		default:
			break;
	}
	return str;
}

BOOL CDLLDoc::DoIsEOFTran()
{
	if (!FActive())
		return -1;	//NG!!!
	ASSERT(m_ext==EXT_XDOC || m_handle);

	if (m_ext==EXT_XDOC)
		return TRUE;
	return (IsEOFTran)(m_handle);
}
/*************************************************************************
*************************************************************************/
BOOL CDLLArc::FInitialize(EXT_TYPE ext/*=EXT_NON*/, char *szBasePath/*=NULL*/, BOOL fActive/*=TRUE*/)
{
	if (CDLL::FInitialize(ext, szBasePath, fActive) == FALSE)
		return FALSE;

	if (WM_ARCEXTRACT_MSG==NULL)
		{
		//WM_ARCEXTRACT_MSGの登録
		WM_ARCEXTRACT_MSG=::RegisterWindowMessage(WM_ARCEXTRACT_TXT);
		if (WM_ARCEXTRACT_MSG==0)
			return FALSE;
		}
	// チェックバージョン＆サポートファンクション
	GetVersion = (DGetVersion)GetProcAddress (m_hDll, szArcFuncLst[m_ext][0]);
	SetBackGroundMode = (DSetBackGroundMode)GetProcAddress (m_hDll, szArcFuncLst[m_ext][1]);
	SetCursorMode = (DSetCursorMode)GetProcAddress (m_hDll, szArcFuncLst[m_ext][2]);
	ArcCmd = (DArcCmd)GetProcAddress (m_hDll, szArcFuncLst[m_ext][3]);
	CheckArchive = (DCheckArchive)GetProcAddress (m_hDll, szArcFuncLst[m_ext][4]);
	OpenArchive = (DOpenArchive)GetProcAddress (m_hDll, szArcFuncLst[m_ext][5]);
	CloseArchive = (DCloseArchive)GetProcAddress (m_hDll, szArcFuncLst[m_ext][6]);
	FindFirst = (DFindFirst)GetProcAddress (m_hDll, szArcFuncLst[m_ext][7]);
	FindNext = (DFindNext)GetProcAddress (m_hDll, szArcFuncLst[m_ext][8]);
	SetOwnerWindow	= (DSetOwnerWindow)GetProcAddress(m_hDll, szArcFuncLst[m_ext][9]);
	ClearOwnerWindow = (DClearOwnerWindow)GetProcAddress(m_hDll, szArcFuncLst[m_ext][10]);
	GetRunning	= (DGetRunning)GetProcAddress(m_hDll, szArcFuncLst[m_ext][11]);


	if (!(GetVersion && /*SetBackGroundMode && SetCursorMode &&*/ 
		ArcCmd && /*CheckArchive &&*/ OpenArchive && CloseArchive &&
		FindFirst && FindNext 
		/*&& SetOwnerWindow && ClearOwnerWindow && GetRunning*/))
		goto FREE_LIB;
	if (/*ext!=EXT_ZIP &&*/ (GetVersion)()<iSupportVersion[m_ext])
		goto FREE_LIB;
//	if (SetOwnerWindow)
//		(SetOwnerWindow)(AfxGetMainWnd()->GetSafeHwnd());
	return TRUE;
FREE_LIB:
	FreeLib();
	return FALSE;
}


int CDLLArc::DoTrans(char *szSrcFile, CString &cstrDes, CString &cstrBasePath)
{
	int iRtn;
	CString strBaseTmp;
	if (!FActive())
		return -1;	//NG!!!

	ASSERT(!m_dFileSrc.GetString()->IsEmpty());
	
	
	// 解凍されたパス付きファイル名の作成
	cstrDes = m_cstrBasePath;
	AddLastBackSlash(&cstrDes);
	cstrDes +=m_dFileSrc.GetName();
	cstrBasePath = cstrDes;
	AddLastBackSlash(&cstrBasePath);
//1999.7.12--->
	if (!m_strAttr.IsEmpty()) {
		AddLastBackSlash(&cstrDes);
		cstrDes += m_strAttr;
	}
//<----1999.7.12


	CDFile cdfile = szSrcFile;
	WORD wh = cdfile.GetString()->GetAt(0);
	if (wh!=(WORD)chBackSlash && wh!=(WORD)chSlash)
		AddLastBackSlash(&cstrDes);
	strBaseTmp = cstrDes;

	cstrDes += cdfile.GetDir();
	cstrDes +=	cdfile.GetName();
	
	CDFile cdfileDes = Convert4UnixPath(cstrDes);
	cstrDes = cdfileDes.GetBuffer();
	
	//ファイルが既にあるかないかのチェック
	// "-m1"オプションがそれをやってくれるはずがやってくれない
	//ので以下のコードを復活する
	if (cdfileDes.GetName().IsEmpty())	//Tar.ack139/
		return -1;	//ディレクトリだ！	//Tar.
	if (cdfileDes.FExistRealFile())
		return 0;//OK

	//ステータスバーの表示	
	CString cstr;
	CString cstrMsg = ((CMainFrame *)AfxGetMainWnd())->GetPaneText();
	if (cstrMsg.Find("...OK")==-1) {
		cstrMsg = m_dFileSrc.GetName().GetBuffer();
		cstrMsg += chTransSeparetor;
		cstrMsg += cdfile.GetName();
//		cstrMsg.MakeLower();
		cstrMsg += chSpace;
	}else
		cstrMsg += " / ";
	cstr.LoadString(IDS_ARC_EXTRACT);
	cstrMsg += cstr;
	cstrMsg += "...";

	((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));

	//コマンドラインの作成
	CString cstrCmd;
	cstrCmd = szArcCmdLst[m_ext];
	//cstrCmd += '\"';
	if (m_ext==EXT_LZH)
		{
		cstrCmd += m_cstrBasePath;	//ﾜｰｸﾃﾞｨﾚｸﾄﾘのセット
		cstrCmd += '\"';
		}

/*	if (m_ext == EXT_ZIP) {
		cstrCmd += chSpace;
		// アーカイブファイル
		cstrCmd += m_dFileSrc.GetBuffer();
		cstrCmd += chSpace;
		// 基準パスの作成
		//strBaseTmp = GetCurrentPath();
		//VERIFY(FCreateDirectory(cdfileDes.GetPath()));
		// 基準パスの指定(\付き)
		cstrCmd += '\"';
		cstrCmd += cdfileDes.GetPath();
		cstrCmd += '\"';
		cstrCmd += chSpace;
		// 解凍ファイルの指定
		cstrCmd += szSrcFile;
	}else
*/	{
		cstrCmd += chSpace;
		// アーカイブファイル
		cstrCmd += '\"';
		cstrCmd += m_dFileSrc.GetBuffer();
		cstrCmd += '\"';
		cstrCmd += chSpace;
		// 基準パスの指定(\付き)
		cstrCmd += '\"';

#ifndef NEED_ZIP32J_IZIP32J
		if (m_ext==EXT_ZIP) {
			//cstrCmd += cdfileDes.GetPath();
			cstrCmd += strBaseTmp;
			//cstrCmd += '\\';
		}else
#endif
//for Tar!
		{
		if(m_ext==EXT_TAR)
			cstrCmd += strBaseTmp;
		else
			cstrCmd += cdfileDes.GetPath();
		}

		FCreateDirectory(cdfileDes.GetPath());

		cstrCmd += '\"';
		cstrCmd += chSpace;
		// 解凍ファイルの指定
		cstrCmd += '\"';
		cstrCmd += szSrcFile;
		cstrCmd += '\"';
	}

	// 解凍されたパス付きファイル名のイニシャルエンプティー
//	if (ClearOwnerWindow)
//		(ClearOwnerWindow)();
	
//	if (SetOwnerWindow && !(SetOwnerWindow)(AfxGetMainWnd()->GetSafeHwnd()))
//		goto ERR;
	if (SetBackGroundMode)
		(SetBackGroundMode)(FALSE);//タスクを占有 cabの場合FALSEが返る
//		VERIFY((SetBackGroundMode)(FALSE));//タスクを占有 cabの場合FALSEが返る

//	if (!WaitEndRunning())
//		return -1;			//User Abort!
#ifdef WIN32
	TRACE(cstrCmd.GetBuffer(0));
	TRACE("\r\n");
	iRtn = (ArcCmd)(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), cstrCmd.GetBuffer(0), vz, sizeof(vz));
#else
	iRtn = (ArcCmd)(cstrCmd.GetBuffer(0), vz, sizeof(vz));
#endif //WIN32
	//if (!strBaseTmp.IsEmpty()) {
	//	VERIFY(SetCurrentPath(strBaseTmp.GetBuffer()));
	//}
	if (iRtn==0)
		{
		cstrMsg +="OK";
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));
		}
	return iRtn;
ERR:
	((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
	return -1;
}
//TRUE:End Working
//FALSE:User Abort!
//if Caller must be set vpFileTransArray->m_fUserAbort=TRUE!
/*
BOOL CDLLArc::WaitEndRunning()
{
	if (!GetRunning())	//解凍中でない？
		return TRUE;
	vpFileTransArray->m_fUserAbort = FALSE;
	while (GetRunning());	//解凍中が終わるまで待つ
	return !vpFileTransArray->m_fUserAbort; //m_fUserAbortが立っていたらユーザがアボートした！
}
*/
//Ａｒｃファイルをセットする
BOOL CDLLArc::FSetSrcFile(char *szSrcFile)
{
	if (m_FindData.hFindHandle)
		{
		VERIFY((CloseArchive)((HARC)m_FindData.hFindHandle)==0);
		m_FindData.hFindHandle=NULL;
		}

	if (!CDLL::FSetSrcFile(szSrcFile))
		return FALSE;
	try {
	BOOL bDoCheck = TRUE;
	if (Getext()== EXT_TAR) {
			CString str = m_dFileSrc.GetBufferExtention();
			str.MakeUpper();
			bDoCheck = (str!="Z");
	}
	if (bDoCheck && CheckArchive &&
		!(CheckArchive)(m_dFileSrc.GetBuffer(), CHECKARCHIVE_RAPID))
		return FALSE;
	//takaso2008
	//}catch (exception &e) {
	}catch (char *str ) {
		ASSERT(FALSE);
		vpFindList->m_FindLog.AddLogString(m_dFileSrc.GetBuffer());
		vpFindList->m_FindLog.AddLogLine("arc file error:");
		return FALSE;
	}
//1999.7.12--->
	m_strAttr = "";
	struct _stat filestat;
	if (_stat( szSrcFile, &filestat ) != 0)
		return false;
	CString str;
	str.Format("%ld",filestat.st_size);
	CTime ctime(filestat.st_mtime);
	m_strAttr = ctime.Format("%Y_%m_%d_%H_%M_%S_") + str;
//<----1999.7.12
	return TRUE;
}

/*************************************************************************
-- Routine:BOOL FFirst ( LPSTR lpDest, LPSTR szFileSpec, WORD attrib )
				FFirst ( LPSTR szFileSpec);
-- Description and Usage:
		アトリビュートにあう、ディレクトリにある最初のファイルを見つけてくる
		SetDta(),FFirst(LPSTR,WORD)は、FFirst(LPSTR,LPSTR,WORD)を２つに分けた
		ものである。
-- Arguments:
		LPSTR lpDest - ファイル名の入るポインタ
		LPSTR szFilSpec - 前回のファイル
		WORD  attrib - 指定アトリビュート
-- Returns:
		ファイルがある - TRUE
		ファイルが無い - FALSE
-- Notes:

-- History:
		'94.8	- created		(M.Design)
*************************************************************************/
BOOL CDLLArc::FFirst ( LPSTR szFileSpec, BOOL fFile)
{
	if (!FActive())
		return FALSE;
	ASSERT(m_ext!=EXT_NON && m_hDll!=NULL);
	ASSERT(!m_dFileSrc.GetString()->IsEmpty());

	if (SetBackGroundMode)
		(SetBackGroundMode)(FALSE);//タスクを占有
		//VERIFY((SetBackGroundMode)(FALSE));//タスクを占有 TarはFALSEで返る
	if (SetCursorMode)
		(SetCursorMode)(FALSE);
		//VERIFY((SetCursorMode)(FALSE));TarはFALSEで返る
#ifdef NOTUSE
	if (fFile)
		{
		//m_FindAttrs.dwAttrib = ATTR_FILES;
		m_fDir = FALSE;
		return FFirst (szFileSpec);
		}
	else
		{
		//m_FindAttrs.dwAttrib = ATTR_DIR; //ﾁｪｯｸの判定のため
		m_fDir = TRUE;
		CString cstr;
		cstr = "*.";
		cstr += szEXT_TYPE[m_ext];
		return FFirst (cstr.GetBuffer(0));
		}
#endif //NOTUSE
		return FFirst (szFileSpec);
	
}

// グローバル・検索ハンドル
BOOL CDLLArc::FFirst (LPSTR szFileSpec)
{
	ASSERT(m_ext!=EXT_NON && m_hDll!=NULL);
	ASSERT(m_FindData.hFindHandle==NULL);
	int rtn;
	// Ａｒｃファイルのオープン...パス無視
//	if (m_dFileSrc.GetString()->IsEmpty() || (m_FindData.hFindHandle=(OpenArchive)(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), m_dFileSrc.GetBuffer(), M_CHECK_ALL_PATH))==NULL)
	if (m_dFileSrc.GetString()->IsEmpty() || (m_FindData.hFindHandle=(OpenArchive)(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), m_dFileSrc.GetBuffer(), 
		M_REGARDLESS_INIT_FILE 
		| M_NOT_USE_DRIVE_LETTER
		| M_ERROR_MESSAGE_OFF))==NULL)
		return FALSE;
	if ((rtn = (FindFirst)(m_FindData.hFindHandle, szFileSpec, &m_ArcInfo)) != 0)
		{
		VERIFY((CloseArchive)((HARC)m_FindData.hFindHandle)==0);
#ifdef _DEBUG
		ASSERT(rtn==-1); //ファイルが見つからない以外のエラー！
#endif
		m_FindData.hFindHandle=NULL;
		return FALSE;
		}
	if (!SaveAndChkAttr())
		return FNext();
	return TRUE;
}
/*************************************************************************
-- Routine:BOOL FNext ( LPSTR lpDest, WORD attrib )
				FNext ()
-- Description and Usage:
		attrib にあう、次のファイルを見つけてくる
-- Arguments:
		LPSTR lpDest - ファイル名ディレクトリ名の入るポインタ
		WORD attrib  - 指定アトリビュート
-- Returns:
		次のファイルがある - TRUE
		もうファイルが無い - FALSE
-- Notes:

-- History:
		'94.8	- created		(M.Design)
*************************************************************************/
BOOL CDLLArc::FNext ( )
{
	if (!FActive())
		return FALSE;
	ASSERT(m_ext!=EXT_NON && m_hDll!=NULL);
	ASSERT(m_FindData.hFindHandle!=NULL);
	ASSERT(m_FindAttrs.dwAttrib);
	int rtn;	
	do
		{
		if ((rtn = (FindNext)(m_FindData.hFindHandle, &m_ArcInfo)) != 0)
			{
			VERIFY((CloseArchive)((HARC)m_FindData.hFindHandle)==0);
			#ifdef _DEBUG
			ASSERT(rtn==-1); //ファイルが見つからない以外のエラー！
			#endif
			m_FindData.hFindHandle=NULL;
			return FALSE;
			}
	}while(!SaveAndChkAttr());

	return TRUE;
}

BOOL CDLLArc::SaveAndChkAttr()
{
	//0Initialize
	memset((void *)&m_FindData.srFD, 0, sizeof(WIN32_FIND_DATA));
	//Save Attribute
	CString cstrAttr = m_ArcInfo.szAttribute;
	if (cstrAttr.Find('R')!=-1)
		m_FindData.srFD.dwFileAttributes = ATTR_READONLY;
	if (cstrAttr.Find('H')!=-1)
		m_FindData.srFD.dwFileAttributes |= ATTR_HIDDEN;
	if (cstrAttr.Find('S')!=-1)
		m_FindData.srFD.dwFileAttributes |= ATTR_SYSTEM;
	//if (cstrAttr.Find('L')!=-1)
	//	m_FindData.srFD.dwFileAttributes |= 
	if (cstrAttr.Find('D')!=-1)
		m_FindData.srFD.dwFileAttributes |= ATTR_DIR;
	if (cstrAttr.Find('A')!=-1)
		m_FindData.srFD.dwFileAttributes |= ATTR_ARCHIVE;

	//Save FileName
	char *p=m_ArcInfo.szFileName;
//	do
//		{
//		if (*p=='/')
//			*p= chBackSlash;
//		}while(*(++p));
#ifdef BUG20120117
	strcpy_s (m_FindData.srFD.cFileName, sizeof(m_FindData.srFD.cFileName), m_ArcInfo.szFileName);
#else
	//warning C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	strcpy (m_FindData.srFD.cFileName, m_ArcInfo.szFileName);
#endif
//	AnsiLower((LPSTR)(m_FindData.srFD.cFileName));

	//Save FileSize
	m_FindData.srFD.nFileSizeLow = m_ArcInfo.dwOriginalSize;
	//Save Date&Time to Last Write Time.
#ifdef WIN32
	VERIFY(DosDateTimeToFileTime(m_ArcInfo.wDate, m_ArcInfo.wTime, &m_FindData.srFD.ftLastWriteTime));
#else
	m_FindData.srFD.Date = m_ArcInfo.wDate;
	m_FindData.srFD.Time = m_ArcInfo.wTime;
#endif //WIN32

	return TRUE;

#ifdef NOTUSE
	CDFile cdfile = m_FindData.srFD.cFileName;
//	cdfile.GetString()->MakeLower();
	
	if (cdfile.GetBufferExtention() == szEXT_TYPE[m_ext])
		return m_fDir;
	else
		return !m_fDir;
#endif //NOTUSE
//	return FCheckAttrsMatch();
}

/*************************************************************************
*************************************************************************/
CDLLArray::~CDLLArray()
{
	for (int i=0; i<GetSize(); i++)
		delete ((CDLL *)GetAt(i));
}

BOOL CDLLArray::FInitialize(char *szWorkPath)
{
	// アーカイブＤＬＬクラスの作成
	CDLL *pDll;

	for (int i=(int)EXT_MIN; i<EXT_MAX; i++)
		{
		if (i>=GetSize())
			{
			if (i>=EXT_ARCMIN && i<=EXT_ARCMAC)
				pDll = new CDLLArc;
			else
				pDll = new CDLLDoc;
			if (!pDll)
				return FALSE;
			Add(pDll);
			if (pDll)
				pDll->FInitialize((EXT_TYPE)i, szWorkPath);
			}
		}
	return TRUE;
}

void CDLLArray::SetFindAttrs(CFindAttrs *pFindAttrs)
{
	for (int i=0; i<GetSize(); i++)
		((CDLL *)GetAt(i))->Initialize(pFindAttrs);
}

void CDLLArray::SetFindFileSpec(CDFileSpec *pFileSpec)
{
	for (int i=0; i<GetSize(); i++)
		((CDLL *)GetAt(i))->InitFileSpec(pFileSpec);
}

CDLL *CDLLArray::PDll(EXT_TYPE ext)
{
	if ((int)ext>=GetSize())
		return NULL;
	return (CDLL *)GetAt((int)ext);
}

BOOL CDLLArray::FActiveAndCheck(EXT_TYPE ext)
{
	if ((int)ext>=GetSize())
		return FALSE;
//	return ((CDLL *)GetAt((int)ext))->FActiveUpdate() && vpFindOption->GetCheckExtType(ext);
	return ((CDLL *)GetAt((int)ext))->FActive() && vpFindOption->GetCheckExtType(ext);
}
