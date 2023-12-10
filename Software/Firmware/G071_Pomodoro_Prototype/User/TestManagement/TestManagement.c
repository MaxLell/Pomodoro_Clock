#include "TestManagement.h"

#include "MessageBroker.h"

status_t TestManagement_MessageCb(msg_t sMsg) {
  switch (sMsg.eMsgId) {
    case MSG_ID_0100:
      log_info("Button was pressed once");
      break;
    case MSG_ID_0300:
      log_info("RTC: 1 Second Tick");
      break;
    default:
      ASSERT_MSG(false, "Unknown Message ID");
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
