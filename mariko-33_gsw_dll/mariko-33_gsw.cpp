#include "mariko-33_gsw.h"

#ifndef NAME_LEN
#define NAME_LEN 256
#endif

unsigned w_count;

BOOL CALLBACK lpEnumFunc(HWND hwnd , LPARAM lparam){
	
	
	if(IsWindowVisible(hwnd) && GetWindowTextLengthW(hwnd)){

		HWND *t_hwnd = reinterpret_cast<HWND *>(lparam);
		t_hwnd[w_count] = hwnd;
		++w_count;
		//wchar_t WindowName[512];
		//GetWindowTextW(hwnd , WindowName , sizeof(WindowName));
		//++w_count;

	}
	
	return 1;
}

BOOL CALLBACK lpEnumFunc_num(HWND hwnd , LPARAM lparam){
	
	//HWND *t_hwnd = reinterpret_cast<HWND *>(lparam);
	if(IsWindowVisible(hwnd) && GetWindowTextLengthW(hwnd)){
		//wchar_t WindowName[512];
		++w_count;

	}
	
	return 1;
}

unsigned get_all_windows_name(unsigned wnum , wchar_t **name){
	
	

	w_count = 0;

	wchar_t t_name[NAME_LEN];

	HWND *g_hwnd = NULL;

	g_hwnd = new HWND [wnum];

	::EnumWindows(lpEnumFunc , reinterpret_cast<LPARAM>(g_hwnd));

	for(unsigned i = 0; i < wnum; ++i){

		GetWindowTextW(g_hwnd[i] , t_name , sizeof(t_name));

		for(unsigned j = 0 ; j < NAME_LEN ; ++j){

			name[i][j] = t_name[j];

		}
		
	}
	
	delete[] g_hwnd;

	g_hwnd = NULL;

	return 0;
	
}

unsigned get_windows_num(){

	unsigned num;
	
	w_count = 0;
	::EnumWindows(lpEnumFunc_num , 0);
	num=w_count;

	return num;
}