///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "frmSaveDialog.h"
#include "../../res/ico_save.xpm"
#include "../tinyxml2.h"
#include<time.h>
#include "../GlobalVariables.h"
#include <wx/checkbox.h>
#include <wx/filepicker.h>

///////////////////////////////////////////////////////////////////////////

void saveFileCSV();//definition of method save csv
void saveFileTXT();//definition of method save txt
char path[1000];//definition of path
FrmSaveDialog::FrmSaveDialog(wxWindow* parent, wxWindowID id, const wxString &title, 
	const wxPoint& position, const wxSize& size, long style) : wxDialog(parent, id, title, position, size, style)
{
	CenterOnScreen();
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);


	bSizer2->Add(0, 0, 1, wxEXPAND, 5);

	lbl_saveDialog_Title = new wxStaticText(this, wxID_ANY, wxT("Do you want save this chat session?"), wxDefaultPosition, wxDefaultSize, 0);
	lbl_saveDialog_Title->Wrap(-1);
	lbl_saveDialog_Title->SetFont(wxFont(12, 70, 90, 90, false, wxEmptyString));

	bSizer2->Add(lbl_saveDialog_Title, 0, wxALIGN_CENTER | wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);


	bSizer2->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(ico_save), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer2->Add(m_bitmap2, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	opt_saveDialog_NO = new wxRadioButton(this, wxID_ANY, wxT("NO, i do not want to save them."), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(opt_saveDialog_NO, 0, wxALL, 5);

	opt_saveDialog_YES = new wxRadioButton(this, wxID_ANY, wxT("YES, i want to save them..."), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(opt_saveDialog_YES, 0, wxALL, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);


	bSizer7->Add(20, 1, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	chk__saveDialog_CSV = new wxCheckBox(this, wxID_ANY, wxT("Save in CSV format"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(chk__saveDialog_CSV, 0, wxALL, 5);

	chk__saveDialog_TXT = new wxCheckBox(this, wxID_ANY, wxT("Save in TXT format"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(chk__saveDialog_TXT, 0, wxALL, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxHORIZONTAL);
	
	lbl__saveDialog_saveIn = new wxStaticText(this, wxID_ANY, wxT("Save in: "), wxDefaultPosition, wxDefaultSize, 0);
	lbl__saveDialog_saveIn->Wrap(-1);
	bSizer9->Add(lbl__saveDialog_saveIn, 0, wxALIGN_CENTER | wxALL, 5);

	fpk__saveDialog_Browse =new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxT(""), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE, wxDefaultValidator, wxDirPickerCtrlNameStr);
	bSizer9->Add(fpk__saveDialog_Browse, 1, wxALL, 5);
	
	bSizer8->Add(bSizer9, 1, wxEXPAND, 5);


	bSizer7->Add(bSizer8, 1, wxEXPAND, 5);


	bSizer6->Add(bSizer7, 1, wxEXPAND, 5);


	bSizer5->Add(bSizer6, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer5, 1, wxEXPAND, 5);


	bSizer1->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);

	cmd_saveDialog_Confirm = new wxButton(this, wxID_ANY, wxT("Confirm"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(cmd_saveDialog_Confirm, 0, wxALL, 5);


	bSizer1->Add(bSizer4, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	// Connect Events
	opt_saveDialog_NO->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(FrmSaveDialog::optNoSelect), NULL, this);
	opt_saveDialog_YES->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(FrmSaveDialog::optYesSelect), NULL, this);
	chk__saveDialog_CSV->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveDialog::opt__saveDialog_CSV), NULL, this);
	chk__saveDialog_TXT->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveDialog::opt__saveDialog_TXT), NULL, this);
	cmd_saveDialog_Confirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmSaveDialog::cmdConfirm_Click), NULL, this);
	fpk__saveDialog_Browse->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(FrmSaveDialog::cmdbrowse), NULL, this); 
	//read label from xml
	char filename[20];
	FILE* file;

	char temp[20], language[20];

	if (file = fopen("conf\\config.txt", "r"))
	{

		fscanf(file, "%s", &temp);
		fscanf(file, "%s", &temp);
		fscanf(file, "%s", &temp);
		fscanf(file, "%s", &language);
		fclose(file);
	}


	strcpy(filename, "lang\\");
	strcat(language, ".xml");
	strcat(filename, language);
	FrmSaveDialog::readXmlLangDoc(filename);
}

FrmSaveDialog::~FrmSaveDialog()
{
	// Disconnect Events
	opt_saveDialog_NO->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(FrmSaveDialog::optNoSelect), NULL, this);
	opt_saveDialog_YES->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(FrmSaveDialog::optYesSelect), NULL, this);
	cmd_saveDialog_Confirm->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmSaveDialog::cmdConfirm_Click), NULL, this);
	chk__saveDialog_CSV->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveDialog::opt__saveDialog_CSV), NULL, this);
	chk__saveDialog_TXT->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveDialog::opt__saveDialog_TXT), NULL, this);
	fpk__saveDialog_Browse->Disconnect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxCommandEventHandler(FrmSaveDialog::cmdbrowse), NULL, this);
}

