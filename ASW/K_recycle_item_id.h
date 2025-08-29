#include <user_exits\user_exits.h>
#include <tccore\item.h>
#include <tccore\aom_prop.h>
#include <tccore\tc_msg.h>
#include <pom\pom\pom.h>
#include <pom\enq\enq.h>

#include <string>
#include <map>
#include <stdlib.h>
#include <time.h>
#include<tc\tc_util.h>
#include<tc\preferences.h>
#include <ae\dataset.h>
#include "K_autocode_util.h"
#include "origin_PropNames.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ECHO(X)      printf X;
#define SYS_LOG(X)   TC_write_syslog X;
#define LOG_ECHO(X)  printf X; TC_write_syslog X;
	/*!
	* \def CALL(x)
	* ¥Ú”°¥ÌŒÛ–≈œ¢
	*/
#define CALL(x) {               \
	int stat;                     \
	char *err_string;             \
	if( (stat = (x)) != ITK_ok)   \
	{                             \
	EMH_ask_error_text (stat, &err_string);              \
	LOG_ECHO( ("ERROR: %d ERROR MSG: %s.\n",stat, err_string) )	\
	LOG_ECHO( ("Function: %s FILE: %s LINE: %d\n", #x, __FILE__, __LINE__ ) )	\
	MEM_free (err_string);   \
	return (stat);          \
}                         \
}
#define ITEM_POM_CLASS "ITEM"

	int QueryReduntantItemId(char* TeZhengMa, char** the_item_id);
	int recycle_ItemID(void* returnValue);
	int recycle_deleted_ItemID(METHOD_message_t* msg, va_list args);
	int SaveReduntantItemId(char* TeZhengMa, char* new_item_id, const char* occupied);
	int recycleNewItemId(METHOD_message_t* msg, va_list args);
	int recycleNewProjectId(METHOD_message_t* msg, va_list args);
	int delete_recycleID(void* returnValue);

#ifdef __cplusplus
}
#endif