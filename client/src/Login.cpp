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
BEGIN_EVENT_TABLE(Login, wxDialog)
////Manual Code Start
////Manual Code End

EVT_CLOSE(Login::OnClose)
EVT_BUTTON(ID_WXBUTTON1, Login::btnloginClick)
EVT_COMBOBOX(ID_WXCOMBOBOX1, Login::cmblingua_SelectionChange)
END_EVENT_TABLE()
////Event Table End

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	// Connect Events
	cmblingua->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
}

Login::~Login()
{
	// Disconnect Events
	cmblingua->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
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

	writeAndReadLabels();
	
}

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void Login::writeAndReadLabels(){
	char lang[20] = { "" };

	strcpy(lang, (char*)cmblingua->GetStringSelection().mb_str().data());

	char filename[20] = { "" };
	strcpy(filename, strcat(lang, ".xml"));

	//ifstream file (filename, ios::in);
	//if (file.is_open()){
	//writeXmlLangDoc(filename);
	//}

	lblserver->SetLabel("");
	lbllingua->SetLabel("");
	lbltrad->SetLabel("");
	btnlogin->SetLabel("");

	readXmlLangDoc(filename);
}

void Login::cmblingua_SelectionChange(wxCommandEvent& event)
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
    strncpy(StringLoginLingua, (const char*)cmblingua->GetStringSelection().mb_str(wxConvUTF8), 20);    
    
    char ip[100];
	hostname_to_ip(StringLoginServer , ip);
	
	
        config=fopen("..\\conf\\config.txt","w");
    	fprintf(config,"%s\n",ip);
    	fprintf(config,"%s\n",StringLoginNick);
    	fprintf(config,"%d\n",cmblingua->GetSelection());
    	fprintf(config,"%s\n",StringLoginLingua);
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
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument(); //creazione documento
	tinyxml2::XMLNode* element = doc->InsertEndChild(doc->NewElement("language")); //creazione nodo radice //
	tinyxml2::XMLElement* sub[14] = { doc->NewElement("lblNameHost"), doc->NewElement("lblLanguage"), doc->NewElement("lblService"),
		doc->NewElement("btnlogin"), doc->NewElement("lblmessage"), doc->NewElement("btnsend"), doc->NewElement("lblexit"),
		doc->NewElement("lbloptions"), doc->NewElement("lblsound"), doc->NewElement("lblenable"), doc->NewElement("lbldisable"),
		doc->NewElement("lblmicrophone"), doc->NewElement("lblmin"), doc->NewElement("lblmax") }; //creazione figli con inserimento tag

	//assegnazione dei valori nei tag
	if (strcmp((char*)(cmblingua->GetStringSelection().mb_str().data()),"English") == 0){
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
	else if (strcmp((char*)(cmblingua->GetStringSelection().mb_str().data()), "Italian") == 0){
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
	else if (strcmp((char*)(cmblingua->GetStringSelection().mb_str().data()), "Portuguese") == 0){
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
	

	doc->Print(); //stampa nella console

	//int value = 10;
	//int result = doc->FirstChildElement()->LastChildElement()->QueryIntAttribute("attrib", &value);

	//stampa sul file
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
	//doc->SaveFile("compact.xml", true);
	delete doc;

}

void Login::readXmlLangDoc(char* filename){

	tinyxml2::XMLDocument xmlDoc;//creazione document per la lettura
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename);		//caricamento del file xml
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();			//lettura del padre language
	tinyxml2::XMLElement * pElement;

	tinyxml2::XMLNode *primoFiglio = pRoot->FirstChild();
	tinyxml2::XMLNode *pFratello = primoFiglio;

	do
	{
		const char* etichetta = pFratello->Value();
		tinyxml2::XMLNode *figlio = pFratello->FirstChild();

		const char* valFiglio = figlio->Value();

		if (strcmp(etichetta, "lblNameHost") == 0) lblserver->SetLabel(valFiglio);
		if (strcmp(etichetta, "lblLanguage") == 0) lbllingua->SetLabel(valFiglio);
		if (strcmp(etichetta, "lblService") == 0) lbltrad->SetLabel(valFiglio);
		if (strcmp(etichetta, "btnlogin") == 0) btnlogin->SetLabel(valFiglio);

		pFratello = pFratello->NextSibling();

	} while (pFratello != NULL);

	return;

}
