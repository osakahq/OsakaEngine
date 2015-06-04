 #include "stdafx.h"
#include "osaka_forward.h"

#ifndef TESTSUITE_TESTSUITEMACRO_H
#define TESTSUITE_TESTSUITEMACRO_H

/* If you use this global variable, make sure to call `OsakaAssertEnd` */
extern Osaka::TestSuite::RPGLibTestSuitePTR ASSERT_RPGLibTestSuitePTR;

void OsakaAssertBegin(Osaka::TestSuite::RPGLibTestSuitePTR& ptr);
/* This is the global function, you can call anywhere */
void OsakaAssert(const bool test, const int cline, const char* cfile);
void OsakaAssertEnd();

/* This is a macro for less writting. */
#define OSAKA_ASSERT(test) OsakaAssert((test), __LINE__, __FILE__)

#endif