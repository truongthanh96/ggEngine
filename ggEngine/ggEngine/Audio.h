#include "GGObject.h"
namespace ggEngine{
	class Audio : public GGObject{
	public:
		void Play();
		void Stop();
		void Loop();
		void Repeat(int numberOfRepeat);
		void Pause();
		void Resume();
		void Destroy(bool clearFromCache = false);
		void Restart();
		//Play the audio, or restart if is playing. 
		void FadeIn(int duration, bool loop = false);
		void FadeOut(int duration);
		//Fade to the specific volume
		void FadeTo(float volume);
	private:
		
	};
}