



#include "mariko-33_sbw.h"



BOOL CALLBACK find_worker(HWND wnd, LPARAM lp);

unsigned set_window_edge(HWND wnd, long and1, long ex_and, long or1, long ex_or)
{
    unsigned gle;
    long style = 0, exstyle = 0;

    SetLastError(0);

    style = GetWindowLongA(wnd, GWL_STYLE);
    if (!style) goto errcheck;
    exstyle = GetWindowLongA(wnd, GWL_EXSTYLE);
errcheck:
    gle = GetLastError();
    if ((!style || !exstyle) && gle) {
        //
        return 1;
    }

    style &= and1;
    exstyle &= ex_and;
    style |= or1;
    exstyle |= ex_or;

    SetLastError(0);

    if (!SetWindowLongA(wnd, GWL_STYLE, style) ||
        !SetWindowLongA(wnd, GWL_EXSTYLE, exstyle))
    {
        gle = GetLastError();
        if (gle) {
            //
            return 1;
        }
    }

    return 0;
}

HWND find_desk()
{
    HWND progman;
    HWND worker;

    
    progman = FindWindowW(L"Progman", 0);

    if (!progman)
    {
        
        return 0;
    }

    

    SendMessageA(progman, 0x052C, 0xD, 0);
    SendMessageA(progman, 0x052C, 0xD, 1);

    
    EnumWindows(find_worker, (LPARAM)&worker);

    if (!worker)
    {
        
        SendMessageA(progman, 0x052C, 0, 0);

       
        EnumWindows(find_worker, (LPARAM)&worker);
    }

    /*
     * windows 7 with aero is almost the same as windows 10, except that we
     * have to hide the WorkerW window and render to Progman child windows
     * instead
     */

    //if (worker && !is_win8_or_later())
    //{
    //    log1("detected windows 7, hiding worker window");
     //   ShowWindow(worker, SW_HIDE);
     //   worker = progman;
    //}

    //if (!worker)
    //{
     //   wp_err("W: couldnt spawn window behind icons, falling back to Progman");
     //   worker = progman;
   // }

    return worker;
}

int set_rect(HWND wnd, RECT* mapped)
{
    if (!GetWindowRect(wnd, (RECT*)mapped)) {
        return 1;
    }

    MapWindowPoints(0, find_desk(), (LPPOINT)mapped, 2);
    return 0;
}

BOOL CALLBACK find_worker(HWND wnd, LPARAM lp)
{
    HWND* pworker = (HWND*)lp;

    if (!FindWindowExA(wnd, 0, "SHELLDLL_DefView", 0)) {
        return TRUE;
    }

    *pworker = FindWindowExA(0, wnd, "WorkerW", 0);
    if (*pworker) {
        
        return FALSE;
    }

    return TRUE;
}

int set_window(HWND wnd)
{
    char wndclass[512];
    HWND wallpaper = find_desk();
    long and1, ex_and;
    RECT r;

    *wndclass = 0;
    GetClassNameA(wnd, wndclass, sizeof(wndclass) - 1);

    if (wallpaper == wnd || !strcmp(wndclass, "Shell_TrayWnd")) {
        
        return 1;
    }

    if (IsChild(wallpaper, wnd)) {
       
        return 1;
    }


    and1 = ~(
        WS_CAPTION |
        WS_THICKFRAME |
        WS_SYSMENU |
        WS_MAXIMIZEBOX |
        WS_MINIMIZEBOX
        );

    ex_and = ~(
        WS_EX_DLGMODALFRAME |
        WS_EX_COMPOSITED |
        WS_EX_WINDOWEDGE |
        WS_EX_CLIENTEDGE |
        WS_EX_LAYERED |
        WS_EX_STATICEDGE |
        WS_EX_TOOLWINDOW |
        WS_EX_APPWINDOW
        );

    if (set_window_edge(wnd, and1, ex_and, WS_CHILD, 0)) {
        return 1;
    }

    
    set_rect(wnd, &r);
    //if (!GetWindowRect(wnd, (RECT*)(&r))) {
     //   return 1;
    //}

   // MapWindowPoints(0, wp_id(), (LPPOINT)(&r), 2);
    //return 0;

    if (!SetParent(wnd, wallpaper)) {
        
        return 1;
    }

    ShowWindow(wnd, SW_SHOW);
    

    return 0;
}
unsigned pos_move(HWND wnd, long left, long top, long right, long bottom)
{
    BOOL succ = SetWindowPos(wnd, 0, left, top, right - left, bottom - top, 0);
    if (!succ) {
        
        return 1;
    }
    return 0;
}
unsigned set_fullscreen(HWND wnd)
{
    HMONITOR mon;
    MONITORINFO mi;
    RECT current_rect;

    if (!GetWindowRect(wnd, (RECT*)(&current_rect))) {
        
            return 1;
    }

    mon = MonitorFromPoint(*(POINT*)&current_rect, MONITOR_DEFAULTTONEAREST);
    if (!mon) {
        
        return 1;
    }

    mi.cbSize = sizeof(mi);

    if (!GetMonitorInfoA(mon, &mi)) {
        
        return 1;
    }

    MapWindowPoints(0, find_desk(), (LPPOINT)&mi.rcMonitor, 2);
    return pos_move(wnd, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right,
        mi.rcMonitor.bottom);
}

unsigned set_wall(wchar_t *nam){

    HWND wnd = FindWindowW(NULL, nam);

    set_window(wnd);
    set_fullscreen(wnd);

	return 0;


}

unsigned pull_out_window(HWND wnd)
{
	HWND wallpaper =find_desk();
	long para1, para2;
	

	if (wallpaper == wnd) {
		//wp_err1("can't del this window\n");
		return 1;
	}

	if (!IsChild(wallpaper, wnd)) {
		//wp_err1("already removed\n");
		return 1;
	}

	//log_window("removing ", wnd);
   

    //SetWindowLongA(wnd, GWL_STYLE, WS_POPUP);
    //SetWindowLongA(wnd, GWL_STYLE, ~WS_CHILD);
    

	if (!SetParent(wnd, NULL)) {
		//wp_err("SetParent failed, GLE=%08X", GetLastError());
		return 1;
	}
    LONG lStyle = GetWindowLongA(wnd, GWL_STYLE);
    lStyle &= ~WS_CHILDWINDOW;
    lStyle &= WS_POPUP;
    //lStyle &= WS_CHILD;
    SetWindowLong(wnd, GWL_STYLE, lStyle);

    para1 = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN;
    para2 = WS_EX_APPWINDOW;
    if (set_window_edge(wnd, -1, -1, para1, para2)) {
        return 1;
    }

   
    //SetWindowLongA(wnd,GWL_STYLE, ~WS_CHILD);
    //SetWindowLongA(wnd,GWL_STYLE, WS_POPUP);
    //SetWindowLongA(wnd, GWL_STYLE, WS_OVERLAPPED);
    //para1 = WS_OVERLAPPEDWINDOW;
	//para2 = WS_EX_APPWINDOW;
    
    //SetWindowLongA(wnd,GWL_STYLE, ~WS_CHILD);
    //SetWindowLongA(wnd,GWL_STYLE, WS_POPUP);

	//if (set_window_edge(wnd, -1, -1, para1, para2)) {
	//	return 1;
	//}
    

	SetWindowPos(wnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE |
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

	InvalidateRect(wallpaper, 0, 1);
	find_desk(); /* can sometimes fix leftover unrefreshed portions */

	return 0;
}