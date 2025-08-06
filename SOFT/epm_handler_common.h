
#ifndef EPM_HANDLER_COMMON
#define EPM_HANDLER_COMMON

#include <epm/epm.h>
#include <string>
#include <map>

#ifdef __cplusplus
extern "C" {
#endif
	using namespace std;
#define TC_specification	"IMAN_specification"
int T5_ERP_CONFIG(EPM_action_message_t msg);
int T5_BOP_INFORM(EPM_action_message_t msg);
int T5_EXPORT_BOM_XML(EPM_action_message_t msg);
int T5_FILL_WORKCENTER(EPM_action_message_t msg);
//int kos_pcb_sign(EPM_action_message_t msg);
int jf_signoff_dataset(EPM_action_message_t msg);
int k_fill_techform(EPM_action_message_t msg);
int k_sign_dataset(EPM_action_message_t msg);
int T5_SUBMIT_SCPZJ(EPM_action_message_t msg);
//518
int sign_rev_form(EPM_action_message_t msg);
int sign_rev_dataset(EPM_action_message_t msg);
#ifdef __cplusplus
}
#endif

#endif 

