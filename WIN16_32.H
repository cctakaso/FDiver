//WIN32対応ヘッダーファイル
//
#define WIN16_32
// WM_COMMAND
// Message Get
#ifdef WIN32
#define DGetWmCommandCmd(wp,lp)		HIWORD(wp)
#define DGetWmCommandId(wp,lp)		LOWORD(wp)
#define DGetWmCommandHwnd(wp,lp)	((HWND)lp)
#else
#define DGetWmCommandCmd(wp,lp)		HIWORD(lp)
#define DGetWmCommandId(wp,lp)		(wp)
#define DGetWmCommandHwnd(wp,lp)	((HWND)LOWORD(lp))
#endif //
// Message Set
#ifdef WIN32
#define DSetWmCommandwParam(Cmd, Id, Hwnd)	MAKELONG(Id, Cmd)
#define DSetWmCommandlParam(Cmd, Id, Hwnd)	(Hwnd)
#else
#define DSetWmCommandwParam(Cmd, Id, Hwnd)	(Id)
#define DSetWmCommandlParam(Cmd, Id, Hwnd)	MAKELONG(Hwnd, Cmd)
#endif //

