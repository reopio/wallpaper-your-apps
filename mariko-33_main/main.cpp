#include "predef.h"



BOOL config_language(wxLocale* locale) {

	FILE* conf;

	LANGID lid = GetSystemDefaultLangID();

	//char lan = '1';



	conf = fopen("configure", "r");
	if (conf == NULL) {

		conf = fopen("configure", "w");
		//huo qu xi tong yu yan bing chuang jian conf
		switch (lid) {

		case 0x0804: {

			//wxLocale* locale = new wxLocale(wxLANGUAGE_CHINESE);
			locale->Init(wxLANGUAGE_CHINESE);
			locale->AddCatalogLookupPathPrefix(wxT("."));
			locale->AddCatalog(wxT("cn"));
			//locale->AddCatalogLookupPathPrefix(wxT("."));
			//locale->AddCatalog(wxT("zh_CN"));
			lan = '0';
			//conf = fopen("configure", "w");
			//fwrite(&lan, sizeof(lan), 1, conf);
			//fclose(conf);
			break;
		}

		case 0x0409: {

			locale->Init(wxLANGUAGE_ENGLISH);
			//locale->AddCatalogLookupPathPrefix(wxT("."));
			//locale->AddCatalog(wxT("en"));
			lan = '1';
			//conf = fopen("configure", "w");
			//fwrite(&lan, sizeof(lan), 1, conf);
			//fclose(conf);
			break;

		}
		default: {

			locale->Init(wxLANGUAGE_ENGLISH);
			//locale->AddCatalogLookupPathPrefix(wxT("."));
			//locale->AddCatalog(wxT("en"));
			lan = '1';
			//conf = fopen("configure", "w");
			//fwrite(&lan, sizeof(lan), 1, conf);
			//fclose(conf);
			break;

		}
		}

		//conf = fopen("configure", "w");
		fwrite(&lan, sizeof(lan), 1, conf);
		fclose(conf);

		return true;

	}
	else {

		fread(&lan, sizeof(lan), 1, conf);
		switch (lan) {

		case '0': {
			locale->Init(wxLANGUAGE_CHINESE);
			locale->AddCatalogLookupPathPrefix(wxT("."));
			locale->AddCatalog(wxT("cn"));
			break;

		}
		case '1': {
			locale->Init(wxLANGUAGE_ENGLISH);
			//locale->AddCatalogLookupPathPrefix(wxT("."));
			//locale->AddCatalog(wxT("en"));
			break;
		}
		default: {
			locale->Init(wxLANGUAGE_ENGLISH);
			//locale->AddCatalogLookupPathPrefix(wxT("."));
			//locale->AddCatalog(wxT("en"));
			break;
		}

		}
		fclose(conf);

		return true;
	}
	return true;

}


DECLARE_APP(MyApp);

IMPLEMENT_APP(MyApp);


bool MyApp::OnInit() {



	setlocale(LC_ALL, "");


	//locale->AddCatalogLookupPathPrefix(wxT("."));
	//locale->AddCatalog(wxT("en"));

	config_language(&(this->locale));


	//wxLocale::AddCatalogLookupPathPrefix(_T("C:\\Users\\gejifeng\\source\\repos\\wx\\x64\\Release"));
	//l_locale.AddCatalog(_T("chs"));

	MyFrame* frame = new MyFrame(_("Wallpaper Galgame/Visual_Novel"));

	frame->Show(true);

	return true;
}

int MyApp::OnExit() {

	//wxMessageBox(L"as", L"ASCDAS");
	killProcessByName(snow_name);
	if (set_or_not != NULL) {
		if (!pullout(set_or_not)) {

			unhook();
			set_or_not = NULL;

		}
		else {
			unhook();
			wxMessageBox(_("Unable to clear! Program Crashed!"), _("WARING"));
			set_or_not = NULL;

		}
	}
	else {
		unhook();
	}


	//wxMessageBox(L"DSADS", L"SDECFS");



	return 0;
}

void MyFrame::logtext(wxString infoma) {

	this->info_to_append = infoma;

	this->info->AppendText(info_to_append);


}

