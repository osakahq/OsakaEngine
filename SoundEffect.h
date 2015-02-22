#include "stdafx.h"
#ifndef ENGINE_SOUNDEFFECT_H
#define ENGINE_SOUNDEFFECT_H
#include "Sound.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		
		class SoundEffect : public Sound {
		public:
			SoundEffect(Debug::DebugPTR& debug, IFileLoaderPTR& fileloader);
			~SoundEffect();
			void _delete();
			void Load(const char* filename);
			void Play(int times);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner */
			Mix_Chunk* effect;
		};
	}
}
#endif