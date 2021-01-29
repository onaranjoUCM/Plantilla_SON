#pragma once
#include"fmod.hpp"// para utilizar el wrapper C++
#include"fmod_errors.h"  // para manejo de errores
#include <iostream>

using namespace FMOD;

class SoundManager {
	System* system_;

public:
	SoundManager(System* system);
	~SoundManager();
	void init();
	void update();
	void release();
};
