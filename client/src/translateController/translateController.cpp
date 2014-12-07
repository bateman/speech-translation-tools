#include "translateController.h"
#include "translateVariable.h"
#include "../connectionController/connectionController.h"
#include "../GlobalVariables.h"

#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "../tinyxml2.h"
#include <curl/curl.h>

using namespace tinyxml2;
using namespace std;

void TranslateController::InitLanguageVariable(char* lang)
{
	char filename[20] = { "" };
	char file_lang[20] = { "" };

	strcpy(filename, lang);

	//Controlla la presenza del file della lingua
	strcat(filename, ".xml");

	ifstream file(filename, ios::in);
	if (!file.is_open()){
		//se non c'è il file traduco e creo
		wxString trad = TranslateController::TraduzioneLabel(lang);

		labels.nameHostServer = strtok((char *)trad.mb_str().data(), ", ");
		labels.language = strtok(NULL, ", ");
		labels.service = strtok(NULL, ", ");
		labels.login = strtok(NULL, ", ");
		labels.gridMessage = strtok(NULL, ", ");
		labels.send = strtok(NULL, ", ");

		writeXmlLangDoc(filename);

	}
	else
	{
		TranslateController::readXmlLangDoc(filename); // leggo e imposto la variabile globale lable
	}
	file.close();
}

wxString TranslateController::TraduzioneLabel(char* language)
{
	wxString labelDefault = "Name,Language,Service,Confirm,Message,Send";
	strcpy(CURRENT_LANG, language);
	if (strcmp(CURRENT_LANG, "English") == 0)				//Non traduco l'inglese
		return labelDefault;
	else
		parseBing(richiestaBing(labelDefault, "English"));	//traduco dall'inglese nella nuova lingua
	return StringTranslate;
}

/*
*   creazione traduzione scrittura e lettura xml per interfaccia
*/
void TranslateController::writeXmlLangDoc(char* filename)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument(); //creazione documento
	tinyxml2::XMLNode* element = doc->InsertEndChild(doc->NewElement("language")); //creazione nodo radice //
	tinyxml2::XMLElement* sub[7] = { doc->NewElement("lblNameHost"), doc->NewElement("lblLanguage"), doc->NewElement("lblService"), doc->NewElement("btnlogin"), doc->NewElement("lblmessage"), doc->NewElement("btnsend") }; //creazione figli con inserimento tag

	//assegnazione dei valori nei tag
	sub[0]->InsertFirstChild(doc->NewText(labels.nameHostServer.c_str() ));
	element->InsertEndChild(sub[0]);
	sub[1]->InsertFirstChild(doc->NewText(labels.language.c_str()));
	element->InsertEndChild(sub[1]);
	sub[2]->InsertFirstChild(doc->NewText(labels.service.c_str()));
	element->InsertEndChild(sub[2]);
	sub[3]->InsertFirstChild(doc->NewText(labels.login.c_str()));
	element->InsertEndChild(sub[3]);
	sub[4]->InsertFirstChild(doc->NewText(labels.gridMessage.c_str()));
	element->InsertEndChild(sub[4]);
	sub[5]->InsertFirstChild(doc->NewText(labels.send.c_str()));
	element->InsertEndChild(sub[5]);

	doc->Print(); //stampa nella console

	//int value = 10;
	//int result = doc->FirstChildElement()->LastChildElement()->QueryIntAttribute("attrib", &value);

	//stampa sul file
	{
		XMLPrinter streamer;
		doc->Print(&streamer);
		printf("%s", streamer.CStr());
	}
		{
			XMLPrinter streamer(0, true);
			doc->Print(&streamer);
		}
		doc->SaveFile(filename);
		//doc->SaveFile("compact.xml", true);
		delete doc;

}

