#ifndef EPM_REGISTER_HANDLER_CUSTOM
#define EPM_REGISTER_HANDLER_CUSTOM

#include <epm/epm.h>

#ifdef __cplusplus
extern "C" {
#endif

extern DLLAPI int USERSERVICE_custom_register_handlers(int *, va_list);
extern DLLAPI int USERSERVICE_custom_register_methods();
//	int Q7_ebom_to_pbom (void * returnValueType);

#ifdef __cplusplus
}
#endif

#endif 


/**
* @}
*/