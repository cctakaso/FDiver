/*    PortTool v2.2     FILESPEC.CPP          */

// filespec.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "fdiver.h"
#include "..\mdfc\dfile.h"
#include "filespec.h"
#include "profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSpecDlg ダイアログ

CFileSpecDlg::CFileSpecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSpecDlg::IDD, pParent)
{
	ReadWriteProfile(TRUE);
	//{{AFX_DATA_INIT(CFileSpecDlg)
//	m_fAtrRead = FALSE;
//	m_fAtrArchive = FALSE;
//	m_fAtrHiden = FALSE;
//	m_fAtrSystem = FALSE;
//	m_fAtrOther = FALSE;
//	m_fAtr = FALSE;
	//}}AFX_DATA_INIT
	// 時間ｲﾆｼｬﾙ
	CTime ctime;
	m_optTime = 0;
	m_tFromTime = 0;
	m_tGoTime = 0;
	m_pFileSpecDlg = NULL;
}

void CFileSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSpecDlg)
//	DDX_Check(pDX, IDC_F_ATR_READ, m_fAtrRead);
	DDX_Check(pDX, IDC_F_HIDEFILE, m_fHideFile);
	DDX_Check(pDX, IDC_F_OTHERFILE, m_fOtherFile);
	DDX_Check(pDX, IDC_F_PRGFILE, m_fProgFile);
	DDX_Check(pDX, IDC_F_DOCFILE, m_fDocFile);
	DDX_Check(pDX, IDC_F_SYSFILE, m_fSysFile);

	DDX_Check(pDX, IDC_F_DOC, m_fdoc);
	DDX_Check(pDX, IDC_F_DOCX, m_fdocx);
	DDX_Check(pDX, IDC_F_XLS, m_fxls);
	DDX_Check(pDX, IDC_F_XLSX, m_fxlsx);
	DDX_Check(pDX, IDC_F_PPT, m_fppt);
	DDX_Check(pDX, IDC_F_PPTX, m_fpptx);
	DDX_Check(pDX, IDC_F_WRI, m_fwri);

	DDX_Check(pDX, IDC_F_JAW, m_fjaw);
	DDX_Check(pDX, IDC_F_JBW, m_fjbw);
	DDX_Check(pDX, IDC_F_JFW, m_fjfw);
	DDX_Check(pDX, IDC_F_JTD, m_fjtd);

	DDX_Check(pDX, IDC_F_PDF, m_fpdf);
	DDX_Check(pDX, IDC_F_HTML, m_fhtml);
	DDX_Check(pDX, IDC_F_EML, m_feml);

	DDX_Check(pDX, IDC_F_SXW, m_fsxw);
	DDX_Check(pDX, IDC_F_SXC, m_fsxc);
	DDX_Check(pDX, IDC_F_SXI, m_fsxi);
	DDX_Check(pDX, IDC_F_SXD, m_fsxd);

	DDX_Check(pDX, IDC_F_ODT, m_fodt);
	DDX_Check(pDX, IDC_F_ODS, m_fods);
	DDX_Check(pDX, IDC_F_ODP, m_fodp);
	DDX_Check(pDX, IDC_F_ODG, m_fodg);

	DDX_Check(pDX, IDC_F_OAS, m_foas);
	DDX_Check(pDX, IDC_F_BUN, m_fbun);
	DDX_Check(pDX, IDC_F_123, m_f123);
	DDX_Check(pDX, IDC_F_RTF, m_frtf);


