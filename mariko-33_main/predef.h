// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
//#include<iostream>
//#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define WXUSINGDLL

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

//#include <string>

#include <tchar.h>
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>

#include <locale.h>
#include <wx/stattext.h>
#include <wx/statline.h>


#include <wx/wxprec.h>
#include <wx/choicdlg.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
//#include "mondrian.xpm"

#define wxID_EFFECT 6480
#define wxID_ENGLISH 6481
#define wxID_CHINESE 6482

HINSTANCE hdll1 = LoadLibraryW(L"mariko-33_gsw.dll");
HINSTANCE hdll2 = LoadLibraryW(L"mariko-33_sbw.dll");
HINSTANCE hdll3 = LoadLibraryW(L"mariko-33_hmi.dll");


//hdll = LoadLibraryW(L"mariko-33_gsw.dll");

typedef unsigned(*NUMFUNC)();
typedef unsigned(*WNAME)(unsigned wnum, wchar_t** name);
typedef unsigned(*SETWALL)(wchar_t* nam);
typedef unsigned(*SETHOOK)(wchar_t* wname);
typedef unsigned(*UNHOOK)();
typedef unsigned(*PULLOUT)(HWND wnd);
NUMFUNC get_num = (NUMFUNC)(GetProcAddress(hdll1, "get_windows_num"));
WNAME get_window = (WNAME)(GetProcAddress(hdll1, "get_all_windows_name"));
SETWALL set_wall = (SETWALL)(GetProcAddress(hdll2, "set_wall"));
SETHOOK set_hook = (SETHOOK)(GetProcAddress(hdll3, "set_hook"));
UNHOOK unhook = (UNHOOK)(GetProcAddress(hdll3, "unhook"));
PULLOUT pullout = (PULLOUT)(GetProcAddress(hdll2, "pull_out_window"));
//std::cout << get_num() << std::endl;

//class Staticline : public wxDialog
//{
//public:
//	Staticline(const wxString& title);
//};
wchar_t snow_name[]={_T("Snow_galback.exe")};

void killProcessByName(wchar_t *filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (_tcscmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

HWND set_or_not = NULL;
//DWORD pid;
BOOL config_language(wxLocale* locale);

char lan='1';

class MyApp :public wxApp {
public:
	///int yy = 9;
	virtual bool OnInit();
	virtual int OnExit();
	wxLocale locale;
};

class MyFrame :public wxFrame {
public:
	MyFrame(const wxString& title);




	void OnOpen(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnEffect(wxCommandEvent& event);
	void OnClear(wxCommandEvent& event);
	void OnChinese(wxCommandEvent& event);
	void OnEnglish(wxCommandEvent& event);


	void logtext(wxString infoma);



	//int yy = 9;


	wxString info_to_append = L"test!\n";

	wxString  text = wxT("directx/3d games and some old games may not be supported!\n\n");
	//		text2 = wxT("eee");
	//Staticline(const wxString& title);




	wxTextCtrl* info = new wxTextCtrl(this, 1, this->text, wxPoint(0, 0), wxSize(470, 200), wxTE_READONLY | wxTE_MULTILINE);// , text2);

private:

	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
EVT_MENU(wxID_HELP, MyFrame::OnHelp)
EVT_MENU(wxID_CLOSE, MyFrame::OnClose)
EVT_MENU(wxID_CHINESE, MyFrame::OnChinese)
EVT_MENU(wxID_ENGLISH, MyFrame::OnEnglish)
EVT_BUTTON(wxID_OPEN, MyFrame::OnOpen)
EVT_BUTTON(wxID_EXIT, MyFrame::OnQuit)
EVT_BUTTON(wxID_HELP, MyFrame::OnHelp)
EVT_BUTTON(wxID_ABOUT, MyFrame::OnAbout)
EVT_BUTTON(wxID_CLOSE, MyFrame::OnClose)
EVT_BUTTON(wxID_EFFECT, MyFrame::OnEffect)
EVT_BUTTON(wxID_CLEAR, MyFrame::OnClear)
END_EVENT_TABLE();

