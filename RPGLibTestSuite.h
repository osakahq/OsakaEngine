 #include "stdafx.h"

#ifndef TESTSUITE_RPGLIBTESTSUITE_H
#define TESTSUITE_RPGLIBTESTSUITE_H
#include "osaka_forward.h"

namespace Osaka{
	
	namespace TestSuite{
		using namespace RPGLib;

		class RPGLibTestSuite{
		public:
			RPGLibTestSuite();
			~RPGLibTestSuite();
			void _delete();
			/* This funcion calls all the tests */
			void RunTests();
			/* This function must be called in order to show fail/success */
			void MakeAssert(const char* test, bool passed);
			/* Check if test any has failed. `MakeAssert` must be called */
			void End();

			//For individual call testing
			void TestLoadGameFile(bool verbose);

			/* Owner */
			Debug::DebugPTR	debug;
		private:
			//Count. You must have `MakeAssert`
			int failedTests;
			int succesfulTests;

			/* This inits call rpg_bootstrap.
			 * I have to make sure that any of the constructor's/Init's function DON'T something */
			void Init(const char* datafile, const char* settingsfile, const char* pack_file);

			/* Owner */
			RPGApplicationPTR	rpgapp;
		};
	}
}
#endif;