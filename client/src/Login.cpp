///-----------------------------------------------------------------
///
/// @file      Login.cpp
/// @author    Utente
/// Created:   08/10/2014 16:43:03
/// @section   DESCRIPTION
///            Login class implementation
///
///------------------------------------------------------------------
#include "translateController\translateVariable.h"
#include "translateController\translateController.h"
#include "Login.h"
#include "ClientTsFrm.h"
#include "AudioWizard.h"
#include <malloc.h>
#include "utility.h"
//#include "tinyxml2.h"
//#include "tinyxml2.cpp"
#include <iostream>
#include <fstream>
#include "../res/ico_connection.xpm"

FILE*config;
char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLanguage[20];
char StringLoginService[20];
int  cmbelement=0;

//----------------------------------------------------------------------------
// Login
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start

/*

*/

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Login::~Login()
{
	// Disconnect Events
	cmblingua->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmb_lingua_SelectionChange), NULL, this);
	cmdConfirm->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::cmdConfirmClick), NULL, this);
} 

void Login::CreateGUIControls()
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->Centre(wxBOTH);
	this->SetSize(wxSize(600, 400));

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);


	bSizer5->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(ico_connection), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer5->Add(m_bitmap1, 0, wxALL, 5);


	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	lblServer = new wxStaticText(this, wxID_ANY, wxT("Name/Host server:"), wxDefaultPosition, wxSize(150, -1), 0);
	lblServer->Wrap(-1);
	bSizer3->Add(lblServer, 0, wxALL, 5);

	txtServer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(txtServer, 1, wxALL, 5);


	bSizer2->Add(bSizer3, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer(wxHORIZONTAL);

	lblNickName = new wxStaticText(this, wxID_ANY, wxT("Nickname:"), wxDefaultPosition, wxSize(150, -1), 0);
	lblNickName->Wrap(-1);
	bSizer31->Add(lblNickName, 0, wxALL, 5);

	txtNickname = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer31->Add(txtNickname, 1, wxALL, 5);


	bSizer2->Add(bSizer31, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer(wxHORIZONTAL);

	lbllanguage = new wxStaticText(this, wxID_ANY, wxT("Language:"), wxDefaultPosition, wxSize(150, -1), 0);
	lbllanguage->Wrap(-1);
	bSizer311->Add(lbllanguage, 0, wxALL, 5);

	cmblingua = new wxComboBox(this, wxID_ANY, wxT("<Select language>"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	cmblingua->Append(wxT("English"));
	cmblingua->Append(wxT("Italian"));
	cmblingua->Append(wxT("Portuguese"));
	cmblingua->Append(wxEmptyString);
	bSizer311->Add(cmblingua, 1, wxALL, 5);


	bSizer2->Add(bSizer311, 0, wxEXPAND, 5);


	bSizer2->Add(20, 20, 0, wxEXPAND, 5);

	lblService = new wxStaticText(this, wxID_ANY, wxT("Service:"), wxDefaultPosition, wxDefaultSize, 0);
	lblService->Wrap(-1);
	bSizer2->Add(lblService, 0, wxALL, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	optGoogle = new wxRadioButton(this, wxID_ANY, wxT("Google Translate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(optGoogle, 0, wxALL, 5);

	optBing = new wxRadioButton(this, wxID_ANY, wxT("Bing Translate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(optBing, 0, wxALL, 5);

	bSizer2->Add(bSizer7, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	bSizer6->Add(0, 0, 1, wxEXPAND, 5);

	cmdConfirm = new wxButton(this, wxID_ANY, wxT("Confirm"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(cmdConfirm, 0, wxALL, 5);

	bSizer2->Add(bSizer6, 0, wxEXPAND, 5);

	this->SetSizer(bSizer2);
	this->Layout();

	// Connect Events
	cmblingua->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmb_lingua_SelectionChange), NULL, this);
	cmdConfirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::cmdConfirmClick), NULL, this);
	
	////GUI Items Creation End
	Login::ReadConfig();

	//Init controller with initial language
	TranslateController::InitController(cmblingua->GetStringSelection().mb_str().data());	
	changeLanguage();

	//writeAndReadLabels();
}

void Login::ReadConfig()
{
	if (config = fopen("conf\\config.txt", "r"))
	{
		fscanf(config, "%s", &StringLoginServer);
		txtServer->SetValue(StringLoginServer);

		fscanf(config, "%s", &StringLoginNick);
		txtNickname->SetValue(StringLoginNick);

		fscanf(config, "%d", &cmbelement);
		cmblingua->SetSelection(cmbelement);

		fscanf(config, "%s", &StringLoginLanguage);
		cmblingua->SetValue(StringLoginLanguage);

		fscanf(config, "%s", &StringLoginService);
		if (StringLoginService == "google")
		{
			optGoogle->SetValue(true);
			optBing->SetValue(false);
		}
		if (StringLoginService == "bing")
		{
			optGoogle->SetValue(false);
			optBing->SetValue(true);
		}

		fclose(config);
	}
	cmblingua->SetSelection(cmbelement);
}

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void Login::cmb_lingua_SelectionChange(wxCommandEvent& event)
{
	TranslateController::InitController(cmblingua->GetStringSelection().mb_str().data());
	changeLanguage();
}

void Login::cmdConfirmClick(wxCommandEvent& event)
{
	// insert your code here
	//wxMessageBox(ip);

	strncpy(StringLoginServer, (const char*)txtServer->GetValue().mb_str(wxConvUTF8), 20);
	strncpy(StringLoginNick, (const char*)txtNickname->GetValue().mb_str(wxConvUTF8), 50);
	strncpy(StringLoginLanguage, (const char*)cmblingua->GetStringSelection().mb_str(wxConvUTF8), 20);

	char ip[100];
	Utility::hostname_to_ip(StringLoginServer, ip);


	config = fopen("conf\\config.txt", "w");
	fprintf(config, "%s\n", ip);
	fprintf(config, "%s\n", StringLoginNick);
	fprintf(config, "%d\n", cmblingua->GetSelection());
	fprintf(config, "%s\n", StringLoginLanguage);
	if (optGoogle->GetValue() == true) fprintf(config, "%s", "google");
	if (optBing->GetValue() == true)   fprintf(config, "%s", "bing");
	fflush(config);
	fclose(config);

	ClientTsFrm* frame = new ClientTsFrm(NULL);
	frame->Show();
	this->Close();
}

void Login::changeLanguage()
{
	lblServer->SetLabel( labels.nameHostServer );
	lbllanguage->SetLabel( labels.language );
	lblService->SetLabel( labels.service );
	cmdConfirm->SetLabel( labels.cmdConfirm );
}