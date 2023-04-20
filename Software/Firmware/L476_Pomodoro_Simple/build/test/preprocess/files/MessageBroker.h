#include "User/MessageBroker/MessageTopics.h"
#include "User/Common/Common.h"






typedef struct

{

    MessageTopics_e eMsgTopic;

    uint16_t u16DataSize;

    uint8_t *au8DataBytes;

} MessageBroker_message_t;





typedef status_t (*Module_msgCallback_t)(MessageBroker_message_t in_sMessage);









typedef struct

{

    MessageTopics_e eMsgTopic;

    Module_msgCallback_t aCallbackArray[5];

} MessageBroker_msgDictinary_t;









status_t MessageBroker_init(void);



status_t MessageBroker_subscribe(

    MessageTopics_e in_eMsgTopic,

    Module_msgCallback_t in_p32FunctionCallback);



status_t MessageBroker_publish(MessageBroker_message_t in_tMessage);
