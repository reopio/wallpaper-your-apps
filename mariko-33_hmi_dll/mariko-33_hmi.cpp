

#include "mariko-33_hmi.h"

using std::cout;
using std::endl;

#ifndef NAME_LEN 
#def NAME_LEN 256
#endif



HHOOK _hook;


HWND dhand = GetDesktopWindow();
HMONITOR mhand = MonitorFromWindow(dhand, MONITOR_DEFAULTTONEAREST);

//DEVICE_SCALE_FACTOR pScale;

//POINT pt;

//pt.x = pt.y = 1;

//HMONITOR mhand = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);

//HRESULT SCAL_OK = GetScaleFactorForMonitor(mhand, &pScale);//get scale



HWND g_hwnd = NULL, curr = NULL;

char curr_title[NAME_LEN];

MOUSEHOOKSTRUCT* pMouseS = NULL;

POINT lopot;

float scal_f = 1, sorn;

float get_scal() {

    MONITORINFOEX miex;
    miex.cbSize = sizeof(miex);
    GetMonitorInfo(mhand, &miex);
    int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
    int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);
    //get logical
    
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;
    int cyPhysical = dm.dmPelsHeight;
    //get physical

    
    float horzScale = ((float)cxPhysical / (float)cxLogical);
    float vertScale = ((float)cyPhysical / (float)cyLogical);
    //calculate

    sorn = vertScale;
    float scl = 1 / vertScale;

    return scl;
}

LRESULT CALLBACK HookCallback(int code , WPARAM wparam , LPARAM lparam){

    pMouseS = (MOUSEHOOKSTRUCT*)lparam;
    if(code == 0){

            if(pMouseS != NULL){

                //lopot.x = pMouseS->pt.x / 2;
                //lopot.y = pMouseS->pt.y / 2;

                //curr = WindowFromPoint(lopot);

                //GetWindowTextA(curr, curr_title, sizeof(curr_title));


                /*
                if(!strcmp(curr_title, "FolderView")){
                    switch(wparam){
                        case WM_LBUTTONDOWN:{
                            PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(pMouseS->pt.x / 2, pMouseS->pt.y / 2));
                            break;
                        }

                        case WM_LBUTTONUP:{
                            PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(pMouseS->pt.x / 2, pMouseS->pt.y / 2));
                            break;
                        }
                        default:break;
                    }
                }/////////////*/
                
                switch (wparam) {
                case WM_LBUTTONDOWN: {

                    curr = WindowFromPoint(pMouseS->pt);

                    GetWindowTextA(curr, curr_title, sizeof(curr_title));

                    if (!strcmp(curr_title, "FolderView")) {
                        //lopot.x = pMouseS->pt.x / 2;
                        //lopot.y = pMouseS->pt.y / 2;

                        //curr = WindowFromPoint(pMouseS->pt);

                        //GetWindowTextA(curr, curr_title, sizeof(curr_title));
                        //SetActiveWindow(g_hwnd);
                        if (GetForegroundWindow() == g_hwnd) {
                            //Sleep(50);
                            //SetActiveWindow(g_hwnd);
                            //SetForegroundWindow(folderv);
                            //Sleep(50);
                            //SetForegroundWindow(g_hwnd);
                            PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                            //SetForegroundWindow(FindWindowW(NULL, L"eeeee.txt - Notepad"));
                        }
                        else {
                            //Sleep(50);
                            SetForegroundWindow(g_hwnd);
                            //Sleep(50);
                            PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                        }
                        /*if (GetForegroundWindow() == g_hwnd) {
                            PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                        }
                        else {
                            SetForegroundWindow(g_hwnd);
                            PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                        }*/
						//Sleep(100);
						//PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(pMouseS->pt.x, pMouseS->pt.y));
                    }
                    else {
                        break;/// !!!!!!!!!!!!!!!!!
                    }

                    break;
                }
                case WM_LBUTTONUP: {

                    curr = WindowFromPoint(pMouseS->pt);

                    GetWindowTextA(curr, curr_title, sizeof(curr_title));

                    if (!strcmp(curr_title, "FolderView")) {
                        //lopot.x = pMouseS->pt.x / 2;
                        //lopot.y = pMouseS->pt.y / 2;

                        //SetForegroundWindow(g_hwnd);
                        //if (GetForegroundWindow() == g_hwnd) {
                        //    PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                        //}
                        //else {
                        //SetActiveWindow(g_hwnd);
                        //SetForegroundWindow(g_hwnd);
                        PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                        //}
                        //PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(pMouseS->pt.x, pMouseS->pt.y));
                    }
                    else {
                        break;/// !!!!!!!!!!!!!!!!!
                    }


                    break;
                }

                default:break;

                }
                

            }

    }

    return CallNextHookEx(_hook, code, wparam, lparam);

}

