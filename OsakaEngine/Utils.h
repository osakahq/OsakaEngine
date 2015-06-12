 #include "stdafx.h"

#ifndef UTIL_UTILS_H
#define UTIL_UTILS_H

namespace Osaka{
	namespace Utils{
		//TODO: Ponerlas como static inline?
		std::string &TrimString(std::string &s);
		void SplitString(std::vector<std::string> &tokens, const std::string &str, const std::string &delimiters = " ");
		
		bool FileExists(const std::string& name);

		inline float Clamp(float n, float lower, float upper){
			return std::max(lower, std::min(n, upper));
		}
		inline int Clamp(int n, int lower, int upper){
			return std::max(lower, std::min(n, upper));
		}
		inline float Round(float n){
			return n < 0.0 ? (float)std::ceil(n - 0.5) : (float)std::floor(n + 0.5);
		}
		inline double Round(double n){
			return n < 0.0 ? std::ceil(n - 0.5) : std::floor(n + 0.5);
		}
	}
}

#endif