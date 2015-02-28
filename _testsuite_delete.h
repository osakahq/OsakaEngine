#ifndef TESTSUITE_CHECKDELETE_H
#define TESTSUITE_CHECKDELETE_H
//namespace std{
//	class string;
//}
#ifdef _DEBUG
	void _STARTCHECKDELETE(bool ascension);
	void _CHECKDELETE(std::string classname, bool deconstructor = true);
	void _ENDCHECKDELETE();
#endif

#endif