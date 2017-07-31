/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ExpressionTestClass.h
 * Author: user
 *
 * Created on 31.07.2017, 20:04:57
 */

#ifndef EXPRESSIONTESTCLASS_H
#define EXPRESSIONTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class ExpressionTestClass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ExpressionTestClass);

    CPPUNIT_TEST(testMakeConstant);

    CPPUNIT_TEST_SUITE_END();

public:
    ExpressionTestClass();
    virtual ~ExpressionTestClass();
    void setUp();
    void tearDown();

private:
    void testMakeConstant();
};

#endif /* EXPRESSIONTESTCLASS_H */

