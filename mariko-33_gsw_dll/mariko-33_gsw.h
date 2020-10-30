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

#define NAME_LEN 256
//#include <locale.h>

IMPORT_DLL unsigned get_all_windows_name(unsigned wnum , wchar_t **name);

//IMPORT_DLL unsigned set_window_name(wchar_t *sname);
IMPORT_DLL unsigned get_windows_num();