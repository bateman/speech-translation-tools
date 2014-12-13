#ifndef _TRANSLATEVARIABLES_H_
#define _TRANSLATEVARIABLES_H_

#include <string>

using namespace std;

typedef struct Labels{
	string nameHostServer = "";
	string language = "";
	string service = "";
	string cmdConfirm = "";
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
extern string StringTranslate;
extern char CURRENT_LANG[20];

#endif // _TRANSLATEVARIABLES_H_

