#include "Executer.h"

#include "Button.h"
#include "MessageBroker.h"
#include "RealTimeClock.h"
#include "StandbyControl.h"
#include "TestManagement.h"

/**
 * @brief  This function initializes the modules used in the program.
 */
void Executer_init(void) {}

/**
 * @brief  The main execution steps are run in this function.
 */
status_t Executer_execute(void) { return STATUS_OK; }

/**
 * This function is called from the main() function in main.c.
 * It is the main execution loop of the program.
 * The reason why the execution is built like this, is because
 * with this way a unit test framework run the main execution task
 * one step at a time. This is useful for debugging and testing.
 */
void Executer_run(void) {
  Executer_init();
  while (Executer_execute() == STATUS_OK) {
    /**
     * The main execution steps are run in the Executer_execute() function.
     */
  }
  ASSERT_MSG(NULL, "shall never reached");
}