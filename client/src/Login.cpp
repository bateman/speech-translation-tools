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
#include "ClientTsFrm.h"
#include "AudioWizard.h"
#include <malloc.h>
#include "utility.h"
#include "tinyxml2.h"
#include "tinyxml2.cpp"
#include <iostream>
#include <fstream>

FILE*config;
char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLanguage[20];
char StringLoginService[20];
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
BEGIN_EVENT_TABLE(Login, wxDialog)
////Manual Code Start
////Manual Code End

EVT_CLOSE(Login::OnClose)
EVT_BUTTON(ID_WXBUTTON1, Login::btnloginClick)
EVT_COMBOBOX(ID_WXCOMBOBOX1, Login::cmblang_SelectionChange)
END_EVENT_TABLE()
////Event Table End

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	// Connect Events
	cmblang->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblang_SelectionChange), NULL, this);
}

Login::~Login()
{
	// Disconnect Events
	cmblang->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblang_SelectionChange), NULL, this);
} 

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

	wxArrayString arrayStringFor_cmblang;
	arrayStringFor_cmblang.Add(_("English"));
	arrayStringFor_cmblang.Add(_("Italian"));
	arrayStringFor_cmblang.Add(_("Portuguese"));
	cmblang = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(248, 128), wxSize(145, 28), arrayStringFor_cmblang, 0, wxDefaultValidator, _("cmblang"));

	lblanguage = new wxStaticText(this, ID_WXSTATICTEXT3, _("Language:"), wxPoint(32, 136), wxDefaultSize, 0, _("lblanguage"));

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
        cmblang->SetSelection(cmbelement);
        
        fscanf(config,"%s",&StringLoginLanguage);
        cmblang->SetValue(StringLoginLanguage);
        
        fscanf(config,"%s",&StringLoginService);
        if(StringLoginService=="google")
        {
            radgoogle->SetValue(true);
            radbing->SetValue(false);
        }
        if(StringLoginService=="bing")
        {
            radgoogle->SetValue(false);
            radbing->SetValue(true);
        }
        
        fclose(config);
    }
    cmblang->SetSelection(cmbelement);

	writeAndReadLabels();
	
}

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void Login::writeAndReadLabels(){
	char lang[20] = { "" };

	strcpy(lang, (char*)cmblang->GetStringSelection().mb_str().data());

	char filename[20] = { "" };
	strcpy(filename, "lang\\");
	strcat(filename, strcat(lang, ".xml"));


	lblserver->SetLabel("");
	lblanguage->SetLabel("");
	lbltrad->SetLabel("");
	btnlogin->SetLabel("");

	readXmlLangDoc(filename);
}

void Login::cmblang_SelectionChange(wxCommandEvent& event)
{
	writeAndReadLabels();
}

/*
 * btnloginClick
 */
void Login::btnloginClick(wxCommandEvent& event)
{
	// insert your code here
	//wxMessageBox(ip);

    strncpy(StringLoginServer, (const char*)txtserver->GetValue().mb_str(wxConvUTF8), 20);
    strncpy(StringLoginNick, (const char*)txtnick->GetValue().mb_str(wxConvUTF8), 50);
    strncpy(StringLoginLanguage, (const char*)cmblang->GetStringSelection().mb_str(wxConvUTF8), 20);    
    
    char ip[100];
	hostname_to_ip(StringLoginServer , ip);
	
	
        config=fopen("..\\conf\\config.txt","w");
    	fprintf(config,"%s\n",ip);
    	fprintf(config,"%s\n",StringLoginNick);
    	fprintf(config,"%d\n",cmblang->GetSelection());
    	fprintf(config,"%s\n",StringLoginLanguage);
    	if(radgoogle->GetValue()==true) fprintf(config,"%s","google");
    	if(radbing->GetValue()==true)   fprintf(config,"%s","bing");
    	fflush(config);
    	fclose(config);
    
	ClientTsFrm* frame = new ClientTsFrm(NULL);
    frame->Show();
	this->Close();
}