//	DDX_Check(pDX, IDC_F_ATR_ARCHIVE, m_fAtrArchive);
//	DDX_Check(pDX, IDC_F_ATR_HIDEN, m_fAtrHiden);
//	DDX_Check(pDX, IDC_F_ATR_SYSTEM, m_fAtrSystem);
//	DDX_Check(pDX, IDC_F_ATR_OTHER, m_fAtrOther);
//	DDX_Check(pDX, IDC_F_ATR, m_fAtr);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate)
		{
		m_optTime = GetCheckedRadioButton(IDC_F_NOTIME, IDC_F_SETDAY)-IDC_F_NOTIME;
		DDX_Text(pDX, IDC_F_FROMDAY, m_cstrFromDay);
		DDX_Text(pDX, IDC_F_FROMHOUR, m_cstrFromHour);
		DDX_Text(pDX, IDC_F_GODAY, m_cstrGoDay);
		DDX_Text(pDX, IDC_F_GOHOUR, m_cstrGoHour);
		if (m_optTime==0)
			{
			m_tFromTime = 0;
			m_tGoTime = 0;
			}
		else
			{
			CTime *pctime;
			int nYearMonthDay[5];
			int i,k,j;
			CString *pcstr;
			for (j=0; j<2; j++)
				{
				if (j==0)
					pcstr=&m_cstrFromDay;
				else
					pcstr=&m_cstrGoDay;
				if (pcstr->IsEmpty())
					{
					if (j==0)
						m_tFromTime = 0;
					else
						m_tGoTime = 0;
					continue;
					}
				memset((void *)nYearMonthDay, 0, sizeof(nYearMonthDay));
				for (i=0, k=0; i<pcstr->GetLength() && k<3; i++)
					{
					if ((*pcstr)[i]>='0' && (*pcstr)[i]<='9')
						nYearMonthDay[k]=nYearMonthDay[k]*10 + (int)((*pcstr)[i]-'0');
					else
						k++;
					}
				if (j==0)
					pcstr=&m_cstrFromHour;
				else
					pcstr=&m_cstrGoHour;
				for (i=0, k=3; i<pcstr->GetLength() && k<5; i++)
					{
					if ((*pcstr)[i]>='0' && (*pcstr)[i]<='9')
						nYearMonthDay[k]=nYearMonthDay[k]*10 + (int)((*pcstr)[i]-'0');
					else
						k++;
					}
				if (pcstr->IsEmpty())
					{
					if (j==0)
						{
						nYearMonthDay[3] = 0;
						nYearMonthDay[4] = 0;
						}
					else
						{
						nYearMonthDay[3] = 23;
						nYearMonthDay[4] = 59;
						}
					continue;
					}
				if (nYearMonthDay[0]<100)
					nYearMonthDay[0] += 1900;
				pctime = new CTime(nYearMonthDay[0],nYearMonthDay[1],nYearMonthDay[2],nYearMonthDay[3],nYearMonthDay[4],0);
				if (j==0)
					m_tFromTime = pctime->GetTime();
				else
					m_tGoTime = pctime->GetTime();
				delete pctime;
				}
			}
		}
	else
		{
		CheckRadioButton(IDC_F_NOTIME, IDC_F_SETDAY, m_optTime+IDC_F_NOTIME);
		if (m_tFromTime==0 && m_tGoTime==0)
			{
			// Today set
			CTime ctime = CTime::GetCurrentTime();
			m_tFromTime = ctime.GetTime();
			m_tGoTime = ctime.GetTime();
			m_cstrFromDay = ctime.Format("%Y/%m/%d");	// time_t
			m_cstrFromHour = "00:00";
			m_cstrGoDay = ctime.Format("%Y/%m/%d");
			m_cstrGoHour = "23:59";
			}
		EnableTimeCtr(m_optTime != 0);
		DDX_Text(pDX, IDC_F_FROMDAY, m_cstrFromDay);
		DDX_Text(pDX, IDC_F_FROMHOUR, m_cstrFromHour);
		DDX_Text(pDX, IDC_F_GODAY, m_cstrGoDay);
		DDX_Text(pDX, IDC_F_GOHOUR, m_cstrGoHour);
		//	}
		}

}

