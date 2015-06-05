 #include "stdafx.h"

#include "RPGLibTestSuite.h"
#include "_testsuite_macro.h"

/* _OSAKA_ASSERT is NOT the owner of this one. Make sure to all `OsakaAssertEnd` */
Osaka::TestSuite::RPGLibTestSuitePTR ASSERT_RPGLibTestSuitePTR = nullptr;

void OsakaAssertBegin(Osaka::TestSuite::RPGLibTestSuitePTR& ptr){
	ASSERT_RPGLibTestSuitePTR = ptr;
}
void OsakaAssert(const bool test, const int cline, const char* cfile){
	ASSERT_RPGLibTestSuitePTR->MakeAssert(test, cline, cfile);
}
void OsakaAssertEx(const int id, const bool test, const int cline, const char* cfile){
	ASSERT_RPGLibTestSuitePTR->MakeAssertEx(id, test, cline, cfile);
}
void OsakaAssertEnd(){
	//Since we are not the owner, we only set it to `nullptr`
	ASSERT_RPGLibTestSuitePTR = nullptr;
}