///-----------------------------------------------------------------
///
/// @file      Login.cpp
/// @author    Utente
/// Created:   08/10/2014 16:43:03
/// @section   DESCRIPTION
///            Login class implementation
///
///------------------------------------------------------------------

#include "Login.h"

#include "AudioWizard.h"
#include <malloc.h>
#include "utility.h"
#include "../res/connect.xpm"

#include <iostream>
#include <fstream>
#include "tinyxml2.h"

#include <string.h>
//#include "GlobalVariables.h"

using namespace tinyxml2;
using namespace std;

FILE*config;
char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLingua[20];
char StringLoginServizio[20];
int  cmbelement=0;

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        printf("Errore nella risoluzione.\n");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;
}
//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Login
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Login,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Login::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,Login::btnloginClick)
	EVT_COMBOBOX(ID_WXCOMBOBOX1, Login::cmblingua_SelectionChange)
END_EVENT_TABLE()
////Event Table End

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	/*
	*	CREATE GUI
	*/

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->Centre(wxBOTH);
	
	this->SetSize(wxSize(600, 400));

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	bSizer5->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap( connect_xpm ), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer5->Add(m_bitmap1, 0, wxALL, 5);


	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	lblNameHost = new wxStaticText(this, wxID_ANY, wxT("Name/Host server:"), wxDefaultPosition, wxSize(150, -1), 0);
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

	lblLanguage = new wxStaticText(this, wxID_ANY, wxT("Language:"), wxDefaultPosition, wxSize(150, -1), 0);
	lblLanguage->Wrap(-1);
	bSizer311->Add(lblLanguage, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmbLingua = new wxComboBox(this, wxID_ANY, wxT("<Select language>"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	cmbLingua->Append(wxT("English"));
	cmbLingua->Append(wxT("Italian"));
	cmbLingua->Append(wxT("Portuguese"));
	//cmbLingua->Append(wxEmptyString);
	bSizer311->Add(cmbLingua, 1, wxALL, 5);


	bSizer2->Add(bSizer311, 0, wxEXPAND, 5);


	bSizer2->Add(20, 20, 0, wxEXPAND, 5);

	lblService = new wxStaticText(this, wxID_ANY, wxT("Service:"), wxDefaultPosition, wxDefaultSize, 0);
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

	cmdConfirm = new wxButton(this, wxID_ANY, wxT("Confirm"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(cmdConfirm, 0, wxALL, 5);


	bSizer2->Add(bSizer6, 0, wxEXPAND, 5);


	this->SetSizer(bSizer2);
	this->Layout();

	// Connect Events
	cmbLingua->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
	cmdConfirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::btnloginClick), NULL, this);

	ReadConfig();

	//CreateGUIControls();
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

/*
void Login::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	radbing = new wxRadioButton(this, ID_WXRADIOBUTTON2, _("Bing Translate"), wxPoint(32, 272), wxSize(161, 17), 0, wxDefaultValidator, _("radbing"));

	radgoogle = new wxRadioButton(this, ID_WXRADIOBUTTON1, _("Google Translate"), wxPoint(32, 240), wxSize(153, 17), 0, wxDefaultValidator, _("radgoogle"));

	lbltrad = new wxStaticText(this, ID_WXSTATICTEXT4, _("Service:"), wxPoint(32, 192), wxDefaultSize, 0, _("lbltrad"));

	wxArrayString arrayStringFor_cmblingua;
	arrayStringFor_cmblingua.Add(_("English"));
	arrayStringFor_cmblingua.Add(_("Italian"));
	arrayStringFor_cmblingua.Add(_("Portuguese"));
	cmblingua = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(248, 128), wxSize(145, 28), arrayStringFor_cmblingua, 0, wxDefaultValidator, _("cmblingua"));

	lbllingua = new wxStaticText(this, ID_WXSTATICTEXT3, _("Language:"), wxPoint(32, 136), wxDefaultSize, 0, _("lbllingua"));

	btnlogin = new wxButton(this, ID_WXBUTTON1, _("Confirm"), wxPoint(451, 332), wxSize(89, 25), 0, wxDefaultValidator, _("btnlogin"));

	txtnick = new wxTextCtrl(this, ID_WXEDIT2, _(""), wxPoint(248, 86), wxSize(121, 22), 0, wxDefaultValidator, _("txtnick"));

	lblnick = new wxStaticText(this, ID_WXSTATICTEXT2, _("Nickname: "), wxPoint(30, 87), wxDefaultSize, 0, _("lblnick"));

	txtserver = new wxTextCtrl(this, ID_WXEDIT1, _("127.0.0.1"), wxPoint(249, 46), wxSize(121, 22), 0, wxDefaultValidator, _("txtserver"));

	lblserver = new wxStaticText(this, ID_WXSTATICTEXT1, _("Name/Host server: "), wxPoint(32, 45), wxDefaultSize, 0, _("lblserver"));

	SetTitle(_("Login Form"));
	SetIcon(wxNullIcon);
	SetSize(8,8,640,480);
	Center();
	
	////GUI Items Creation End
	
	
	if (config = fopen("..\\conf\\config.txt", "r"))
    {

        fscanf(config,"%s",&StringLoginServer);
        txtserver->SetValue(StringLoginServer);
        
        fscanf(config,"%s",&StringLoginNick);
        txtnick->SetValue(StringLoginNick);
        
        fscanf(config,"%d",&cmbelement);
        cmblingua->SetSelection(cmbelement);
        
        fscanf(config,"%s",&StringLoginLingua);
        cmblingua->SetValue(StringLoginLingua);
        
        fscanf(config,"%s",&StringLoginServizio);
        if(StringLoginServizio=="google")
        {
            radgoogle->SetValue(true);
            radbing->SetValue(false);
        }
        if(StringLoginServizio=="bing")
        {
            radgoogle->SetValue(false);
            radbing->SetValue(true);
        }
        
        fclose(config);
    }
    cmblingua->SetSelection(cmbelement);
	
}
*/

void Login::ReadConfig()
{
	if (config = fopen("..\\conf\\config.txt", "r"))
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
		if (StringLoginServizio == "google")
		{
			radGoogle->SetValue(true);
			radBing->SetValue(false);
		}
		if (StringLoginServizio == "bing")
		{
			radGoogle->SetValue(false);
			radBing->SetValue(true);
		}

		fclose(config);
	}
	cmbLingua->SetSelection(cmbelement);
}

/*	
 * EVENTI 
*/

/*
*	cmbSelectionChange
*/

void Login::cmblingua_SelectionChange(wxCommandEvent& event)
{

	char lang[20] = { "" };
	char filename[20] = { "" };

	strcpy(lang, (char*)cmbLingua->GetStringSelection().mb_str().data());
	wxString trad = traduzioneLabel(lang);
	labels.nameHostServer = strtok((char *)trad.mb_str().data(), ", ");
	labels.language = strtok(NULL, ", ");
	labels.service = strtok(NULL, ", ");
	labels.login = strtok(NULL, ", ");
	labels.gridMessage = strtok(NULL, ", ");
	labels.send = strtok(NULL, ", ");

	strcpy(filename, strcat(lang, ".xml"));
	ifstream file(filename,ios::in);
	if (!file.is_open()){
		writeXmlLangDoc(filename);
	}

	readXmlLangDoc(filename);

	file.close();

	/*lblNameHost->SetLabel("");
    //lblNickName->SetLabel("");
	lblLanguage->SetLabel("");
	lblService->SetLabel("");
	cmdConfirm->SetLabel("");*/

	lblNameHost->SetLabel(wxString::FromUTF8(labels.nameHostServer));

	//lblNickName->SetLabel(labels.nickname);
	
	lblLanguage->SetLabel(wxString::FromUTF8(labels.language));

	lblService->SetLabel(wxString::FromUTF8(labels.service));
	
	cmdConfirm->SetLabel(wxString::FromUTF8(labels.login));

}

/*
 * btnloginClick
 */
void Login::btnloginClick(wxCommandEvent& event)
{
	// insert your code here
	//wxMessageBox(ip);
	
    strncpy(StringLoginServer, (const char*)txtNameHost->GetValue().mb_str(wxConvUTF8), 20);
    strncpy(StringLoginNick, (const char*)txtNickName->GetValue().mb_str(wxConvUTF8), 50);
    strncpy(StringLoginLingua, (const char*)cmbLingua->GetStringSelection().mb_str(wxConvUTF8), 20);    
    
    char ip[100];
	hostname_to_ip(StringLoginServer , ip);
	
	
        config=fopen("..\\conf\\config.txt","w");
		fprintf(config, "%s\n", ip); 
    	fprintf(config,"%s\n",StringLoginNick);
    	fprintf(config,"%d\n",cmbLingua->GetSelection());
    	fprintf(config,"%s\n",StringLoginLingua);
    	if(radGoogle->GetValue()==true) fprintf(config,"%s","google");
    	if(radBing->GetValue()==true)   fprintf(config,"%s","bing");
    	fflush(config);
    	fclose(config);
    
	ClientTsFrm* frame = new ClientTsFrm(NULL);
    frame->Show();
	this->Close();
}
void Login::readXmlLangDoc(char* filename){

	tinyxml2::XMLDocument xmlDoc;//creazione document per la lettura
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename); //caricamento del file xml
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();//lettura del padre language

	tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("lblNameHost"); //lettura figlio
	labels.nameHostServer = const_cast<char *>(pElement->GetText());//lettura valore del figlio
	/*
	pElement = pRoot->FirstChildElement("lblNickName");//lettura figlio
	lblNickName = const_cast<char *>(pElement->GetText());//lettura valore del figlio
	*/
	pElement = pRoot->FirstChildElement("lblLanguage");//lettura figlio
	strcpy(labels.language, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	pElement = pRoot->FirstChildElement("lblService");//lettura figlio
	strcpy(labels.service, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	pElement = pRoot->FirstChildElement("btnlogin");//lettura figlio
	strcpy(labels.login, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	pElement = pRoot->FirstChildElement("lblmessage");//lettura figlio
	strcpy(labels.gridMessage, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	pElement = pRoot->FirstChildElement("btnsend");//lettura figlio
	strcpy(labels.send, const_cast<char *>(pElement->GetText()));//lettura valore del figlio

}

//creazione traduzione scrittura e lettura xml per interfaccia
void Login::writeXmlLangDoc(char* filename)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument(); //creazione documento
	tinyxml2::XMLNode* element = doc->InsertEndChild(doc->NewElement("language")); //creazione nodo radice //
	tinyxml2::XMLElement* sub[7] = { doc->NewElement("lblNameHost"), doc->NewElement("lblLanguage"), doc->NewElement("lblService"), doc->NewElement("btnlogin"), doc->NewElement("lblmessage"), doc->NewElement("btnsend") }; //creazione figli con inserimento tag

	//assegnazione dei valori nei tag
	sub[0]->InsertFirstChild(doc->NewText(labels.nameHostServer));
	element->InsertEndChild(sub[0]);
	sub[1]->InsertFirstChild(doc->NewText(labels.language));
	element->InsertEndChild(sub[1]);
	sub[2]->InsertFirstChild(doc->NewText(labels.service));
	element->InsertEndChild(sub[2]);
	sub[3]->InsertFirstChild(doc->NewText(labels.login));
	element->InsertEndChild(sub[3]);
	sub[4]->InsertFirstChild(doc->NewText(labels.gridMessage));
	element->InsertEndChild(sub[4]);
	sub[5]->InsertFirstChild(doc->NewText(labels.send));
	element->InsertEndChild(sub[5]);

	doc->Print(); //stampa nella console

	//int value = 10;
	//int result = doc->FirstChildElement()->LastChildElement()->QueryIntAttribute("attrib", &value);

	//stampa sul file
	{
		XMLPrinter streamer;
		doc->Print(&streamer);
		printf("%s", streamer.CStr());
	}
		{
			XMLPrinter streamer(0, true);
			doc->Print(&streamer);
		}
	doc->SaveFile(filename);
	//doc->SaveFile("compact.xml", true);
	delete doc;
	
}