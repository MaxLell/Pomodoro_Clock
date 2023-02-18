#include "App/Support/Common.h"






typedef enum

{

    E_TEST_1 = 0U,

    E_TEST_2,

    E_TRIGGER_BUTTON_EVENT,

} MessageBroker_messageTopics_e;



typedef struct

{

    MessageBroker_messageTopics_e eMsgTopic;

    uint16_t u16DataSize;

    uint32_t *au32Data;

} MessageBroker_message_t;





typedef status_t (*Module_msgCallback_t)(MessageBroker_message_t in_sMessage);









typedef struct

{

    MessageBroker_messageTopics_e eMsgTopic;

    Module_msgCallback_t aCallbackArray[5];

} MessageBroker_msgDictinary_t;









status_t MessageBroker_init(void);



status_t MessageBroker_subscribe(

    MessageBroker_messageTopics_e in_eMsgTopic,

    Module_msgCallback_t in_p32FunctionCallback);



status_t MessageBroker_publish(MessageBroker_message_t in_tMessage);