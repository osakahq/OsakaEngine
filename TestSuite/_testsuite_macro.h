 #include "stdafx.h"

#ifndef TESTSUITE_TESTSUITEMACRO_H
#define TESTSUITE_TESTSUITEMACRO_H

#include "idtests.h"

namespace Osaka{
	namespace TestSuite{
		class RPGLibTestSuite;
	}
}

/* NOT Owner. If you use this global variable, make sure to call `OsakaAssertEnd` */
extern Osaka::TestSuite::RPGLibTestSuite* ASSERT_RPGLibTestSuite;

void OsakaAssertBegin(Osaka::TestSuite::RPGLibTestSuite* ptr);
/* This is the global function, you can call anywhere */
void OsakaAssert(const bool test, const int cline, const char* cfile);
/* Expect. */
void OsakaAssertEx(const int id, const bool test, const int cline, const char* cfile);
void OsakaAssertEnd();

/* This is a macro for less writting. */
#define OSAKA_ASSERT(test) OsakaAssert((test), __LINE__, __FILE__)
#define OSAKA_ASSERTEX(id, test) OsakaAssertEx((id),(test), __LINE__, __FILE__)

#endif