#include "nimbly/experimental/tests/flexbit_tests.hpp"

const int TENMILL = 10000000;
const int ONEHUND = 100;

void TestSuite_FlexBit::load_tests()
{
    if (testmanager == nullptr)
    {
        return;
    }

    register_test("N-tB052",new TestFlexBit_Push(ONEHUND));
    register_test("N-tS052", new TestFlexBit_Push(TENMILL), false);

    register_test("N-tB053", new TestFlexBit_Peek());

    register_test("N-tB054", new TestFlexBit_Poll(ONEHUND));
    register_test("N-tS054", new TestFlexBit_Poll(TENMILL), false);

    register_test("N-tB051",new TestFlexBit_ToString(ONEHUND));
    register_test("N-tS051",new TestFlexBit_ToString(TENMILL), false);

}
