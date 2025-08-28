#ifndef COMMON_ITK_UTIL
#define COMMON_ITK_UTIL

#ifdef __cplusplus
extern "C" {
#endif

#define DOFREE(obj)								\
{												\
	if(obj)										\
	{											\
		MEM_free(obj);							\
		obj = NULL;								\
	}											\
}
	void ECHO(char *format, ...);
	void CreateLogFile(char* FunctionName, char *userId, char **fullname);
	void CreateFileName(char* FunctionName, char *userId, char **fullname);
	void CreateTempFileName(char*preFix, const char* FunctionName, char *ext, char *userId, char **fullname, char **fileName);
	void WriteLog(logical debug,const char* format, ...);
	void WriteLog1(const char* txt);
	void initUserDir(char *userId);
	//void initUserDir(char *userId,char **dir);
	void CloseLog(void);
	void set_bypass(logical bypass);
	int ORIGIN_close_bypass(void *returnValue);
	int ORIGIN_set_bypass(void *returnValue);
	int GetLocalizedType(void * return_data);
	int WriteToFile(logical debug, FILE* file, const char* format, ...);
	int CreateUserFile(logical debug, char* FunctionName, char *userId, char **fullname, FILE **file);

#ifdef __cplusplus
}
#endif

#endif