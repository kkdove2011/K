
char* G2U(const char* gb2312);
int getPrefStrings(const char *preference, TC_preference_search_scope_t scope, vector<string> &pref_vec);
int export_dataset_file(bool debug, tag_t dataset,const char *ref_name,char *userId, char *ext, char **filename, char **original_name);
int GetBomView(tag_t rev_tag, char* viewtype, tag_t *bomView, tag_t *bomBVR, int debug);
int GetBomLinePropString(bool debug, tag_t line, char* propName, int errCode, char** attr_val);
void Split(string strArg, char spliter, vector<string> &ans);
int import_dataset_file(tag_t dataset, const char *ref_name, char *ext, char *fullfilename, char *original_name);
int import_dataset_file_binary(tag_t dataset, const char *ref_name, char *ext, char *fullfilename, char *original_name);
int readError(bool debug, char *errFilePath, int errCode);
void deleteFile(bool debug, char *path);
bool CheckType(string config, char* type, char spliter);
bool propExist(bool debug, tag_t obj, const char *propName);
bool isRev(char* object_type);