/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================


// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "Login.h"
#include "ClientTsFrm.h"
#include "AudioWizard.h"
#include "string.h"
#include "GlobalVariables.h"
#include "translateController\translateVariable.h"
#include "crtdefs.h"
#include <wx/msgdlg.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// Variable
// ----------------------------------------------------------------------------

Labels labels;
string StringTranslate = "";
char CURRENT_LANG[20] = { "English" };
unsigned short PORT = 9987;
unsigned int curRow = 0;
unsigned int curCol = 0;
short flag = 0;
int VAD_VALUE = 1;
int index = -1;
char LANG_MSG_SRC[20] = { "" };
char MSG_SRC[50] = { "" };
char GOOGLE_API_KEY[50] = { "" };
char url[256] = { "" };
char MSG_PARSE[1024] = { "" };
char translate_jar[512] = { "" };
int cmbel = 0;

bool sound_flag = false;			//Flag to start/stop 
bool tts_flag = false;				//Flag to start/stop TextToSpeech 		
bool write_flag = false;			//Flag to recognize Typing
bool tasto_stt_flag = false;		//Flag to activate Automatic SpeechToText
bool finish_ctrl_flag = false;		//Flag to recognize CTRL press button
bool automatic_stt_flag = false;

wxString strGlobale = "";
wxString oldstrGlobale = "";
wxString strNick = "";
wxString strMessage = "";
//wxString StringTranslate = "";
//wxString StringSource = "";
string StringSourceLog = "";

wxString SourceLanguageLog = "";
wxString oldStringTranslate = "";
wxString StringOriginal = "";
wxString strSpeak = "";

DWORD myThreadID;
DWORD myThreadID2;
DWORD myThreadID3;
DWORD myThreadID4;

unsigned count_client;
struct user person[MAX];
time_t rawtime;
struct tm * timeinfo;
MESSAGE diary[1024];
COLORE colors[10];
FILE* chatSessionLog;				//Log File for chat recording at the end of a chat session
FILE* chatSessionLogCsv;
wxGrid *gridptr;

list<string> clientMessages;		
list<string> clientMessagesCsv;
string logmessagecsv;
string logmessage;

char NICK[50];
char SERVER_ADDRESS[20];
char SERVICE[20];

ISoundEngine* engine;
IAudioRecorder* recorder;

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	try
	{
		// call the base class initialization method, currently it only parses a
		// few common command-line options but it could be do more in the future
		if (!wxApp::OnInit())
			return false;
		Login * dialog = new Login(NULL);
		SetTopWindow(dialog);
		//frame->Show();
		dialog->Show();
		/*AudioWizard* frame = new AudioWizard(NULL);
		frame->Show();*/
		return true;
		// create the main application window
		//MyFrame *frame = new MyFrame("Minimal wxWidgets App");

		// and show it (the frames, unlike simple controls, are not shown when
		// created initially)
		//frame->Show(true);

		// success: wxApp::OnRun() will be called which will enter the main message
		// loop and the application will run. If we returned false here, the
		// application would exit immediately.
		return true;
	}
	catch (const std::exception &e)
	{
		wxMessageBox( e.what() );
	}
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About...\tF1", "Show about dialog");

    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
#endif // wxUSE_STATUSBAR
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}
