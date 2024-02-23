#include "Encoder.h"
#include "MessageBroker.h"
#include "Encoder_Hardware.h"

status_e Encoder_messageCallback(const msg_t *const in_psMsg)
{
    ASSERT_MSG(!(in_psMsg == NULL), "in_psMsg is NULL");
    ASSERT_MSG(!(in_psMsg->eMsgId != MSG_0600), "Invalid Message");
    if (in_psMsg->eMsgId != MSG_0600)
    {
        return STATUS_ERROR;
    }

    // Reset the Encoder Value
    Encoder_Hardware_resetEncoderValue();
    return STATUS_SUCCESS;
}

void Encoder_init()
{

    // Initialize the hardware
    Encoder_Hardware_init();

    // Subscribe to the Reset Encoder Value message
    MessageBroker_subscribe(MSG_0600, &Encoder_messageCallback);

    // Reset the Encoder Value
    Encoder_Hardware_resetEncoderValue();
}

void Encoder_execute()
{
    int32_t s32EncoderValue = 0;

    // Get the Encoder value
    Encoder_Hardware_getCurrentEncoderValue(&s32EncoderValue);

    // Publish the Encoder Value Changed message with the current value
    msg_t sMsg;
    sMsg.eMsgId = MSG_0601;
    uint8_t au8DataBytes[4];
    au8DataBytes[0] = (uint8_t)s32EncoderValue;
    au8DataBytes[1] = (uint8_t)(s32EncoderValue >> 8);
    au8DataBytes[2] = (uint8_t)(s32EncoderValue >> 16);
    au8DataBytes[3] = (uint8_t)(s32EncoderValue >> 24);
    sMsg.au8DataBytes = au8DataBytes;
    sMsg.u16DataSize = 4;
    status_e eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus != STATUS_SUCCESS), "Failed to publish Encoder Value Changed message");
}
