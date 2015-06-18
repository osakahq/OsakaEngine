 #include "stdafx.h"

#ifndef TESTSUITE_RPGLIBTESTSUITE_H
#define TESTSUITE_RPGLIBTESTSUITE_H

#define ASSERTEX_NOTCALLED 0
#define ASSERTEX_FAIL 1
#define ASSERTEX_SUCCESS 2

#include <osaka_forward.h>

namespace Osaka{
	namespace TestSuite{
		using namespace RPGLib;

		struct TEST_PHASE{
			TEST_PHASE(){}
			enum Value{
				PHASE1 = 1, PHASE2 = 2
			};
		};

		class RPGLibTestSuite{
		public:
			RPGLibTestSuite();
			~RPGLibTestSuite();
			
			/* This funcion calls all the tests */
			void Run(TEST_PHASE::Value phase);
			/* This function must be called in order to show fail/success */
			void MakeAssert(const bool test, const int cline, const char* cfile);
			void MakeAssertEx(const int id, const bool test, const int cline, const char* cfile);
			/* Check if test any has failed. `MakeAssert` must be called */
			void CheckResults();

			/* Individual tests. */
			void IndividualTest_LoadGameFileTest(const char* filedata, bool verbose);

			/* Owner */
			Debug::Debug*	debug;
		private:
			//Count. You must have `MakeAssert`
			int failedTests;
			int succesfulTests;

			/* This is a list of the expected tests. (with OSAKA_ASSERT_EX(...)) 
			 * int = id of test, int = result */
			std::unordered_map<int, int> expectedTests;
			void AddExpectedTests(int size, int* array_ids);

			/* Owner */
			RPGApplication*	rpgapp;
		};
	}
}
#endif;