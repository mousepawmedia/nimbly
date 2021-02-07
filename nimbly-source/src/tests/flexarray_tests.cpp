#include "nimbly/tests/flexarray_tests.hpp"

const int ONETHOU = 1000;
const int HUNTHOU = 100000;
//const int TENMIL = 10,000,000; // for stress testing

void TestSuite_FlexArray::load_tests()
{
    //Benchmark test section for "Push" function (flexarray vs. vector)
    //push at end
    register_test("N-tB0101", new TestFArray_Push(ONETHOU), true, new TestVector_Push(ONETHOU));
    register_test("N-tS0101", new TestFArray_Push(HUNTHOU), false);

    //Benchmark test section for "Shift" function (flexarray vs. vector)
    //push at front
    register_test("N-tB0102", new TestFArray_Shift(ONETHOU), true, new TestVector_Shift(ONETHOU));
    register_test("N-tS0102", new TestFArray_Shift(HUNTHOU), false);

    //Benchmark test section for "Insert" function (flexarray vs. vector)
    //insert at middle
    register_test("N-tB0103", new TestFArray_Insert(ONETHOU), true, new TestVector_Insert(ONETHOU));
    register_test("N-tS0103", new TestFArray_Insert(HUNTHOU), false);

    register_test("N-tB0104", new TestFArray_Yank(ONETHOU), true, new TestVector_Yank(ONETHOU));
    register_test("N-tS0104", new TestFArray_Yank(HUNTHOU), false);

    register_test("N-tB0105", new TestFArray_Unshift(ONETHOU), true, new TestVector_Unshift(ONETHOU));
    register_test("N-tS0105", new TestFArray_Unshift(HUNTHOU), false);

    register_test("N-tB0106", new TestFArray_Pop(ONETHOU), true, new TestVector_Pop(ONETHOU));
    register_test("N-tS0106", new TestFArray_Pop(HUNTHOU), false);

    register_test("N-tB0107", new TestFArray_Erase(ONETHOU), true, new TestVector_Erase(ONETHOU));
    register_test("N-tS0107", new TestFArray_Erase(HUNTHOU), false);

    register_test("N-tB0108", new TestFArray_Peek(), true, new TestVector_Peek());

    register_test("N-tB0109", new TestFArray_Contained(), true);
    register_test("N-tB0110", new TestFArray_SharedPtr(), true);
    register_test("N-tB0111", new TestFArray_UniquePtr(), true);
}
