#include <stdarg.h>
#include <tccore/custom.h>
#include <server_exits/user_server_exits.h>
#include "kutil.h"
#include <list>

#ifdef __cplusplus
extern "C" {
#endif

typedef list<tag_t> RetData;
typedef list<tag_t>::iterator RetDataIterator;
typedef map<string, string>   SearchCriterionInputs;
	
DLLAPI int USERSERVICE_custom_register_methods();
DLLAPI int K_invoke_pdm_server(int *decision, va_list args);
DLLAPI int USERSERVICE_custom_register_handlers(int* decision, va_list args);

int Get_New_ID(tag_t item_type_tag, string old_id, string suffix, string& new_item_id);
int CONNOR_SIGN_MASTER(EPM_action_message_t msg);
int CONNOR_SIGN_DATASET(EPM_action_message_t msg);
//int check_form_attribute(EPM_action_message_t msg);
//int check_owner(EPM_rule_message_t msg);
//int check_release(EPM_rule_message_t msg);
void map_insert(map < string, string >* strmap, string index, string x);
void init_search_criteria_map(string searchStr, SearchCriterionInputs& searchCriteria);
void init_search_criteria_vector(string searchStr, vector<string>& propNames, vector<string>& propValues);
int Parse_NX_Template_By_ID(const std::string& itemID, std::string& res);
int Read_NX_Image_By_ID(const std::string& itemID, std::string& res);
int Download_Dataset_By_UID(const std::string& itemID, std::string& res);
int Get_All_SubTypes(const std::string& typeName, std::string& res);
int SEARCH_AUTOCODE_NODE(const std::string& typeName, std::string& res);
int Get_Uid(const std::string& name, std::string& res);
int SEARCH_AUTOCODE_SEGMENT(const std::string& searchStr, std::string& res);
int SEARCH_AUTOCODE_USER(const std::string& searchStr, std::string& res);
int GET_TREE_AND_LIST_STRING_VALUE(const std::string& searchStr, std::string& res);
int GET_NEW_REV_ID(const std::string& typeNameStr, std::string& res);
int GET_LOGICAL_PROP_VALUE(const std::string& str, std::string& res);
int SEARCH_TREE_OR_LIST_NODE(const std::string& searchStr, std::string& res);
int GET_TREE_AND_LIST_STRING_VALUES(const std::string& searchStr, std::string& res);
int SEARCH_PARENT_TREE_OR_LIST_NODE(const std::string& searchStr, std::string& res);
int ICS_GET_ATTRIBUTES(const std::string& str, std::string& res);
int ICS_ATTR_IS_REFERENCE_ATTRIBUTE(const std::string& str, std::string& res);
int ICS_ATTR_ASK_PROPERTY(const std::string& str, std::string& res);
int ICS_ATTR_ASK_KEYLOV(const std::string& str, std::string& res);
int GET_DISPLAY_PROP_VALUE(const std::string& str, std::string& res);
int FIND_LOV_BY_NAME(const std::string& str, std::string& res);
int GET_REFERENCE_PROP_VALUE(const std::string& str, std::string& res);
int QUERY_PART_NO(const std::string& str, std::string& res);
int DELETE_RECYCLE_ID(const std::string& str, std::string& res);
int ITEM_EXIST(const std::string& str, std::string& res);
int ITEM_CREATE(const std::string& str, std::string& res);
int ADD_TO_NEWSTUFF(const std::string& uid, std::string& res);
int GET_CLASSIFICATION_ID(const std::string& uid, std::string& res);
int SEND_ITEM_TO_CLASSIFICATION(const std::string& str, std::string& res);
int GET_ITEMTYPE_BY_ID(const std::string& item_id, std::string& res);
int GET_REVUID_BY_ID(const std::string& item_id, std::string& res);
int ITEM_UPDATE(const std::string& str, std::string& res);
int READ_NX_TEMPLATE_BOM(const std::string& itemID, std::string& res);
int GET_CLONE_INFO(const std::string& uid, std::string& res);
int GET_LATEST_ITEM_REVISION(const std::string& str, std::string& res);
int GRANT_PRIVILEGE(const std::string& str, std::string& res);
int GET_UOM_TAGS(const std::string& str, std::string& res);
int UPDATE_UOM(const std::string& str, std::string& res);
int GET_REFERENCE_PROP_VALUE_ARRAY(const std::string& str, std::string& res);
int ICS_ATTR_ASK_METRIC_UNIT(const std::string& str, std::string& res);

#define debug true
#define OUTPUT_CODE_ERROR -1
#define SPLITTER "&;&"
#define SPLIT_SECTION "&SECTION&"
#define SPLIT_PROP_STR "&PROP&"
#define SPLIT_PROP_NAME_VALUE "&=&"

#ifdef __cplusplus
}
#endif

