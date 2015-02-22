 #include "stdafx.h"
#ifndef RPGLIB_SOUNDMANAGER_H
#define RPGLIB_SOUNDMANAGER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class SoundManager{
		public:
			SoundManager(FactoryPTR& factory, Engine::SDLLibPTR& sdl);
			~SoundManager();
			void _delete();

			void SetSounds(unorderedmap_sound_dataPTR& sounds);
			void LoadSound(const std::string id);

			void SetVolume(int volume);
			void SetMusicVolume(int volume);

			void PlaySoundEffect(std::string id, int times);

			void PlayMusic(std::string id);
			void PauseMusic();
			void ResumeMusic();
			void StopMusic();
			void StopMusicFadeOut(int ms);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			FactoryPTR factory;
			/* NOT Owner */
			Engine::SDLLibPTR sdl;
			/* NOT Owner. Unorderedmap */
			unorderedmap_sound_dataPTR sounds;
			/* Owner of all Sounds* */
			std::unordered_map<std::string, Engine::SoundPTR> esounds;
		};
	}
}
#endif