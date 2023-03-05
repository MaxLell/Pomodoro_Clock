#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
#include "App/Support/DbgMacros.h"


void setUp(void) {}



void tearDown(void) {}



void test_DbgMacros_can_assert_true_captureFaults() {

  int result = ((1 == 1 == 1) ? (void)0U : DbgMacros_error((char*)"test/App/test_DbgMacros.c", 9));

  printf("[INFO]  (%s:%d) " "%d" "\n", "test/App/test_DbgMacros.c", 10, result);

}
