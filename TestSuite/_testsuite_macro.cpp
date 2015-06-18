 #include "stdafx.h"

#include "RPGLibTestSuite.h"
#include "_testsuite_macro.h"

/* _OSAKA_ASSERT is NOT the owner of this one. Make sure to all `OsakaAssertEnd` */
Osaka::TestSuite::RPGLibTestSuite* ASSERT_RPGLibTestSuite = NULL;

void OsakaAssertBegin(Osaka::TestSuite::RPGLibTestSuite* ptr){
	ASSERT_RPGLibTestSuite = ptr;
}
void OsakaAssert(const bool test, const int cline, const char* cfile){
	ASSERT_RPGLibTestSuite->MakeAssert(test, cline, cfile);
}
void OsakaAssertEx(const int id, const bool test, const int cline, const char* cfile){
	ASSERT_RPGLibTestSuite->MakeAssertEx(id, test, cline, cfile);
}
void OsakaAssertEnd(){
	//Since we are not the owner, we only set it to `nullptr`
	ASSERT_RPGLibTestSuite = NULL;
}