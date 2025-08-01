#include <tc\tc_macros.h>
#include <tc\emh.h>
#include <epm\epm_toolkit_tc_utils.h>
#include <tc\preferences.h>
#include <tccore\grm.h>
#include <tccore\aom.h>
#include <tccore\aom_prop.h>
#include <tccore\workspaceobject.h>
#include <ae/ae.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <base_utils/IFail.hxx>
#include <base_utils/TcResultStatus.hxx>
using namespace std;

#define DOFREE(obj)								\
  {												\
  	if(obj)										\
  	{											\
  		MEM_free(obj);							\
  		obj = NULL;								\
  	}											\
  }
char* getTime();
int getCurrentMilliSeconds();
string trim(const string& str);
int ReportError(logical is_utf8, int err_code, const char* format, ...);
void StartLog(string str);
void Log(const char* format, ...);
int Log(IFail ex);
void CloseLog();
void set_bypass(logical bypass);
char* G2U(const char* gb2312);
char* U2G(const char* utf8);
void Split(string strArg, string spliter, vector<string>& ans);
logical inArray(vector<string> types, string type);