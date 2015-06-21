#include "stdafx.h"
#ifndef ENGINE_SOUNDEFFECT_H
#define ENGINE_SOUNDEFFECT_H
#include "Sound.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		
		class SoundEffect : public Sound {
		public:
			SoundEffect(Debug::Debug* debug, IFileLoader* fileloader);
			~SoundEffect();
			
			void Load(const char* filename) override;
			void Play(int times);
			Mix_Chunk* GetRAWMixChunk();
		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner */
			Mix_Chunk* effect;
		};
	}
}
#endif