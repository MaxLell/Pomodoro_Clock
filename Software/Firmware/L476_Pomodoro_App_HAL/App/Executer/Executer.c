#include "Executer.h"

#include "BlinkyLed.h"
#include "Button_Conductor.h"
#include "MessageBroker.h"

void Executer_init(void) { BlinkyLed_init(); }

status_t Executer_exec(void) { return STATUS_OK; }