void FrmSaveDialog::optNoSelect(wxCommandEvent& event) 
{ 
	//if option No is selected
	chk__saveDialog_CSV->Disable();
	chk__saveDialog_TXT->Disable();
	fpk__saveDialog_Browse->Disable();
	cmd_saveDialog_Confirm->Enable();
	
}
void FrmSaveDialog::optYesSelect(wxCommandEvent& event) 
{ 
	//if option Yes is selected
	chk__saveDialog_CSV->Enable();
	chk__saveDialog_TXT->Enable();
	fpk__saveDialog_Browse->Disable();
	cmd_saveDialog_Confirm->Disable();
	if (fpk__saveDialog_Browse->GetPath().mb_str().length()!=0) cmd_saveDialog_Confirm->Enable();
}
void FrmSaveDialog::opt__saveDialog_CSV(wxCommandEvent& event){
	//if option save csv is selected
	if ((*FrmSaveDialog::chk__saveDialog_CSV).GetValue() || (*FrmSaveDialog::chk__saveDialog_TXT).GetValue())
	fpk__saveDialog_Browse->Enable();
	else
	fpk__saveDialog_Browse->Disable();
}
void FrmSaveDialog::opt__saveDialog_TXT(wxCommandEvent& event){
	//if option save txt is selected
	if ((*FrmSaveDialog::chk__saveDialog_CSV).GetValue() || (*FrmSaveDialog::chk__saveDialog_TXT).GetValue())
		fpk__saveDialog_Browse->Enable();
	else
		fpk__saveDialog_Browse->Disable();
}

void FrmSaveDialog::cmdbrowse(wxCommandEvent& event){
	//browse enable if the path is setted
	if ((*FrmSaveDialog::chk__saveDialog_CSV).GetValue() || (*FrmSaveDialog::chk__saveDialog_TXT).GetValue())
		cmd_saveDialog_Confirm->Enable();
	else
		cmd_saveDialog_Confirm->Disable();

}
void FrmSaveDialog::cmdConfirm_Click(wxCommandEvent& event) 
{ 
	//if confirm is pressed
	if ( (*FrmSaveDialog::opt_saveDialog_NO).GetValue() )
	{
		Close();
	}
	else
	{
		strcpy(path, fpk__saveDialog_Browse->GetPath().mb_str());
		if ((*FrmSaveDialog::chk__saveDialog_CSV).GetValue()) saveFileCSV();
		if ((*FrmSaveDialog::chk__saveDialog_TXT).GetValue()) saveFileTXT();

	}
	Close();
}

void FrmSaveDialog::readXmlLangDoc(char* filename){
	//read xml method
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename);
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
	tinyxml2::XMLElement * pElement;

	tinyxml2::XMLNode *firstChild = pRoot->FirstChild();
	tinyxml2::XMLNode *pBrother = firstChild;

	do
	{
		const char* label = pBrother->Value();
		tinyxml2::XMLNode *child = pBrother->FirstChild();

		const char* valChild = child->Value();

		if (strcmp(label, "lblsavemessage") == 0) lbl_saveDialog_Title->SetLabel(valChild);
		if (strcmp(label, "lblnomessage") == 0) opt_saveDialog_NO->SetLabelText(valChild);
		if (strcmp(label, "lblyesmessage") == 0) opt_saveDialog_YES->SetLabelText(valChild);
		if (strcmp(label, "lblsavecsv") == 0) chk__saveDialog_CSV->SetLabelText(valChild);
		if (strcmp(label, "lblsavetxt") == 0)  chk__saveDialog_TXT->SetLabelText(valChild);
		if (strcmp(label, "lblsavein") == 0) lbl__saveDialog_saveIn->SetLabelText(valChild);
		if (strcmp(label, "btnbrowse") == 0) fpk__saveDialog_Browse->SetLabelText(valChild); 
		if (strcmp(label, "btnlogin") == 0) cmd_saveDialog_Confirm->SetLabelText(valChild);
		

		pBrother = pBrother->NextSibling();

	} while (pBrother != NULL);

	return;

}

void saveFileCSV()
{
	char filenamecsv[2000] = { "" };
	//saving current time
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char temp[100];
	strftime(temp, 100, "%d-%m-%Y_%H-%M-%S", timeinfo);
	puts(temp);
	strcpy(filenamecsv, path);
	strcat(filenamecsv, "\\chatLog");
	strcat(filenamecsv, temp);
	strcat(filenamecsv, ".csv");

	if (chatSessionLogCsv = fopen(filenamecsv, "w"))
	{
		int i;
		list<string>::iterator it;
		for (it = clientMessagesCsv.begin(); it != clientMessagesCsv.end(); it++)
		{
			string temp = *it;
			fprintf(chatSessionLogCsv, "%s", temp.c_str());
		}

		fclose(chatSessionLogCsv);
	}
}
void saveFileTXT(){

	char filename[2000] = { "" };
	//saving current time
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char temp[100];
	strftime(temp, 100, "%d-%m-%Y_%H-%M-%S", timeinfo);
	puts(temp);
	strcpy(filename, path);
	strcat(filename, "\\chatLog");
	strcat(filename, temp);
	strcat(filename, ".txt");

	if (chatSessionLog = fopen(filename, "w"))
	{
		int i;
		list<string>::iterator it;
		for (it = clientMessages.begin(); it != clientMessages.end(); it++)
		{
			string temp = *it;
			fprintf(chatSessionLog, "%s", temp.c_str());
			fprintf(chatSessionLog, "%s", "\n");
		}

		fclose(chatSessionLog);
	}
}