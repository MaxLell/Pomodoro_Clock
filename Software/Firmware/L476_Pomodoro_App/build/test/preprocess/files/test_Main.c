#include "App/Main/Main.h"
#include "build/test/mocks/mock_Executer.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_Main_Should_InitializeTheDriversThenCallMainLoop(void)

{

    Executer_init_CMockExpect(15);



    Executer_exec_CMockExpectAndReturn(17, (0));

    Executer_exec_CMockExpectAndReturn(18, (0));

    Executer_exec_CMockExpectAndReturn(19, (255));



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((testableMain())), (((void*)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

}