void Login::writeXmlLangDoc(char* filename)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument(); 
	tinyxml2::XMLNode* element = doc->InsertEndChild(doc->NewElement("language"));
	tinyxml2::XMLElement* sub[14] = { doc->NewElement("lblNameHost"), doc->NewElement("lblLanguage"), doc->NewElement("lblService"),
		doc->NewElement("btnlogin"), doc->NewElement("lblmessage"), doc->NewElement("btnsend"), doc->NewElement("lblexit"),
		doc->NewElement("lbloptions"), doc->NewElement("lblsound"), doc->NewElement("lblenable"), doc->NewElement("lbldisable"),
		doc->NewElement("lblmicrophone"), doc->NewElement("lblmin"), doc->NewElement("lblmax") }; 
	
	if (strcmp((char*)(cmblang->GetStringSelection().mb_str().data()),"English") == 0){
		sub[0]->InsertFirstChild(doc->NewText("Name/Host Server:"));
		element->InsertEndChild(sub[0]);
		sub[1]->InsertFirstChild(doc->NewText("Language:"));
		element->InsertEndChild(sub[1]);
		sub[2]->InsertFirstChild(doc->NewText("Service:"));
		element->InsertEndChild(sub[2]);
		sub[3]->InsertFirstChild(doc->NewText("Confirm"));
		element->InsertEndChild(sub[3]);
		sub[4]->InsertFirstChild(doc->NewText("Message"));
		element->InsertEndChild(sub[4]);
		sub[5]->InsertFirstChild(doc->NewText("Send"));
		element->InsertEndChild(sub[5]);
		sub[6]->InsertFirstChild(doc->NewText("Exit"));
		element->InsertEndChild(sub[6]);
		sub[7]->InsertFirstChild(doc->NewText("Options"));
		element->InsertEndChild(sub[7]);
		sub[8]->InsertFirstChild(doc->NewText("Audio"));
		element->InsertEndChild(sub[8]);
		sub[9]->InsertFirstChild(doc->NewText("Enable"));
		element->InsertEndChild(sub[9]);
		sub[10]->InsertFirstChild(doc->NewText("Disable"));
		element->InsertEndChild(sub[10]);
		sub[11]->InsertFirstChild(doc->NewText("Adjust the sensitivity of the microphone"));
		element->InsertEndChild(sub[11]);
		sub[12]->InsertFirstChild(doc->NewText("the lowest captures all the sounds from the mic without filters"));
		element->InsertEndChild(sub[12]);
		sub[13]->InsertFirstChild(doc->NewText("while the maximum value does not capture any sound"));
		element->InsertEndChild(sub[13]);
	}
	else if (strcmp((char*)(cmblang->GetStringSelection().mb_str().data()), "Italian") == 0){
		sub[0]->InsertFirstChild(doc->NewText("Nome/Host Server:"));
		element->InsertEndChild(sub[0]);
		sub[1]->InsertFirstChild(doc->NewText("Linguaggio:"));
		element->InsertEndChild(sub[1]);
		sub[2]->InsertFirstChild(doc->NewText("Servizio:"));
		element->InsertEndChild(sub[2]);
		sub[3]->InsertFirstChild(doc->NewText("Conferma"));
		element->InsertEndChild(sub[3]);
		sub[4]->InsertFirstChild(doc->NewText("Messaggio"));
		element->InsertEndChild(sub[4]);
		sub[5]->InsertFirstChild(doc->NewText("Invia"));
		element->InsertEndChild(sub[5]);
		sub[6]->InsertFirstChild(doc->NewText("Esci"));
		element->InsertEndChild(sub[6]);
		sub[7]->InsertFirstChild(doc->NewText("Opzioni"));
		element->InsertEndChild(sub[7]);
		sub[8]->InsertFirstChild(doc->NewText("Audio"));
		element->InsertEndChild(sub[8]);
		sub[9]->InsertFirstChild(doc->NewText("Abilita"));
		element->InsertEndChild(sub[9]);
		sub[10]->InsertFirstChild(doc->NewText("Disabilita"));
		element->InsertEndChild(sub[10]);
		sub[11]->InsertFirstChild(doc->NewText("Regola la sensibilità del microfono"));
		element->InsertEndChild(sub[11]);
		sub[12]->InsertFirstChild(doc->NewText("Il valore minimo cattura tutti i suoni dal microfono senza filtri"));
		element->InsertEndChild(sub[12]);
		sub[13]->InsertFirstChild(doc->NewText("Mentre il valore massimo non cattura nessun suono"));
		element->InsertEndChild(sub[13]);
	}
	else if (strcmp((char*)(cmblang->GetStringSelection().mb_str().data()), "Portuguese") == 0){
		sub[0]->InsertFirstChild(doc->NewText("Nome/Host Server:"));
		element->InsertEndChild(sub[0]);
		sub[1]->InsertFirstChild(doc->NewText("Linguagem:"));
		element->InsertEndChild(sub[1]);
		sub[2]->InsertFirstChild(doc->NewText("Serviço:"));
		element->InsertEndChild(sub[2]);
		sub[3]->InsertFirstChild(doc->NewText("Confirmação"));
		element->InsertEndChild(sub[3]);
		sub[4]->InsertFirstChild(doc->NewText("Mensagens"));
		element->InsertEndChild(sub[4]);
		sub[5]->InsertFirstChild(doc->NewText("Enviar"));
		element->InsertEndChild(sub[5]);
		sub[6]->InsertFirstChild(doc->NewText("Parar"));
		element->InsertEndChild(sub[6]);
		sub[7]->InsertFirstChild(doc->NewText("Opções"));
		element->InsertEndChild(sub[7]);
		sub[8]->InsertFirstChild(doc->NewText("Àudio"));
		element->InsertEndChild(sub[8]);
		sub[9]->InsertFirstChild(doc->NewText("Habilitar"));
		element->InsertEndChild(sub[9]);
		sub[10]->InsertFirstChild(doc->NewText("Desabilitar"));
		element->InsertEndChild(sub[10]);
		sub[11]->InsertFirstChild(doc->NewText("Ajustar a sensibilidade do microfone"));
		element->InsertEndChild(sub[11]);
		sub[12]->InsertFirstChild(doc->NewText("O menor captura todos os sons do microfone sem filtros"));
		element->InsertEndChild(sub[12]);
		sub[13]->InsertFirstChild(doc->NewText("Enquanto o valor máximo não capturar qualquer som"));
		element->InsertEndChild(sub[13]);
	}
	

	doc->Print(); 

	{
		tinyxml2::XMLPrinter streamer;
		doc->Print(&streamer);
		printf("%s", streamer.CStr());
	}
		{
			tinyxml2::XMLPrinter streamer(0, true);
			doc->Print(&streamer);
		}
	doc->SaveFile(filename);
	
	delete doc;

}

void Login::readXmlLangDoc(char* filename){

	tinyxml2::XMLDocument xmlDoc;//create document to read
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename);		//load file xml
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();			
	tinyxml2::XMLElement * pElement;

	tinyxml2::XMLNode *firstChild = pRoot->FirstChild();
	tinyxml2::XMLNode *pBrother = firstChild;

	do
	{
		const char* label = pBrother->Value();
		tinyxml2::XMLNode *child = pBrother->FirstChild();

		const char* valChild = child->Value();

		if (strcmp(label, "lblNameHost") == 0) lblserver->SetLabel(valChild);
		if (strcmp(label, "lblLanguage") == 0) lblanguage->SetLabel(valChild);
		if (strcmp(label, "lblService") == 0) lbltrad->SetLabel(valChild);
		if (strcmp(label, "btnlogin") == 0) btnlogin->SetLabel(valChild);

		pBrother = pBrother->NextSibling();

	} while (pBrother != NULL);

	return;

}
