#include "FrmMailSending.h"

FrmMailSending::FrmMailSending(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	CenterOnScreen();

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);
	bSizer3->Add(0, 0, 1, wxEXPAND, 5);
	bSizer3->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(sendemail_xpm), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer3->Add(m_bitmap1, 0, wxALL, 5);

	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer(wxHORIZONTAL);

	lblTo = new wxStaticText(this, wxID_ANY, labels.mailTo.append(":"), wxDefaultPosition, wxSize(100, -1), 0);
	lblTo->Wrap(-1);
	bSizer31->Add(lblTo, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txtTo = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer31->Add(txtTo, 1, wxALL, 5);

	bSizer1->Add(bSizer31, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer(wxHORIZONTAL);

	lblSubject = new wxStaticText(this, wxID_ANY, labels.mailSubject.append(":"), wxDefaultPosition, wxSize(100, -1), 0);
	lblSubject->Wrap(-1);
	bSizer311->Add(lblSubject, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txtSubject = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer311->Add(txtSubject, 1, wxALL, 5);


	bSizer1->Add(bSizer311, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer313;
	bSizer313 = new wxBoxSizer(wxHORIZONTAL);

	lblText = new wxStaticText(this, wxID_ANY, labels.mailBody.append(":"), wxDefaultPosition, wxSize(100, -1), 0);
	lblText->Wrap(-1);
	bSizer313->Add(lblText, 0, wxALL, 5);

	txtText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE);
	bSizer313->Add(txtText, 1, wxALL, 5);


	bSizer1->Add(bSizer313, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer312;
	bSizer312 = new wxBoxSizer(wxHORIZONTAL);

	lblAttachment = new wxStaticText(this, wxID_ANY, labels.mailAttachment, wxDefaultPosition, wxSize(100, -1), 0);
	lblAttachment->Wrap(-1);
	bSizer312->Add(lblAttachment, 0, wxALIGN_CENTER | wxALL, 5);

	filePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, labels.fileSelect, wxT("*.txt;*.csv"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
	bSizer312->Add(filePicker, 1, wxALL, 5);


	bSizer1->Add(bSizer312, 1, wxEXPAND, 5);


	bSizer1->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer(wxHORIZONTAL);


	bSizer30->Add(0, 0, 1, wxEXPAND, 5);

	btnCancel = new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer30->Add(btnCancel, 0, wxALL, 5);

	btnSend = new wxButton(this, wxID_ANY, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer30->Add(btnSend, 0, wxALL, 5);


	bSizer1->Add(bSizer30, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	// Connect Events
	btnCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmMailSending::btnCancelMailClick), NULL, this);
	btnSend->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmMailSending::btnSendMailClick), NULL, this);

}

FrmMailSending::~FrmMailSending()
{
	//disconnect events
	btnCancel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmMailSending::btnCancelMailClick), NULL, this);
	btnSend->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmMailSending::btnSendMailClick), NULL, this);
}

void FrmMailSending::btnSendMailClick(wxCommandEvent& event)
{
	char* subject = (char*)malloc(strlen((const char*)txtSubject->GetValue().mb_str(wxConvUTF8)) + 1);
	char* to = (char*)malloc(strlen((const char*)txtTo->GetValue().mb_str(wxConvUTF8)) + 1);
	char* body = (char*)malloc(strlen((const char*)txtText->GetValue().mb_str(wxConvUTF8)) + 1);
	char* attachment = (char*)malloc(strlen((const char*)filePicker->GetPath().mb_str(wxConvUTF8)) + 1);

	strcpy(subject, (const char*)txtSubject->GetValue().mb_str(wxConvUTF8));
	strcpy(to, (const char*)txtTo->GetValue().mb_str(wxConvUTF8));
	strcpy(body, (const char*)txtText->GetValue().mb_str(wxConvUTF8));
	strcpy(attachment, (const char*)filePicker->GetPath().mb_str(wxConvUTF8));

	if (sendMail(subject, body, to, attachment) == true) {
		wxMessageBox(labels.mailSuccess);
		this->Close();
	}
	else
		wxMessageBox(labels.mailError);
}

void FrmMailSending::btnCancelMailClick(wxCommandEvent& event){
	this->Close();
}

bool FrmMailSending::sendMail(char* subject, char* body, char* to, char* attachment){

	bool success;

	CkMailMan mailman;

	//  Any string argument automatically begins the 30-day trial.

	success = mailman.UnlockComponent("30-day trial");
	if (success != true)
		return false;

	//  Set the SMTP server.
	mailman.put_SmtpHost("smtp.gmail.com");
	mailman.put_SmtpSsl(true);
	mailman.put_SmtpPort(465);

	// Set the SMTP login/password (if required)
	// sender data
	mailman.put_SmtpUsername("proguniversita@gmail.com");
	mailman.put_SmtpPassword("teamtranslate");

	success = mailman.VerifySmtpConnection();
	if (success != true)
		return false;

	success = mailman.VerifySmtpLogin();
	if (success != true)
		return false;

	//  Create a new email object
	CkEmail email;

	email.put_From("TeamTranslate <proguniversita@gmail.com>");
	email.put_Subject(subject);
	email.put_Body(body);
	email.addFileAttachment(attachment);

	// add all recipient (they must be separated by ;
	char * pch;
	pch = strtok(to, ";");
	while (pch != NULL)
	{
		email.AddTo("", pch);
		pch = strtok(NULL, ";");
	}

	success = mailman.SendEmail(email);
	if (success != true)
		return false;


	//  Call SendEmail to connect to the SMTP server and send.
	//  The connection (i.e. session) to the SMTP server remains
	//  open so that subsequent SendEmail calls may use the
	//  same connection.

	//  Some SMTP servers do not actually send the email until
	//  the connection is closed.  In these cases, it is necessary to
	//  call CloseSmtpConnection for the mail to be  sent.
	//  Most SMTP servers send the email immediately, and it is
	//  not required to close the connection.  We'll close it here
	//  for the example:
	success = mailman.CloseSmtpConnection();
	if (success != true)
		return false;

	return true;
}
