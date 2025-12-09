/*    PortTool v2.2     CREJIT.CPP          */
// crejit.cpp : インプリメンテーション ファイル
//
//#include "stdlib.h"
#include "stdafx.h"
#include "mdglibs.h"
#include "crejit.h"
#include "time.h"
#include "Fdiver.h"
#include "profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CCrejit ダイアログ

CCrejit::CCrejit(CWnd* pParent /*=NULL*/)
	: CDialog(CCrejit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCrejit)
		// 注意: ClassWizard はこの位置にメンバの初期化処理を追加します。
	m_tLimitTime = 0;
	m_uiTimer = 0;
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// CCrejit メッセージハンドラ
BEGIN_MESSAGE_MAP(CCrejit, CDialog)
	//{{AFX_MSG_MAP(CCrejit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

WORD CCrejit::FInitial()
{
	GetProfile();
	// ﾊﾟｽﾜｰﾄﾞﾁｪｯｸ
	if (!FValidID(&m_sUserID))
		{
		// ﾀｲﾏﾘｸｴｽﾄ
#ifdef NOTUSE
//チェックしない
		for (m_uiTimer = 16; SetTimer(m_uiTimer, 1000, NULL) == 0 && --m_uiTimer>0; );
		if (m_uiTimer==0)
			return CRJ_ER_TIMERREQ;
		else
			{
			KillTimer(m_uiTimer);
			return CRJ_ER_PASSWORD;
			}
#else
		return CRJ_ER_PASSWORD;
#endif
		}
	else
		return CRJ_ER_OK;
}



/*************************************************************************
-- Routine: BOOL CCrejit::WriteLimitTime(time_t ltime)
-- Description and Usage:
		iniファイルに使用有効期限を設定します。
		一度だけしか起動しません。
-- Arguments:
		time_t ltime : iniへ書き込む使用有効期限。 
-- Returns:
		成功した時は TRUE を、失敗した時は FALSE を返します。
-- Notes:
-- History:
		'94.12	- created		(M.Design)
*************************************************************************/

BOOL CCrejit::WriteLimitTime(time_t ltime)
{
	//: warning C4996: '_ltoa': This function or variable may be unsafe. Consider using _ltoa_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//_ltoa(ltime, vz, 10); 
	_ltoa_s(ltime, vz, sizeof(vz), 10); 

	theProfile.WriteString("USER", CRJ_TIME_STR, vz);
	return TRUE;
}


/*************************************************************************
-- Routine: void CCrejit::GetProfile()
-- Description and Usage:
		ユーザーIDを取得します。
-- Arguments:
		char* lpUserID : ユーザーIDの入った文字列のポインタ。
-- Returns:
		成功した時は TRUE を、失敗した時は FALSE を返します。
-- Notes:
-- History:
		'94.12	- created		(M.Design)
*************************************************************************/

void CCrejit::GetProfile()
{

	m_sUserID = theProfile.ReadString("USER", CRJ_ID_STR, NULL);

	if (!FValidID(&m_sUserID))
		{
		CString strTime;
		strTime = theProfile.ReadString("USER", CRJ_TIME_STR, NULL);
		m_tLimitTime = atol(strTime.GetBuffer(0));
		m_sUserID.Empty();
		}
}

/*************************************************************************
-- Routine: BOOL CCrejit::SetProfile()
-- Description and Usage:
		ユーザーIDを取得します。
-- Arguments:
		char* lpUserID : ユーザーIDの入った文字列のポインタ。
-- Returns:
		成功した時は TRUE を、失敗した時は FALSE を返します。
-- Notes:
-- History:
		'94.12	- created		(M.Design)
*************************************************************************/

BOOL CCrejit::SetProfile()
{
	theProfile.WriteString("USER", CRJ_ID_STR, m_sUserID.GetBuffer(CRJ_USERID_LENGTH));
	return TRUE;
}

void CCrejit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCrejit)
	DDX_Control(pDX, IDC_TIMER_TIME, m_csTime);
	DDX_Control(pDX, IDC_TIMER_USERID, m_editUserID);
	DDX_Text(pDX, IDC_TIMER_USERID, m_sUserID);
	DDX_Control(pDX, IDC_CRJTMPID, m_csTmpID);
	//}}AFX_DATA_MAP
}


BOOL CCrejit::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CenterWindow();


	GetProfile();
	if (FValidID(&m_sUserID))
		{
		SetDlgItemText(IDC_MITOROKU, ""); //未登録を削除
		m_uiTimer = 0;
		}
	else
		{
		// TODO: この位置にその他の初期化用コードを追加してください。
		CTime tm = CTime::GetCurrentTime();		// 現在時刻の取得
    	
		if(m_tLimitTime == 0 || m_tLimitTime > (tm.GetTime() + CRJ_TIME_LIMIT) )
			{
			m_tLimitTime = tm.GetTime() + CRJ_TIME_LIMIT;	// 7*24*60*60= 604800
			WriteLimitTime(m_tLimitTime);
			}
		

		srand((unsigned)time(NULL));
	
	#ifdef PLEASE_TEMP_ID
		for (int i=0; i<5; i++)
			m_sTmpID += rand()%25 + 'A';

		m_csTmpID.SetWindowText(m_sTmpID);
	#endif //PLEASE_TEMP_ID

		for (m_uiTimer = 16; SetTimer(m_uiTimer, 1000, NULL) == 0 && --m_uiTimer>0; );
		if (m_uiTimer>0)
			OnTimer(0);
		}

	m_editUserID.SetFocus();

	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります。
}

