#include "Sound.h"
#include <Windows.h>

SoundTrack::SoundTrack(System* system, const char* soundName, bool loop, bool _3d) {
	system_ = system;
	soundName_ = soundName;
	loop_ = loop;
	_3d_ = _3d;
	
	init();
}

SoundTrack::~SoundTrack() {
	release();
}

void SoundTrack::init() {
	FMOD_MODE loopMode;
	FMOD_MODE dimensionMode;

	if (loop_) {
		loopMode = FMOD_LOOP_NORMAL;
	}
	else {
		loopMode = FMOD_LOOP_OFF;
	}

	if (_3d_) {
		dimensionMode = FMOD_3D;
	}
	else {
		dimensionMode = FMOD_2D;
	}

	system_->createSound(soundName_,    // path al archivo de sonido
		dimensionMode | loopMode,    // valores (por defecto en este caso: sin loop, 2D)
		0,// informacion adicional (nada en este caso)
		&sound);// handle al buffer de sonido
}

void SoundTrack::release() {
	sound->release();
}

void SoundTrack::play() {
	system_->playSound(sound,   // buffer que se "engancha" a ese canal
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false,   // arranca sin "pause" (se reproduce directamente)
		&channel); // devuelve el canal que asigna
	// el sonido ya se esta reproduciendo
}

void SoundTrack::stop()
{
	channel->stop();
}

void SoundTrack::togglePause() {
	bool paused;
	channel->getPaused(&paused);
	channel->setPaused(!paused);
}

void SoundTrack::toggleMute() {
	bool mute;
	channel->getMute(&mute);
	channel->setMute(!mute);
}

void SoundTrack::setVolume(float volume) {
	channel->setVolume(volume_);
}

void SoundTrack::changeVolume(float volume) {
	volume_ = volume_ + volume;
	channel->setVolume(volume_);
}

void SoundTrack::changePan(float pan) {
	channel->setPan(pan);
}

void SoundTrack::fadeInManual(int ms, float volumeVariation) {
	int msStep = ms / 10;
	float volumeStep = volumeVariation / 10;

	for (int i = 0;i < 10;i++) {
		volume_ = volume_ + volumeStep;
		channel->setVolume(volume_);
		system_->update();
		Sleep(msStep);
	}
}

void SoundTrack::fadeOutManual(int ms, float volumeVariation) {
	int msStep = ms / 10;
	float volumeStep = volumeVariation / 10;

	for (int i = 0;i < 10;i++) {
		volume_ = volume_ - volumeStep;
		channel->setVolume(volume_);
		system_->update();
		Sleep(msStep);
	}
}

void SoundTrack::fadeInAuto(int ms, float volumeVariation) {
	unsigned long long parentclock;
	int rate;
	int seconds = ms / 1000;
	channel->getDSPClock(nullptr, &parentclock);
	system_->getSoftwareFormat(&rate, 0, 0);
	channel->addFadePoint(parentclock, volume_);
	volume_ = volume_ + volumeVariation;
	channel->addFadePoint(parentclock + (rate * seconds), volume_);
}

void SoundTrack::fadeOutAuto(int ms, float volumeVariation) {
	unsigned long long parentclock;
	int rate;
	int seconds = ms / 1000;
	channel->getDSPClock(nullptr, &parentclock);
	system_->getSoftwareFormat(&rate, 0, 0);
	channel->addFadePoint(parentclock, volume_);
	volume_ = volume_ - volumeVariation;
	channel->addFadePoint(parentclock + (rate * seconds), volume_);
}

void SoundTrack::startDelayed(int milliseconds) {
	channel->setPosition(milliseconds, FMOD_TIMEUNIT_MS);
}

void SoundTrack::setLoopTimes(int n) {
	channel->setLoopCount(n);
}

void SoundTrack::setPositionAndVelocity(FMOD_VECTOR pos, FMOD_VECTOR vel) {
	channel->set3DAttributes(&pos, &vel);
}
