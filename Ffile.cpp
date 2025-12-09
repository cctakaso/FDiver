/*    PortTool v2.2     FFILE.CPP          */

#include "stdafx.h"
#include <malloc.h>
#include "Fdiver.h"
#include "mainfrm.h"
#include "ffile.h"
#include "grep.h"
#include "findlist.h"
#include "findopti.h"
#include "finddlg.h"
#include "..\mdfc\ch.h"
#include "findlog.h"
#include "filetran.h"
#include "dfilearc.h"
#include "..\mdfc\dbcs.h"
#include "CDxdoc2txt.h"

extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CFindOption *vpFindOption;		// ｵﾌﾟｼｮﾝｵﾌﾞｼﾞｪｸﾄ
BOOL FCheckEsc();	// グローバル ESCチェック関数
extern BOOL vfCloseApp;	// ｱﾌﾟﾘｹｰｼｮﾝの終了
extern CFindDlg *vpFindDlg; // ﾌｧｲﾝﾄﾞﾀﾞｲｱﾛｸﾞ
extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CFileTransArray *vpFileTransArray;
//#define GLOBAL_ALLOC //M_ALLOC
// new 失敗時にどんな異常かを表示

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DISP_PERFECT
//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
//'\0'は、スペースに変換


CFindFile::CFindFile()
{
	m_hReadBuff = NULL;
	m_lpReadBuff = NULL;
	m_lpReadBuff_back = NULL;
	m_pFileSpec = NULL;
	m_pFilePath = NULL;
	m_pReadFile = NULL;
	m_pszForFindList = NULL;
	m_pFileScan = NULL;
	m_pKftDll = NULL;
}

CFindFile::~CFindFile()
{
	if (m_pFileSpec)
		delete m_pFileSpec;
	if (m_pFilePath)
		delete m_pFilePath;
	if (m_pszForFindList)
		delete [] m_pszForFindList;
	if (m_pFileScan)
		delete m_pFileScan;
	CleanUpForRead();
	if (m_pReadFile)
		delete m_pReadFile;
};

// ファイル名をイニシャルセットする
BOOL CFindFile::FInitFiles(CDFile *pcFilePath, CDFileSpec *pcFileSpec, BOOL fSubDir, BOOL fArcEnable)
{

	m_fSubDir = fSubDir;

	m_fArcEnable = fArcEnable;

	if (!m_pFilePath)
		m_pFilePath = new CDFile();
	m_pFilePath->SetFName(pcFilePath->GetBuffer());
	//ASSERT(m_pFilePath->FExistAbsPath());
	if (!m_pFileSpec)
		m_pFileSpec = new CDFileSpec();
	*m_pFileSpec = pcFileSpec->GetBuffer();

	
	if (!m_pszForFindList)
		m_pszForFindList = new char[vpFindOption->m_iDspListColum+2];
	
	if (!m_pFileScan)
		m_pFileScan = new CFileScan;
	ASSERT(m_pFileScan);
	if (!m_pReadFile)
		m_pReadFile = new CDFile;
	ASSERT(m_pReadFile);

	vpFindList->SendMessage (WM_SETREDRAW, TRUE, 0L ) ;
	vpFindList->UpdateWindow();


	BOOL fArcExtOnly=FALSE;
	CString cStr;
	CDFile cdFile;
	for (int i=0; !(cStr=m_pFileSpec->GetString(i)).IsEmpty(); i++)
		{
		cdFile = cStr.GetBuffer(0);
		if (!(fArcExtOnly=FIsArcExtention(cdFile.GetBufferExtention())))
			break;
		}
	
	if (fArcExtOnly)
		{
		//圧縮ﾌｧｲﾙだけ検索ファイル指定
		if (vpFindDlg->FFindFileOnly())
			//ファイル名検索で、圧縮ﾌｧｲﾙ内も検索で且つ
			//圧縮ﾌｧｲﾙ内検索フラグをＯＦＦにする
			m_fArcEnable = FALSE;
		else
			{
			//指定の圧縮ﾌｧｲﾙ内の格納ﾌｧｲﾙについてのみ全スキャン
			//強制的に圧縮ﾌｧｲﾙを検索する
			m_fArcEnable = TRUE;
			// ファイルスキャンの条件イニシャル
			m_pFileScan->FInitialize(vpFindDlg->m_fileSpecDlg.GetIAttr(), 
				m_pFileSpec, vpFindDlg->m_fileSpecDlg.GetFromTime(), vpFindDlg->m_fileSpecDlg.GetGoTime(), vpFindDlg->FFindFileOnly());
			// ファイル変換のイニシャル処理
			m_FileTransForSearch.Initialize(m_TranData, vpFindDlg->FFindFileOnly(), m_fArcEnable, m_pFileScan->PGetFindAttrs());
			CDFileSpec cdFileCol = szStarDotStar;
			vpFileTransArray->SetFindFileSpec(&cdFileCol); //ﾌｧｲﾙｽﾍﾟｯｸｽﾄﾘﾝｸﾞだけ変える
			// ファイルスキャンの条件イニシャル=時間条件クリア
			m_pFileScan->FInitialize(vpFindDlg->m_fileSpecDlg.GetIAttr(), 
				m_pFileSpec, 0, 0, vpFindDlg->FFindFileOnly());
			return TRUE;
			}
		}

	if (m_fArcEnable)
		m_pFileSpec->AddSpecString(vpFileTransArray->GetSupportArcFileSpec().GetBuffer());
	// ファイルスキャンの条件イニシャル
	m_pFileScan->FInitialize(vpFindDlg->m_fileSpecDlg.GetIAttr(), 
		m_pFileSpec, vpFindDlg->m_fileSpecDlg.GetFromTime(), vpFindDlg->m_fileSpecDlg.GetGoTime(), vpFindDlg->FFindFileOnly());
	// ファイル変換のイニシャル処理
	m_FileTransForSearch.Initialize(m_TranData, vpFindDlg->FFindFileOnly(), m_fArcEnable, m_pFileScan->PGetFindAttrs());

	return TRUE;
}


