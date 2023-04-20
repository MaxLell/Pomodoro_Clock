#include "MessageBroker.h"

/**
 * Message 2010, 0204
 * This is only a dummy message for experimentation.
 * You manually need to set these topics here up.
 */
#ifdef TEST
STATIC MessageBroker_msgDictinary_t sTestTopic_1;
STATIC MessageBroker_msgDictinary_t sTestTopic_2;
#endif
/**
 * The Message Topics are defined here
 */
STATIC MessageBroker_msgDictinary_t sTopicTriggerButton;
STATIC MessageBroker_msgDictinary_t sTopicCurrentMinute;
STATIC MessageBroker_msgDictinary_t sTopicOnSecondPassed;
STATIC MessageBroker_msgDictinary_t sTopicPomodoroFsmStateChanged;
STATIC MessageBroker_msgDictinary_t sTopicLctrlStateChanged;
STATIC MessageBroker_msgDictinary_t sTopicTimeAndDate;

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC MessageBroker_msgDictinary_t *sMessageTopicIndex[E_TOPIC_LAST_TOPIC] = {NULL};

status_t MessageBroker_init()
{

#ifdef TEST
    /* Set the Topics of the respective messages */
    sTestTopic_1.eMsgTopic = E_TEST_1;
    sTestTopic_2.eMsgTopic = E_TEST_2;
    /* Place the different topics / message types in the Library */
    sMessageTopicIndex[E_TEST_1] = &sTestTopic_1;
    sMessageTopicIndex[E_TEST_2] = &sTestTopic_2;
#endif
    /* Set the Topics of the respective messages */
    sTopicTriggerButton.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;
    sTopicCurrentMinute.eMsgTopic = E_TOPIC_CURRENT_MINUTE;
    sTopicOnSecondPassed.eMsgTopic = E_TOPIC_ONE_SECOND_PASSED;
    sTopicPomodoroFsmStateChanged.eMsgTopic = E_TOPIC_PFSM_STATE_CHANGED;
    sTopicLctrlStateChanged.eMsgTopic = E_TOPIC_LCTRL_STATE_CHANGED;
    sTopicTimeAndDate.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    /* Place the different topics / message types in the Library */
    sMessageTopicIndex[E_TOPIC_TRIGGER_BUTTON_PRESSED] = &sTopicTriggerButton;
    sMessageTopicIndex[E_TOPIC_CURRENT_MINUTE] = &sTopicCurrentMinute;
    sMessageTopicIndex[E_TOPIC_ONE_SECOND_PASSED] = &sTopicOnSecondPassed;
    sMessageTopicIndex[E_TOPIC_PFSM_STATE_CHANGED] = &sTopicPomodoroFsmStateChanged;
    sMessageTopicIndex[E_TOPIC_LCTRL_STATE_CHANGED] = &sTopicLctrlStateChanged;
    sMessageTopicIndex[E_TOPIC_TIME_AND_DATE] = &sTopicTimeAndDate;

    /* set all the elements of the Callback arrays to zero */
    for (uint16_t topic = 0; topic < E_TOPIC_LAST_TOPIC; topic++)
    {
        for (uint16_t index = 0; index < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; index++)
        {
            sMessageTopicIndex[topic]->aCallbackArray[index] = 0;
        }
    }

    return STATUS_OK;
}

status_t MessageBroker_subscribe(
    MessageTopics_e in_eMsgTopic,
    Module_msgCallback_t in_p32FunctionCallback)
{

    /* Run the Null Pointer checks */
    check(NULL != in_p32FunctionCallback, "input function pointer is NULL");

    uint16_t u16EmptyPointerPositionIndex = 0;
    for (uint16_t u16ArrayIndex = 0; u16ArrayIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u16ArrayIndex++)
    {
        /* Find the first element in the callback array, that is not equal 0 */
        if (sMessageTopicIndex[in_eMsgTopic]->aCallbackArray[u16ArrayIndex] == 0)
        {
            u16EmptyPointerPositionIndex = u16ArrayIndex;
            break;
        }
    }
    if (u16EmptyPointerPositionIndex == (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1))
    {
        log_warning("Callback Array for Topic %d is full. This is the last possible subscription!", in_eMsgTopic);
    }
    sMessageTopicIndex[in_eMsgTopic]->aCallbackArray[u16EmptyPointerPositionIndex] = in_p32FunctionCallback;
    return STATUS_OK;

error:
    return STATUS_NULL_POINTER;
}

status_t MessageBroker_publish(MessageBroker_message_t in_tMessage)
{
    /* find the dictinary that corresponds to the message's Topic */
    MessageTopics_e eTopic = in_tMessage.eMsgTopic;

    /* Run all the Callback functions there are in the Callback Array and pass the Message over */
    for (uint8_t u8CallbackIndex = 0; u8CallbackIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u8CallbackIndex++)
    {
        if (sMessageTopicIndex[eTopic]->aCallbackArray[u8CallbackIndex] != NULL)
        {
            /* Run the function pointers and provide the specified argument */
            sMessageTopicIndex[eTopic]->aCallbackArray[u8CallbackIndex](in_tMessage);
        }
    }
    return STATUS_OK;
}