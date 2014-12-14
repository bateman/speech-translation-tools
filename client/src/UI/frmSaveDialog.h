///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class FrmSaveDialog
///////////////////////////////////////////////////////////////////////////////
class FrmSaveDialog : public wxDialog
{
private:

protected:
	wxStaticText* lbl_saveDialog_Title;
	wxStaticBitmap* m_bitmap2;
	wxRadioButton* opt_saveDialog_NO;
	wxRadioButton* opt_saveDialog_YES;
	wxCheckBox* chk__saveDialog_CSV;
	wxCheckBox* chk__saveDialog_TXT;
	wxStaticText* lbl__saveDialog_saveIn;
	wxFilePickerCtrl* fpk__saveDialog_Browse;
	wxButton* cmd_saveDialog_Confirm;

	// Virtual event handlers, overide them in your derived class
	void optNoSelect(wxCommandEvent& event);
	void optYesSelect(wxCommandEvent& event);
	void cmdConfirm_Click(wxCommandEvent& event);


public:

	FrmSaveDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("Save session chat"), 
				  const wxPoint& pos = wxPoint(5, 5), const wxSize& size = wxSize(437, 300), 
				  long style = wxCAPTION | wxSYSTEM_MENU | wxSTAY_ON_TOP);
	~FrmSaveDialog();

};

#endif //__NONAME_H__
