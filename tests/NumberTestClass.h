#ifndef NUMBERTESTCLASS_H
#define NUMBERTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class NumberTestClass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(NumberTestClass);

    CPPUNIT_TEST(testOperatorPlus);
    CPPUNIT_TEST(testOperatorMinus);
    CPPUNIT_TEST(testOperatorMultiply);
    CPPUNIT_TEST(testOperatorDivide);
    
    CPPUNIT_TEST_SUITE_END();

public:
    NumberTestClass();
    virtual ~NumberTestClass();
    void setUp();
    void tearDown();

private:
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorMultiply();
    void testOperatorDivide();
};

#endif /* NUMBERTESTCLASS_H */