LRESULT CALLBACK HookCallback_S(int code, WPARAM wparam, LPARAM lparam) {

    pMouseS = (MOUSEHOOKSTRUCT*)lparam;
    if (code == 0) {

        if (pMouseS != NULL) {

            //lopot.x = pMouseS->pt.x / 2;
            //lopot.y = pMouseS->pt.y / 2;

            //curr = WindowFromPoint(lopot);

            //GetWindowTextA(curr, curr_title, sizeof(curr_title));


            /*
            if(!strcmp(curr_title, "FolderView")){
                switch(wparam){
                    case WM_LBUTTONDOWN:{
                        PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(pMouseS->pt.x / 2, pMouseS->pt.y / 2));
                        break;
                    }

                    case WM_LBUTTONUP:{
                        PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(pMouseS->pt.x / 2, pMouseS->pt.y / 2));
                        break;
                    }
                    default:break;
                }
            }/////////////*/

            
            switch (wparam) {
            case WM_LBUTTONDOWN: {

                lopot.x = scal_f * pMouseS->pt.x;
                lopot.y = scal_f * pMouseS->pt.y;
                curr = WindowFromPoint(lopot);
                GetWindowTextA(curr, curr_title, sizeof(curr_title));
                if (!strcmp(curr_title, "FolderView")) {
                    //lopot.x = pMouseS->pt.x / 2;
                    //lopot.y = pMouseS->pt.y / 2;

                    //curr = WindowFromPoint(lopot);

                    //GetWindowTextA(curr, curr_title, sizeof(curr_title));
                    if (GetForegroundWindow() == g_hwnd) {
                        //Sleep(50);
                        //SetActiveWindow(g_hwnd);
                        //SetForegroundWindow(folderv);
                        //Sleep(50);
                        //SetForegroundWindow(g_hwnd);
                        PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                        //SetForegroundWindow(FindWindowW(NULL, L"eeeee.txt - Notepad"));
                    }
                    else {
                        //Sleep(50);
                        SetForegroundWindow(g_hwnd);
                        //Sleep(50);
                        PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                    }
                    //SetActiveWindow(g_hwnd);
                    //SetForegroundWindow(g_hwnd);
                    //SetFocus(g_hwnd);
                    //SetActiveWindow(g_hwnd);
                    //Sleep(100);
                    //PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                    //PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                    //SetForegroundWindow(g_hwnd);
					//Sleep(100);
					//PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                }
                else {
                    //SetForegroundWindow(g_hwnd);
                    //Sleep(100);
                    //PostMessageW(g_hwnd, WM_LBUTTONDOWN, NULL, MAKELPARAM(lopot.x, lopot.y));
                    break;/// !!!!!!!!!!!!!!!!!
                }

                break;
            }
            case WM_LBUTTONUP: {
                lopot.x = scal_f * pMouseS->pt.x;
                lopot.y = scal_f * pMouseS->pt.y;
                curr = WindowFromPoint(lopot);
                GetWindowTextA(curr, curr_title, sizeof(curr_title));
                if (!strcmp(curr_title, "FolderView")) {
                    //lopot.x = pMouseS->pt.x / 2;
                    //lopot.y = pMouseS->pt.y / 2;

                    //curr = WindowFromPoint(lopot);

                    //GetWindowTextA(curr, curr_title, sizeof(curr_title));
                    //SetForegroundWindow(g_hwnd);
                    //if (GetForegroundWindow() == g_hwnd) {
                        //PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                    //}
                    ///else {
                    //SetActiveWindow(g_hwnd);
                    //SetForegroundWindow(g_hwnd);
                    //SetFocus(g_hwnd);
                    //SetActiveWindow(g_hwnd);
                    //Sleep(50);
                    PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                    //SetForegroundWindow(FindWindowW(NULL, L"eeeee.txt - Notepad"));
                    //SetForegroundWindow(g_hwnd);
                    //}
                    //PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                }
                else {
                    //SetForegroundWindow(g_hwnd);
                    //PostMessageW(g_hwnd, WM_LBUTTONUP, NULL, MAKELPARAM(lopot.x, lopot.y));
                    break;/// !!!!!!!!!!!!!!!!!
                }


                break;
            }

            default:break;

            }
            

        }

    }

    return CallNextHookEx(_hook, code, wparam, lparam);

}

unsigned set_hook(wchar_t *wname){

    g_hwnd = FindWindowW(NULL , wname);
    
    if(g_hwnd == NULL){

        return 1;//error : unable to find window!

    }

    scal_f = get_scal();

    if (sorn < 1.02) {
        if (!(_hook = SetWindowsHookEx(WH_MOUSE_LL, HookCallback, NULL, 0))) {

            return 2;//error : unable to set hook!

        }
    }
    else {
        if (!(_hook = SetWindowsHookEx(WH_MOUSE_LL, HookCallback_S, NULL, 0))) {

            return 2;//error : unable to set hook!

        }

    }

    


    //if(!(_hook = SetWindowsHookEx(WH_MOUSE_LL , HookCallback, NULL, 0))){

    //        return 2;//error : unable to set hook!

    //}


    return 3;//success
        


}

unsigned unhook(){

    if(UnhookWindowsHookEx(_hook)){
		return 1;
    }
    else {
        exit(-1);
    }
	
	return 0;

}