void MyFrame::OnEnglish(wxCommandEvent& event) {

	FILE* conf;
	char mak = '1';
	conf = fopen("configure", "w");
	fwrite(&mak, sizeof(mak), 1, conf);
	fclose(conf);
	wxMessageBox(_("Restart Software to take effect!"), _("TIPS"));

	Close(TRUE);



}

void MyFrame::OnChinese(wxCommandEvent& event) {
	FILE* conf;
	char mak = '0';
	conf = fopen("configure", "w");
	fwrite(&mak, sizeof(mak), 1, conf);
	fclose(conf);
	wxMessageBox(_("Restart Software to take effect!"), _("TIPS"));

	Close(TRUE);

}

void MyFrame::OnClear(wxCommandEvent& event) {


	//ShellExecute(NULL, _T("open"), snow_name, NULL, NULL, SW_SHOW);
	//killProcessByName(snow_name);
	wxMessageBox(_("Coming soon"), "info");

}
void MyFrame::OnEffect(wxCommandEvent& event) {

	//ShellExecute(NULL, _T("open"), snow_name, NULL, NULL, SW_SHOW);
	wxMessageBox(_("Coming soon"), "info");

}

void MyFrame::OnQuit(wxCommandEvent& event)
{
	//wxMessageBox(L"as", L"ASCDAS");
	if (set_or_not == NULL) {
		unhook();
		killProcessByName(snow_name);//defined in head file
		Close(TRUE);
	}
	else {
		killProcessByName(snow_name);
		if (!pullout(set_or_not)) {

			unhook();
			set_or_not = NULL;
			Close(TRUE);
		}
		else {
			wxMessageBox(_("Unable to clear! Program Crashed!"), _("WARNING"));
			unhook();
			set_or_not = NULL;
			Close(TRUE);
		}
	}

	//Close(true);
}



void MyFrame::OnOpen(wxCommandEvent& event)
{

	if (set_or_not != NULL) {

		wxMessageBox(_("A window is running, please turn it of first"), _("ERROR"), wxOK | wxICON_INFORMATION);

		this->logtext(_("A window is running, please turn it of first\n\n"));

		return;
	}

	unsigned windows_num = get_num();

	wchar_t selle[256];

	wchar_t** windows_list = new wchar_t* [windows_num];
	for (unsigned i = 0; i < windows_num; ++i) {
		windows_list[i] = new wchar_t[256];
	}
	get_window(windows_num, windows_list);


	wxArrayString choices;
	//choices.Add(_T("one"));
	//choices.Add(_T("two"));
	//choices.Add(_T("three"));

	for (unsigned i = 0; i < windows_num; ++i) {
		choices.Add(windows_list[i]);
	}


	for (unsigned i = 0; i < windows_num; ++i) {
		delete[] windows_list[i];
	}
	delete[] windows_list;


	wxSingleChoiceDialog dialog(this, _("Windows available:"), _("Please select window"), choices);
	dialog.SetSelection(2);
	if (dialog.ShowModal() == wxID_OK) {
		for (unsigned i = 0; i < 256; ++i) {
			selle[i] = (wchar_t)dialog.GetStringSelection().wc_str()[i];
		}
		//selle = (wchar_t)dialog.GetStringSelection().wc_str();
		//wxString mystring(selle);
		wxMessageBox(selle, _("Selected"));
		this->logtext(_("Selected\n\n"));

		this->info_to_append = L"setting now...\n\n";
		this->info->AppendText(info_to_append);

		//
		set_or_not = FindWindowW(NULL, selle);
		set_hook(selle);
		set_wall(selle);
		SetForegroundWindow(set_or_not);
		//wxMessageBox(L"kojjhij");
		
		//set_or_not = FindWindowW(NULL, selle);
		//if (set_or_not == NULL) {
		//	wxMessageBox(L"dsfcsdfsdfsdf", _("已选择，请按OK确认！"));
		//}
		//wxMessageBox(set_or_not, _("已选择，请按OK确认！"));
		this->info_to_append = L"done!\n\n";
		this->info->AppendText(info_to_append);
		//delete[] selle;
	}



}

