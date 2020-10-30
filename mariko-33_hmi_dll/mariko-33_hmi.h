#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include<iostream>
#include<Windows.h>
#include<shellscalingapi.h>

#pragma comment(lib,"Shcore.lib")

#define IMPORT_DLL extern "C" __declspec(dllimport)

#define NAME_LEN 256

IMPORT_DLL unsigned set_hook(wchar_t *wname);

IMPORT_DLL unsigned unhook();
