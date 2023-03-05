#include "unity.h"
#include "mock_Executer.h"
#include "Main.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Main_Should_InitializeTheDriversThenCallMainLoop(void)
{
    Executer_init_Expect();

    Executer_exec_ExpectAndReturn(STATUS_OK);
    Executer_exec_ExpectAndReturn(STATUS_OK);
    Executer_exec_ExpectAndReturn(STATUS_UNKNOWN_ERR);

    TEST_ASSERT_EQUAL(0, testableMain());
}