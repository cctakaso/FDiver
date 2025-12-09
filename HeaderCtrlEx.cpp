// HeaderCtrlEx.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "FDiver.h"
#include "HeaderCtrlEx.h"
#include "findopti.h"
#include "..\mdfc\dfileexp.h"
#include "findlist.h"
extern CFindList *vpFindList;		// 検索結果ﾘｽﾄへのﾎﾟｲﾝﾀ
extern CFindOption *vpFindOption;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx

CHeaderCtrlEx::CHeaderCtrlEx()
{
	m_fDir = -1;
	m_fFile = -1;
	m_et = -1;
	for (int pos=0; pos<HEADERITEM_NUM; pos++)
		m_cxs[pos] = 0;
}

CHeaderCtrlEx::~CHeaderCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlEx)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx メッセージ ハンドラ

int CHeaderCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHeaderCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//ﾌｫﾝﾄの設定
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 11;//13;
	lf.lfWeight = 400;
	lf.lfCharSet = SHIFTJIS_CHARSET; //ANSI_CHARSET;
	lf.lfQuality = DRAFT_QUALITY;
	lf.lfItalic = FALSE; //TRUE;
	lf.lfPitchAndFamily = 50; //18;
	//lf.lfPitchAndFamily = 34;
	//strcpy_s(lf.lfFaceName, sizeof(lf.lfFaceName), _T("ＭＳ Ｐゴシック") /*_T("Times New Roman")*/);
	strcpy(lf.lfFaceName, _T("MS Sans Serif"));
	VERIFY(m_font.CreateFontIndirect(&lf));

	m_pfontOld = GetFont();
	SetFont(&m_font);

	//ビットマップの取得
	m_bmpTree.LoadBitmap(IDB_TREE);
	m_bmpLine.LoadBitmap(IDB_LINE);
	m_bmpPath.LoadBitmap(IDB_PATH);
	m_bmpFile.LoadBitmap(IDB_FILE);
	m_bmpDown.LoadBitmap(IDB_DOWN);


	return 0;
}

