#include "unity.h"
#include "Executer.h"
#include "StandbyControl.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Executer_init_ShouldInitializeAllModules(void)
{
    StandbyControl_init();
}

void test_Executer_execute_should_ExecuteAllModules(void)
{
    StandbyControl_execute();
}
