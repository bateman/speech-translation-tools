#include <string>

using namespace std;

//#ifndef WX_PRECOMP
//	#include <wx/wx.h>
//	#include <wx/dialog.h>
//#else
//	#include <wx/wxprec.h>
//#endif
//
class TranslateController
{
	public:
		static void TranslateController::InitController(string lan);	
		static void TranslateController::writeXmlLangDoc(string lan, string fileName);
		static void TranslateController::readXmlLangDoc(string filename);
		static void TranslateController::writeAndReadLabels();
};