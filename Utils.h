 #include "stdafx.h"

namespace Osaka{
	namespace Utils{
		//TODO: Ponerlas como static inline?
		std::string &TrimString(std::string &s);
		void SplitString(std::vector<std::string> &tokens, const std::string &str, const std::string &delimiters = " ");
		
		bool FileExists(const std::string& name);
	}
}