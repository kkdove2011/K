#ifndef THINKSOFT_UTIL_H
#define THINKSOFT_UTIL_H

#include <tc\tc_macros.h>
#include <tccore\method.h>
#include <tccore/workspaceobject.h>
#include <tccore/item.h>
#include <form\form.h>
#include <tccore\aom.h>
#include <tccore\aom_prop.h>
#include <tccore/grm.h>
#include <tccore/grmtype.h>
#include <tc\preferences.h>
#include <tc\folder.h>
#include <property\prop.h>
#include <ict\ict_userservice.h>
#include <lov\lov.h>
#include <time.h>
//using namespace Teamcenter;
#include <ug_va_copy.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int GetStringArrayPreference( TC_preference_search_scope_e eScope, const char *szPrefName, int *iPrefCount, char ***sszValues );
int GetStringPreference( TC_preference_search_scope_e eScope, const char *szPrefName, char **ssxValues );

string stringTrim( string strArg );

void SplitStr( string strArg, string spliter, vector<string> &ans );

extern "C" int POM_AM__set_application_bypass(logical bypass);
extern "C" int AM__set_application_bypass(logical bypass);

#endif //THINKSOFT_UTIL_H
