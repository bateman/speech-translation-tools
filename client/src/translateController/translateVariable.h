#ifndef _TRANSLATEVARIABLES_H_
#define _TRANSLATEVARIABLES_H_

//#include "src/GlobalVariables.h"
#include <string>

using namespace std;

typedef struct Labels{
	string nameHostServer = "";
	string language = "";
	string service = "";
	string login = "";
	string gridMessage = "";
	string send = "";
	string exit = "";
	string options = "";
	string sound = "";
	string enable = "";
	string disable = "";
	string microphone = "";
	string min = "";
	string max = "";

};

extern Labels labels;
static wxString StringTranslate = "";
static char CURRENT_LANG[20] = { "English" };

#endif // _TRANSLATEVARIABLES_H_

