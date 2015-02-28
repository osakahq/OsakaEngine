 #include "stdafx.h"

#ifndef TESTSUITE_RPGLIBTESTSUITE_H
#define TESTSUITE_RPGLIBTESTSUITE_H
#include "osaka_forward.h"

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
			void _delete();

			/* This funcion calls all the tests */
			void Run(TEST_PHASE::Value phase);
			/* This function must be called in order to show fail/success */
			void MakeAssert(const bool test, const int cline, const char* cfile);
			/* Check if test any has failed. `MakeAssert` must be called */
			void CheckResults();

			/* Individual tests. */
			void IndividualTest_LoadGameFileTest(const char* filedata, bool verbose);

			/* Owner */
			Debug::DebugPTR	debug;
		private:
			//Count. You must have `MakeAssert`
			int failedTests;
			int succesfulTests;

			/* Owner */
			RPGApplicationPTR	rpgapp;
		};
	}
}
#endif;