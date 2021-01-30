#pragma once
#include"fmod.hpp"// para utilizar el wrapper C++
#include"fmod_errors.h"  // para manejo de errores
#include <iostream>¡

using namespace FMOD;

class SoundTrack {
	Sound* sound;

	// system y result de SoundManager
	System* system_;

	const char* soundName_;
	bool loop_;
	bool _3d_;

	Channel* channel;

	float volume_;

public:
	SoundTrack(System* system, const char* soundName, bool loop, bool _3d);
	~SoundTrack();
	void init();
	void release();

	void play();
	void stop();
	void togglePause();
	void toggleMute();
	void setVolume(float volume);
	void changeVolume(float volume);
	void changePan(float pan);

	void setPitch(float p);

	void fadeInManual(int ms, float volumeVariation);
	void fadeOutManual(int ms, float volumeVariation);

	void fadeInAuto(int ms, float volumeVariation);
	void fadeOutAuto(int ms, float volumeVariation);

	void startDelayed(int milliseconds);
	void setLoopTimes(int n); // n=-1 for infinite loop

	void setPositionAndVelocity(FMOD_VECTOR pos, FMOD_VECTOR vel);
};