void TranslateController::readXmlLangDoc(char* filename){

	tinyxml2::XMLDocument xmlDoc;//creazione document per la lettura
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename);		//caricamento del file xml
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();			//lettura del padre language
	tinyxml2::XMLElement * pElement;

	tinyxml2::XMLNode *primoFiglio = pRoot->FirstChild();
	tinyxml2::XMLNode *pFratello = primoFiglio;

	labels.nameHostServer = "pippo";

	do
	{
		const char* etichetta = pFratello->Value();
		tinyxml2::XMLNode *figlio = pFratello->FirstChild();

		const char* valFiglio = figlio->Value();

		if (strcmp(etichetta, "lblNameHost") == 0) labels.nameHostServer = valFiglio;
		if (strcmp(etichetta, "lblLanguage") == 0) labels.language = valFiglio;
		if (strcmp(etichetta, "lblService") == 0) labels.service = valFiglio;
		if (strcmp(etichetta, "btnlogin") == 0) labels.login = valFiglio;
		if (strcmp(etichetta, "lblmessage") == 0) labels.gridMessage = valFiglio;
		if (strcmp(etichetta, "btnsend") == 0) labels.send = valFiglio;

		pFratello = pFratello->NextSibling();
	
	} while (pFratello != NULL);

	/*
	
	pElement = pRoot->FirstChildElement("lblNameHost");				//lettura figlio
	labels.nameHostServer = const_cast<char *>(pElement->GetText());//lettura valore del figlio
	
	//pElement = pRoot->FirstChildElement("lblNickName");//lettura figlio
	//lblNickName = const_cast<char *>(pElement->GetText());//lettura valore del figlio
	
	pElement = pRoot->FirstChildElement("lblLanguage");				//lettura figlio
	strcpy(labels.language, const_cast<char *>(pElement->GetText()));//lettura valore del figlio

	pElement = pRoot->FirstChildElement("lblService");//lettura figlio
	strcpy(labels.service, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	
	pElement = pRoot->FirstChildElement("btnlogin");//lettura figlio
	strcpy(labels.login, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	
	pElement = pRoot->FirstChildElement("lblmessage");//lettura figlio
	strcpy(labels.gridMessage, const_cast<char *>(pElement->GetText()));//lettura valore del figlio
	
	pElement = pRoot->FirstChildElement("btnsend");//lettura figlio
	strcpy(labels.send, const_cast<char *>(pElement->GetText()));//lettura valore del figlio

	*/

	return;

}

void TranslateController::parseBing(char *word)
{

	char *buffer;
	unsigned int i;
	int result;
	buffer = strstr(word, ">");
	result = (int)(buffer - word + 1);
	if (buffer != NULL)
		printf("%s found at position %d\n", word, result);
	else

		return;
	for (i = 1; i<strlen(buffer); i++) buffer[i - 1] = buffer[i];
	buffer[strlen(buffer) - 10] = '\0';
	StringTranslate = wxString::FromAscii(buffer); // StringTranslate contains the text translate
}

void TranslateController::parseGoogle(char *str)
{
	unsigned int i = 0;
	int j = 0;
	char * pch;
	char * stringalpha;
	char finale[2048] = { "" };

	char buffer[512] = { "" };

	pch = strtok(str, ",.:\"'{}();200[]");
	while (pch != NULL)
	{
		strcat(buffer, pch);
		pch = strtok(NULL, ",.:\"'{}();200[]");
	}

	char prova[256];
	int quanto;
	char * p = strstr(buffer, "Text");
	if (p == NULL)
	{
		return;
	}
	else
	{
		quanto = strlen(p);
		strncpy(prova, strstr(buffer, "Text"), quanto);
		prova[quanto] = '\0';
		stringalpha = strstr(prova, "Text");
		for (i = 4; i < strlen(strstr(prova, "Text")); i++)
		{
			finale[j] = stringalpha[i];
			j++;
		}
		StringTranslate = wxString::FromAscii(finale);	//StringTranslate contains the message translate
	}
}

