/**
* @file common_itk_util.cpp
* @brief itk warpper utility function
* @author James
* @history
* ===================================================================================
* Date             Name                   Description of Change
* 18-July-2008     James
*/

#pragma warning (disable: 4996) 
#pragma warning (disable: 4819) 
#pragma warning(disable: 4995 ) 
#pragma warning (disable: 4013) 

#include <epm/epm.h>
#include <epm/epm_toolkit_tc_utils.h>
#include <ict/ict_userservice.h>
#include <tccore/item.h>
#include <ae/ae.h>
#include <tc/folder.h>
#include <tccore/aom.h>
#include <sa/sa.h>
#include <tccore/aom_prop.h>
#include <property/prop_errors.h>
#include <tccore/workspaceobject.h>
#include <tc/preferences.h>
#include <tccore/imantype.h>
#include <tccore//grm.h>
#include <tccore/grmtype.h>
#include <sa/am.h>
#include <cfm/cfm.h>
#include <bom/bom.h>
#include <tccore/uom.h>
#include <ps/ps.h>
#include <epm/signoff.h>
#include <fclasses/tc_date.h>
#include <tccore/imantype.h>
#include <textsrv/textserver.h>
#include <user_exits/epm_toolkit_utils.h>
#include <ss/ss_errors.h>

#include <stdlib.h>
#include <io.h>
#include <stdio.h>
#include <time.h>
#include <direct.h>
#include "error_handling.h"
#include "common_itk_util.h"

#ifdef WIN32
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#endif


#define ARGS_LENGTH 200
#define ARGS_NAME_DEBUG "-debug"
#define DEBUG "-debug="
#define MAX_PRINTLINE_LENGTH 2000
#define MAX_PATH_LENGTH 2000
#define MAX_ARGUMENT_LENGTH 400
#define MAX_PARAMNAME_LENGTH 50
#define MAX_FILE_EXT_LENGTH 10
#define TRUE_FLAG 1
#define FALSE_FLAG 0
#define DETAILLOG 1


void ECHO(char *format, ...)
{
	//if( !YFJC_OPT_DEBUG )
	//    return; 

	char msg[1024];
	va_list args;

	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	printf(msg);
	TC_write_syslog(msg);
}

FILE* logFile = NULL;

void set_bypass(logical bypass)
{
	//AM__set_application_bypass(bypass);
	POM_AM__set_application_bypass(bypass);
}

int ORIGIN_set_bypass(void *returnValue)
{
	POM_AM__set_application_bypass(true);
	return  0;
}

int ORIGIN_close_bypass(void *returnValue)
{
	POM_AM__set_application_bypass(false);
	return  0;
}

int GetLocalizedType(void * return_data) {

	int ifail = ITK_ok;
	char *uid = NULL, *nl = NULL;
	char* flag = "";
	tag_t type_tag=NULLTAG;
	tag_t release_stat = NULLTAG;
	char server_string[10];
	ITKCALL(ifail = USERARG_get_string_argument(&uid));
	ITKCALL(ifail = USERARG_get_string_argument(&nl));
	ECHO("查询对象 %s 本地化 = %s \n", uid, nl);
	ITKCALL(ifail = POM_string_to_tag(uid, &type_tag));
	if (type_tag != NULLTAG) {
		char localization_status;
		logical master;
		ITKCALL(ifail = AOM_UIF_ask_localized_value_string(type_tag, "type_name", nl, &flag, &localization_status, &master));
		ECHO("对象类型：%s %c\n", flag, localization_status);
		if (ifail == ITK_ok&&localization_status=='A') {
			strcpy(server_string, flag);
			*((char **)return_data) =
				(char *)MEM_alloc((strlen(server_string) + 1) * sizeof(char));
			strcpy(*((char **)return_data), server_string);
		}
		DOFREE(flag);
	}
	MEM_free(uid);
	MEM_free(nl);
	return ITK_ok;
}

/*=============================================================================*
 * FUNCTION: current_time
 * PURPOSE : get the current datetime
 * INPUT:
 *     date_t* date_tag  	// current date time tag
 *
 * RETURN:
 *     void
 *============================================================================*/
