#include<stdio.h>
#include <string>
#include<iostream> 
#include <vector>
#include <map>
#include <list>


//tc
#include<tccore\custom.h>
#include<tc\tc_macros.h>
#include<tccore\aom.h>
#include<ict\ict_userservice.h>
#include<fclasses\tc_string.h>
#include<property\prop.h>
#include<tccore\item.h>
#include<tc\iman.h>

#include <tccore\aom_prop.h>
#include <epm\epm.h>
#include <tccore\grm.h>
#include <sa\am.h>
#include <ps\ps.h>
#include <time.h>
#include <tccore\grmtype.h>
#include "origin_PropNames.h"
#include <pom/enq/enq.h>

#include<tc\preferences.h>


using namespace std;

//#include <libuserext_exports.h>
#ifdef __cplusplus
extern "C" {
#endif

#define GET_ID_RETRIES  10
#define CYCLE_TIMES   10
#define STARTNUMBER  1
#define PADNUMBER  4
#define RETRY_STRING   "10"
#define HANDLE_ERROR_S1(E,S) \
	{ EMH_store_initial_error_s1(EMH_severity_error,(E),(S)); return(E); }

#define REPORT_IFAIL(M) \
	ifail?printf("%s : ERROR : ifail = %d\n",M,ifail):printf("%s : Ok\n",M)

#define HANDLE_ERROR(E) \
	{ EMH_store_initial_error(EMH_severity_error,(E)); return(E); }

#define HANDLE_ERROR_S1(E,S) \
	{ EMH_store_initial_error_s1(EMH_severity_error,(E),(S)); return(E); }

#define HANDLE_ERROR_AND_RELEASE(E,I) \
	{ \
	(void)release_number(I); \
	EMH_store_initial_error(EMH_severity_error,(E)); \
	return(E); \
}

#define TEST_ERROR(E) \
	if ((E) != ITK_ok) return(E);

#define TEST_POM_ERROR(E) \
	if ((E) != ITK_ok) HANDLE_ERROR(E)

#define TEST_ERROR_AND_RELEASE(E,I) \
	if ((E) != ITK_ok) { (void)release_number(I); return(E); }

	/* Define the number of retries when fetching the next ID. */
	/* This must be stored in both numeric and string forms.   */
#define GET_ID_RETRIES  10
#define RETRY_STRING   "10"

	/* Empty string test macro */
#define IS_EMPTY(S)  (!(*(S)))

	/* Define the methods by which a new item name can be obtained */
#define SEED_METHOD   0
#define BUILD_METHOD  1

	/* The following define the maximum index number to be used.  *
	* Note that the actual maximum is one less than MAXNUM.      *
	* NUMERIC_LIMIT must be large enough to store decimal string *
	* version of MAXNUM plus a NULL terminator.  */
#define NUMERIC_LIMIT   12
#define MAXNUM          0x7FFFFFFF
	/* define the class for which id and rev is generated */
#define CLASS_IS_ITEM       0
#define CLASS_IS_DATASET    1

#define origin_autocode_sequence_exclude_number "origin_autocode_sequence_exclude_number"

	tag_t getCurrentUser();
	char* filterChar(string str, string  filterStr);
	date_t	getCurrentDate();
	void map_insert(map < string, string >* strmap, string index, string x);
	int select_id_counter(const char* id_counter, int next_id, tag_t* id_counter_tag, logical* is_new);
	int load_current_number(tag_t id_counter_tag, const char* id_counter, int* next_id, logical* is_new);
	//int load_current_number(tag_t id_counter_tag, const char *id_counter, int *next_id, logical *is_new);
	int get_sequence_no(const char* pattern_code, int length, int start_index, int end_index, int step, int* new_id, const char* code_exclude_character);
	int generate_num(const char* pattern_code, int length, int new_index, char** generated_num);
	int  filterItemID(const char* filterStr, int new_id);
	int  isContainsStr(char* sourceStr, char* containsStr);
#ifdef __cplusplus
}
#endif