char *TranslateController::richiestaBing(wxString StringSource, char * lang)
{
	if (strcmp(lang, CURRENT_LANG) == 0) return (char*)StringSource.mb_str().data();	//If the message is written in client's language then return

	CURL *curl2;
	CURL *curl3;
	CURLcode res2;
	struct curl_slist *chunk = NULL;
	struct stringa f;
	ConnectionController::init_string(&f);
	struct stringa p;
	ConnectionController::init_string(&p);

	curl_global_init(CURL_GLOBAL_ALL);

	curl2 = curl_easy_init();
	if (curl2)
	{

		curl_easy_setopt(curl2, CURLOPT_URL, "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13"); //Set the url of http request
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYHOST, 0L);	//Use SSL Protocol
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0L);	//Use SSL protocol
		curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, ConnectionController::writefunc);	//Function to handle http request
		curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &f);				//Save answer into string 
		curl_easy_setopt(curl2, CURLOPT_POST, 1L);					//Inform the server to a post request
		curl_easy_setopt(curl2, CURLOPT_USERAGENT, "libcurl-agent/1.0");	//Fill user-agent to not decline our request
		curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1L);

		FILE *bing;
		if (bing = fopen("..\\conf\\BING.txt", "r"))
		{

			char CLIENT_ID[50] = "";
			char CLIENT_SECRET[128] = "";

			fscanf(bing, "%s", CLIENT_ID);
			fscanf(bing, "%s", CLIENT_SECRET);

			char * encode_key = curl_easy_escape(curl2, CLIENT_SECRET, strlen(CLIENT_SECRET));	//Leave incorrect url characters from CLIENT_ID nad CLIENT_SECRET
			char url2[1024] = { "" };
			strcpy(url2, "client_id=");
			strcat(url2, CLIENT_ID);
			strcat(url2, "&client_secret=");
			strcat(url2, encode_key);
			strcat(url2, "&scope=http://api.microsofttranslator.com&grant_type=client_credentials");
			curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, url2);
		}

		res2 = curl_easy_perform(curl2);
		/*
		Save into pagina.htm the json answer of access_token
		*/
		FILE *html;
		if (html = fopen("..\\conf\\pagina.htm", "w"))
		{
			fprintf(html, "%s", f.ptr);
			fflush(html);
			fclose(html);
		}

		ConnectionController::JSON();	//Parse answer for access_token value to start the translation
		char auth[2048] = { "" };
		char header[2048 + 512] = { "" };

		FILE * jfile;
		if (jfile = fopen("..\\conf\\JSON.txt", "r+"))
		{
			fscanf(jfile, "%s", &auth);
			fflush(jfile);
			fclose(jfile);
		}
		strcpy(header, "Authorization: Bearer ");
		strcat(header, auth);
		char languagesrc[30] = { "" };
		char languagedst[30] = { "" };
		if (strcmp(lang, "Italian") == 0)
		{
			strcpy(languagesrc, "it");
			if (strcmp(CURRENT_LANG, "English") == 0) strcpy(languagedst, "en");
			if (strcmp(CURRENT_LANG, "Italian") == 0) strcpy(languagedst, "it");
			if (strcmp(CURRENT_LANG, "Portuguese") == 0) strcpy(languagedst, "pt");
		}
		else if (strcmp(lang, "English") == 0)
		{
			strcpy(languagesrc, "en");
			if (strcmp(CURRENT_LANG, "English") == 0) strcpy(languagedst, "en");
			if (strcmp(CURRENT_LANG, "Italian") == 0) strcpy(languagedst, "it");
			if (strcmp(CURRENT_LANG, "Portuguese") == 0) strcpy(languagedst, "pt");
		}
		else if (strcmp(lang, "Portuguese") == 0)
		{
			strcpy(languagesrc, "pt");
			if (strcmp(CURRENT_LANG, "English") == 0) strcpy(languagedst, "en");
			if (strcmp(CURRENT_LANG, "Italian") == 0) strcpy(languagedst, "it");
			if (strcmp(CURRENT_LANG, "Portuguese") == 0) strcpy(languagedst, "pt");
		}
		curl3 = curl_easy_init();
		char *trueheader = curl_easy_unescape(curl3, header, 0, NULL);


		const char *BufferSource = curl_easy_escape(curl3, (char*)StringSource.mb_str().data(), strlen((char*)StringSource.mb_str().data()));


		char url3[512] = { "" };
		strcpy(url3, "http://api.microsofttranslator.com/V2/Http.svc/Translate?text=");

		//strcat(url3, url_encode(pr).c_str());
		strcat(url3, BufferSource);
		strcat(url3, "&from=");
		strcat(url3, languagesrc);
		strcat(url3, "&to=");
		strcat(url3, languagedst);

		curl_easy_setopt(curl3, CURLOPT_URL, url3);
		curl_easy_setopt(curl3, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		chunk = curl_slist_append(chunk, header);
		res2 = curl_easy_setopt(curl3, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl3, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, ConnectionController::writefunc);
		curl_easy_setopt(curl3, CURLOPT_WRITEDATA, &p);
		res2 = curl_easy_perform(curl3);


		if (res2 != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res2));
		curl_easy_cleanup(curl2);
	}
	curl_global_cleanup();

	FILE *html;
	if (html = fopen("..\\conf\\trad.htm", "w"))
	{
		fprintf(html, "%s", p.ptr);
		fflush(html);
		fclose(html);
	}
	return p.ptr;
}

