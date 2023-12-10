#include "TestManagement.h"

#include "MessageBroker.h"
#include "MessageDefinitions.h"

status_t TestManagement_MessageCb(msg_t sMsg) {
  switch (sMsg.eMsgId) {
    case MSG_ID_0100:
      log_info("Button was pressed once");
      break;
    case MSG_ID_0300:
      TimeAndDate_t *psTimeAndDate = (TimeAndDate_t *)sMsg.au8DataBytes;
      log_info("Time: %02d:%02d:%02d", psTimeAndDate->u8Hour,
               psTimeAndDate->u8Minute, psTimeAndDate->u8Second);
      log_info("------");
      log_info("Date: %02d.%02d.%02d", psTimeAndDate->u8Day,
               psTimeAndDate->u8Month, psTimeAndDate->u8Year);
      break;
    default:
      ASSERT_MSG(FALSE, "Unknown Message ID");
      break;
  }
  return STATUS_OK;
}

void TestManagement_init(void) {
  MessageBroker_subscribe(MSG_ID_0100, TestManagement_MessageCb);
  MessageBroker_subscribe(MSG_ID_0300, TestManagement_MessageCb);
}

void TestManagement_execute(void) {
  // Do nothing and wait around until better stuff is to be done
}
