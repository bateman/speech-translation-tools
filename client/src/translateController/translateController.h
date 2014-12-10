#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

class TranslateController
{
	public:
		static void InitLanguageVariable(char* lang);
		static wxString TraduzioneLabel(char* language);
		static void writeXmlLangDoc(char* filename);
		static void readXmlLangDoc(char* filename);
		
		
		
		
};