void MyFrame::OnAbout(wxCommandEvent& event) {



	wxMessageBox(_("Made by mariko-33"), L"Information");


	//ShellExecute(NULL, _T("open"), _T("explorer.exe"), _T("http://www.baidu.com"), NULL, SW_SHOW);


}
void MyFrame::OnClose(wxCommandEvent& event) {

	if (set_or_not == NULL) {

		wxMessageBox(_("No window is running"), _("ERROR"), wxOK | wxICON_INFORMATION);
		this->logtext(_("No window is running\n\n"));

		return;

	}


	if (!pullout(set_or_not)) {

		unhook();

		set_or_not = NULL;

		return;
	}

	wxMessageBox(_("Unable to recover window, crashed"), _("WARNING"), wxOK | wxICON_INFORMATION);
	logtext(_("WARNING: unable to recover window!\n\n"));
	unhook();
	exit(-1);

}

void MyFrame::OnHelp(wxCommandEvent& event) {

	//this->text = L"scdscsdc";
	//this->info->AppendText(info_to_append);
	switch (lan) {
	case '0': {
		//ShellExecute(NULL, _T("open"), _T("explorer.exe"), _T("http://www.baidu.com"), NULL, SW_SHOW);
		//bilibili
		ShellExecute(NULL, L"open", L"Readme.txt", NULL, NULL, SW_SHOWNORMAL);
		break;
	}
	default: {
		//readme.txt
		ShellExecute(NULL, L"open", L"Readme.txt", NULL, NULL, SW_SHOWNORMAL);
		break;
	}
	}
	//ShellExecute(NULL, _T("open"), _T("explorer.exe"), _T("http://www.baidu.com"), NULL, SW_SHOW);
}





MyFrame::MyFrame(const wxString& title)
	:wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(470, 360)) {
	//SetIcon(wxIcon(mondrian_xpm));
	SetIcon(wxIcon(L"myicon"));
	wxMenu* menuOpen = new wxMenu;
	wxMenu* menuLanguage = new wxMenu;
	wxMenu* menuAbout = new wxMenu;
	wxMenu* menuHelp = new wxMenu;

	wxButton* button1 = new wxButton(this, wxID_OPEN, _("Open"), wxPoint(10, 210), wxDefaultSize),
		* button2 = new wxButton(this, wxID_CLOSE, _("Recover"), wxPoint(100, 210), wxDefaultSize),
		* button3 = new wxButton(this, wxID_EFFECT, _("Snow"), wxPoint(190, 210), wxDefaultSize),
		* button4 = new wxButton(this, wxID_CLEAR, _("Clear"), wxPoint(280, 210), wxDefaultSize),
		* button5 = new wxButton(this, wxID_EXIT, _("Exit"), wxPoint(370, 210), wxDefaultSize),
		* button6 = new wxButton(this, wxID_HELP, _("Help"), wxPoint(10, 245), wxSize(200, 23)),
		* button7 = new wxButton(this, wxID_ABOUT, _("About"), wxPoint(245, 245), wxSize(200, 23));
	//button1->Bind();
		//* button6 = new wxButton(this, wxID_OK, _T("       "), wxPoint(10, 10), wxDefaultSize);

	/*
	wxString  text = wxT("'Cause sometimes you feel tired,\
	feel weak, and when you feel weak,\
	you feel like you wanna just give up.\n\
	But you gotta search within you,\
	you gotta find that inner strength\n\
	and just pull that shit out of you\
	and get that motivation to not give up\n\
	and not be a quitter,\
	no matter how bad you wanna just fall flat on your face and collapse.");
//		text2 = wxT("eee");*/

//wxTextCtrl* textctrl = new wxTextCtrl(this, 1, this->text, wxPoint(0, 0), wxSize(470, 200), wxTE_READONLY | wxTE_MULTILINE);// , text2);




	menuOpen->Append(wxID_OPEN, _("Open"));
	menuLanguage->Append(wxID_CHINESE, "Chinese");
	menuLanguage->Append(wxID_ENGLISH, "English");
	menuHelp->Append(wxID_HELP, _("Help"));
	menuAbout->Append(wxID_ABOUT, _("About"));


	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuOpen, _("Open"));

	menuBar->Append(menuHelp, _("Help"));
	menuBar->Append(menuAbout, _("About"));
	menuBar->Append(menuLanguage, L"Language");
	SetMenuBar(menuBar);


	CreateStatusBar();


	SetStatusText("Made by mariko-33");
}