void current_time(date_t * date_tag)
{
	time_t ltime;
	struct tm *today;

	// Set time zone from TZ environment variable. If TZ is not set,
	// the operating system is queried to obtain the default value 
	// for the variable. 
	//
	//_tzset();

	// Get UNIX-style time and display as number and string.
	time(&ltime);

	today = localtime(&ltime);
	date_tag->year = today->tm_year + 1900;
	date_tag->month = today->tm_mon;
	date_tag->day = today->tm_mday;
	date_tag->hour = today->tm_hour;
	date_tag->minute = today->tm_min;
	date_tag->second = today->tm_sec;
}
/*=============================================================================*
 * FUNCTION: CreateLogFile
 * PURPOSE : create log file
 * INPUT:
 *     char* FunctionName  	// the funtion which need to create log file
 *     FILE** logFile		// out: the log file pointer
 *
 * RETURN:
 *     void
 *============================================================================*/

void initUserDir(char *userId){
	char logFileDir[MAX_PATH_LENGTH];
	memset(logFileDir, 0, sizeof(logFileDir));
	sprintf(logFileDir, "%s", getenv("TEMP"));
	strcat(logFileDir, "\\tc_");
	strcat(logFileDir, userId);
	if (chdir(logFileDir) != ITK_ok) {
		printf(">> 新建路径：%s\n",logFileDir);
		mkdir(logFileDir);
	}
}


//void initUserDir(char *userId,char **dir) {
//	char logFileDir[MAX_PATH_LENGTH];
//	memset(logFileDir, 0, sizeof(logFileDir));
//	sprintf(logFileDir, "%s", getenv("TEMP"));
//	strcat(logFileDir, "\\tc_");
//	strcat(logFileDir, userId);
//	if (chdir(logFileDir) != ITK_ok) {
//		printf(">> 新建路径：%s\n", logFileDir);
//		mkdir(logFileDir);
//	}
//	sprintf(*dir, "%s", logFileDir);
//}

