#include "nimbly/tests/flexstack_tests.hpp"

const int ONETHOU = 1000;
const int HUNTHOU = 100000;

void TestSuite_FlexStack::load_tests()
{
    register_test("N-tB0301", new TestFStack_Push(ONETHOU), true, new TestSStack_Push(ONETHOU));
    register_test("N-tS0301", new TestFStack_Push(HUNTHOU), false);

    register_test("N-tB0302", new TestFStack_Peek());

    register_test("N-tB0303", new TestFStack_Pop(ONETHOU), true, new TestSStack_Pop(ONETHOU));
    register_test("N-tS0303", new TestFStack_Pop(HUNTHOU), false);
}
