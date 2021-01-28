#include "SoundManager.h"

SoundManager::SoundManager(System* system)
{
	system_ = system;
	init();
}

SoundManager::~SoundManager()
{
	release();
}

void SoundManager::init()
{
	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	system_->init(128, FMOD_INIT_NORMAL, 0);  // Inicializacion de FMOD
}

void SoundManager::update()
{
	system_->update();
}

void SoundManager::release()
{
	system_->release();
}


