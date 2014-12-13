#include "translateController.h"
#include "translateVariable.h"
#include <string>
#include <fstream>
#include "../tinyxml2.h"

using namespace std;

void TranslateController::InitController(string lan)
{
	//Check if xml exists
	string fileName = "lang\\" +  lan + ".xml";
	ifstream file(fileName);
	if ( file.good() ) {				//Nothing
		file.close();
	}
	else {
		writeXmlLangDoc(lan, fileName);	//Create file XML
		file.close();
	}
	readXmlLangDoc(fileName);	//read XML and set labels variable
}

void TranslateController::writeXmlLangDoc(string lan , string fileName)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLNode* element = doc->InsertEndChild(doc->NewElement("language"));
	tinyxml2::XMLElement* sub[14] = 
	{ 
		doc->NewElement("lblNameHost"), doc->NewElement("lblLanguage"), doc->NewElement("lblService"),
		doc->NewElement("btnlogin"), doc->NewElement("lblmessage"), doc->NewElement("btnsend"), doc->NewElement("lblexit"),
		doc->NewElement("lbloptions"), doc->NewElement("lblsound"), doc->NewElement("lblenable"), doc->NewElement("lbldisable"),
		doc->NewElement("lblmicrophone"), doc->NewElement("lblmin"), doc->NewElement("lblmax") 
	};

	if ( lan == "English" ){
		sub[0]->InsertFirstChild(doc->NewText("Name/Host Server:"));
		element->InsertEndChild(sub[0]);
		sub[1]->InsertFirstChild(doc->NewText("Language:"));
		element->InsertEndChild(sub[1]);
		sub[2]->InsertFirstChild(doc->NewText("Service:"));
		element->InsertEndChild(sub[2]);
		sub[3]->InsertFirstChild(doc->NewText("Confirm"));
		element->InsertEndChild(sub[3]);
		sub[4]->InsertFirstChild(doc->NewText("Message"));
		element->InsertEndChild(sub[4]);
		sub[5]->InsertFirstChild(doc->NewText("Send"));
		element->InsertEndChild(sub[5]);
		sub[6]->InsertFirstChild(doc->NewText("Exit"));
		element->InsertEndChild(sub[6]);
		sub[7]->InsertFirstChild(doc->NewText("Options"));
		element->InsertEndChild(sub[7]);
		sub[8]->InsertFirstChild(doc->NewText("Audio"));
		element->InsertEndChild(sub[8]);
		sub[9]->InsertFirstChild(doc->NewText("Enable"));
		element->InsertEndChild(sub[9]);
		sub[10]->InsertFirstChild(doc->NewText("Disable"));
		element->InsertEndChild(sub[10]);
		sub[11]->InsertFirstChild(doc->NewText("Adjust the sensitivity of the microphone"));
		element->InsertEndChild(sub[11]);
		sub[12]->InsertFirstChild(doc->NewText("the lowest captures all the sounds from the mic without filters"));
		element->InsertEndChild(sub[12]);
		sub[13]->InsertFirstChild(doc->NewText("while the maximum value does not capture any sound"));
		element->InsertEndChild(sub[13]);
	}
	else if (strcmp( lan.c_str() , "Italian") == 0){
		sub[0]->InsertFirstChild(doc->NewText("Nome/Host Server:"));
		element->InsertEndChild(sub[0]);
		sub[1]->InsertFirstChild(doc->NewText("Linguaggio:"));
		element->InsertEndChild(sub[1]);
		sub[2]->InsertFirstChild(doc->NewText("Servizio:"));
		element->InsertEndChild(sub[2]);
		sub[3]->InsertFirstChild(doc->NewText("Conferma"));
		element->InsertEndChild(sub[3]);
		sub[4]->InsertFirstChild(doc->NewText("Messaggio"));
		element->InsertEndChild(sub[4]);
		sub[5]->InsertFirstChild(doc->NewText("Invia"));
		element->InsertEndChild(sub[5]);
		sub[6]->InsertFirstChild(doc->NewText("Esci"));
		element->InsertEndChild(sub[6]);
		sub[7]->InsertFirstChild(doc->NewText("Opzioni"));
		element->InsertEndChild(sub[7]);
		sub[8]->InsertFirstChild(doc->NewText("Audio"));
		element->InsertEndChild(sub[8]);
		sub[9]->InsertFirstChild(doc->NewText("Abilita"));
		element->InsertEndChild(sub[9]);
		sub[10]->InsertFirstChild(doc->NewText("Disabilita"));
		element->InsertEndChild(sub[10]);
		sub[11]->InsertFirstChild(doc->NewText("Regola la sensibilità del microfono"));
		element->InsertEndChild(sub[11]);
		sub[12]->InsertFirstChild(doc->NewText("Il valore minimo cattura tutti i suoni dal microfono senza filtri"));
		element->InsertEndChild(sub[12]);
		sub[13]->InsertFirstChild(doc->NewText("Mentre il valore massimo non cattura nessun suono"));
		element->InsertEndChild(sub[13]);
	}
	else if (strcmp( lan.c_str() , "Portuguese") == 0){
		sub[0]->InsertFirstChild(doc->NewText("Nome/Host Server:"));
		element->InsertEndChild(sub[0]);
		sub[1]->InsertFirstChild(doc->NewText("Linguagem:"));
		element->InsertEndChild(sub[1]);
		sub[2]->InsertFirstChild(doc->NewText("Serviço:"));
		element->InsertEndChild(sub[2]);
		sub[3]->InsertFirstChild(doc->NewText("Confirmação"));
		element->InsertEndChild(sub[3]);
		sub[4]->InsertFirstChild(doc->NewText("Mensagens"));
		element->InsertEndChild(sub[4]);
		sub[5]->InsertFirstChild(doc->NewText("Enviar"));
		element->InsertEndChild(sub[5]);
		sub[6]->InsertFirstChild(doc->NewText("Parar"));
		element->InsertEndChild(sub[6]);
		sub[7]->InsertFirstChild(doc->NewText("Opções"));
		element->InsertEndChild(sub[7]);
		sub[8]->InsertFirstChild(doc->NewText("Àudio"));
		element->InsertEndChild(sub[8]);
		sub[9]->InsertFirstChild(doc->NewText("Habilitar"));
		element->InsertEndChild(sub[9]);
		sub[10]->InsertFirstChild(doc->NewText("Desabilitar"));
		element->InsertEndChild(sub[10]);
		sub[11]->InsertFirstChild(doc->NewText("Ajustar a sensibilidade do microfone"));
		element->InsertEndChild(sub[11]);
		sub[12]->InsertFirstChild(doc->NewText("O menor captura todos os sons do microfone sem filtros"));
		element->InsertEndChild(sub[12]);
		sub[13]->InsertFirstChild(doc->NewText("Enquanto o valor máximo não capturar qualquer som"));
		element->InsertEndChild(sub[13]);
	}

	doc->Print();
	{
		tinyxml2::XMLPrinter streamer;
		doc->Print(&streamer);
		printf("%s", streamer.CStr());
	}
		{
			tinyxml2::XMLPrinter streamer(0, true);
			doc->Print(&streamer);
		}
		doc->SaveFile( fileName.c_str() );

		delete doc;

}

