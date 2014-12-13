///-----------------------------------------------------------------
///
/// @file      Login.h
/// @author    Utente
/// Created:   08/10/2014 16:43:03
/// @section   DESCRIPTION
///            Login class declaration
///
///------------------------------------------------------------------

#ifndef __LOGIN_H__
#define __LOGIN_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/radiobut.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
////Header Include End

////Dialog Style Start
#undef Login_STYLE
#define Login_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class Login : public wxDialog
{		
	public:
		Login(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Login_STYLE);
		virtual ~Login();
		void txtserverUpdated(wxCommandEvent& event);
		void cmb_lingua_SelectionChange(wxCommandEvent& event);
		void cmdConfirmClick(wxCommandEvent& event);
		
	protected:
		wxStaticBitmap* m_bitmap1;
		wxStaticText* lblServer;
		wxTextCtrl* txtServer;
		wxStaticText* lblNickName;
		wxTextCtrl* txtNickname;
		wxStaticText* lbllanguage;
		wxComboBox* cmblingua;
		wxStaticText* lblService;
		wxRadioButton* optGoogle;
		wxRadioButton* optBing;
		wxButton* cmdConfirm;		
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void ReadConfig();
		void changeLanguage();
};

#endif
