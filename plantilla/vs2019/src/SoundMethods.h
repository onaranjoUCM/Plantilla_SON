#pragma once
#include"fmod.hpp"// para utilizar el wrapper C++
#include"fmod_errors.h"  // para manejo de errores
#include <iostream>

#include "SoundManager.h"
#include "Sound.h"

using namespace FMOD;

static class SoundMethods
{
public:
	static void fundidoManual(SoundTrack* sound1, SoundTrack* sound2, int ms, float volumeVariation);
	static void fundidoAuto(SoundTrack* sound1, SoundTrack* sound2, int ms, float volumeVariation);
};

