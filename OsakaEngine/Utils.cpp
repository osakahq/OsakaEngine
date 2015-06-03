 #include "stdafx.h"
#include <sys/stat.h>

namespace Osaka{
	namespace Utils{
		
		//Source: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
		template<int (&F)(int)> int _safe_ctype(unsigned char c) { return F(c); }
		/* I'm not sure how to put it directly into the s.erase function */
		int _isspace_wrapper(int c) {
			return _safe_ctype<std::isspace>(c);
			/*if(c <= int(UCHAR_MAX) && c >= 0){ /*error* }
			return std::isspace(c);*/
		}
		std::string &TrimString(std::string &s) {
			//s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			//s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(_isspace_wrapper))).base(), s.end());
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(_isspace_wrapper))));
			return s;
		}

		//Source: http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
		//Source: http://stackoverflow.com/questions/9378500/why-is-splitting-a-string-slower-in-c-than-python
		void SplitString(std::vector<std::string> &tokens, const std::string &str, const std::string &delimiters = " "){
			// Skip delimiters at beginning
			std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

			// Find first non-delimiter
			std::string::size_type pos = str.find_first_of(delimiters, lastPos);

			while (std::string::npos != pos || std::string::npos != lastPos) {
				// Found a token, add it to the vector
				tokens.push_back(str.substr(lastPos, pos - lastPos));
				// Skip delimiters
				lastPos = str.find_first_not_of(delimiters, pos);
				// Find next non-delimiter
				pos = str.find_first_of(delimiters, lastPos);
			}
		}

		//Source: http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
		bool FileExists(const std::string& name){
			struct stat buffer;   
			return (stat (name.c_str(), &buffer) == 0); 
		}

	}
}
