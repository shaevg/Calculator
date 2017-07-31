#ifndef CALCULATORTESTCLASS_H
#define CALCULATORTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class CalculatorTestClass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CalculatorTestClass);

    CPPUNIT_TEST(testCheckExpression);

    CPPUNIT_TEST_SUITE_END();

public:
    CalculatorTestClass();
    virtual ~CalculatorTestClass();
    void setUp();
    void tearDown();

private:
    void testCheckExpression();
};

#endif /* CALCULATORTESTCLASS_H */