void CHeaderCtrlEx::ResetHeaderType(int et, bool bForceChange)
{
	if (!IsWindowVisible())
		return;
	BOOL bChangeType = (m_fDir != vpFindOption->m_fDir ||
						m_fFile != vpFindOption->m_fFile);

	HD_ITEM hd;

	if (bForceChange) {
		bChangeType = TRUE;
		et = m_et;
	}

	if (bChangeType || m_et != et)
		{
		m_fDir = vpFindOption->m_fDir;
		m_fFile = vpFindOption->m_fFile;
		m_et = et;

		RemoveItems();
		memset(&hd, 0, sizeof(hd));
		hd.mask = HDI_BITMAP | HDI_FORMAT | HDI_WIDTH;
		hd.fmt = HDF_CENTER | HDF_BITMAP;

#ifdef NOTUSE//ビットマップの種類を変える場合
		switch(m_et)
			{
			case -1:
				if (!(!m_fDir && !m_fFile))
					{
					hd.hbm = m_bmpDown;
					hd.cxy = vpFindOption->m_cxDown;
					CHeaderCtrl::InsertItem(0, &hd);
					return;
					}
			case BFT_DIR:
				hd.hbm = m_bmpPath;
				break;
			case BFT_NO:
				hd.hbm = m_bmpLine;
				break;
			default:
				hd.hbm = m_bmpFile;
				break;
			}
#endif
		//いつもDown Bitmapを表示する
		hd.hbm = m_bmpDown;

		//if (m_et==-1 && !(!m_fDir && !m_fFile))
		if (m_et==-1)
			{
			hd.cxy = vpFindOption->m_cxDown;
			CHeaderCtrl::InsertItem(0, &hd);
			return;
			}
		

		//分類毎にﾍｯﾀﾞｰを付ける
		if (m_fDir && m_fFile)
			switch(m_et)
				{
			case BFT_DIR:
				hd.cxy = vpFindOption->m_cxTreePath;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(0, vpFindOption->m_strPathHeader);
				break;
			case BFT_NO:
				hd.cxy = vpFindOption->m_cxTreeLine;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxLine, vpFindOption->m_strLineHeader);
				InsertItem(0, vpFindOption->m_strTextHeader);
				break;
			default:
				hd.cxy = vpFindOption->m_cxTreeFile;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxName, vpFindOption->m_strNameHeader);
				InsertItem(vpFindOption->m_cxSize, vpFindOption->m_strSizeHeader);
				InsertItem(vpFindOption->m_cxDate, vpFindOption->m_strDateHeader);
				InsertItem(vpFindOption->m_cxAttr, vpFindOption->m_strAttrHeader);
				break;
				}
		else if (!m_fDir && !m_fFile)
			{
#ifdef NOTUSE//ビットマップの種類を変える場合
			hd.hbm = m_bmpLine;
#endif
			if (m_et == BFT_NO) {
				hd.cxy = vpFindOption->m_cxListLine;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxPath, vpFindOption->m_strPathHeader);
				InsertItem(vpFindOption->m_cxName, vpFindOption->m_strNameHeader);
				InsertItem(vpFindOption->m_cxLine, vpFindOption->m_strLineHeader);
				InsertItem(0, vpFindOption->m_strTextHeader);
			}else{
				hd.cxy = vpFindOption->m_cxFileFile;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxName, vpFindOption->m_strNameHeader);
				InsertItem(vpFindOption->m_cxPath, vpFindOption->m_strPathHeader);
				InsertItem(vpFindOption->m_cxSize, vpFindOption->m_strSizeHeader);
				InsertItem(vpFindOption->m_cxDate, vpFindOption->m_strDateHeader);
				InsertItem(vpFindOption->m_cxAttr, vpFindOption->m_strAttrHeader);
			}
		}
		else if (m_fDir && !m_fFile)
			switch(m_et)
				{
			case BFT_DIR:
				hd.cxy = vpFindOption->m_cxPathPath;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(0, vpFindOption->m_strPathHeader);
				break;
			default:
				hd.cxy = vpFindOption->m_cxPathLine;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxName, vpFindOption->m_strNameHeader);
				InsertItem(vpFindOption->m_cxLine, vpFindOption->m_strLineHeader);
				InsertItem(0, vpFindOption->m_strTextHeader);
				break;
				}
		else if (!m_fDir && m_fFile)
			switch(m_et)
				{
			case BFT_NO:
				hd.cxy = vpFindOption->m_cxFileLine;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxLine, vpFindOption->m_strLineHeader);
				InsertItem(0, vpFindOption->m_strTextHeader);
				break;
			default:
				hd.cxy = vpFindOption->m_cxFileFile;
				CHeaderCtrl::InsertItem(0, &hd);
				InsertItem(vpFindOption->m_cxName, vpFindOption->m_strNameHeader);
				InsertItem(vpFindOption->m_cxPath, vpFindOption->m_strPathHeader);
				InsertItem(vpFindOption->m_cxSize, vpFindOption->m_strSizeHeader);
				InsertItem(vpFindOption->m_cxDate, vpFindOption->m_strDateHeader);
				InsertItem(vpFindOption->m_cxAttr, vpFindOption->m_strAttrHeader);
				break;
				}
#ifdef _DEBUG
		else
			ASSERT(FALSE);
#endif

		}
}

void CHeaderCtrlEx::RemoveItems(int nUpper)
{
	int n = GetItemCount();
	while(n-->nUpper)
		DeleteItem(n);
}

void CHeaderCtrlEx::InsertItem(int cx, const CString &str)
{
	int pos = GetItemCount();
	if (pos<0)
		return;
	HD_ITEM hd;
	memset(&hd, 0, sizeof(hd));
	hd.mask = HDI_TEXT | HDI_FORMAT /*| HDI_WIDTH*/;
	if (cx<=0)
		{
		hd.fmt = HDF_LEFT | HDF_STRING;
		hd.cxy = DCX_MUGEN;
		}
	else
		{
		hd.fmt = HDF_CENTER | HDF_STRING;
		hd.cxy = cx;
		}
	hd.pszText = (LPSTR)((LPCSTR)str);
	hd.cchTextMax = str.GetLength();
	CHeaderCtrl::InsertItem(pos,&hd);
}