BEGIN_MESSAGE_MAP(CFileSpecDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSpecDlg)
	ON_BN_CLICKED(IDC_F_NOTIME, OnClickedOfNotime)
	ON_BN_CLICKED(IDC_F_TODAY, OnClickedOfToday)
	ON_BN_CLICKED(IDC_F_YESTERDAY, OnClickedOfYesterday)
	ON_BN_CLICKED(IDC_F_THISWEEK, OnClickedOfThisweek)
	ON_BN_CLICKED(IDC_F_SETDAY, OnClickedOfSetday)
	ON_EN_CHANGE(IDC_F_FROMDAY, OnChangeTimeCtr)
	ON_EN_CHANGE(IDC_F_FROMHOUR, OnChangeTimeCtr)
	ON_EN_CHANGE(IDC_F_GODAY, OnChangeTimeCtr)
	ON_EN_CHANGE(IDC_F_GOHOUR, OnChangeTimeCtr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSpecDlg メッセージハンドラ

void CFileSpecDlg::OnOK()
{
	UpdateData(TRUE);
	if (!m_fSysFile && !m_fHideFile && !m_fProgFile && !m_fDocFile && !m_fOtherFile)
		{
		Message(IDS_OPT_FILETYPE);
		return ;
		}
	else if (m_optTime+IDC_F_NOTIME == IDC_F_SETDAY)
		{
		CTime ctime;
		ctime = ctime.GetCurrentTime();
		time_t tCurrent = ctime.GetTime();
		if (m_tFromTime>tCurrent)
			{
			Message(IDS_TOLARGETIME_ERR);
			m_ceFromDay.SetSel(0,-1);
			m_ceFromDay.SetFocus();
			return;
			}
		else if (m_tFromTime==0 && m_tGoTime)
			{
			Message(IDS_PLEASE_INPUTTIME);
			m_ceFromDay.SetFocus();
			return;
			}
		}

	delete m_pFileSpecDlg;

	CDialog::OnOK();
}

void CFileSpecDlg::OnClickedOfNotime()
{
	EnableTimeCtr(FALSE);
}

void CFileSpecDlg::OnClickedOfSetday()
{
	EnableTimeCtr(TRUE);
}

void CFileSpecDlg::OnClickedOfToday()
{
	UpdateData(TRUE);
	CTime ctime = CTime::GetCurrentTime();
	m_tFromTime = ctime.GetTime();
	m_tGoTime = m_tFromTime;
	m_cstrFromDay = ctime.Format("%Y/%m/%d");	// time_t
	m_cstrFromHour = "00:00";
	m_cstrGoDay = m_cstrFromDay;
	m_cstrGoHour = "23:59";
	m_optTime = IDC_F_TODAY-IDC_F_NOTIME;
	UpdateData(FALSE);
}
void CFileSpecDlg::OnClickedOfYesterday()
{
	UpdateData(TRUE);
	CTime ctime = CTime::GetCurrentTime();
	CTimeSpan ctimespan(1, 0, 0, 0);
	ctime -= ctimespan;
	m_tFromTime = ctime.GetTime();
	m_cstrFromDay = ctime.Format("%Y/%m/%d");	// time_t
	m_cstrFromHour = "00:00";
	m_tGoTime = m_tFromTime;
	m_cstrGoDay = m_cstrFromDay;
	m_cstrGoHour = "23:59";
	m_optTime = IDC_F_YESTERDAY-IDC_F_NOTIME;
	UpdateData(FALSE);
}
void CFileSpecDlg::OnClickedOfThisweek()
{
	UpdateData(TRUE);
	CTime ctime = CTime::GetCurrentTime();
	CTimeSpan ctimespan(ctime.GetDayOfWeek()-1, 0, 0, 0);
	m_tGoTime = ctime.GetTime();
	m_cstrGoDay = ctime.Format("%Y/%m/%d");
	m_cstrGoHour = "23:59";
	ctime -= ctimespan;
	m_tFromTime = ctime.GetTime();
	m_cstrFromDay = ctime.Format("%Y/%m/%d");	// time_t
	m_cstrFromHour = "00:00";
	m_optTime = IDC_F_THISWEEK-IDC_F_NOTIME;
	UpdateData(FALSE);
}


void CFileSpecDlg::EnableTimeCtr(BOOL f)
{
	GetDlgItem(IDC_F_FROMDAY)->EnableWindow(f);
	GetDlgItem(IDC_F_FROMHOUR)->EnableWindow(f);
	GetDlgItem(IDC_F_GODAY)->EnableWindow(f);
	GetDlgItem(IDC_F_GOHOUR)->EnableWindow(f);
}

void CFileSpecDlg::OnChangeTimeCtr()
{
	m_optTime = IDC_F_SETDAY-IDC_F_NOTIME;
	CheckRadioButton(IDC_F_NOTIME, IDC_F_SETDAY, m_optTime+IDC_F_NOTIME);
}

/*
#ifdef WIN32
BOOL CFileSpecDlg::FMatchTime(FILETIME fileTime)
{
	CTime ctime(fileTime);

	time_t tt = ctime.GetTime();

	if (m_tFromTime)
		{
		if (tt<m_tFromTime)
			return FALSE;
		}
	if (m_tGoTime)
		{
		if (tt>m_tGoTime)
			return FALSE;
		}
	return TRUE;
}
#else
BOOL CFileSpecDlg::FMatchTime(unsigned short wDate, unsigned short wTime)
{
	CTime ctime(wDate, wTime);

	time_t tt = ctime.GetTime();

	if (m_tFromTime)
		{
		if (tt<m_tFromTime)
			return FALSE;
		}
	if (m_tGoTime)
		{
		if (tt>m_tGoTime)
			return FALSE;
		}
	return TRUE;
}
#endif //WIN32

#ifdef WIN32
BOOL CFileSpecDlg::FMatchAttr(DWORD b, char *sz)
#else
BOOL CFileSpecDlg::FMatchAttr(BYTE b, char *sz)
#endif //WIN32
{
	if (b & ATTR_HIDDEN)
		{
		if (!m_fHideFile)
			return FALSE;
		}
	if (b & ATTR_SYSTEM)
		{
		if (m_fSysFile)
			return TRUE;
		else
			return FALSE;
		}
	if (m_fProgFile && m_fDocFile && m_fOtherFile)
		return TRUE;
    if (FIsProgFile(sz))
		{
		if (m_fProgFile)
			return TRUE;
		}
    else
		{
		if (m_fDocFile && m_fOtherFile)
			return TRUE;
    	if (FIsDocFile(sz))
			{
			if (m_fDocFile)
				return TRUE;
			}
   		else
			{
			if (m_fOtherFile)
				return TRUE;
			}
		}
	return FALSE;
}

//BOOL CFileSpecDlg::FMatchAttr(BYTE b)
//{
//	if (b & ATTR_HIDDEN && m_fAtrHiden)
//		return TRUE;
//	if (b & ATTR_SYSTEM && m_fAtrSystem)
//		return TRUE;
//	if (b & ATTR_READONLY && m_fAtrRead)
//		return TRUE;
//	if (b & ATTR_ARCHIVE && m_fAtrArchive)
//		return TRUE;
//	if (m_fAtrOther && !(b & (ATTR_HIDDEN | ATTR_SYSTEM | ATTR_READONLY | ATTR_ARCHIVE)))
//		return TRUE;
//	return FALSE;
//}
*/

// プロファイルを読み書きする。
void CFileSpecDlg::ReadWriteProfile(BOOL fRead)
{
	if (fRead)
		{
		m_fSysFile = theProfile.ReadInt("FindOption", "fSysFile", 0);
		m_fHideFile = theProfile.ReadInt("FindOption", "fHideFile", 0);
		m_fProgFile = theProfile.ReadInt("FindOption", "fProgFile", 0);
		m_fDocFile = theProfile.ReadInt("FindOption", "fDocFile", 1);	// default =TRUE
		m_fOtherFile = theProfile.ReadInt("FindOption", "fOtherFile", 1);

		m_fdoc = theProfile.ReadInt("FindOption", "fdoc", 1);
		m_fdocx = theProfile.ReadInt("FindOption", "fdocx", 1);
		m_fxls = theProfile.ReadInt("FindOption", "fxls", 1);
		m_fxlsx = theProfile.ReadInt("FindOption", "fxlsx", 1);
		m_fppt = theProfile.ReadInt("FindOption", "fppt", 1);
		m_fpptx = theProfile.ReadInt("FindOption", "fpptx", 1);
		m_fwri = theProfile.ReadInt("FindOption", "fwri", 1);

		m_fjaw = theProfile.ReadInt("FindOption", "fjaw", 1);
		m_fjbw = theProfile.ReadInt("FindOption", "fjbw", 1);
		m_fjfw = theProfile.ReadInt("FindOption", "fjfw", 1);
		m_fjtd = theProfile.ReadInt("FindOption", "fjtd", 1);

		m_fpdf = theProfile.ReadInt("FindOption", "fpdf", 1);
		m_fhtml = theProfile.ReadInt("FindOption", "fhtml", 0);	//takaso2010
		m_feml = theProfile.ReadInt("FindOption", "feml", 1);

		m_fsxw = theProfile.ReadInt("FindOption", "fsxw", 1);
		m_fsxc = theProfile.ReadInt("FindOption", "fsxc", 1);
		m_fsxi = theProfile.ReadInt("FindOption", "fsxi", 1);
		m_fsxd = theProfile.ReadInt("FindOption", "fsxd", 1);

		m_fodt = theProfile.ReadInt("FindOption", "fodt", 1);
		m_fods = theProfile.ReadInt("FindOption", "fods", 1);
		m_fodp = theProfile.ReadInt("FindOption", "fodp", 1);
		m_fodg = theProfile.ReadInt("FindOption", "fodg", 1);

		m_foas = theProfile.ReadInt("FindOption", "foas", 1);
		m_fbun = theProfile.ReadInt("FindOption", "fbun", 1);
		m_f123 = theProfile.ReadInt("FindOption", "f123", 1);
		m_frtf = theProfile.ReadInt("FindOption", "frtf", 1);

	}else{
		theProfile.WriteInt("FindOption", "fSysFile", m_fSysFile);
		theProfile.WriteInt("FindOption", "fHideFile", m_fHideFile);
		theProfile.WriteInt("FindOption", "fProgFile", m_fProgFile);
		theProfile.WriteInt("FindOption", "fDocFile", m_fDocFile);
		theProfile.WriteInt("FindOption", "fOtherFile", m_fOtherFile);

		theProfile.WriteInt("FindOption", "fdoc", m_fdoc);
		theProfile.WriteInt("FindOption", "fdocx", m_fdocx);
		theProfile.WriteInt("FindOption", "fxls", m_fxls);
		theProfile.WriteInt("FindOption", "fxlsx", m_fxlsx);
		theProfile.WriteInt("FindOption", "fppt", m_fppt);
		theProfile.WriteInt("FindOption", "fpptx", m_fpptx);
		theProfile.WriteInt("FindOption", "fwri", m_fwri);

		theProfile.WriteInt("FindOption", "fjaw", m_fjaw);
		theProfile.WriteInt("FindOption", "fjbw", m_fjbw);
		theProfile.WriteInt("FindOption", "fjfw", m_fjfw);
		theProfile.WriteInt("FindOption", "fjtd", m_fjtd);

		theProfile.WriteInt("FindOption", "fpdf", m_fpdf);
		theProfile.WriteInt("FindOption", "fhtml", m_fhtml);
		theProfile.WriteInt("FindOption", "feml", m_feml);

		theProfile.WriteInt("FindOption", "fsxw", m_fsxw);
		theProfile.WriteInt("FindOption", "fsxc", m_fsxc);
		theProfile.WriteInt("FindOption", "fsxi", m_fsxi);
		theProfile.WriteInt("FindOption", "fsxd", m_fsxd);

		theProfile.WriteInt("FindOption", "fodt", m_fodt);
		theProfile.WriteInt("FindOption", "fods", m_fods);
		theProfile.WriteInt("FindOption", "fodp", m_fodp);
		theProfile.WriteInt("FindOption", "fodg", m_fodg);

		theProfile.WriteInt("FindOption", "foas", m_foas);
		theProfile.WriteInt("FindOption", "fbun", m_fbun);
		theProfile.WriteInt("FindOption", "f123", m_f123);
		theProfile.WriteInt("FindOption", "frtf", m_frtf);
	}
}


BOOL CFileSpecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();	
	// TODO: この位置にその他の初期化用コードを追加してください。
	// for backup!
	m_pFileSpecDlg = new CFileSpecDlg;
	*m_pFileSpecDlg = this;
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CFileSpecDlg::OnCancel()
{
	*this = m_pFileSpecDlg;
	delete m_pFileSpecDlg;
	
	CDialog::OnCancel();
}

void CFileSpecDlg::operator = ( CFileSpecDlg *pFileSpecDlg )
{
	m_optTime = pFileSpecDlg->m_optTime;
	m_tFromTime = pFileSpecDlg->m_tFromTime;
	m_tGoTime = pFileSpecDlg->m_tGoTime;
	m_fHideFile = pFileSpecDlg->m_fHideFile;
	m_fOtherFile = pFileSpecDlg->m_fOtherFile;
	m_fProgFile = pFileSpecDlg->m_fProgFile;
	m_fDocFile = pFileSpecDlg->m_fDocFile;
	m_fSysFile = pFileSpecDlg->m_fSysFile;

	m_fdoc = pFileSpecDlg->m_fdoc;
	m_fdocx = pFileSpecDlg->m_fdocx;
	m_fxls = pFileSpecDlg->m_fxls;
	m_fxlsx = pFileSpecDlg->m_fxlsx;
	m_fppt = pFileSpecDlg->m_fppt;
	m_fpptx = pFileSpecDlg->m_fpptx;
	m_fwri = pFileSpecDlg->m_fwri;

	m_fjaw = pFileSpecDlg->m_fjaw;
	m_fjbw = pFileSpecDlg->m_fjbw;
	m_fjfw = pFileSpecDlg->m_fjfw;
	m_fjtd = pFileSpecDlg->m_fjtd;

	m_fpdf = pFileSpecDlg->m_fpdf;
	m_fhtml = pFileSpecDlg->m_fhtml;
	m_feml = pFileSpecDlg->m_feml;

	m_fsxw = pFileSpecDlg->m_fsxw;
	m_fsxc = pFileSpecDlg->m_fsxc;
	m_fsxi = pFileSpecDlg->m_fsxi;
	m_fsxd = pFileSpecDlg->m_fsxd;

	m_fodt = pFileSpecDlg->m_fodt;
	m_fods = pFileSpecDlg->m_fods;
	m_fodp = pFileSpecDlg->m_fodp;
	m_fodg = pFileSpecDlg->m_fodg;

	m_foas = pFileSpecDlg->m_foas;
	m_fbun = pFileSpecDlg->m_fbun;
	m_f123 = pFileSpecDlg->m_f123;
	m_frtf = pFileSpecDlg->m_frtf;



	m_cstrFromDay = pFileSpecDlg->m_cstrFromDay;
	m_cstrFromHour = pFileSpecDlg->m_cstrFromHour;
	m_cstrGoDay = pFileSpecDlg->m_cstrGoDay;
	m_cstrGoHour = pFileSpecDlg->m_cstrGoHour;
}

int CFileSpecDlg::GetIAttr()
{
	int iAttr=0;
	iAttr += (m_fSysFile ? FSAT_SYS:0);
	iAttr += (m_fHideFile ? FSAT_HIDE:0);
	iAttr += (m_fProgFile ? FSAT_PROG:0);
	iAttr += (m_fDocFile ? FSAT_DOC:0);
	iAttr += (m_fOtherFile ? FSAT_OTHER:0);
	return iAttr;
}

time_t CFileSpecDlg::GetFromTime()
{
	if (m_optTime==0)
		return 0;
	else
		return m_tFromTime;
}
time_t CFileSpecDlg::GetGoTime()
{
	if (m_optTime==0)
		return 0;
	else
		return m_tGoTime;
}


char *szEXTX_TYPE[EXTX_MAX][6] =
{
	//microsoft
	{"doc","","","","",""},
	{"docx","docm","","","",""},
	{"xls","","","","",""},
	{"xlsx","xlsm","","","",""},
	{"ppt","","","","",""},
	{"pptx","pptm","","","",""},
	{"wri","","","","",""},
	//ジャストシステム
	{"jaw","jtw","","","",""},
	{"jbw","juw","","","",""},
	{"jfw","jvw","","","",""},
	{"jtd","jtt","","","",""},
	//internet
	{"pdf","","","","",""},
	{"html","mht","","","",""},
	{"eml","","","","",""},
	//OpenOffice
	{"sxw","","","","",""},
	{"sxc","","","","",""},
	{"sxi","","","","",""},
	{"sxd","","","","",""},
	//Open Document
	{"odt","","","","",""},
	{"ods","","","","",""},
	{"odp","","","","",""},
	{"odg","","","","",""},
	//Others
	{"oas","oa2","oa3","","",""},
	{"bun","","","","",""},
	{"wj2","wj3","wk3","wk4","123",""},
	{"rtf","","","","",""},
};

EXTX_TYPE CFileSpecDlg::ExtxFromSzExt(char *szExt)
{
	CString cstr = szExt;
	EXTX_TYPE extx = EXTX_NO;
	BOOL f;
	cstr.MakeLower();
	for (int i=0; i<EXTX_MAX && extx == EXTX_NO; i++) {
		for (int k=0; szEXTX_TYPE[i][k][0]!='\0'; k++) {
			if (cstr == szEXTX_TYPE[i][k]) {
				extx =  (EXTX_TYPE)i;
				break;
			}
		}
	}
	switch(extx) {
		case EXTX_DOC:
			f = m_fdoc;
			break;
		case EXTX_DOCX:
			f = m_fdocx;
			break;
		case EXTX_XLS:
			f = m_fxls;
			break;
		case EXTX_XLSX:
			f = m_fxlsx;
			break;
		case EXTX_PPT:
			f = m_fppt;
			break;
		case EXTX_PPTX:
			f = m_fpptx;
			break;
		case EXTX_WRI:
			f = m_fwri;
			break;
	//ジャストシステム
		case EXTX_JAW:
			f = m_fjaw;
			break;
		case EXTX_JBW:
			f = m_fjbw;
			break;
		case EXTX_JFW:
			f = m_fjfw;
			break;
		case EXTX_JTD:
			f = m_fjtd;
			break;
	//internet
		case EXTX_PDF:
			f = m_fpdf;
			break;
		case EXTX_HTML:
			f = m_fhtml;
			break;
		case EXTX_EML:
			f = m_fdoc;
			break;
	//OpenOffice
		case EXTX_SXW:
			f = m_fsxw;
			break;
		case EXTX_SXC:
			f = m_fsxc;
			break;
		case EXTX_SXI:
			f = m_fsxi;
			break;
		case EXTX_SXD:
			f = m_fsxd;
			break;
	//Open Document
		case EXTX_ODT:
			f = m_fodt;
			break;
		case EXTX_ODS:
			f = m_fods;
			break;
		case EXTX_ODP:
			f = m_fodp;
			break;
		case EXTX_ODG:
			f = m_fodg;
			break;
	//Others
		case EXTX_OAS:
			f = m_foas;
			break;
		case EXTX_BUN:
			f = m_fbun;
			break;
		case EXTX_123:
			f = m_f123;
			break;
		case EXTX_RTF:
			f = m_frtf;
			break;
		default:
			f = FALSE;
			break;
	}
	return f ? extx:EXTX_NO;
}
