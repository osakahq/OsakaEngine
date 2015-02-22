 #include "stdafx.h"
#ifndef RPGLIB_FONTMANAGER_H
#define RPGLIB_FONTMANAGER_H

namespace Osaka{
	namespace RPGLib{
		struct fontcharacter_data;

		class FontManager{
		public:
			FontManager();
			~FontManager();
			void _delete();
			void SetFontmap(std::unordered_map<std::string, fontcharacter_data*>& fontmap);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner. */
			std::unordered_map<std::string, fontcharacter_data*>* fontmap;
		};
	}
}
#endif