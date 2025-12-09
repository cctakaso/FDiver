/*    PortTool v2.2     greppat.h          */

// greppat.h : ヘッダー ファイル
//

#ifndef __GREPPAT_H_
#define __GREPPAT_H_

#include "metachar.h"
#include "metastr.h"

/********************************************
	CGrepPattern クラス
*********************************************/
#ifdef _DEBUG
class CGrepPattern :public CObject
#else
class CGrepPattern :public CObject
#endif //_DEBUG
{
public:
	CGrepPattern();// コンストラクタ
	~CGrepPattern();
	void Initialize(char *sz);

	CString m_cstr;
	WORD *m_pwSpecial;
	WORD *m_pwPattern;			//pattern area pointer.
	int m_cchBlockSize;
	int m_cchPattern;
	//for B&M-Table
	int m_dcpMatchAny;
	int m_iwMatchAnyPos;
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG
protected:

};

enum KeyBlock_Type
{
	kbtGrep,
	kbtSubKeyIn,
	kbtDumy
};


enum ScanLogic
{
	slNextPat,		//pDocは引き続き、新しいpGrepPatternでマッチング処理をする
	slNextBlock,
	slEndBlock,
	slFalseLogic	//rlOut==rlTrue:現在の行はCFindListにAddして、このファイルでのｽﾄｯｸしておいたものをCFindListで有効とする
};


/********************************************
	CKeyBlock クラス
*********************************************/
class CKeyInLogic;

#ifdef _DEBUG
class CKeyBlock : public CObject
#else
class CKeyBlock : public CObject
#endif //_DEBUG
{
public:
	CKeyBlock();// コンストラクタ
	~CKeyBlock();


	BOOL Initialize(KeyBlock_Type kbt, char *sz);

	KeyBlock_Type m_kbt;
	union {
		//CStringArray2 m_arystrPats;	// サーチパターン・ストリング配列--->あとには削除する
		CGrepPattern *m_pGrepPat;		// Grepパターン（struct CGrepPattern）配列
		CKeyInLogic *m_pSubKeyIn;	// このキーワードに含まれる、副キーワード(CkeyLogic)へのポインタ
		};
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG
protected:
	void Clear();
};


