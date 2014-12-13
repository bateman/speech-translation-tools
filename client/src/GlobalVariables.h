//#include "ClientTsFrm.h"
//#include "AudioWizard.h"
//#include "Login.h"

#ifndef _GLOBALVARIABLE_H_
#define _GLOBALVARIABLE_H_

#include "utility.h"
#include <windows.h>
#include <atlbase.h>
#include <sphelper.h>
#include <sapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sstream>
#include <time.h>
#include <limits.h>
#include <audiere.h>
#include <irrKlang.h>
#include <string.h>
#include <iostream>
#include <list>
#include <public_definitions.h>
#include <public_errors.h>
#include <clientlib_publicdefinitions.h>
#include <clientlib.h>
#include <curl/curl.h>
#include <wx/msgdlg.h>
#include <wx/sstream.h>
#include <wx/protocol/http.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextstyles.h>
#include <wx/richtext/richtextxml.h>
#include <wx/richtext/richtexthtml.h>
#include <wx/richtext/richtextformatdlg.h>
#include <wx/richtext/richtextsymboldlg.h>
#include <wx/richtext/richtextstyledlg.h>
#include <wx/richtext/richtextprint.h>
#include <wx/richtext/richtextimagedlg.h>
#include "../include/wx/grid.h"
#include "rapidjson/document.h"		
#include "rapidjson/prettywriter.h"	
#include "rapidjson/filestream.h"

#include "../res/keyboard.xpm"
#include "../res/microphone.xpm"
#include "../res/italy.xpm"
#include "../res/usa.xpm"
#include "../res/brasil.xpm"

#define MAX 30

#define DEFAULT_VIRTUAL_SERVER 1
#define NAME_BUFSIZE 1024

#define CHECK_ERROR(x) if((error = x) != ERROR_ok) { goto on_error; }
#define IDENTITY_BUFSIZE 1024

#ifdef _WIN32
#define snprintf sprintf_s
#define SLEEP(x) Sleep(x)
#else
#define SLEEP(x) usleep(x*1000)
#endif

using namespace audiere;
using namespace std;
using namespace ATL;
using namespace rapidjson;
using namespace irrklang;

struct WaveHeader {
	/* Riff chunk */
	char riffId[4];
	unsigned int len;
	char riffType[4];

	/* Format chunk */
	char fmtId[4];  // 'fmt '
	unsigned int fmtLen;
	unsigned short formatTag;
	unsigned short channels;
	unsigned int samplesPerSec;
	unsigned int avgBytesPerSec;
	unsigned short blockAlign;
	unsigned short bitsPerSample;

	/* Data chunk */
	char dataId[4];  // 'data'
	unsigned int dataLen;
};

typedef struct color
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;
} COLORE;

struct user
{
	wxString name;
	unsigned short color;
	unsigned short used = 0;
	unsigned short speak = 0;
	unsigned short write = 0;
	wxString lang;
};

struct stringa {
	char *ptr;
	size_t len;
};

typedef struct message
{
	wxString nick;
	wxString msgnew;
	wxString lang;
	wxString msgold;
} MESSAGE;

typedef struct header_file
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;            // sample_rate denotes the sampling rate.
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;         // subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;

struct WriteThis {
	const char *readptr;
	long sizeleft;
};

extern DWORD myThreadID;
extern DWORD myThreadID2;
extern DWORD myThreadID3;
extern DWORD myThreadID4;

extern int iresult;
extern short flag; //Flag to exit from client

extern wxString strGlobale;
extern wxString oldstrGlobale;
extern wxString strNick;
extern wxString strMessage;
//wxString StringTranslate = "";
//wxString StringSource = "";
extern string StringSourceLog;

extern wxString SourceLanguageLog;
extern wxString oldStringTranslate;
extern wxString StringOriginal;
extern wxString strSpeak;

extern char SERVER_ADDRESS[20];
extern char NICK[50];
//char CURRENT_LANG[20];
extern char SERVICE[20];
extern char LANG_MSG_SRC[20];
extern char MSG_SRC[50];
extern char GOOGLE_API_KEY[50];
extern char url[256];
extern char MSG_PARSE[1024];
extern char translate_jar[512];
extern unsigned short PORT;	//Number port of server
extern int cmbel;				//Index of comboBox choose
extern int index;
extern int VAD_VALUE;			//Minimum value to record audio
extern COLORE colors[10];
extern unsigned count_client;
extern unsigned short set_color_client;	//Own client color name
extern struct user person[MAX];			//Array of user to record client's information
extern ISoundEngine* engine;			//Audio Engine to record sound
extern IAudioRecorder* recorder;		//Flow of audio daa
extern bool sound_flag;					//Flag to start/stop 
extern bool tts_flag;					//Flag to start/stop TextToSpeech 		
extern bool write_flag;					//Flag to recognize Typing
extern bool tasto_stt_flag;				//Flag to activate Automatic SpeechToText
extern bool finish_ctrl_flag;			//Flag to recognize CTRL press button
extern bool automatic_stt_flag;
extern wxRichTextCtrl *chatptr;			//Pointer to edit the chatptr
extern unsigned int curRow;				//Initialize Row index
extern unsigned int curCol;				//Initialize Column index
extern MESSAGE diary[1024];				//Structure to record log chatptr
extern wxGrid *gridptr;					//Pointer to edit the chatptr grid
extern FILE* chatSessionLog;				//Log File for chat recording at the end of a chat session
extern FILE* chatSessionLogCsv;			//Log File for chat recording at the end of a chat session for cvs
extern time_t rawtime;						//CurrentTime
extern struct tm * timeinfo;				//Structure for timestamp
extern list<string> clientMessages;		//List of client messages for log
extern list<string> clientMessagesCsv;		//List of client messages for log for cvs
extern string logmessage;					//Single Log message
extern string logmessagecsv;


#endif // _GLOBALVARIABLE_H_