void TranslateController::readXmlLangDoc(string filename){

	tinyxml2::XMLDocument xmlDoc;//create document to read
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename.c_str());		//load file xml
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
	tinyxml2::XMLElement * pElement;

	tinyxml2::XMLNode *firstChild = pRoot->FirstChild();
	tinyxml2::XMLNode *pBrother = firstChild;

	do
	{
		const char* label = pBrother->Value();
		tinyxml2::XMLNode *child = pBrother->FirstChild();

		const char* valChild = child->Value();

		if (strcmp(label, "lblNameHost") == 0) labels.nameHostServer = valChild;
		if (strcmp(label, "lblLanguage") == 0) labels.language = valChild;
		if (strcmp(label, "lblService") == 0) labels.service = valChild;
		if (strcmp(label, "btnlogin") == 0) labels.cmdConfirm = valChild;

		pBrother = pBrother->NextSibling();

	} while (pBrother != NULL);

	return;

}

void TranslateController::writeAndReadLabels(){

	char lang[20] = { "" };

	//strcpy(lang, (char*)cmblingua->GetStringSelection().mb_str().data());

	char filename[20] = { "" };
	strcpy(filename, "lang\\");
	strcat(filename, strcat(lang, ".xml"));

	/*lblServer->SetLabel("");
	lbllanguage->SetLabel("");
	lblService->SetLabel("");
	cmdConfirm->SetLabel("");*/

	readXmlLangDoc(filename);
}

//
//
//
//
//
//