/********************************************
	CKeyLogic クラス群
*********************************************/
/********************************************
	CKeyLogic 基本クラス
*********************************************/
#ifdef _DEBUG
class CKeyLogic : public CObject
#else
class CKeyLogic : public CObject
#endif //_DEBUG
{
public:
	CKeyLogic(){
		m_piKeyMatched=NULL; };// 標準のコンストラクタ
	~CKeyLogic() {
			Clear(); };


	// m_keyOutLogic.strPatLogicのロジックをチェックして、値を返す
	ReturnLogic CheckLogic();
	void SetRlOne(ReturnLogic rl);
	void SetFalseForAllNutral();
	void SetNutralForAll();
	void SetNutralForSub();
	void SetNutral();
	void ResetBlockIndex();			// 全てのm_indexLogicをイニシャルする

	int GetNowIndexLogic() {
		return m_indexLogic; }
	ScanLogic GetSelGrepPatternFlow(CGrepPattern *&pGrepPattern);
	CGrepPattern *GetSelGrepPattern()	{
		ASSERT(GetSelKeyBlock()->m_kbt==kbtGrep);
		return GetSelKeyBlock()->m_pGrepPat; }
	void InitSelToStr();
	void SetSelCchMatched(int cchMatched) {
		ASSERT(FStrIndex(m_indexLogic));
		m_piKeyMatched[m_indexLogic] = cchMatched; };
	int *m_piKeyMatched;	// キーワードロジックマッチCKeyInLogicでしか使わない
	char *GetLogicBuffer() {
		return m_strKeyLogic.GetBuffer(0); }
	CString &GetLogicStr() {
		return m_strKeyLogic; }
	CString TransFromEntryMetaString(char *pstr, BOOL fFirst=FALSE, CMetaStringArray *pMetaStringArray=NULL);
	CKeyInLogic *GetSubKeyLogic(int index)	{
		ASSERT(GetKeyBlock(index)->m_kbt==kbtSubKeyIn);
		return GetKeyBlock(index)->m_pSubKeyIn; }
	CKeyBlock *GetKeyBlock(int index)	{
		return ((CKeyBlock *)m_aryKeyBlock[index]); }
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG
protected:
	CString m_strKeyLogic;		// キーワードロジック・ストリング
	CString m_strSXorLogic;		// SXorの為のフラグ格納領域
	ReturnLogic m_rl;			// 全体のリターンロジック

	CPtrArray m_aryKeyBlock;	//CKeyBlockへのポインタ配列
//	CStringArray2 m_arystrPats;	// サーチパターン・ストリング配列--->あとには削除する
//	CPtrArray m_arypPat;		// Grepパターン（CGrepPattern）配列

//	CPtrArray *m_arySubKeys;	// このキーワードに含まれる、副キーワード(CkeyLogic)へのポインタ

	int m_indexLogic;
	char m_tok;		// ﾄｰｸﾝ
	char *m_ptok;	// ﾄｰｸﾝﾎﾟｲﾝﾀ
	
	BOOL SetNextIndexLogicSimple();
	BOOL FStrIndex(int index) {
		return FStrCh(m_strKeyLogic[index]); };
	BOOL FStrCh(char ch);
	CKeyInLogic *GetSelSubKeyLogic()	{
		ASSERT(GetSelKeyBlock()->m_kbt==kbtSubKeyIn);
		return GetSelKeyBlock()->m_pSubKeyIn; }
	CKeyBlock *GetSelKeyBlock()	{
		return GetKeyBlock(m_indexLogic); }
	// パターン内のワード文字列を与えて、ロジックパターンを作成してゆく
	ReturnLogic SetLogicPatternForWord(MetaCharCheckFlag mf, char *pstr);
	BOOL FCheckLogical(MetaCharCheckFlag mf, char *pstr);
	void Clear();
	virtual ReturnLogic term()=0;
	virtual ReturnLogic fact()=0;
	ReturnLogic And(ReturnLogic rlL, ReturnLogic rlR);
	ReturnLogic Or(ReturnLogic rlL, ReturnLogic rlR=rlFalse);
	virtual ReturnLogic Xor(ReturnLogic rlL, ReturnLogic rlR)=0;
	ReturnLogic Not(ReturnLogic rl);
	void advance(int next = 1);
	void eat(char ch);
//	ReturnLogic CheckSubLogic();
};
/********************************************
	CKeyInLogic 派生クラス
*********************************************/
class CKeyInLogic :public CKeyLogic
{
public:
	CKeyInLogic(){};// 標準のコンストラクタ
	~CKeyInLogic(){};
	ReturnLogic Initialize(char *sz);
	BOOL SetNextIndexLogic(int &cchMatched, BOOL fStr=FALSE);
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG
protected:
	int GetBeforStrIndex(int index);
	int GetBeforTrueIndex(int index);
	virtual ReturnLogic term();
	virtual ReturnLogic fact();
	virtual ReturnLogic Xor(ReturnLogic rlL, ReturnLogic rlR);
	ReturnLogic Xor(ReturnLogic rlR);
};
/********************************************
	CKeyOutLogic 派生クラス
*********************************************/
class CKeyOutLogic :public CKeyLogic
{
public:
	CKeyOutLogic(){};// 標準のコンストラクタ
	~CKeyOutLogic(){};

	BOOL Initialize(char *sz, BOOL bMsg=TRUE);
	// セットしてある検索パターン文字列を取得する
	ScanLogic ScanStrNext(CGrepPattern *&pGrepPattern, int &cchMatched, BOOL ffirst);
	// セットしてある検索パターン文字列を取得する
	ScanLogic ScanPatternNext(CGrepPattern *&pGrepPattern , ReturnLogic rlIn,  int &cchMatched, ReturnLogic &rlLine/*この行は追加するか？*/, ReturnLogic &rlLogic);
	void ScanPatternFirst(CGrepPattern *&pGrepPattern);
	int GetMinMatchedForGrep();
	BOOL FResetSXorIndexLogic(int index);
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG
protected:
	virtual ReturnLogic term();
	virtual ReturnLogic fact();
	virtual ReturnLogic Xor(ReturnLogic rlL, ReturnLogic rlR);

};

#endif // !__GREPPAT_H_