void CCrejit::OnOK()
{
	// TODO: この位置にその他の検証用のコードを追加してください。
	UpdateData(TRUE);
	if (FValidID(&m_sUserID))
		{
		SetProfile();
		Message(IDS_CRJ_OK);
		if (m_uiTimer>0)
			KillTimer(m_uiTimer);
		EndDialog(IDOK);
		}
#ifdef PLEASE_TEMP_ID
	else if (FValidTmpID(&m_sUserID))
#else
	else if (m_sUserID.IsEmpty())
#endif //PLEASE_TEMP_ID
		{
		CString cstr;
		m_csTime.GetWindowText(cstr);
		if (m_uiTimer>0)
			KillTimer(m_uiTimer);
#ifdef TIME_OVER_IS_BYE		//時間が０なら動作しない
		if (cstr[0]=='0' || cstr[0]=='-')
			EndDialog(IDCANCEL);
		else
#endif 
			EndDialog(IDOK);
		}
	else
		{
		BeepMessage(IDS_CRJ_NG);
		m_editUserID.SetSel(0,-1);
		m_editUserID.SetFocus();
		}
}

BOOL CCrejit::FValidID(CString *pcstr)
{
//#define CRJ_NEW_USERID_LENGTH	12	//"XYIJ9805210B"
//#define CRJ_USERID_LENGTH	9		//"XYIJ0777B"
	//tY6\ryeark\53bY3\rmonth148
	//tY699k8iir/3bY311148
	//tY698kTUW403bY310148
	//tY699kGEaXf3bY39148
	//---99-12345----12---
	//---99-12345----1---
	//01234567890123456789
	if(pcstr->GetLength() >= 19)	{
		long ryear = atol( pcstr->Mid(3,2) );
		long rmonth = atol( (pcstr->GetLength()==19) ? pcstr->Mid(15,1):pcstr->Mid(15,2) );
		long nNumber = atol( pcstr->Mid(6,5) );
	/*	if (pcstr->Left(3) == "tY6"
			&& pcstr->Mid(5,1) == "k"
			&& pcstr->Mid(11,4) == "3bY3"
			&& pcstr->Right(3) == "148"
			&& (ryear >= 94
			|| ryear <= 10)
			&& (rmonth >= 1
			&& rmonth <= 12)
			)
			return TRUE;
	*/
	//ze7\ryeark\53bY3\rmonthq8w
	//ze799m8iir/R2p611q8w
	//ze798mTUW40R2p610q8w
	//ze799mGEaXfR2p69q8w
	//---99-12345----12---
	//---99-12345----1---
	//01234567890123456789
		if  (pcstr->Left(3) == "ze7"
			&& pcstr->Mid(5,1) == "m"
			&& pcstr->Mid(11,4) == "R2p6"
			&& pcstr->Right(3) == "q8w"
			&& (ryear >= 94
			|| ryear <= 10)
			&& (rmonth >= 1
			&& rmonth <= 12)
			)
			return TRUE;
	}
	return FALSE;
/*
	}else if(pcstr->GetLength() == CRJ_NEW_USERID_LENGTH)	{
		pcstr->MakeUpper();
		long nNumber = atol( pcstr->Mid(4,7) );
		return (pcstr->Left(4) == "XYIJ"
			&& nNumber > 0
			&& nNumber < 9999999
			&& pcstr->Right(1) == "B");
	}else if(pcstr->GetLength() == CRJ_USERID_LENGTH) {
		pcstr->MakeUpper();
		long nNumber = atol( pcstr->Mid(4,4) );
		return (pcstr->Left(4) == "XYIJ"
			&& nNumber > 0
			&& nNumber < 9999
			&& pcstr->Right(1) == "B");
	} else { //1060ﾁｪｯｸ 送金代行番号　　：9709-1060-A010 = 14
		if (pcstr->GetLength()==14) {
			return (pcstr->Mid(4,6) == PROJ_SHARE_ID);
		}else
			return FALSE;
	}
*/
}


void CCrejit::OnTimer(UINT nIDEvent)
{
	// TODO: この位置にメッセージ ハンドラのコードを追加するか、またはデフォルト処理の呼び出しを行う。
	
	long nTimeLimit;
	CTime tm = CTime::GetCurrentTime();
	nTimeLimit = m_tLimitTime - tm.GetTime();
	if( nTimeLimit < 0 )
		{
		if (m_uiTimer>0)
			{
			KillTimer(m_uiTimer);
			m_uiTimer = 0;
			}
		BeepMessage(IDS_CRJ_OVER);
		m_tLimitTime = nTimeLimit;
		m_csTime.SetWindowText("0");
		//EndDialog(IDCANCEL);
		return;
	} 
	CString cstr;
	//warning C4996: '_ltoa': This function or variable may be unsafe. Consider using _ltoa_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//_ltoa( nTimeLimit, vz, 10);
	_ltoa_s( nTimeLimit, vz, sizeof(vz), 10);
	TRACE("Time Limit is %s\n",vz);
	m_csTime.GetWindowText(cstr);
	if (cstr!=vz)
		m_csTime.SetWindowText(vz);
}


void CCrejit::OnCancel()
{
	// TODO: この位置にその他の後処理用のコードを追加してください。
	if (m_uiTimer>0)
		KillTimer(m_uiTimer);
	EndDialog(IDCANCEL);
}
