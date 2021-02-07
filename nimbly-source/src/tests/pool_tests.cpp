#include "nimbly/tests/pool_tests.hpp"

void TestSuite_Pool::load_tests()
{
    register_test("N-tB0401",
        new TestPool_ThriceFill(), true, new TestPool_ThriceFillAlloc());

    register_test("N-tB0402",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::DFLT));
    register_test("N-tB0403",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::COPY));
    register_test("N-tB0404",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::DFLT_FAILSAFE));
    register_test("N-tB0405",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::COPY_FAILSAFE));

    register_test("N-tB0406",
        new TestPool_Access());

    register_test("N-tB0407",
        new TestPool_Access());

    register_test("N-tB0408",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_FULL_ASGN));
    register_test("N-tB0409",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_FULL_ASGN_CPY));
    register_test("N-tB040A",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_ACC_DELETED_REF));
    register_test("N-tB040B",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_DES_FOREIGN_REF));
    register_test("N-tB040C",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_DES_DELETED_REF));
    register_test("N-tB040D",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_DES_FOREIGN_REF));
}