void CreateTempFileName(char*preFix,const char* FunctionName,char *ext, char *userId, char **fullname,char **fileName)
{
	int ifail = ITK_ok;
	//date_t status_now;
	//char* date_string = NULL;
	char date_string[MAX_PATH_LENGTH];
	char logFileDir[MAX_PATH_LENGTH];
	char logFileName[MAX_PATH_LENGTH];
	//char* session_uid = NULL;
	//tag_t session_tag = NULLTAG;

	time_t now;
	struct tm *p;

	time(&now);

	//logFile = NULL;
	//current_time(&status_now);
	p = localtime(&now);

	memset(date_string, 0, sizeof(date_string));
	sprintf(date_string, "%4d%02d%02d%02d%02d%02d", 1900 + p->tm_year, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	//sprintf(date_string, "%4d%02d%02d", 1900 + p->tm_year, p->tm_mon + 1, p->tm_mday);
	//if( DATE_date_to_string( status_now, "%Y%m%d%H%M%S", &date_string) != ITK_ok )
	//ifail = ITK_date_to_string (status_now, &date_string );
	//if (ifail)
	//{
	//	printf("!*ERROR*!: Failed to get current date time\n");
	//	goto CLEANUP;
	//}

	memset(logFileDir, 0, sizeof(logFileDir));
	memset(logFileName, 0, sizeof(logFileName));
	//get log dir
	sprintf(logFileDir, "%s", getenv("TEMP"));
	strcat(logFileDir, "\\tc_");
	strcat(logFileDir, userId);
	//printf("\n log file dir: %s\n", logFileDir);
	//try to change dir to TC_USER_LOG_DIR

	//get session_uid to make sure the log file name unique
	//POM_ask_session(&session_tag);
	//ITK__convert_tag_to_uid(session_tag, &session_uid);
	//get logFileName
	sprintf(logFileName, "%s_%s_%s.%s", preFix,FunctionName, date_string,ext);
	//printf("log file name: %s\n", logFileName);

	*fullname = (char *)MEM_alloc(sizeof(char) * 512);
	sprintf(*fullname, "%s\\%s", logFileDir, logFileName);
	*fileName = (char *)MEM_alloc(sizeof(char) * 512);
	sprintf(*fileName, "%s", logFileName);
	//for(i = 0; _access((char *)logFileName, 4) == 0; i++)
	/*{
		memset(logFileName, 0, sizeof(logFileName));
		sprintf(logFileName, "%s_%s_%s_%d.log", FunctionName, session_uid, date_string, i);
	}
	printf("final log file name: %s\n", logFileName);*/

	//create log file
	//logFile = fopen(logFileName, "a");

CLEANUP:;
	//DOFREE(date_string);
	/*if(session_uid!=NULL){
		MEM_free(session_uid);
		session_uid=NULL;
	}*/
}

void CreateFileName(char* FunctionName, char *userId, char **fullname)
{
	int ifail = ITK_ok;
	//date_t status_now;
	//char* date_string = NULL;
	char date_string[MAX_PATH_LENGTH];
	char logFileDir[MAX_PATH_LENGTH];
	char logFileName[MAX_PATH_LENGTH];
	//char* session_uid = NULL;
	//tag_t session_tag = NULLTAG;

	time_t now;
	struct tm *p;

	time(&now);

	//logFile = NULL;
	//current_time(&status_now);
	p = localtime(&now);

	memset(date_string, 0, sizeof(date_string));
	sprintf(date_string,"%4d%02d%02d%02d%02d%02d",1900+p->tm_year,p->tm_mon+1 ,p->tm_mday ,p->tm_hour,p->tm_min ,p->tm_sec );
	//sprintf(date_string, "%4d%02d%02d", 1900 + p->tm_year, p->tm_mon + 1, p->tm_mday);
	//if( DATE_date_to_string( status_now, "%Y%m%d%H%M%S", &date_string) != ITK_ok )
	//ifail = ITK_date_to_string (status_now, &date_string );
	//if (ifail)
	//{
	//	printf("!*ERROR*!: Failed to get current date time\n");
	//	goto CLEANUP;
	//}

	memset(logFileDir, 0, sizeof(logFileDir));
	memset(logFileName, 0, sizeof(logFileName));
	//get log dir
	sprintf(logFileDir, "%s", getenv("TEMP"));
	strcat(logFileDir, "\\tc_");
	strcat(logFileDir, userId);
	//printf("\n log file dir: %s\n", logFileDir);
	//try to change dir to TC_USER_LOG_DIR

	//get session_uid to make sure the log file name unique
	//POM_ask_session(&session_tag);
	//ITK__convert_tag_to_uid(session_tag, &session_uid);
	//get logFileName
	sprintf(logFileName, "%s_%s_%s.log", FunctionName, userId, date_string);
	//printf("log file name: %s\n", logFileName);

	*fullname = (char *)MEM_alloc(sizeof(char) * 512);
	sprintf(*fullname, "%s\\%s", logFileDir, logFileName);

	//for(i = 0; _access((char *)logFileName, 4) == 0; i++)
	/*{
		memset(logFileName, 0, sizeof(logFileName));
		sprintf(logFileName, "%s_%s_%s_%d.log", FunctionName, session_uid, date_string, i);
	}
	printf("final log file name: %s\n", logFileName);*/

	//create log file
	//logFile = fopen(logFileName, "a");

CLEANUP:;
	//DOFREE(date_string);
	/*if(session_uid!=NULL){
		MEM_free(session_uid);
		session_uid=NULL;
	}*/
}

void CreateLogFile(char* FunctionName, char *userId, char **fullname)
{
	int ifail = ITK_ok;
	//date_t status_now;
	//char* date_string = NULL;
	char date_string[MAX_PATH_LENGTH];
	char logFileDir[MAX_PATH_LENGTH];
	char logFileName[MAX_PATH_LENGTH];
	//char* session_uid = NULL;
	//tag_t session_tag = NULLTAG;

	time_t now;
	struct tm *p;

	time(&now);

	logFile = NULL;
	//current_time(&status_now);
	p = localtime(&now);

	memset(date_string, 0, sizeof(date_string));
	//sprintf(date_string,"%4d%02d%02d%02d%02d%02d",1900+p->tm_year,p->tm_mon+1 ,p->tm_mday ,p->tm_hour,p->tm_min ,p->tm_sec );
	sprintf(date_string, "%4d%02d%02d", 1900 + p->tm_year, p->tm_mon + 1, p->tm_mday);
	//if( DATE_date_to_string( status_now, "%Y%m%d%H%M%S", &date_string) != ITK_ok )
	//ifail = ITK_date_to_string (status_now, &date_string );
	//if (ifail)
	//{
	//	printf("!*ERROR*!: Failed to get current date time\n");
	//	goto CLEANUP;
	//}

	memset(logFileDir, 0, sizeof(logFileDir));
	memset(logFileName, 0, sizeof(logFileName));
	//get log dir
	sprintf(logFileDir, "%s", getenv("TEMP"));
	strcat(logFileDir, "\\tc_");
	strcat(logFileDir, userId);
	//printf("\n log file dir: %s\n", logFileDir);
	//try to change dir to TC_USER_LOG_DIR
	if (chdir(logFileDir) != ITK_ok)
	{
		//not set TC_USER_LOG_DIR
		//log in to default TC_LOG
		memset(logFileDir, 0, sizeof(logFileDir));
		sprintf(logFileDir, "%s", getenv("TC_LOG"));
		printf("\n TC_USER_LOG_DIR invalide, log file dir: %s\n", logFileDir);
		if (chdir(logFileDir) != ITK_ok)
		{
			//still can not change to log dir
			printf("!*ERROR*!: Failed to change dir to TC_USER_LOG_DIR\n");
			goto CLEANUP;
		}
	}

	//get session_uid to make sure the log file name unique
	//POM_ask_session(&session_tag);
	//ITK__convert_tag_to_uid(session_tag, &session_uid);
	//get logFileName
	sprintf(logFileName, "%s_%s_%s.log", FunctionName, userId, date_string);
	//printf("log file name: %s\n", logFileName);

	*fullname = (char *)MEM_alloc(sizeof(char) * 512);
	sprintf(*fullname, "%s\\%s", logFileDir, logFileName);

	//for(i = 0; _access((char *)logFileName, 4) == 0; i++)
	/*{
		memset(logFileName, 0, sizeof(logFileName));
		sprintf(logFileName, "%s_%s_%s_%d.log", FunctionName, session_uid, date_string, i);
	}
	printf("final log file name: %s\n", logFileName);*/

	//create log file
	logFile = fopen(logFileName, "a");

CLEANUP:;
	//DOFREE(date_string);
	/*if(session_uid!=NULL){
		MEM_free(session_uid);
		session_uid=NULL;
	}*/
}

int CreateUserFile(logical debug,char* FunctionName, char *userId, char **fullname,FILE **file)
{
	int ifail = ITK_ok;
	//date_t status_now;
	//char* date_string = NULL;
	char date_string[MAX_PATH_LENGTH];
	char logFileDir[MAX_PATH_LENGTH];
	char logFileName[MAX_PATH_LENGTH];
	//char* session_uid = NULL;
	//tag_t session_tag = NULLTAG;

	time_t now;
	struct tm *p;

	time(&now);

	//logFile = NULL;
	//current_time(&status_now);
	p = localtime(&now);

	memset(date_string, 0, sizeof(date_string));
	sprintf(date_string,"%4d%02d%02d%02d%02d%02d",1900+p->tm_year,p->tm_mon+1 ,p->tm_mday ,p->tm_hour,p->tm_min ,p->tm_sec );
	//sprintf(date_string, "%4d%02d%02d", 1900 + p->tm_year, p->tm_mon + 1, p->tm_mday);
	//if( DATE_date_to_string( status_now, "%Y%m%d%H%M%S", &date_string) != ITK_ok )
	//ifail = ITK_date_to_string (status_now, &date_string );
	//if (ifail)
	//{
	//	printf("!*ERROR*!: Failed to get current date time\n");
	//	goto CLEANUP;
	//}

	memset(logFileDir, 0, sizeof(logFileDir));
	memset(logFileName, 0, sizeof(logFileName));
	//get log dir
	sprintf(logFileDir, "%s", getenv("TEMP"));
	strcat(logFileDir, "\\tc_");
	strcat(logFileDir, userId);
	//printf("\n log file dir: %s\n", logFileDir);
	//try to change dir to TC_USER_LOG_DIR
	if (chdir(logFileDir) != ITK_ok)
	{
		//not set TC_USER_LOG_DIR
		//log in to default TC_LOG
		memset(logFileDir, 0, sizeof(logFileDir));
		sprintf(logFileDir, "%s", getenv("TC_LOG"));
		WriteLog(debug, "TC_USER_LOG_DIR invalide, log file dir: %s",logFileDir);
		//printf("\n TC_USER_LOG_DIR invalide, log file dir: %s\n", logFileDir);
		if (chdir(logFileDir) != ITK_ok)
		{
			//still can not change to log dir
			WriteLog(debug, "!*ERROR*!: Failed to change dir to TC_USER_LOG_DIR");
			//printf("!*ERROR*!: Failed to change dir to TC_USER_LOG_DIR\n");
			return -1;
		}
	}

	//get session_uid to make sure the log file name unique
	//POM_ask_session(&session_tag);
	//ITK__convert_tag_to_uid(session_tag, &session_uid);
	//get logFileName
	sprintf(logFileName, "%s_%s_%s.txt", FunctionName, userId, date_string);
	//printf("log file name: %s\n", logFileName);

	*fullname = (char *)MEM_alloc(sizeof(char) * 512);
	sprintf(*fullname, "%s\\%s", logFileDir, logFileName);

	//for(i = 0; _access((char *)logFileName, 4) == 0; i++)
	/*{
		memset(logFileName, 0, sizeof(logFileName));
		sprintf(logFileName, "%s_%s_%s_%d.log", FunctionName, session_uid, date_string, i);
	}
	printf("final log file name: %s\n", logFileName);*/

	//create log file
	*file = fopen(logFileName, "a");
	return ITK_ok;
//CLEANUP:;
	//DOFREE(date_string);
	/*if(session_uid!=NULL){
		MEM_free(session_uid);
		session_uid=NULL;
	}*/
}



/*=============================================================================*
 * FUNCTION: WriteLog
 * PURPOSE : write log, if debug log File not null, write log message to log File
 * INPUT:
 *     const char* format // debug message string
 *
 * RETURN:
 *     void
 *============================================================================*/
#define MAX_LOG_LENGTH 8000
void WriteLog(logical debug, const char* format, ...)
{
	va_list arg;
	char tmp[MAX_LOG_LENGTH];
	char date_string[MAX_LOG_LENGTH];
	time_t now;
	struct tm *p;
	//get the message
	memset(tmp, 0, sizeof(tmp));
	va_start(arg, format);
	vsprintf(tmp, format, arg);
	va_end(arg);
	//printf("%s\n", tmp);
	printf("%s\n", tmp);
	//print message to log file
	if (!debug) {
		return;
	}
	if (logFile)
	{
		time(&now);
		//current_time(&status_now);
		p = localtime(&now);
		memset(date_string, 0, sizeof(date_string));
		sprintf(date_string, "%02d:%02d:%02d", p->tm_hour, p->tm_min, p->tm_sec);
		fprintf(logFile, "[%s] %s\n", date_string, tmp);
		fflush(logFile);
	}
	else
	{
		ECHO("*!Error!*: Log File Not Exist\n");
	}
}

int WriteToFile(logical debug,FILE* file, const char* format, ...)
{
	va_list arg;
	char tmp[MAX_PRINTLINE_LENGTH];

	//get the message
	memset(tmp, 0, sizeof(tmp));
	va_start(arg, format);
	vsprintf(tmp, format, arg);
	va_end(arg);
	//print message to log file
	WriteLog(debug, "写入内容：%s", tmp);
	if (file)
	{
		fprintf(file, "%s", tmp);
		fflush(file);
		return ITK_ok;
	}
	else
	{
		WriteLog(debug,"写入文件失败，文件不存在");
		return -1;
	}
}


void WriteLog1(const char* txt)
{
	char date_string[MAX_PATH_LENGTH];
	time_t now;
	struct tm *p;
	time(&now);
	//current_time(&status_now);
	p = localtime(&now);
	memset(date_string, 0, sizeof(date_string));
	sprintf(date_string, "%02d:%02d:%02d", p->tm_hour, p->tm_min, p->tm_sec);

	if (logFile)
	{
		printf("%s\n", txt);
		//print message to log file
		fprintf(logFile, "[%s] %s\n", date_string, txt);
		fflush(logFile);
	}
	else
	{
		printf("*!Error!*: Log File Not Exist\n");
	}
}

void CloseLog(void)
{
	if (logFile)
	{
		fclose(logFile);
		logFile = NULL;
	}
}
