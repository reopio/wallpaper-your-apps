#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif







#include <iostream>

#include <windows.h>

#define IMPORT_DLL extern "C" __declspec(dllimport)


IMPORT_DLL unsigned set_wall(wchar_t *nam);

IMPORT_DLL unsigned pull_out_window(HWND wnd);