int CFindFile::StartScan(CGrepEngin *pcEngin, long lReadSize, int iPatternLength)
{
	BOOL rtn;
	if (lReadSize!=NULL && FInitRead(lReadSize, iPatternLength)==FALSE)
		return 0;
	//ASSERT(pcEngin);
	ASSERT(m_pFilePath);
	m_pcGrepEngin = pcEngin;
//  Move to more fast!!!!
//	vpFindList->SendMessage (WM_SETREDRAW, TRUE, 0L ) ;
//	vpFindList->UpdateWindow();
	vpFindList->m_FindLog.ResetLog();
	if (m_fSubDir)
		wsprintf(vz, "[KeyWord] %s [FileType] %s\r\n[Paths]   %s",vpFindDlg->GetStrBuffer(),m_pFileSpec->GetBuffer(),m_pFilePath->GetBuffer());
	else
		wsprintf(vz, "[KeyWord] %s [FileType] %s\r\n[Path]    %s",vpFindDlg->GetStrBuffer(),m_pFileSpec->GetBuffer(),m_pFilePath->GetBuffer());
	vpFindList->m_FindLog.AddLogLine(vz, FALSE);
	ASSERT(m_pFileScan);


	((CMainFrame *)AfxGetMainWnd())->SetPaneText();	//clear
	((CMainFrame *)AfxGetMainWnd())->SetWindowText("    0 - FDiver");

	if (vpFindDlg->FFindFileOnly())
		{
		// オプションをファイル名表示のみに一度してから、SearchFilesDiskOrList()をコールして、あとで元に戻す
		int optDispNum = vpFindDlg->m_optDispNum;
		BOOL fDispDoc = vpFindDlg->m_fDispDoc;
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vpFindDlg->GetFileSpec()->GetBuffer(), 5);
		vpFindDlg->m_optDispNum = 0;
		vpFindDlg->m_fDispDoc = FALSE;
//		rtn = SearchFilesDiskOrList(m_pFilePath->GetFName().GetBuffer());

		rtn = SearchFilesDiskOrList(m_pFilePath->GetBuffer());
		vpFindDlg->m_optDispNum = optDispNum;
		vpFindDlg->m_fDispDoc = fDispDoc;
		}
	else
		{
//#ifdef _DEBUG
//#pragma message ("DEBUG時：FFILE.CPP SetPaneText()を削除")
//#else
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(vpFindDlg->GetStrBuffer(), 5);
//#endif
		rtn = SearchFilesDiskOrList(m_pFilePath->GetBuffer());
//		rtn = SearchFilesDiskOrList(m_pFilePath->GetPath().GetBuffer());
		}

	if (!vfCloseApp)
		{
		CDString cdstr;
		if (rtn)
			{
			if (vpFindList->m_wFoundDirs>0 || vpFindList->m_wFoundFiles>0 || vpFindList->m_wFoundCount>0)
				cdstr.LoadString(IDS_STBAR_ENDSCAN);
			else
				cdstr.LoadString(IDS_STBAR_NOTFOUND);
			}
		else
			cdstr.LoadString(IDS_STBAR_STOP);
		cdstr += ": ";
		wsprintf(vz, "%d paths - %d files - %d lines Found", (int)vpFindList->m_wFoundDirs, (int)vpFindList->m_wFoundFiles, (int)vpFindList->m_wFoundCount);
		cdstr += vz;
		vpFindList->m_FindLog.AddLogLine(cdstr.GetBuffer(0));
		((CMainFrame *)AfxGetMainWnd())->SetPaneText(cdstr.GetBuffer());
		((CMainFrame *)AfxGetMainWnd())->SetWindowText("FDiver");

		// １件以上見つかって且つ、ﾘｽﾄ項目が一つも選ばれていない場合は、最終ｴﾝﾄﾘｰが見えるようにｽｸﾛｰﾙさせる
		if (vpFindList->m_wFoundCount>0 && vpFindList->SendMessage( LB_GETCURSEL, 0, 0)==LB_ERR)

			vpFindList->SendMessage( LB_SETTOPINDEX, (WORD)vpFindList->SendMessage( LB_GETCOUNT, 0, 0 ) -1, 0) ;
		vpFindList->SendMessage (WM_SETREDRAW, TRUE, 0L ) ;
		vpFindList->InvalidateRect(NULL);
		if (vpFindOption->m_fSound)
			MessageBeep(MB_OK);
		if (vpFindOption->m_fToTopWin)
			{
			if (::GetActiveWindow()!=AfxGetApp()->m_pMainWnd->GetSafeHwnd())
				{
				AfxGetApp()->m_pMainWnd->SetForegroundWindow();//SetFocus();全然効かない
				//AfxGetApp()->m_pMainWnd->SetActiveWindow();
				}
			}
		vpFindList->UpdateWindow();
		}
	return rtn;
}


BOOL CFindFile::SearchFilesDiskOrList(char * szPath)
{
	 //絞り込み検索でない？
	if (szPath[0]!='\0')	{
		vpFindList->ResetContent();		// 検索結果ﾘｽﾄのリセット
		CDPathSpec cdPathSpec;
		CString cSpec;
		cdPathSpec.AddSpecString(szPath);
		for (int i=0; !(cSpec=cdPathSpec.GetString(i)).IsEmpty(); i++) {
			if (!SearchFilesDisk(cSpec.GetBuffer(0)))
				return FALSE;
		}
	}else{
		BOOL fRtn;
		CListEntryArray *pEntryArray = vpFindList->RenewEntryArray();	// ｴﾝﾄﾘｰﾊﾞｯﾌｧﾎﾟｲﾝﾀ
		vpFindList->ResetContent();		// 検索結果ﾘｽﾄのリセット
		fRtn=SearchFilesList(pEntryArray);
		delete pEntryArray;
		return fRtn;
	}
	return TRUE;
}
	