int CHeaderCtrlEx::GetCxs(int et, stCXALIGN *pData)
{
	ASSERT(et>-1);
	stCXALIGN *pDataInit = pData;
	if (m_fDir && m_fFile)
		switch(et)
			{
		case BFT_DIR:
			(pData++)->cx = vpFindOption->m_cxTreePath;
			(pData++)->cx = DCX_MUGEN;
			break;
		case BFT_NO:
			(pData++)->cx = vpFindOption->m_cxTreeLine;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxLine;
			(pData++)->cx = DCX_MUGEN;
			break;
		default:
			(pData++)->cx = vpFindOption->m_cxTreeFile;
			(pData++)->cx = vpFindOption->m_cxName;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxSize;
			(pData++)->cx = vpFindOption->m_cxDate;
			(pData++)->cx = vpFindOption->m_cxAttr;
			break;
			}
	else if (!m_fDir && !m_fFile) {
		if (et == BFT_NO) {
			(pData++)->cx = vpFindOption->m_cxListLine;
			(pData++)->cx = vpFindOption->m_cxPath;
			(pData++)->cx = vpFindOption->m_cxName;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxLine;
			(pData++)->cx = DCX_MUGEN;
		}else{
			(pData++)->cx = vpFindOption->m_cxFileFile;
			(pData++)->cx = vpFindOption->m_cxName;
			(pData++)->cx = vpFindOption->m_cxPath;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxSize;
			(pData++)->cx = vpFindOption->m_cxDate;
			(pData++)->cx = vpFindOption->m_cxAttr;
		}
	} else if (m_fDir && !m_fFile)
		switch(et)
			{
		case BFT_DIR:
			(pData++)->cx = vpFindOption->m_cxPathPath;
			(pData++)->cx = DCX_MUGEN;
			break;
		default:
			(pData++)->cx = vpFindOption->m_cxPathLine;
			(pData++)->cx = vpFindOption->m_cxName;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxLine;
			(pData++)->cx = DCX_MUGEN;
			break;
			}
	else if (!m_fDir && m_fFile)
		switch(et)
			{
		case BFT_NO:
			(pData++)->cx = vpFindOption->m_cxFileLine;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxLine;
			(pData++)->cx = DCX_MUGEN;
			break;
		default:
			(pData++)->cx = vpFindOption->m_cxFileFile;
			(pData++)->cx = vpFindOption->m_cxName;
			(pData++)->cx = vpFindOption->m_cxPath;
			pData->align = right;
			(pData++)->cx = vpFindOption->m_cxSize;
			(pData++)->cx = vpFindOption->m_cxDate;
			(pData++)->cx = vpFindOption->m_cxAttr;
			break;
			}
#ifdef _DEBUG
	else
		ASSERT(FALSE);
#endif
	return (int)(pData - pDataInit);
}

int CHeaderCtrlEx::SetCxs()
{
	int n = GetItemCount();
	HD_ITEM hd;
	memset(&hd, 0, sizeof(hd));
	hd.mask = HDI_WIDTH;
	for (int pos=0; pos<n; pos++)
		{
		CHeaderCtrl::GetItem(pos,&hd);
		m_cxs[pos] = hd.cxy;
		ASSERT(pos<HEADERITEM_NUM);
		}

	if (m_et==-1 && !(!m_fDir && !m_fFile))
		{
		vpFindOption->m_cxDown = m_cxs[0];
		return n;
		}
	if (m_fDir && m_fFile)
		switch(m_et)
			{
		case BFT_DIR:
			vpFindOption->m_cxTreePath = m_cxs[0];
			break;
		case BFT_NO:
			vpFindOption->m_cxTreeLine = m_cxs[0];
			vpFindOption->m_cxLine = m_cxs[1];
			break;
		default:
			vpFindOption->m_cxTreeFile = m_cxs[0];
			vpFindOption->m_cxName = m_cxs[1];
			vpFindOption->m_cxSize = m_cxs[2];
			vpFindOption->m_cxDate = m_cxs[3];
			vpFindOption->m_cxAttr = m_cxs[4];
			break;
			}
	else if (!m_fDir && !m_fFile){
		if (m_et == BFT_NO) {
			vpFindOption->m_cxListLine = m_cxs[0];
			vpFindOption->m_cxPath = m_cxs[1];
			vpFindOption->m_cxName = m_cxs[2];
			vpFindOption->m_cxLine = m_cxs[3];
		}else{
			vpFindOption->m_cxFileFile = m_cxs[0];
			vpFindOption->m_cxName = m_cxs[1];
			vpFindOption->m_cxPath = m_cxs[2];
			vpFindOption->m_cxSize = m_cxs[3];
			vpFindOption->m_cxDate = m_cxs[4];
			vpFindOption->m_cxAttr = m_cxs[5];
		}
	}else if (m_fDir && !m_fFile)
		switch(m_et)
			{
		case BFT_DIR:
			vpFindOption->m_cxPathPath = m_cxs[0];
			break;
		default:
			vpFindOption->m_cxPathLine = m_cxs[0];
			vpFindOption->m_cxName = m_cxs[1];
			vpFindOption->m_cxLine = m_cxs[2];
			break;
			}
	else if (!m_fDir && m_fFile)
		switch(m_et)
			{
		case BFT_NO:
			vpFindOption->m_cxFileLine = m_cxs[0];
			vpFindOption->m_cxLine = m_cxs[1];
			break;
		default:
			vpFindOption->m_cxFileFile = m_cxs[0];
			vpFindOption->m_cxName = m_cxs[1];
			vpFindOption->m_cxPath = m_cxs[2];
			vpFindOption->m_cxSize = m_cxs[3];
			vpFindOption->m_cxDate = m_cxs[4];
			vpFindOption->m_cxAttr = m_cxs[5];
			break;
			}
#ifdef _DEBUG
	else
		ASSERT(FALSE);
#endif
	vpFindList->InvalidateRect(NULL);
	return n;
}

