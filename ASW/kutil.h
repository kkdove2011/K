#include <tc\tc_macros.h>
#include <tc\emh.h>
#include <tc\preferences.h>
#include <property\propdesc.h>
#include <epm\epm.h>
#include <epm\epm_toolkit_tc_utils.h>
#include <tccore\item.h>
#include <tccore\grmtype.h>
#include <tchar.h>
#include <tccore\grm.h>
#include <tccore\imantype.h>
#include <sa\am.h>
#include <sa\sa.h>
#include <tccore\aom.h>
#include <tccore\aom_prop.h>
#include <property\prop_errors.h>
#include <tccore\workspaceobject.h>
#include <qry\qry.h>
#include <bom\bom_attr.h>
#include <bom\bom.h>
#include <epm\signoff.h>
#include <pom\pom\pom.h>
#include <pom\pom\pom_errors.h>
#include <fclasses\tc_date.h>
#include <epm\cr.h>
#include <cfm\cfm.h>
#include <time.h>
#include <ae/ae.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <string>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <res\reservation.h>


#ifdef WIN32
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

#define DOFREE(obj)								\
{												\
	if(obj)										\
	{											\
		MEM_free(obj);							\
		obj = NULL;								\
	}											\
}

extern "C" int POM_AM__set_application_bypass(logical bypass);

using namespace std;

void WriteLog(logical debug, const char* format, ...);
void set_bypass(logical bypass);
char* G2U(const char* gb2312);
int getPrefStrings(const char* preference, TC_preference_search_scope_t scope, vector<string>& pref_vec);
int export_dataset_file(bool debug, tag_t dataset, const char* ref_name, const char* ext, char** filename, char** original_name);
int GetBomView(tag_t rev_tag, const char* viewtype, tag_t* bomView, tag_t* bomBVR, bool debug);
int GetBomLinePropString(bool debug, tag_t line, char* propName, int errCode, char** attr_val);
void Split(string strArg, char spliter, vector<string>& ans);
void Split(string strArg, string spliter, vector<string>& ans);
int getPrefStrings2(const char* preference, TC_preference_search_scope_t scope, char splitter, vector<string>& pref_vec);
int import_dataset_file(tag_t dataset, const char* ref_name, char* ext, char* fullfilename, char* original_name);
int import_dataset_file_binary(tag_t dataset, const char* ref_name, char* ext, char* fullfilename, char* original_name);
int readError(bool debug, char* errFilePath, int errCode);
void deleteFile(bool debug, char* path);
bool CheckType(string config, char* type, char spliter);
bool propExist(bool debug, tag_t obj, const char* propName);
bool isRev(char* object_type);
int GetProcessTargets(bool debug, int att_cnt, tag_t* attachments, vector<tag_t>& targets, char* formType, char splitter);
bool inArray(vector<string> types, string type);
int getIndexInArray(vector<string> types, string type);
int findUser(bool debug, string userStr, tag_t* user_tag);
bool isType(tag_t item, char* type);
void initUserDir(char* userId);
int CreateUserFile(logical debug, const char* FunctionName, char* userId, char** fullname, FILE** file);
int WriteToFile(logical debug, FILE* file, const char* format, ...);