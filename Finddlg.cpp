m/*    PortTool v2.2     FINDDLG.CPP          */

// finddlg.cpp : インプリメンテーション ファイル
//
// Timeについて
// ダイアログ生成時、日付データのみを入れる時間は入れない
// データは保存され、m_fExpandOptionがTRUE時のみ有効となる。
#include "stdafx.h"
#include "OBJIDL.h"
#include "shlobj.h"
#include "string.h"
#include "fdiver.h"
#include "fdivedoc.h"
#include "finddlg.h"
#include "ffile.h"
#include "grep.h"
#include "findopti.h"
//#include "optdlg.h"
//#include "findspee.h"
#include "findlist.h"
#include "metainp.h"
#include "greppat.h"
#include "metastr.h"
#include "setpdlg2.h"
#include "filetran.h"
#include "profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CFindOption *vpFindOption;
//extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CKeyOutLogic *vpKeyOutLogic;
extern CMetaStringArray *vpMetaStringArray;
extern CFileTransArray *vpFileTransArray;

IMPLEMENT_SERIAL(CFindDlg, CDialog, 0)

BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_F_SETPATH, OnClickedFSetpath)
	ON_BN_CLICKED(IDC_F_PAST, OnClickedFPast)
	ON_CBN_DROPDOWN(IDC_F_FILE, OnDropdownFFile)
	ON_BN_CLICKED(IDC_F_FILE_DROP, OnClickedFDrop)
	ON_BN_CLICKED(IDC_F_SETFILESPEC, OnClickedFSetfilespec)
	ON_BN_CLICKED(IDC_F_SETSTRSPEC, OnClickedFSetstrspec)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_F_META_INPUT, OnClickedFMetaInput)
	ON_CBN_DROPDOWN(IDC_F_STRING, OnDropdownFString)
	ON_BN_CLICKED(IDC_F_SETMETHODSPEC, OnFSetmethodspec)
	ON_CBN_SELENDOK(IDC_F_STRING, OnSelendokFString)
	ON_CBN_EDITUPDATE(IDC_F_STRING, OnEditupdateFString)
	ON_BN_CLICKED(IDC_F_SETPATH_FOLDER, OnFSetpathFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CFindDlg ダイアログ

void CFindDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		{
		ar << m_cStr;
		ar << m_cFileSpec;
		m_cFilePath.Serialize(ar);
		ar << (WORD)m_fSubDir;
		ar << (WORD)m_fFindFileOnly;
		ar << (WORD)m_fArc;
		}
	else
		{
		ar >> m_cStr;
		ar >> m_cFileSpec;
		m_cFilePath.Serialize(ar);
		WORD w;
		ar >> w;
		m_fSubDir = w;
		ar >> w;
		m_fFindFileOnly = w;
		ar >> w;
#ifdef WIN32
		m_fArc = w;
#else
		//16bit環境では、圧縮ファイルの連続検索は不可！
		m_fArc = FALSE;
#endif
		AddFindSpecs();
		}
}

CFindDlg::CFindDlg(CWnd* pParent)
	: CDialog(CFindDlg::IDD, pParent/*CWnd *pParent*/)
{
	//{{AFX_DATA_INIT(CFindDlg)
	m_iSelForStrSpec = -1;
	m_fMetaChars = FALSE;
	//}}AFX_DATA_INIT
	for (int i=0; i<WFD_COMBOENTRY; i++)
		{
		m_pcStrComboStr[i] = new CString;
		ASSERT(m_pcStrComboStr[i]);
		m_pcStrComboFile[i] = new CString;
		ASSERT(m_pcStrComboFile[i]);
		m_pcStrComboPath[i] = new CString;
		ASSERT(m_pcStrComboPath[i]);
		}
	ReadWriteProfile(TRUE);
	// 行位置を意識する。
	m_optDispNum = 1;
	// ドキュメントを表示する
	m_fDispDoc = TRUE;
}

CFindDlg::~CFindDlg()
{
	ReadWriteProfile(FALSE);
	for (int i=0; i<WFD_COMBOENTRY; i++)
		{
		delete m_pcStrComboStr[i];
		delete m_pcStrComboFile[i];
		delete m_pcStrComboPath[i];
		}

}

