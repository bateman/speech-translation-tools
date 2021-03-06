#include "Login.h"

FILE*config;
char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLingua[20];
char StringLoginServizio[20];
int  cmbelement = 0;

Labels labels;
char CURRENT_LANG[20] = { "English" };
wxString StringTranslate = "";

int hostname_to_ip(char * hostname, char* ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		// get the host info
		printf("Errore nella risoluzione.\n");
		return 1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return 0;
	}

	return 1;
}

BEGIN_EVENT_TABLE(Login, wxDialog)
EVT_CLOSE(Login::OnClose)
EVT_BUTTON(ID_WXBUTTON1, Login::btnloginClick)
EVT_COMBOBOX(ID_WXCOMBOBOX1, Login::cmblingua_SelectionChange)
END_EVENT_TABLE()

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style) : wxDialog(parent, id, title, position, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->Centre(wxBOTH);

	this->SetSize(wxSize(600, 400));

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	bSizer5->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(connect_xpm), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer5->Add(m_bitmap1, 0, wxALL, 5);


	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	lblNameHost = new wxStaticText(this, wxID_ANY, wxT("Login"), wxDefaultPosition, wxSize(150, -1), 0);
	lblNameHost->Wrap(-1);
	bSizer3->Add(lblNameHost, 0, wxALIGN_CENTER | wxALL, 5);

	txtNameHost = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(txtNameHost, 1, wxALL, 5);


	bSizer2->Add(bSizer3, 0, wxALIGN_CENTER | wxEXPAND, 5);

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer(wxHORIZONTAL);

	lblNickName = new wxStaticText(this, wxID_ANY, wxT("Nickname:"), wxDefaultPosition, wxSize(150, -1), 0);
	lblNickName->Wrap(-1);
	bSizer31->Add(lblNickName, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txtNickName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer31->Add(txtNickName, 1, wxALL, 5);


	bSizer2->Add(bSizer31, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer(wxHORIZONTAL);

	lblLanguage = new wxStaticText(this, wxID_ANY, labels.language, wxDefaultPosition, wxSize(150, -1), 0);
	lblLanguage->Wrap(-1);
	bSizer311->Add(lblLanguage, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmbLingua = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	cmbLingua->Append(wxT("English"));
	cmbLingua->Append(wxT("Italian"));
	cmbLingua->Append(wxT("Portuguese"));
	bSizer311->Add(cmbLingua, 1, wxALL, 5);


	bSizer2->Add(bSizer311, 0, wxEXPAND, 5);


	bSizer2->Add(20, 20, 0, wxEXPAND, 5);

	lblService = new wxStaticText(this, wxID_ANY, labels.service, wxDefaultPosition, wxDefaultSize, 0);
	lblService->Wrap(-1);
	bSizer2->Add(lblService, 0, wxALL, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	radGoogle = new wxRadioButton(this, wxID_ANY, wxT("Google Translate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(radGoogle, 0, wxALL, 5);

	radBing = new wxRadioButton(this, wxID_ANY, wxT("Bing Translate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(radBing, 0, wxALL, 5);

	bSizer2->Add(bSizer7, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);


	bSizer6->Add(0, 0, 1, wxEXPAND, 5);

	cmdConfirm = new wxButton(this, wxID_ANY, labels.confirm, wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(cmdConfirm, 0, wxALL, 5);


	bSizer2->Add(bSizer6, 0, wxEXPAND, 5);


	this->SetSizer(bSizer2);
	this->Layout();

	// Connect Events
	cmbLingua->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
	cmdConfirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::btnloginClick), NULL, this);

	ReadConfig();
	Login::SetLabel();
}

Login::~Login()
{
	// Disconnect Events
	cmbLingua->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
	cmdConfirm->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::btnloginClick), NULL, this);
}

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void Login::ReadConfig()
{
	ifstream file("..\\bin\\conf\\config.txt", ios::in);
	if (file.is_open()){
		if (config = fopen("..\\bin\\conf\\config.txt", "r"))
		{

			fscanf(config, "%s", &StringLoginServer);
			txtNameHost->SetValue(StringLoginServer);

			fscanf(config, "%s", &StringLoginNick);
			txtNickName->SetValue(StringLoginNick);

			fscanf(config, "%d", &cmbelement);
			cmbLingua->SetSelection(cmbelement);

			fscanf(config, "%s", &StringLoginLingua);
			cmbLingua->SetValue(StringLoginLingua);

			fscanf(config, "%s", &StringLoginServizio);
			if (strcmp(StringLoginServizio,"google")==0)
			{
				radGoogle->SetValue(true);
				radBing->SetValue(false);
			}
			else
			{
				radGoogle->SetValue(false);
				radBing->SetValue(true);
			}

			TranslateController::InitLanguageVariable(StringLoginLingua);
			cmbLingua->SetSelection(cmbelement);

			fclose(config);
		}
	}
	else{
		cmbLingua->SetSelection(0);
		TranslateController::InitLanguageVariable((char *)cmbLingua->GetString(cmbLingua->GetSelection()).mb_str(wxConvUTF8).data());
	}

}

void Login::cmblingua_SelectionChange(wxCommandEvent& event)
{
	char lang[20] = { "" };
	strcpy(lang, (char*)cmbLingua->GetStringSelection().mb_str().data());

	TranslateController::InitLanguageVariable(lang);;
	Login::SetLabel();
}

void Login::SetLabel(){
	lblNameHost->SetLabel(labels.nameHostServer.append("/host server:").c_str());
	lblLanguage->SetLabel(labels.language.append(":").c_str());
	lblService->SetLabel(labels.service.append(":").c_str());
	cmdConfirm->SetLabel(labels.confirm.c_str());
}

void Login::btnloginClick(wxCommandEvent& event)
{
	strncpy(StringLoginServer, (const char*)txtNameHost->GetValue().mb_str(wxConvUTF8), 20);
	strncpy(StringLoginNick, (const char*)txtNickName->GetValue().mb_str(wxConvUTF8), 50);
	strncpy(StringLoginLingua, (const char*)cmbLingua->GetStringSelection().mb_str(wxConvUTF8), 20);

	char ip[20];
	hostname_to_ip(StringLoginServer, ip);

	config = fopen("..\\bin\\conf\\config.txt", "w");
	fprintf(config, "%s\n", ip);
	fprintf(config, "%s\n", StringLoginNick);
	fprintf(config, "%d\n", cmbLingua->GetSelection());
	fprintf(config, "%s\n", StringLoginLingua);
	if (radGoogle->GetValue() == true) fprintf(config, "%s", "google");
	if (radBing->GetValue() == true)   fprintf(config, "%s", "bing");
	fflush(config);
	fclose(config);

	TranslateController::InitLanguageVariable(StringLoginLingua);

	ClientTsFrm* frame = new ClientTsFrm(NULL);
	frame->Show();
	this->Close();
}


