 #include "stdafx.h"
#ifndef RPGLIB_SOUNDMANAGER_H
#define RPGLIB_SOUNDMANAGER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class SoundManager{
		public:
			SoundManager(Factory* factory, Engine::SDLLib* sdl);
			~SoundManager();
			
			void Init();
			void SetSounds(unorderedmap_sound_data& sounds);
			void LoadSound(const std::string& id);

			void SetVolume(int volume);
			void SetMusicVolume(int volume);

			void PlaySoundEffect(const std::string& id, int times);

			void PlayMusic(const std::string& id);
			void PauseMusic();
			void ResumeMusic();
			void StopMusic();
			void StopMusicFadeOut(int ms);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			Factory* factory;
			/* NOT Owner */
			Engine::SDLLib* sdl;
			/* NOT Owner. Unorderedmap */
			unorderedmap_sound_data sounds;
			/* Owner of all Sounds* */
			std::unordered_map<std::string, Engine::Sound*> esounds;
		};
	}
}
#endif