BOOL CHeaderCtrlEx::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	HD_NOTIFY FAR * phdn = (HD_NOTIFY FAR *)lParam; 
	if (message==WM_NOTIFY && (int)wParam==2)
		{
		switch(phdn->hdr.code) {
			case HDN_ITEMCHANGED://phdn->hdr.code==HDN_ENDTRACK)
				SetCxs();
				break;
			case HDN_ITEMCLICK:
				if (phdn->iButton != 0)	//others of left button case is break.
					break;
				//if index=0 then show popup menu.
				if (phdn->iItem==0)
					{
						CMenu popMenu;
						popMenu.LoadMenu(IDR_POPUP);
						CRect rc;
						GetWindowRect(&rc);
						popMenu.GetSubMenu(0)->TrackPopupMenu(0,rc.left,rc.bottom,AfxGetMainWnd());
						break;
					}
				//others indexs are sorting.
				if (m_fDir && m_fFile)
					switch(m_et) {
					case BFT_DIR:
						//if (phdn->iItem==1)
						//	vpFindList->SortList(SORTTYPE_NAME);
						break;
					case BFT_NO:
						break;
					default:
						if (phdn->iItem==1)
							vpFindList->SortList(SORTTYPE_NAME);
						else if (phdn->iItem==2)
							vpFindList->SortList(SORTTYPE_SIZE);
						else if (phdn->iItem==3)
							vpFindList->SortList(SORTTYPE_DATE);
						/*else if (phdn->iItem==4)
							vpFindList->SortList(SORTTYPE_ATTR);
						*/
						break;
					}
				else if (!m_fDir && !m_fFile)
					{
					if (phdn->iItem==1)
						vpFindList->SortList(SORTTYPE_NO);
					else if (phdn->iItem==2)
						vpFindList->SortList(SORTTYPE_NAME);
					}
				else if (m_fDir && !m_fFile)
					switch(m_et){
					case BFT_DIR:
						//if (phdn->iItem==1)
						//	vpFindList->SortList(SORTTYPE_NAME);
						break;
					default:
						if (phdn->iItem==1)
							vpFindList->SortList(SORTTYPE_NAME);
						/*else if (phdn->iItem==4)
							vpFindList->SortList(SORTTYPE_ATTR);
						*/
						break;
					}
				else if (!m_fDir && m_fFile)
					switch(m_et) {
					case BFT_NO:
						break;
					default:
						if (phdn->iItem==1)
							vpFindList->SortList(SORTTYPE_NAME);
						else if (phdn->iItem==2)
							vpFindList->SortList(SORTTYPE_NO);
						else if (phdn->iItem==3)
							vpFindList->SortList(SORTTYPE_SIZE);
						else if (phdn->iItem==4)
							vpFindList->SortList(SORTTYPE_DATE);
						/*else if (phdn->iItem==5)
							vpFindList->SortList(SORTTYPE_ATTR);
						*/
						break;
					}
				#ifdef _DEBUG
				else
					ASSERT(FALSE);
				#endif
				break;
			}
		}

	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CHeaderCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}