BOOL CFindFile::SearchFilesList(CListEntryArray *pEntryArray)
{
	BOOL	bFound;
	CDFile cdFile;
	FIND_DATA	DTA;

TRY {
	register CDFileExp *pcdFile;
	for (register size_ent n=0; n<pEntryArray->m_wUseEntry; n++)
		{
		if (FCheckEsc())
			return FALSE;
		pcdFile = pEntryArray->m_bse[n].pcdFile;
		if (pcdFile && !pcdFile->GetString()->IsEmpty())
			{
			if (pcdFile->FExistName())
				{
				//pcdFile->GetString()->MakeLower();
				cdFile.SetName(pcdFile->GetBuffer());
				bFound = m_pFileScan->FFirst(cdFile.GetBuffer(), TRUE);
				m_pFileScan->PopData(&DTA);//DTA = *m_pDTA;
				if (bFound)
					{
					// ｽﾃｰﾀｽﾊﾞｰに処理中ﾌｧｲﾙを表示
					if (m_TranData.fTrans)
						{
						CString cstrMsg = m_TranData.dFileCollectBefor.GetBuffer();
						//cstrMsg.MakeLower();
						((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));
						}
					else
						((CMainFrame *)AfxGetMainWnd())->SetPaneText(cdFile.GetBuffer());

					// ｽﾃｰﾀｽﾊﾞｰに処理ﾌｧｲﾙ数を表示
					wsprintf(vz, "%6d", ++vpFindList->m_wFileCount);
					((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 4);

					if (vpFindDlg->FFindFileOnly())
						{
						m_pReadFile ->SetFName(cdFile.GetBuffer());
						if (!vpFindList->FAddList(this))
							return FALSE;
						}
					else
						{
						// 見つけたﾌｧｲﾙのﾘｰﾄﾞ初期処理
						switch (SetReadFile(cdFile.GetBuffer()))
							{
							case IDABORT:
								return FALSE;
								break;
							case IDOK:
								// 検索ﾌｧｲﾙ表示
								//vpFindList->SendMessage( LB_ADDSTRING, 0, (LPARAM)(LPSTR)szNewPath ) ;
								if (!m_pcGrepEngin->FDoGrep())
									{
									CloseReadFile();
									return FALSE;	//ｸﾞﾚｯﾌﾟのﾕｰｻﾞによる中断
									}
								CloseReadFile();
								break;
							default:
							//case IDIGNORE:
								break;
							}
						}
					}
				}
			else// if (pcdFile->FExistPath())
				{
				// ディレクトリで最初のファイル
				m_fFirstFileOfDir = TRUE;
				cdFile = pcdFile->GetBuffer();
				//cdFile.GetString()->MakeLower();
				// ｽﾃｰﾀｽﾊﾞｰに処理中ﾌｧｲﾙを表示
				((CMainFrame *)AfxGetMainWnd())->SetPaneText(cdFile.GetBuffer());
				}
			}
		}
	return TRUE;
	}
CATCH(CMemoryException, e)
	{
	BeepMessageLog(IDS_OVERMEM_FORLST);
	CloseReadFile();
	}
END_CATCH
	return FALSE;
}

BOOL CFindFile::SearchFilesDisk(char * szPath)
{
	BOOL	bFound;
	CDFile	cdFile,cdFileTrans;
	CDString cSpec;
	FIND_DATA	DTA;

TRY {
	// ディレクトリで最初のファイル
	m_fFirstFileOfDir = TRUE;

	//AnsiLower((LPSTR)szPath);
	// ｽﾃｰﾀｽﾊﾞｰに処理中ﾌｧｲﾙを表示
	((CMainFrame *)AfxGetMainWnd())->SetPaneText(szPath);

	cdFile = szPath;

	for (int i=0; !(cSpec=m_pFileSpec->GetString(i)).IsEmpty(); i++)
		{	
		cdFile.SetName(cSpec.GetBuffer());

		/* Search for the first file satisfying the FileSpecs */
		//AnsiToOem(szNewPath, vz);
		bFound = m_pFileScan->FFirst(cdFile.GetBuffer(), TRUE);
		m_pFileScan->PopData(&DTA);//DTA = *m_pDTA;
		if (!bFound) {
			DWORD dw = GetLastError();
			if (dw==53 || dw==ERROR_NOT_READY) {
				AfxMessageBox(IDS_ERR_NOREAY_NET_DRV);
				return FALSE;
			}
			#ifdef _DEBUG
			ASSERT(dw==53 || dw==ERROR_NOT_READY || dw==ERROR_FILE_NOT_FOUND || dw==ERROR_PATH_NOT_FOUND || dw==ERROR_NO_MORE_FILES); //ファイルが見つからない以外のエラー！
			#endif
		}
		while (bFound)
			{
			if (FCheckEsc())
				return FALSE;
			/* Make sure this is not a "." or ".." directory. */

			// ここでｸﾞﾚｯﾌﾟ処理をします。
			//AnsiLower((LPSTR)(DTA.srFD.cFileName));
		//	CString str = (LPSTR)(DTA.srFD.cFileName);
		//	str.MakeLower();
		//	strcpy(DTA.srFD.cFileName, str.GetBuffer(0));

			// ﾃﾞｰﾀのﾄﾗﾝｽﾚｰﾄ
			cdFile.SetName(DTA.srFD.cFileName);
			cdFileTrans = cdFile;
			m_TranData.pdFile = &cdFileTrans;
			
			bFound = m_FileTransForSearch.FFirst(m_TranData);

			BOOL fAbort = FALSE;
			size_ent wFoundCount = vpFindList->m_wFoundCount;

			while(bFound)
				{
				// ｽﾃｰﾀｽﾊﾞｰに処理中ﾌｧｲﾙを表示
				if (m_TranData.fTrans)
					{
					CString cstrMsg = m_TranData.dFileCollectBefor.GetBuffer();
					//cstrMsg.MakeLower();
					((CMainFrame *)AfxGetMainWnd())->SetPaneText(cstrMsg.GetBuffer(0));
					}
				else
					((CMainFrame *)AfxGetMainWnd())->SetPaneText(cdFileTrans.GetBuffer());
#ifdef NOTUSE
				((CMainFrame *)AfxGetMainWnd())->SetPaneText(szPath);
#endif //NOTUSE

				// ｽﾃｰﾀｽﾊﾞｰに処理ﾌｧｲﾙ数を表示
				wsprintf(vz, "%6d", ++vpFindList->m_wFileCount);
				((CMainFrame *)AfxGetMainWnd())->SetPaneText(vz, 4);


				if (vpFindDlg->FFindFileOnly())
					{
					*m_pReadFile = cdFileTrans;
					fAbort = !vpFindList->FAddList(this);
					}
				else
					{
					wFoundCount = vpFindList->m_wFoundCount;
					// 見つけたﾌｧｲﾙのﾘｰﾄﾞ初期処理
					switch (SetReadFile(cdFileTrans.GetBuffer()))
						{
						case IDABORT:
							fAbort =  TRUE; //return FALSE;
							break;
						case IDOK:
							// 検索ﾌｧｲﾙ表示
							//vpFindList->SendMessage( LB_ADDSTRING, 0, (LPARAM)(LPSTR)szNewPath ) ;
							fAbort = !m_pcGrepEngin->FDoGrep();
							//漢字変換したかか否か？
							if (vpFindList->m_wFoundCount > wFoundCount)
								MarkKftTransFile();
							CloseReadFile();
							break;
						default:
						//case IDIGNORE:
							break;
						}
					// 変換ﾌｧｲﾙの場合オプションにより、削除動作
					if (m_TranData.fTrans && 
						(vpFindOption->m_optFTRemain==0 ||
						(vpFindOption->m_optFTRemain==1 && vpFindList->m_wFoundCount==wFoundCount)
						) )
						{
#ifdef WIN32
						if (!cdFileTrans.GetDrvName().IsEmpty() && cdFileTrans.CountSubDir()>=2)
#else
						if (cdFileTrans.GetDrvName()!=NO_DRV && cdFileTrans.CountSubDir()>=2)
#endif
							{
							TRY {
								cdFileTrans.Remove();
								}
							CATCH(CFileException, e)
								{
								//無視する
								}
							END_CATCH
							}
						}
					}
				if (fAbort)
					break;
				cdFileTrans = cdFile;
				//m_TranData.pdFile = &cdFileTrans; //前回設定済み
				bFound = m_FileTransForSearch.FNext(m_TranData);
				}
			//HACK!!!!ほんとうは、FindFileOnly時に解凍した入れ子のＤＬＬを削除しなければ
			//ならないが、ここではもはや情報がないのでやめる
			if (fAbort)
				((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);	//ｸﾞﾚｯﾌﾟのﾕｰｻﾞによる中断
			if (FCheckEsc())
				return FALSE;
			/* Search for more files in the current directory */
			m_pFileScan->PushData(&DTA);//*m_pDTA = DTA;
			bFound = m_pFileScan->FNext();
			m_pFileScan->PopData(&DTA);//DTA = *m_pDTA;
			}
		}


	if (!m_fSubDir)
		return TRUE;
	/* Now see if there are any subdirectories here */
	cdFile.SetName(szStarDotStar);
	bFound = m_pFileScan->FFirst(cdFile.GetBuffer(), FALSE);
	m_pFileScan->PopData(&DTA);//DTA = *m_pDTA;
 
	while (bFound)
		{
		if (FCheckEsc())
			return FALSE;
		/* Make sure this is not a "." or ".." directory. */
		if ((DTA.srFD.cFileName[0] != '.') && (DTA.srFD.dwFileAttributes & ATTR_DIR))
			{
			/* Yes, search and add files in this directory */
			ASSERT(DTA.srFD.dwFileAttributes & ATTR_DIR);
			//OemToAnsi(DTA.srFD.cFileName, szNextFile);
			VERIFY(cdFile.GetString()->FRemoveTail());
			cdFile.SetName("");
			*cdFile.GetString() += DTA.srFD.cFileName;
			*cdFile.GetString() += '\\';
			//strcat(szNextFile, "\\");
		
			/* Add all files in this subdirectory. */
			if (!SearchFilesDisk(cdFile.GetBuffer()))
				return FALSE;
			}
		m_pFileScan->PushData(&DTA);//*m_pDTA = DTA;
		bFound = m_pFileScan->FNext();
		m_pFileScan->PopData(&DTA);//DTA = *m_pDTA;
		}
	return TRUE;
	}
CATCH(CMemoryException, e)
	{
	BeepMessageLog(IDS_OVERMEM_FORLST);
	CloseReadFile();
	}
END_CATCH
	return FALSE;
}
//漢字ｺｰﾄﾞ変換マーク
void CFindFile::MarkKftTransFile()
{
	//コード変換した？
	CListEntry *pListEntry = vpFindList->GetLastFileListEntry();
	if (m_pKftDll && pListEntry) {
		CString str = m_pKftDll->DoGetType();
		//ASSERT(kanjType != kt_binary);
		//ASSERT(kanjType != kt_unknown);
		if (!str.IsEmpty()) {
			str = " <" + str + ">";
			*pListEntry->pcdFile->GetString() += str;
		}
	}
	vpFindList->m_wLastFileListEntry = 0;//clear
}

BOOL FCheckEsc()
{
	if (!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
		return TRUE;
	
//	AfxGetApp()->OnIdle(1);
	MSG msg;
//	if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
	if (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
		if (msg.message==WM_KEYDOWN)
			{
			TranslateMessage(&msg);
			if (msg.wParam==VK_ESCAPE)
				{
//				::GetMessage(&msg, NULL, WM_KEYDOWN, WM_KEYDOWN);
				((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
				return TRUE;
				}
			DispatchMessage(&msg);
			}
		else if (msg.message==WM_CLOSE)
			{
			//((CFdiverApp *)AfxGetApp())->SetFindDoingFlg(FALSE);
			//Eate!
			AfxGetMainWnd()->PostMessage(WM_KEYDOWN, VK_ESCAPE, 0);
			return FALSE;
			}			
		else
			{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			}
		}

	if (!((CFdiverApp *)AfxGetApp())->GetFindDoingFlg())
		return TRUE;
	return FALSE;
}

BOOL CFindFile::FInitRead(long readsize, int iPatternLength)
{

	ASSERT(readsize>0);
	ASSERT(iPatternLength>0);
	if (readsize<=iPatternLength)
		return FALSE;
	m_lReadBuffSize=readsize;
	m_iPatternLength = iPatternLength;
#ifdef GLOBAL_ALLOC
	BYTE far *lpb;
	HGLOBAL hGl;
//	if ((lpb= new BYTE[m_lReadBuffSize])==NULL)
//	if ((lpb= (BYTE far *)_frealloc(m_lpReadBuff, m_lReadBuffSize))==NULL)
	if (m_hReadBuff==NULL)
		{
		 if ((hGl= GlobalAlloc(GMEM_FIXED,m_lReadBuffSize))==NULL)
		 	{
			ASSERT(FALSE);
			goto Err;
			}
		m_hReadBuff = hGl;
		if ((lpb=(BYTE far *)GlobalLock(hGl))==NULL)
			{
			ASSERT(FALSE);
			goto Err;
			}
		m_lpReadBuff = lpb;
		}
	else
		{
		if ((long)GlobalSize(m_hReadBuff)!=m_lReadBuffSize)
			{
			GlobalUnlock(m_hReadBuff);
			if ((hGl= GlobalReAlloc(m_hReadBuff, m_lReadBuffSize, 0))==NULL)
				{
				ASSERT(FALSE);
				goto Err;
				}
			m_hReadBuff = hGl;
			if ((lpb=(BYTE far *)GlobalLock(hGl))==NULL)
				{
				ASSERT(FALSE);
				goto Err;
				}
			m_lpReadBuff = lpb;
			}
		}
#else
#ifdef M_ALLOC
	BYTE far *lpb;
//	if ((lpb= new BYTE[m_lReadBuffSize])==NULL)
//	if ((lpb= (BYTE far *)_frealloc(m_lpReadBuff, m_lReadBuffSize))==NULL)
	if (m_lpReadBuff==NULL)
		{
		 if ((lpb = (BYTE far *)_fmalloc (m_lReadBuffSize))==NULL)
		 	{
			ASSERT(FALSE);
			goto Err;
			}
		m_lpReadBuff = lpb;
		}
	else
		{
		 if ((lpb = (BYTE far *)_frealloc (m_lpReadBuff, m_lReadBuffSize))==NULL)
		 	{
			ASSERT(FALSE);
			goto Err;
			}
		m_lpReadBuff = lpb;
		}
#else
	BYTE far *lpb;
//	if ((lpb= new BYTE[m_lReadBuffSize])==NULL)
//	if ((lpb= (BYTE far *)_frealloc(m_lpReadBuff, m_lReadBuffSize))==NULL)
	CleanUpForRead();
	 if ((lpb= new BYTE[m_lReadBuffSize])==NULL)
	 	{
		ASSERT(FALSE);
		goto Err;
		}
	m_lpReadBuff = lpb;
	m_lpReadBuff_back = lpb;
#endif //M_ALLOC
#endif //GLOBAL_ALLOC

	return TRUE;
Err:
	{
	BeepMessage(IDS_NOMEM_READBUFF);
	return FALSE;
	}
}
void CFindFile::CleanUpForRead()
{
#ifdef GLOBAL_ALLOC
	if (m_hReadBuff)
		{
		GlobalUnlock(m_hReadBuff);
		GlobalFree(m_hReadBuff);
		}
	m_hReadBuff = NULL;
#else
#ifdef M_ALLOC
	if (m_lpReadBuff)
		_ffree (m_lpReadBuff);
	m_lpReadBuff = NULL;
#else
	if (m_lpReadBuff_back)
		delete [] m_lpReadBuff_back;
	m_lpReadBuff = NULL;
	m_lpReadBuff_back = NULL;
	m_strReadBack.Empty();
#endif //M_ALLOC
#endif //GLOBAL_ALLOC
}
int CFindFile::SetReadFile(char *szFile)
{
		
//	if (vpFindDlg->m_optDispNum == 1/* Line Num */)
//		{
		m_lSeekLineBefor = 0;
		m_lLineBefor = 1;
#ifdef MATCHANY
		m_lOffScanStBuff = 0;
		m_lLineScanStBuff = 1;
#endif
//		}
	m_lpReadBuff = m_lpReadBuff_back;

	m_lSeek=0;
	m_lReadSize =0;
	m_pReadFile -> SetFName(szFile);
	CDString cdstr;
	TRY
	{
	// 漢字フィルターＯＮ？
	CDFile cdFile = szFile;
	EXTX_TYPE extx_type = vpFindDlg->m_fileSpecDlg.ExtxFromSzExt(cdFile.GetBufferExtention());

	m_pKftDll = NULL;

	if (extx_type != EXTX_NO) {
		m_ext_type = EXT_XDOC;
		m_dFileSrc = szFile;
	}
	else
		m_ext_type = EXT_KFT;

	CDLLDoc *pDll = (CDLLDoc*)vpFileTransArray->m_arypDll.PDll(m_ext_type);
	if (vpFileTransArray->m_arypDll.FActiveAndCheck(m_ext_type) && pDll) {
		m_pKftDll = pDll;
		m_pKftDll->FSetSrcFile(szFile);
		CString str = m_pReadFile->GetBuffer();
		str += (m_ext_type == EXT_KFT ? ".sj":"");
		while(!m_pKftDll->DoOpenTran(str.GetBuffer())) {
			if (vpFindOption->m_fNoErrDsp) {
				vpFindList->m_FindLog.AddLogString(szFile);
				cdstr.LoadString(IDS_ERR_FILEOPEN);
				vpFindList->m_FindLog.AddLogLine(cdstr.GetBuffer(0));
				return IDIGNORE;	//always Ignore!
			} else {
				cdstr.LoadString(IDS_CANNOTOPEN);
				cdstr += szFile;
				int rtn;
				switch(rtn=AfxMessageBox( cdstr.GetBuffer(), MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION))	{
					case IDABORT:
					case IDIGNORE:
						vpFindList->m_FindLog.AddLogString(szFile);
						cdstr.LoadString(IDS_ERR_FILEOPEN);
						vpFindList->m_FindLog.AddLogLine(cdstr.GetBuffer(0));
						return rtn;
						break;
					default:
						break;
				}
			}
		}
	}else{
	while (!m_pReadFile->Open((CFile::modeRead | CFile::shareDenyNone)))
		{
		if (m_pReadFile->Open((CFile::modeRead | CFile::shareCompat)))
			break;
		if (vpFindOption->m_fNoErrDsp)
			{
			vpFindList->m_FindLog.AddLogString(szFile);
			cdstr.LoadString(IDS_ERR_FILEOPEN);
			vpFindList->m_FindLog.AddLogLine(cdstr.GetBuffer(0));
			return IDIGNORE;	//always Ignore!
			}
		else
			{
			cdstr.LoadString(IDS_CANNOTOPEN);
			cdstr += szFile;
			int rtn;
			switch(rtn=AfxMessageBox( cdstr.GetBuffer(), MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION))
				{
				case IDABORT:
				case IDIGNORE:
					vpFindList->m_FindLog.AddLogString(szFile);
					cdstr.LoadString(IDS_ERR_FILEOPEN);
					vpFindList->m_FindLog.AddLogLine(cdstr.GetBuffer(0));
					return rtn;
					break;
				default:
					break;
				}
			}
		}
	}
	return IDOK;
	}CATCH (CFileException, e){
		#ifdef _DEBUG
			afxDump <<"File Err!" << e->m_cause << "\n";
		#endif
	}
	END_CATCH
	ASSERT(FALSE);
	return IDABORT;
}
void CFindFile::CloseReadFile()
{
	if (m_pReadFile) {
		if (m_pKftDll)
			m_pKftDll->DoCloseTran();
		else
			m_pReadFile->Close();
	}
}


long CFindFile::ReadBuffer()
{
	if (!m_pReadFile)
		return 0;

	TRY
	{
//	m_pReadFile->Open((CFile::modeRead | CFile::shareExclusive));
	if (m_lReadSize>0)
		{ // ２回目以降のﾘｰﾄﾞ
		// 前回で全てリードしたか？
		if (m_pKftDll) {
			if (m_pKftDll->DoIsEOFTran())
				return 0;
		} else if (m_lReadSize<(m_lReadBuffSize-1))
			return 0;
		if (vpFindDlg->m_optDispNum == 1/* Line Num */)
			{
			// 前回ﾘｰﾄﾞしたﾊﾞｯﾌｧをｽｷｬﾝして、次ﾘｰﾄﾞした先頭行数と、表示用先頭位置を求めておく。
			long lOffset;									// ｽｷｬﾝﾊﾞｯﾌｧｵﾌｾｯﾄ=以前見つけた行のｵﾌｾｯﾄをセット
#ifdef MATCHANY
			long lReadSize = m_lReadSize;
			if (m_lSeekLineBefor>(m_lSeek+m_lOffScanStBuff))
				lOffset = m_lSeekLineBefor - m_lSeek;
			else
				lOffset = m_lOffScanStBuff;
#else
			long lReadSize = (m_lReadSize-(m_iPatternLength-1));
			if (m_lSeekLineBefor>m_lSeek)
				lOffset = m_lSeekLineBefor - m_lSeek;
			else
				lOffset = (m_iPatternLength-1); //0;
#endif

			long lOffsetLine;
			BYTE  far *lpch = &m_lpReadBuff[lOffset];			// ｽｷｬﾝﾊﾞｯﾌｧﾎﾟｲﾝﾀｾｯﾄ=以前見つけた行の先頭ﾎﾟｲﾝﾀセット
			BYTE far *lpchFirst = lpch;
			long lLine = m_lLineBefor;						// ｽｷｬﾝﾗｲﾝ=以前見つけた行数セット
			BYTE far *lpchCR = 0, *lpchLF=0;
			for(lOffsetLine=lOffset; lOffset<lReadSize; lOffset++, lpch++)
				{
				if (*lpch == (BYTE)chReturn)
					{
					if (vpFindOption->m_bCRIsNewLine)
						lLine++;
					}
				else if (*lpch == (BYTE)chNL)
					{
					if (!vpFindOption->m_bCRIsNewLine)
						lLine++;
					else if (lpch>lpchFirst && *(lpch-1) != (BYTE)chReturn)
						lLine++;
					lOffsetLine=lOffset+1;
					}
				}
			if (vpFindDlg->m_fDispDoc)
				{
				// 最終行文字列表示用以上にあるか？
				if ((lOffset = lReadSize-lOffsetLine) >= vpFindOption->m_iDspListColum)
					lOffset = vpFindOption->m_iDspListColum-1; //表示用に切り詰める
				if (lOffset>0)
					{
					// 表示用に最終行文字列を入れておく.
					ASSERT(lOffset<=vpFindOption->m_iDspListColum);
					strncpy_s(m_pszForFindList, vpFindOption->m_iDspListColum+2, (char far *)&m_lpReadBuff[lOffsetLine], (int)lOffset);
#ifdef DISP_PERFECT
//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
//'\0'は、スペースに変換
					m_pszForFindList[lOffset] = chNL;
#else
					m_pszForFindList[lOffset] = '\0';
#endif
					}
				else
#ifdef DISP_PERFECT
//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
//'\0'は、スペースに変換
					m_pszForFindList[0] = chNL;
#else
					m_pszForFindList[0] = '\0';
#endif
				}
			m_lLineScanStBuff = m_lLineBefor = lLine;
			m_lSeekLineBefor= m_lSeek + lOffsetLine;
			//TRACE("lOffsetLine =%d, \n",lOffsetLine);
			}
#ifdef MATCHANY
		m_lOffScanStBuff = 256;
		//if (m_pcGrepEngin->FMetaChars())
		//	m_lOffScanStBuff = 256;
		//else
		//	m_lOffScanStBuff = m_iPatternLength - 1;
		if (m_pKftDll) {
			BYTE bTmp[256];
			long sizeT = m_lReadSize>256 ? 256:m_lReadSize;
			memcpy(bTmp, m_lpReadBuff+m_lReadSize-sizeT, sizeT);
			memcpy(m_lpReadBuff, bTmp, sizeT);
			//999-256=a
			//a+999-256=b
			//b+999-256=c
			if (m_lSeek==0)
				m_lSeek = m_lReadSize - sizeT;	//BUGFIX.1998.04.15 add
			else
				m_lSeek += (m_lReadSize - sizeT);	//BUGFIX.1998.04.15 add
			if ((m_lReadSize = (long)m_pKftDll->DoReadTran(m_lpReadBuff+sizeT,m_lReadBuffSize-1-sizeT))<=(m_iPatternLength-1))
				return 0;
			m_lReadSize += sizeT;	//BUGFIX.1998.04.15 add
		}else{
			//999-256=a
			//a+999-256=b
			//b+999-256=c
			if ((m_lSeek = m_pReadFile->Seek(-m_lOffScanStBuff, CFile::current))<0)
				goto ERR;
			if ((m_lReadSize = (long)m_pReadFile->Read(m_lpReadBuff,m_lReadBuffSize-1))<=(m_iPatternLength-1))
				return 0;
		}
#else
		if ((m_lSeek = m_pReadFile->Seek(1-m_iPatternLength, CFile::current))<0)
			goto ERR;
		if ((m_lReadSize = (long)m_pReadFile->Read(m_lpReadBuff,m_lReadBuffSize-1))<=(m_iPatternLength-1))
			return 0;
#endif
	}else {
		if (m_pKftDll) {
			if (m_ext_type == EXT_XDOC) {
				CString cstrCmd;
				int i=2;
//				cstrCmd += '\"';

				cstrCmd += m_dFileSrc.GetBuffer();

//				cstrCmd += '\"';
				((CDxdoc2txt *)(m_pKftDll->GetDll()))->Convert(cstrCmd.GetBuffer(), &m_strReadBack); //szArcFuncLst[m_ext][5]
				m_lpReadBuff = (BYTE *)m_strReadBack.GetBuffer();
				m_lReadSize = m_strReadBack.GetLength();
				if (m_lReadSize<=(m_iPatternLength-1)) {
					m_strReadBack.Empty();
					return 0;
				}
			}else{
				if ((m_lReadSize = (long)m_pKftDll->DoReadTran(m_lpReadBuff,m_lReadBuffSize-1))<=(m_iPatternLength-1))
					return 0;
			//TRACE("PKF-------->\n",m_pReadFile->GetBuffer());
			//TRACE("m_lReadSize =%d\n",m_lReadSize);
			}
		}else{
			if ((m_lReadSize = (long)m_pReadFile->Read(m_lpReadBuff,m_lReadBuffSize-1))<=(m_iPatternLength-1))
				return 0;
			//TRACE("Nomal---->\n",m_pReadFile->GetBuffer());
			//TRACE("m_lReadSize =%d\n",m_lReadSize);
		}
	}
#ifdef DISP_PERFECT
//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
//'\0'は、スペースに変換
	if (m_ext_type != EXT_XDOC) {
		m_lpReadBuff[m_lReadSize] = (BYTE)chNL;//'\0';
	}
#else
	m_lpReadBuff[m_lReadSize] = '\0';
#endif
	//TRACE("\r\nﾘｰﾄﾞｻｲｽﾞ=%ld",m_lReadSize);
	return m_lReadSize;
	}
	
	CATCH (CFileException, e)
	{
		#ifdef _DEBUG
			afxDump <<"File Err!" << e->m_cause << "\n";
		#endif
	}
	END_CATCH
ERR:
	ASSERT(FALSE);
	CloseReadFile();
	return -1;
}

BYTE far *CFindFile::GetLineInfo(long lSeekFind, long cchMatched, long *plLine)
{
	ASSERT(plLine);

	long lOffsetFind = lSeekFind - m_lSeek;		// 見つけたﾊﾞｯﾌｧｵﾌｾｯﾄ位置
	long lOffset;

#ifdef MATCHANY
	long lLine;
	if (lSeekFind>=m_lSeekLineBefor &&
			m_lSeekLineBefor>(m_lSeek+m_lOffScanStBuff))
		{
		lOffset = m_lSeekLineBefor - m_lSeek;		// ｽｷｬﾝﾊﾞｯﾌｧｵﾌｾｯﾄ=以前見つけた行のｵﾌｾｯﾄをセット
		lLine = m_lLineBefor;						// ｽｷｬﾝﾗｲﾝ=以前見つけた行数セット
		}
	else
		{
		lOffset = m_lOffScanStBuff;	//m_lSeekLineBefor - m_lSeek;
		lLine = m_lLineScanStBuff;
		}
#else
	ASSERT(lSeekFind>=m_lSeekLineBefor);
	long lLine = m_lLineBefor;						// ｽｷｬﾝﾗｲﾝ=以前見つけた行数セット
	if (m_lSeekLineBefor>m_lSeek)
		lOffset = m_lSeekLineBefor - m_lSeek;		// ｽｷｬﾝﾊﾞｯﾌｧｵﾌｾｯﾄ=以前見つけた行のｵﾌｾｯﾄをセット
	else
		lOffset = (m_iPatternLength-1); //0;
#endif
	BYTE far *lpchLine;
	BYTE far *lpch = &m_lpReadBuff[lOffset];			// ｽｷｬﾝﾊﾞｯﾌｧﾎﾟｲﾝﾀｾｯﾄ=以前見つけた行の先頭ﾎﾟｲﾝﾀセット
	BYTE far *lpchFirst = lpch;
	for(lpchLine=lpch; lOffset<lOffsetFind; lOffset++, lpch++)
		{
		if (*lpch == (BYTE)chReturn)
			{
			if (vpFindOption->m_bCRIsNewLine)
				lLine++;
			lpchLine=lpch+1;
			}
		else if (*lpch == (BYTE)chNL)
			{
			if (!vpFindOption->m_bCRIsNewLine)
				lLine++;
			else if (lpch>lpchFirst && *(lpch-1) != (BYTE)chReturn)
				lLine++;
			lpchLine=lpch+1;
			}
		}
#ifdef DISP_PERFECT
//'99/5/4 : 表示する行先頭バイト位置が、見つけた位置よりも随分前にある
//つまり、検索された文字列がリスト中に見えなくなるような場合は、
//見つけた文字がリストの1/8に来るようにする
	if (m_lLineBefor != lLine) { //takaso2010
		if (lpch - lpchLine /*+ cchMatched*/ > vpFindOption->m_iDspListColum) {
			long llineTmp = lOffsetFind >6 ? lOffsetFind - 6:1;//((vpFindOption->m_iDspListColum-cchMatched) >>3);
			lpch = &m_lpReadBuff[llineTmp];
			lpchLine = (llineTmp>0 && CtOfDbcsPch((char*)lpchLine, (char*)lpch) == ctDbc2b) ? lpch-1:lpch;
		}
	}
	
#endif
	// ﾊﾞｯﾌｧの先頭行で尚且つ、前のﾘｰﾄﾞで行の先頭部分がとってあった場合か？
	if (lLine==m_lLineBefor && m_lSeekLineBefor<m_lSeek)
		{
		// ﾌｧｲﾙ先頭以外のﾘｰﾄﾞﾊﾞｯﾌｧの最初の行なので、とっておいたﾗｲﾝﾊﾞｯﾌｧの文字列を返す。
		*plLine = m_lLineBefor;	// 行数ｾｯﾄ
		if (vpFindDlg->m_fDispDoc)
			{
			// 表示用には、足りないか？
			int len;
			if ((len=strlen(m_pszForFindList)) < vpFindOption->m_iDspListColum)
				{
				// ﾘｰﾄﾞﾊﾞｯﾌｧの先頭から足し合わせる。
#ifdef MATCHANY
				strncat_s (m_pszForFindList, vpFindOption->m_iDspListColum+2, (char far *)&m_lpReadBuff[lOffset], vpFindOption->m_iDspListColum - len);
#else
				strncat (m_pszForFindList, (char far *)m_lpReadBuff, vpFindOption->m_iDspListColum - len);
#endif
#ifdef DISP_PERFECT
//'99/5/4 : 表示行の途中桁に'\0'があってもちゃんと表示する
//'\0'は、スペースに変換
				m_pszForFindList[vpFindOption->m_iDspListColum] = chNL;
#else
				m_pszForFindList[vpFindOption->m_iDspListColum] = '\0';
#endif
				}
			return (BYTE far *)m_pszForFindList;
			}
		else
			return NULL;
		}
	// 現在のﾘｰﾄﾞﾊﾞｯﾌｧ内で事足りる
	// 行先頭ｼｰｸ位置および行番号を保持する
	if (m_lLineBefor != lLine) { //takaso2010
		m_lLineBefor = lLine;
		m_lSeekLineBefor = m_lSeek + (lpchLine - m_lpReadBuff);
	}
	*plLine = lLine;	// 行数ｾｯﾄ
	if (vpFindDlg->m_fDispDoc)
		return lpchLine;		// 行先頭ﾎﾟｲﾝﾀ
	else
		return NULL;
}