// プロファイルを読み書きする。
void CFindDlg::ReadWriteProfile(BOOL fRead)
{
	if (fRead)
		{
		m_fSubDir = theProfile.ReadInt("FindDlg", "fSubDir", (int)TRUE); // default=Find Subdirectory set
#ifdef WIN32
		m_fArc = theProfile.ReadInt("FindDlg", "fArc", (int)TRUE); // default=Find Subdirectory set
#else
		//16bit環境では、圧縮ファイルの連続検索は不可！
		m_fArc = FALSE;
#endif //WIN32
		m_fMetaChars = theProfile.ReadInt("FindDlg", "fMetaChars", (int)FALSE); // default=FALSE
		CDString cdstr;
		int i,k;
		cdstr = "Str";
		for (i=0,k=0; i<WFD_COMBOENTRY; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			*m_pcStrComboStr[k] = theProfile.ReadString("FindDlg", cdstr+vz, "");	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
			if (!m_pcStrComboStr[k]->IsEmpty())
				k++;
			//	m_pcStrComboStr[k]->MakeLower();
			}
		m_cStr = *m_pcStrComboStr[0];//theProfile.ReadString("FindDlg", "STR0", "");

		cdstr = "File";
		for (i=0,k=0; i<WFD_COMBOENTRY; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			*m_pcStrComboFile[k++] = theProfile.ReadString("FindDlg", cdstr+vz, "");	// ｺﾝﾎﾞﾎﾞｯｸｽﾌｧｲﾙｽﾍﾟｯｸ配列
			if (!m_pcStrComboFile[k]->IsEmpty())
				k++;
				//m_pcStrComboFile[k++]->MakeLower();
			}
		m_cStrFile = *m_pcStrComboFile[0];//theProfile.ReadString("FindDlg", "FILE0", "*.*");
		if (m_cStrFile.IsEmpty())
			m_cStrFile = "*.txt";

		cdstr = "Path";
		for (i=0,k=0; i<WFD_COMBOENTRY; i++)
			{
			_itoa_s(i, vz, sizeof(vz), 10);
			*m_pcStrComboPath[k] = theProfile.ReadString("FindDlg", cdstr+vz, "");	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
			if (!m_pcStrComboPath[k]->IsEmpty())
				k++;
			//	m_pcStrComboPath[k++]->MakeLower();
			}
		// 一つもｴﾝﾄﾘｰがない場合は、カレントパスをｴﾝﾄﾘｰする
		if (k==0)
			{
			*m_pcStrComboPath[0] = GetCurrentPath();
			//m_pcStrComboPath[0]->MakeLower();
			RemoveLastBackSlash(m_pcStrComboPath[0]);
			}
		m_cStrPath = *m_pcStrComboPath[0];
		}
	else
		{
		while(theProfile.WriteInt("FindDlg", "fSubDir", m_fSubDir)==0)
			{
			switch(BeepMessage(IDS_WRITEOPT_DISKERR, MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION))
				{
				case IDABORT:
					return;
					break;
				case IDRETRY:
					continue;
					break;
				case IDIGNORE:
					goto GoGo;
					break;
				}
			}
GoGo:
		theProfile.WriteInt("FindDlg", "fArc", m_fArc);
		theProfile.WriteInt("FindDlg", "fMetaChars", m_fMetaChars);

		CDString cdstr;
		int i,k;
		cdstr = "Str";
		for (i=0,k=0; i<WFD_COMBOENTRY; i++)
			{
			if (!m_pcStrComboStr[i]->IsEmpty())
				{
				_itoa_s(i, vz, sizeof(vz), 10);
				theProfile.WriteString("FindDlg", cdstr+vz, m_pcStrComboStr[i]->GetBuffer(0));	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
				}
			}
		cdstr = "File";
		for (i=0,k=0; i<WFD_COMBOENTRY; i++)
			{
			if (!m_pcStrComboFile[i]->IsEmpty())
				{
				_itoa_s(i, vz, sizeof(vz), 10);
				theProfile.WriteString("FindDlg", cdstr+vz, m_pcStrComboFile[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽﾌｧｲﾙｽﾍﾟｯｸ配列
				}
			}
		cdstr = "Path";
		for (i=0,k=0; i<WFD_COMBOENTRY; i++)
			{
			if (!m_pcStrComboPath[i]->IsEmpty())
				{
				_itoa_s(i, vz, sizeof(vz), 10);
				theProfile.WriteString("FindDlg", cdstr+vz, m_pcStrComboPath[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽﾊﾟｽ配列
				}
			}
		}
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
	DDX_Control(pDX, IDC_F_CMB_STRSPEC, m_combStrSpec);
	DDX_Control(pDX, IDC_F_PATH, m_comboPath);
	DDX_Control(pDX, IDC_F_FILE, m_comboFile);
	DDX_Control(pDX, IDC_F_STRING, m_comboStr);
	DDX_CBString(pDX, IDC_F_STRING, m_cStr);
	DDV_MaxChars(pDX, m_cStr, 255);
	DDX_CBString(pDX, IDC_F_FILE, m_cStrFile);
	DDX_CBString(pDX, IDC_F_PATH, m_cStrPath);
	DDX_Check(pDX, IDC_F_SUBDIR, m_fSubDir);
	DDX_Check(pDX, IDC_F_ARC, m_fArc);
	DDX_CBIndex(pDX, IDC_F_CMB_STRSPEC, m_iSelForStrSpec);
	DDX_Check(pDX, IDC_F_META_INPUT, m_fMetaChars);
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CFindDlg メッセージハンドラ

BOOL CFindDlg::OnInitDialog()
{
	int i;

	CDialog::OnInitDialog();

	CenterWindow();


	CString cstr;
	cstr.LoadString(IDS_TITESEARCH);
	// ﾄﾞﾛｯﾌﾟﾎﾞﾀﾝ2を押していない。
	m_fOnDropBtn2 = FALSE;
	
	
	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
	m_combStrSpec.ResetContent();
	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
	m_comboStr.ResetContent();
	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
	m_comboFile.ResetContent();
	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
	m_comboPath.ResetContent();
	// ｺﾝﾄﾛｰﾙのｲﾆｼｬﾙｾｯﾄ
	// ｻﾌﾞﾃﾞｨﾚｸﾄﾘも検索？
	//CheckDlgButton(IDC_F_SUBDIR,m_fSubDir);
	// 検索文字列
	SetDlgItemText(IDC_F_STRING, m_cStr/*m_cStr.GetBuffer(0)*/);
	// 検索ファイル
	SetDlgItemText(IDC_F_FILE, m_cStrFile.GetBuffer(0));

	for (i=0; i<m_strSpec.m_aryStr.GetSize(); i++)
		m_combStrSpec.AddString(m_strSpec.m_aryStr[i].GetBuffer(0));
	m_combStrSpec.SetCurSel(m_strSpec.m_iSel);

	// ""空白文字列の取り扱い：
	// 空白文字列は、コンボボックス中に入れない。
	for (i=0; i<WFD_COMBOENTRY; i++)
		{
		if (!m_pcStrComboStr[i]->IsEmpty())
			m_comboStr.AddString(m_pcStrComboStr[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
		if (!m_pcStrComboFile[i]->IsEmpty())
			m_comboFile.AddString(m_pcStrComboFile[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
		if (!m_pcStrComboPath[i]->IsEmpty())
			m_comboPath.AddString(m_pcStrComboPath[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
		}
#ifdef SHIBORI	
	if (((CFdiverDoc *)((CFrameWnd *)AfxGetApp()->m_pMainWnd)->GetActiveDocument())->m_pFindList->GetMemEntrys()>0) //ﾘｽﾄに項目があるか？
		m_comboPath.AddString(cstr.GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
#endif //SHIBORI

	if (m_cStrPath==cstr.GetBuffer(0))
		{
		if (m_comboPath.SelectString(0,m_cStrPath)==CB_ERR)
			m_comboPath.SetCurSel(0);
		}
	else
		m_comboPath.SetCurSel(0);

	m_comboStr.SetFocus();

#ifdef WIN32
	GetDlgItem(IDC_F_ARC)->EnableWindow(vpFileTransArray->FArcSupport());
#else
	//16bit環境では、圧縮ファイルの連続検索は不可！
	GetDlgItem(IDC_F_ARC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_F_ARC)->EnableWindow(FALSE);
#endif

	return 0;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CFindDlg::OnClose()
{
	
	CDialog::OnClose();
}

void CFindDlg::OnOK()
{
	if (FGoFind())
		{
		AddFindSpecs();
		EndDialog(TRUE);
		}
}

void CFindDlg::AddFindSpecs()
{
	AddFindStrSpec(m_cStr.GetBuffer(0));
	AddFindFileSpec(m_cFileSpec.GetBuffer(0));
	AddFindPathSpec(m_cFilePath.GetBuffer());
}

void CFindDlg::AddFindStrSpec(char *sz)
{
	// 検索文字列
	m_cStr = sz;
	if (*sz)
		{
		int i;
		for (i=0; i<WFD_COMBOENTRY; i++)
			{
			if (*m_pcStrComboStr[i]==sz)
				break;
			}
		if (i>0)
			{
			if (i==WFD_COMBOENTRY)
				i--;
			delete m_pcStrComboStr[i];
			memmove((void *)&m_pcStrComboStr[1],(void *)&m_pcStrComboStr[0], sizeof(m_pcStrComboStr[0])*i);
			m_pcStrComboStr[0] = new CString(sz);
			}
		}
}
void CFindDlg::AddFindFileSpec(char *sz)
{
	// 検索ﾌｧｲﾙｽﾍﾟｯｸ
	m_cStrFile = sz;
	if (*sz)
		{
		int i;
		for (i=0; i<WFD_COMBOENTRY; i++)
			{
			if (*m_pcStrComboFile[i]==sz)
				break;
			}
		if (i>0)
			{
			if (i==WFD_COMBOENTRY)
				i--;
			delete m_pcStrComboFile[i];
			memmove((void *)&m_pcStrComboFile[1],(void *)&m_pcStrComboFile[0], sizeof(m_pcStrComboFile[0])*i);
			m_pcStrComboFile[0] = new CString(sz);
			}
		}

}

void CFindDlg::AddFindPathSpec(char *sz, BOOL bAppend)
{
	int i;
	if (!sz || *sz=='\0')
		return;
	if (bAppend) {
		if (m_cStrPath!="")
			m_cStrPath += chSemi;
		m_cStrPath += sz;
	}else{
		m_cStrPath = sz;
	}
	//m_cStrPath.MakeLower();

	RemoveLastBackSlash(&m_cStrPath);
	// 検索パス
	for (i=0; i<WFD_COMBOENTRY; i++) {
		if (*m_pcStrComboPath[i]==m_cStrPath.GetBuffer(0))
			break;
	}
	if (i>0){
		if (i==WFD_COMBOENTRY)
			i--;
		delete m_pcStrComboPath[i];
		memmove((void *)&m_pcStrComboPath[1],(void *)&m_pcStrComboPath[0], sizeof(m_pcStrComboPath[0])*i);
		m_pcStrComboPath[0] = new CString(m_cStrPath);
	}
}

BOOL CFindDlg::FGoFind()
{
	// ｺﾝﾄﾛｰﾙ情報取得
	UpdateData(TRUE);	// get
	ASSERT(m_iSelForStrSpec>=0);

	m_strSpec.m_iSel = m_iSelForStrSpec;
	
	// 検索文字列あり？
	if (FValidFindSpec())
		return TRUE;
	else
		return FALSE;
}

// 指定された検索条件は正しいか？
BOOL CFindDlg::FValidFindSpec()
{
	CWaitCursor cur;
	CString cstr;

	m_fFindFileOnly=m_cStr.IsEmpty();
	// ﾌｧｲﾙのみ検索ではなくて、且つ正規表現フラグＯＮか？
	if (!m_fFindFileOnly && m_fMetaChars)
		{
		// 正規表現をチェックする
		UINT ui = 0;
		//ニュートラル以外は、エラーメッセージリソースＩＤを取得する
		if (!vpKeyOutLogic->Initialize(m_cStr.GetBuffer(0)))
			{
			m_comboStr.SetFocus();
			return FALSE;
			}
		}

	if (m_cStrFile.IsEmpty())
		m_cStrFile = szStarDotStar;

	cstr.LoadString(IDS_TITESEARCH);
	if (m_cStrPath==cstr.GetBuffer(0))
		{
		m_cFileSpec = m_cStrFile.GetBuffer(0);
		//m_cFileSpec.MakeLower();
		m_cFilePath = "";
		return TRUE;
		}

	m_cFileSpec = m_cStrFile.GetBuffer(0);
	m_cFileSpec.MakeLower();
	m_cFilePath = m_cStrPath;
	//m_cFilePath.GetString()->MakeLower();

	CDPathSpec cdPathSpec;
	CString cSpec;
	BOFFSET offset_first;
	cdPathSpec.AddSpecString(m_cFilePath.GetBuffer());
	for (int i=0; !(cSpec=cdPathSpec.GetString(i, &offset_first)).IsEmpty(); i++) {
		if (!CheckPath(cSpec.GetBuffer(0))) {
			m_comboPath.SetEditSel(offset_first, offset_first+cSpec.GetLength());
			AfxMessageBox(IDS_INVAL_PATH);
			m_comboPath.SetFocus();
			m_comboPath.SetEditSel(offset_first, offset_first+cSpec.GetLength());
			return FALSE;
		}
	}
	m_cFilePath = cdPathSpec;

	return TRUE;
}

void CFindDlg::OnCancel()
{
	EndDialog(FALSE);
}





void CFindDlg::OnClickedFPast()
{
#ifdef METASTRING
	if (m_comboStr.GetDroppedState())
		{
		m_comboStr.ShowDropDown(FALSE);
		}
	else
		{
		CString cstr;
		UpdateData(TRUE);
		// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列削除
		while(m_comboStr.GetCount()>0)
			m_comboStr.DeleteString(0);
		for (int i=0; i<vpMetaStringArray->GetSize(); i++)
			{ //Titleのみを設定する
			cstr = vpMetaStringArray->PGetMetaString(i)->GetStrForTitle();
			m_comboStr.AddString(cstr.GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
			}
		//m_fMetaChars = TRUE; //SPEC:正規表現チェックボックスをＯＮ
		UpdateData(FALSE);
		m_comboStr.SetFocus();
		m_fOnDropBtn2 = TRUE;
		m_comboStr.ShowDropDown();
		m_fOnDropBtn2 = FALSE;
		}
#else
//not use
	m_comboStr.SetEditSel(0,-1);
	m_comboStr.Clear();
	m_comboStr.Paste();
	m_comboStr.SetEditSel(0,-1);
	m_comboStr.SetFocus();
#endif
}

void CFindDlg::OnDropdownFString()
{
#ifdef METASTRING
	if (m_fOnDropBtn2)
		return;
	UpdateData(TRUE);
	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列削除
	while(m_comboStr.GetCount()>0)
		m_comboStr.DeleteString(0);
	// 空白文字列は、コンボボックス中に入れない。
	for (int i=0; i<WFD_COMBOENTRY; i++)
		{
		if (!m_pcStrComboStr[i]->IsEmpty())
			m_comboStr.AddString(m_pcStrComboStr[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
		}
	UpdateData(FALSE);
#endif //METASTRING
}

void CFindDlg::OnClickedFDrop()
{
	if (m_comboFile.GetDroppedState())
		{
		m_comboFile.ShowDropDown(FALSE);
		}
	else
		{
		UpdateData(TRUE);
		// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列削除
		while(m_comboFile.GetCount()>0)
			m_comboFile.DeleteString(0);
		for (int i=0; i<vpFindOption->m_aryStrFiles.GetSize(); i++)
			{ //CComboBox
			m_comboFile.AddString(vpFindOption->m_aryStrFiles[i].GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
			}
		UpdateData(FALSE);
		m_comboFile.SetFocus();
		m_fOnDropBtn2 = TRUE;
		m_comboFile.ShowDropDown();
		m_fOnDropBtn2 = FALSE;
		}
}

void CFindDlg::OnDropdownFFile()
{
	if (m_fOnDropBtn2)
		return;
	UpdateData(TRUE);
	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列削除
	while(m_comboFile.GetCount()>0)
		m_comboFile.DeleteString(0);
	// 空白文字列は、コンボボックス中に入れない。
	for (int i=0; i<WFD_COMBOENTRY; i++)
		{
		if (!m_pcStrComboFile[i]->IsEmpty())
			m_comboFile.AddString(m_pcStrComboFile[i]->GetBuffer(0));// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
		}
	UpdateData(FALSE);
}



void CFindDlg::OnClickedFSetfilespec()
{
	m_fileSpecDlg.DoModal();
}



void CFindDlg::OnDestroy()
{
	CDialog::OnDestroy();
/*	
	// TODO: この位置にメッセージ ハンドラのコードを追加してください。
	ReadWriteProfile(FALSE);
	for (int i=0; i<WFD_COMBOENTRY; i++)
		{
		delete m_pcStrComboStr[i];
		delete m_pcStrComboFile[i];
		delete m_pcStrComboPath[i];
		}
*/	
}

void CFindDlg::OnClickedFMetaInput()
{
	UpdateData(TRUE);
	/*if (m_fMetaChars && vpFindOption->m_fMetaHelp)
		{
		CMetaInputDlg metaInputDlg;
		metaInputDlg.Initialize(&m_cStr, vpMetaStringArray);
		metaInputDlg.DoModal();

		m_comboStr.SetEditSel(0,-1);
		m_comboStr.Clear();
		SetDlgItemText(IDC_F_STRING, m_cStr);
		m_comboStr.SetEditSel(0,-1);
		m_comboStr.SetFocus();
		}
	*/
}

void CFindDlg::OnFSetmethodspec() 
{
	UpdateData(TRUE);
	m_strSpec.m_iSel = m_iSelForStrSpec;
	CStrSpecDlg strSpecDlg;

	strSpecDlg.Initialize(&m_strSpec);
	strSpecDlg.DoModal();

	// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
	m_combStrSpec.ResetContent();
	for (int i=0; i<m_strSpec.m_aryStr.GetSize(); i++)
		m_combStrSpec.AddString(m_strSpec.m_aryStr[i].GetBuffer(0));
	m_combStrSpec.SetCurSel(m_strSpec.m_iSel);
}

void CFindDlg::OnClickedFSetstrspec()
{
	UpdateData(TRUE);
	CMetaInputDlg metaInputDlg;
	metaInputDlg.Initialize(&m_cStr, vpMetaStringArray);
	metaInputDlg.DoModal();

	//m_comboStr.SetEditSel(0,-1);
	//m_comboStr.Clear();
	SetDlgItemText(IDC_F_STRING, m_cStr/*m_cStr.GetBuffer(0)*/);
	m_comboStr.SetEditSel(0,-1);
	m_comboStr.SetFocus();
	OnEditupdateFString();
}


void CFindDlg::OnSelendokFString() 
{
	if (m_comboStr.GetCurSel()!=CB_ERR)
		{
		m_comboStr.GetLBText(m_comboStr.GetCurSel(), m_cStr);
		BOOL fMetaChars = FIsMetaChars(m_cStr);
		if (fMetaChars!=m_fMetaChars)
			{
			m_fMetaChars = fMetaChars;
			CheckDlgButton(IDC_F_META_INPUT, m_fMetaChars ? BST_CHECKED:BST_UNCHECKED);
			}
		}
}

BOOL CFindDlg::FIsMetaChars(CString &str)
{
	BOOL fMetaChars = m_fMetaChars;
	if (str.Find(_T("[["))==0 && str.Find(_T("]]"))==(str.GetLength()-2))
		fMetaChars = TRUE;
//	else if (!str.IsEmpty()) {
//		fMetaChars = ((vpKeyOutLogic->Initialize(m_cStr.GetBuffer(0), FALSE)) &&
//		vpKeyOutLogic->GetLogicStr()!="2");
//	}
		//	}else
//		fMetaChars = FALSE;
	return fMetaChars;
}


void CFindDlg::OnEditupdateFString() 
{
	GetDlgItemText(IDC_F_STRING,m_cStr);

	BOOL fMetaChars = FIsMetaChars(m_cStr);
	if (fMetaChars!=m_fMetaChars)
		{
		m_fMetaChars = fMetaChars;
		CheckDlgButton(IDC_F_META_INPUT, m_fMetaChars ? BST_CHECKED:BST_UNCHECKED);
		}
}

void CFindDlg::OnClickedFSetpath()
{
	if (m_comboPath.GetCurSel()>=0)
		m_comboPath.GetLBText(m_comboPath.GetCurSel(), m_cStrPath);
	m_cFilePath = m_cStrPath;

	CDPathSpec cdPathSpec;
	CString cSpec;
	cdPathSpec.AddSpecString(m_cFilePath.GetBuffer());
	if (cdPathSpec.GetSize()>0)
		cSpec = cdPathSpec.GetString(cdPathSpec.GetSize()-1);

	
	// 絞り込み検索ボタンの初期状態設定
	int iTiteSearch;
	CString cstrTite;
	cstrTite.LoadString(IDS_TITESEARCH);
	if (((CFdiverDoc *)((CFrameWnd *)AfxGetApp()->m_pMainWnd)->GetActiveDocument())->m_pFindList->GetMemEntrys()>0)
	 //ﾘｽﾄに項目があるか？
		iTiteSearch = (cSpec == cstrTite ? 1:0); /*1==check!*/
	else
		iTiteSearch = -1;	// グレーに！
	
	CSetPathDlgForScan PathDlg(cSpec.GetBuffer(0), iTiteSearch);

	if (PathDlg.DoModal())
		{
		// 検索パス
		if (PathDlg.m_iTiteSearch>0)
			{
			ASSERT(m_comboPath.GetCount()>0);
			m_comboPath.SetCurSel(m_comboPath.GetCount()-1);
			}
		else
			{
			if (::GetAsyncKeyState(VK_CONTROL)&0x8000) {
				if (m_cStrPath!="")
					m_cStrPath += chSemi;
				m_cStrPath += PathDlg.GetPathBuffer();
			}else
				m_cStrPath = PathDlg.GetPathBuffer();
			//m_cStrPath.MakeLower();
			CDPathSpec cdPathSpec;
			cdPathSpec.AddSpecString(m_cStrPath.GetBuffer(0));
			m_cStrPath = cdPathSpec;

			m_comboPath.InsertString(0, m_cStrPath);// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
			if (m_comboPath.GetCount()>WFD_COMBOENTRY)
				m_comboPath.DeleteString(WFD_COMBOENTRY);
			m_comboPath.SetCurSel(0);
			}
		}
}

#define LOCATE_FOLDER

#ifdef LOCATE_FOLDER

char   vzPath[2*MAX_PATH];

int CALLBACK
BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData) {
   TCHAR szDir[MAX_PATH];

   switch(uMsg) {
      case BFFM_INITIALIZED: {
         //if (GetCurrentDirectory(DWORD(sizeof(szDir)/sizeof(TCHAR)),
         //                       LPTSTR(szDir))) {
            // WParam is TRUE since you are passing a path.
            // It would be FALSE if you were passing a pidl.
         //   SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)szDir);
         //}
		 SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)vzPath);
         break;
      }
      case BFFM_SELCHANGED: {
         // Set the status window to the currently selected path.
         if (SHGetPathFromIDList((LPITEMIDLIST) lp ,szDir)) {
            SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
         }
         break;
      }
      default:
         break;
   }
   return 0;
}
#endif //#ifdef LOCATE_FOLDER


LPMALLOC pMalloc;    /* Gets the Shell's default allocator */

void CFindDlg::OnFSetpathFolder() 
{
    BROWSEINFO bi; 
    LPSTR lpBuffer[2*MAX_PATH]; 
#ifdef LOCATE_FOLDER
//	HRESULT       hr;
//	OLECHAR       olePath[2*MAX_PATH];
//	ULONG         chEaten;
//	ULONG         dwAttributes;
//	LPSHELLFOLDER pDesktopFolder; 
#endif //#ifdef LOCATE_FOLDER
    LPITEMIDLIST pidl=NULL;
	LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
	HWND hwnd = AfxGetMainWnd()->GetSafeHwnd();
 

	if (m_comboPath.GetCurSel()>=0)
		m_comboPath.GetLBText(m_comboPath.GetCurSel(), m_cStrPath);
	m_cFilePath = m_cStrPath;

	if (::SHGetMalloc(&pMalloc) != NOERROR)
		return;

#ifdef LOCATE_FOLDER
    //
    // Convert the path to an ITEMIDLIST.
    //
	CDString str = m_cStrPath;
	RemoveLastBackSlash(&str);
	strcpy_s((char*)vzPath, sizeof(vzPath), str);
//	if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder))) {
//		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, vzPath, -1,
//							olePath, MAX_PATH);
//		hr = pDesktopFolder->ParseDisplayName( NULL,
//													  NULL,
//													  olePath,
//													  &chEaten,
//													  &pidl,
//													  &dwAttributes);
//		if (FAILED(hr))
//			pidl = NULL;
//	}
#endif //#ifdef LOCATE_FOLDER

    // Allocate a buffer to receive browse information. 
    //if ((lpBuffer = (LPSTR) pMalloc->lpVtbl->Alloc( 
    //        pMalloc, MAX_PATH)) == NULL) 
    //if ((lpBuffer = (LPSTR) pMalloc->Alloc( 
    //       MAX_PATH)) == NULL) 
    //    goto CleanUp;
 
    // Get the PIDL for the Programs folder. 
    //if (!SUCCEEDED(SHGetSpecialFolderLocation( 
    //        hwnd, CSIDL_PROGRAMS, &pidlPrograms))) { 
        //pMalloc->lpVtbl->Free(pMalloc, lpBuffer); 
        //pMalloc->Free(lpBuffer); 
        //goto CleanUp;
    //} 
 
    // Fill in the BROWSEINFO structure. 
    CString strTitle;
	strTitle.LoadString(IDS_PATHDLG_TITLE);
    bi.hwndOwner = hwnd; 
    bi.pidlRoot = pidl; 
    bi.pszDisplayName = (char*)lpBuffer; 
	bi.lpszTitle = strTitle;
    bi.ulFlags = BIF_RETURNONLYFSDIRS;//BIF_RETURNFSANCESTORS; 
    bi.lpfn = BrowseCallbackProc; 
    bi.lParam = 0; 
 
    // Browse for a folder and return its PIDL. 
    pidlBrowse = SHBrowseForFolder(&bi); 
    if (pidlBrowse != NULL) { 
 
        if (SHGetPathFromIDList(pidlBrowse, (char*)lpBuffer)) {
			if (::GetAsyncKeyState(VK_CONTROL)&0x8000) {
				if (m_cStrPath!="")
					m_cStrPath += chSemi;
				m_cStrPath += (char*)lpBuffer;
			}else
				m_cStrPath = (char*)lpBuffer;
			//m_cStrPath.MakeLower();
			CDPathSpec cdPathSpec;
			cdPathSpec.AddSpecString(m_cStrPath.GetBuffer(0));
			m_cStrPath = cdPathSpec;


			m_comboPath.InsertString(0, m_cStrPath);// ｺﾝﾎﾞﾎﾞｯｸｽ検索文字列配列
			if (m_comboPath.GetCount()>WFD_COMBOENTRY)
				m_comboPath.DeleteString(WFD_COMBOENTRY);
			m_comboPath.SetCurSel(0);
		}
        // Show the display name, title, and file system path. 
        //MessageBox(hwnd, lpBuffer, "Display name", MB_OK); 
        //if (SHGetPathFromIDList(pidlBrowse, lpBuffer)) 
        //   SetWindowText(hwnd, lpBuffer); 
 
        // Free the PIDL returned by SHBrowseForFolder. 
        //pMalloc->lpVtbl->Free(pMalloc, pidlBrowse); 
        pMalloc->Free(pidlBrowse); 
    } 

    //pMalloc->lpVtbl->Free(pMalloc, pidl); 
	if (pidl)
		pMalloc->Free(pidl); 
    //pMalloc->lpVtbl->Free(pMalloc, lpBuffer); 
    //pMalloc->Free(lpBuffer); 
//CleanUp:
     // Release the shell's allocator.
	pMalloc->Release();
}