char *TranslateController::richiestaGoogle(wxString StringSource, char * lang)
{

	if (strcmp(lang, CURRENT_LANG) == 0) return (char*)StringSource.mb_str().data();

	CURL *curl;
	CURLcode res;

	strcpy(url, "");
	char languagesrc[30] = { "" };
	char languagedst[30] = { "" };
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	struct stringa s;
	ConnectionController::init_string(&s);
	if (strcmp(lang, "Italian") == 0)
	{
		strcpy(languagesrc, "it");
		if (strcmp(CURRENT_LANG, "English") == 0) strcpy(languagedst, "en");
		if (strcmp(CURRENT_LANG, "Italian") == 0) strcpy(languagedst, "it");
		if (strcmp(CURRENT_LANG, "Portuguese") == 0) strcpy(languagedst, "pt");
	}
	else if (strcmp(lang, "English") == 0)
	{
		strcpy(languagesrc, "en");
		if (strcmp(CURRENT_LANG, "English") == 0) strcpy(languagedst, "en");
		if (strcmp(CURRENT_LANG, "Italian") == 0) strcpy(languagedst, "it");
		if (strcmp(CURRENT_LANG, "Portuguese") == 0) strcpy(languagedst, "pt");
	}
	else if (strcmp(lang, "Portuguese") == 0)
	{
		strcpy(languagesrc, "pt");
		if (strcmp(CURRENT_LANG, "English") == 0) strcpy(languagedst, "en");
		if (strcmp(CURRENT_LANG, "Italian") == 0) strcpy(languagedst, "it");
		if (strcmp(CURRENT_LANG, "Portuguese") == 0) strcpy(languagedst, "pt");
	}


	if (curl)
	{
		strcpy(url, "https://www.googleapis.com/language/translate/v2?key=");
		strcat(url, GOOGLE_API_KEY);

		strcat(url, "&q=");
		const char *BufferSource = curl_easy_escape(curl, (char*)StringSource.mb_str().data(), strlen((char*)StringSource.mb_str().data()));
		strcat(url, BufferSource);
		strcat(url, "&source=");
		strcat(url, languagesrc);
		strcat(url, "&target=");
		strcat(url, languagedst);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ConnectionController::writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
		return s.ptr;
	}

	curl_global_cleanup();
}