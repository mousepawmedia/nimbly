#include "nimbly/tests/flexqueue_tests.hpp"

const int ONETHOU = 1000;
const int HUNTHOU = 100000;

void TestSuite_FlexQueue::load_tests()
{
    register_test("N-tB0201", new TestFQueue_Push(ONETHOU), true,  new TestSQueue_Push(ONETHOU));
    register_test("N-tS0201", new TestFQueue_Push(HUNTHOU), false);

    register_test("N-tB0202", new TestFQueue_Peek());

    register_test("N-tB0203", new TestFQueue_Pop(ONETHOU), true, new TestSQueue_Pop(ONETHOU));
    register_test("N-tS0203", new TestFQueue_Pop(HUNTHOU), false);
}
