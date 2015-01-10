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

FILE*config;
char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLingua[20];
char StringLoginServizio[20];
int  cmbelement=0;
string user_locale;

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
END_EVENT_TABLE()
////Event Table End

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	//bool result = SplashScreen::GetSplashScreen("res/splash.jpg", wxBITMAP_TYPE_JPEG, 3000);


	this->nations = new NationList();
	this->nations->ReadFromFile("conf\\locales_code.txt");
	CreateGUIControls();
}

Login::~Login()
{
	free(this->nations);
} 

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

void Login::CreateGUIControls()
{
	////Widget Archive declarations and creation
	//char name[10];
	//strcpy(name, "log.zip");
	//wxFFileOutputStream *out = new wxFFileOutputStream(name);
	//wxZipOutputStream *zip = new wxZipOutputStream(out);
	//wxTextOutputStream txt(*zip);
	//wxString sep(wxFileName::GetPathSeparator());

	////Write on file
	//ofstream myfile("entry1.txt");
	//if (myfile.is_open())
	//{
	//	myfile << "This is a line.\n";
	//	myfile << "This is another line.\n";
	//	myfile.close();
	//}
	//else cout << "Unable to open file";
	//
	////Create a file txt in the Archive
	//if (filesize("entry1.txt") > 20){
	//	zip->PutNextEntry(wxT("entry1.txt"));

	//	string text;
	//	string line;
	//	ifstream myfile("entry1.txt");
	//	if (myfile.is_open())
	//	{
	//		while (getline(myfile, line))
	//		{
	//			text = text + line + "\n";
	//		}
	//		myfile.close();
	//	}
	//	else cout << "Unable to open file";

	//	//Write on file in Archive
	//	txt << text;
	//	zip->CloseEntry();
	//}

	//	//Create a file txt in the Archive
	//	if (filesize("entry1.txt") > 20){
	//		zip->PutNextEntry(wxT("entry1.txt"));

	//		string text;
	//		string line;
	//		ifstream myfile("entry1.txt");
	//		if (myfile.is_open())
	//		{
	//			while (getline(myfile, line))
	//			{
	//				text = text + line + "sdhfjkdhsjk" +"\n";
	//			}
	//			myfile.close();
	//		}
	//		else cout << "Unable to open file";

	//		//Write on file in Archive
	//		txt << text;
	//		zip->CloseEntry();
	//}
	//	zip->Close();
	//	free(out);
	//	free(zip);


	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	radbing = new wxRadioButton(this, ID_WXRADIOBUTTON2, _("Bing Translate"), wxPoint(32, 272), wxSize(161, 17), 0, wxDefaultValidator, _("radbing"));

	radgoogle = new wxRadioButton(this, ID_WXRADIOBUTTON1, _("Google Translate"), wxPoint(32, 240), wxSize(153, 17), 0, wxDefaultValidator, _("radgoogle"));

	lbltrad = new wxStaticText(this, ID_WXSTATICTEXT4, _("Service:"), wxPoint(32, 192), wxDefaultSize, 0, _("lbltrad"));

	wxArrayString arrayStringFor_cmblingua;
	cmblingua = new wxBitmapComboBox(this, ID_WXBITMAPCOMBOBOX1, _(""), wxPoint(248, 128), wxSize(145, 28), arrayStringFor_cmblingua, 0, wxDefaultValidator, _("cmblingua"));
	wxInitAllImageHandlers();

	for (int i = 0; i < this->nations->GetSize(); i++)
	{
		char language[30];
		char nation[30];
		char path[50];
		bool loaded;

		strcpy(language, this->nations->GetList()->at(i).GetLanguage());
		strcpy(nation, this->nations->GetList()->at(i).GetNation());

		wxBitmap bitmap = wxBitmap();
		strcpy(path, "res/");
		strcat(path, nation);
		strcat(path, ".png");
		loaded = bitmap.LoadFile(path, wxBITMAP_TYPE_PNG);

		if (!loaded)
			bitmap.LoadFile("res/Default.png", wxBITMAP_TYPE_PNG);

		cmblingua->Append(language, bitmap);
	}
	
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
	
	cmblingua->SetEditable(false);
	radbing->SetValue(true);

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

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * btnloginClick
 */
void Login::btnloginClick(wxCommandEvent& event)
{
	// insert your code here
	//wxMessageBox(ip);
	LoginWarnings *warn = new LoginWarnings();

    strncpy(StringLoginServer, (const char*)txtserver->GetValue().mb_str(wxConvUTF8), 20);
    strncpy(StringLoginNick, (const char*)txtnick->GetValue().mb_str(wxConvUTF8), 50);
    strncpy(StringLoginLingua, (const char*)cmblingua->GetStringSelection().mb_str(wxConvUTF8), 20);    

    char ip[100];
	hostname_to_ip(StringLoginServer , ip);

	if (strcmp(StringLoginServer, "") == 0)
		warn->SetHostnameEmpty(true);
	if (strcmp(StringLoginNick, "") == 0)
		warn->SetNicknameEmpty(true);
	
	

    config=fopen("..\\conf\\config.txt","w");
    fprintf(config,"%s\n",ip);
    fprintf(config,"%s\n",StringLoginNick);
    fprintf(config,"%d\n",cmblingua->GetSelection());
    fprintf(config,"%s\n",StringLoginLingua);
    if(radgoogle->GetValue()==true) fprintf(config,"%s","google");
    if(radbing->GetValue()==true)   fprintf(config,"%s","bing");
    fflush(config);
    fclose(config);

	ClientTsFrm* frame = new ClientTsFrm(warn, NULL);
//	frame->setUserLocal(user_locale);
    frame->Show();
	this->Close();
}
