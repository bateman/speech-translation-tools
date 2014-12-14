///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "frmSaveDialog.h"
#include "../../res/ico_save.xpm"


///////////////////////////////////////////////////////////////////////////

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
	(*opt_saveDialog_NO).SetValue(true);

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

	fpk__saveDialog_Browse = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
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
	cmd_saveDialog_Confirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmSaveDialog::cmdConfirm_Click), NULL, this);
}

FrmSaveDialog::~FrmSaveDialog()
{
	// Disconnect Events
	opt_saveDialog_NO->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(FrmSaveDialog::optNoSelect), NULL, this);
	opt_saveDialog_YES->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(FrmSaveDialog::optYesSelect), NULL, this);
	cmd_saveDialog_Confirm->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmSaveDialog::cmdConfirm_Click), NULL, this);

}

void FrmSaveDialog::optNoSelect(wxCommandEvent& event) 
{ 
	event.Skip(); 
}
void FrmSaveDialog::optYesSelect(wxCommandEvent& event) 
{ 
	event.Skip(); 
}
void FrmSaveDialog::cmdConfirm_Click(wxCommandEvent& event) 
{ 
	if ( (*FrmSaveDialog::opt_saveDialog_NO).GetValue() )
	{
		wxMessageBox("Non salvo");
		Close();
	}
	else
	{
		wxMessageBox("Salvo");
	}
	Close();
}
