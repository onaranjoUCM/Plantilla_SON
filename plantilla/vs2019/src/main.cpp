#include "fmod.hpp"
#include "../common.h"

#include "SoundManager.h"
#include "Sound.h"
#include "SoundMethods.h"

using namespace FMOD;

int FMOD_Main() {
	// inicializacion
	System* system;
	System_Create(&system); // Creamos el objeto system
	SoundManager* manager = new SoundManager(system);

	SoundTrack* sound = new SoundTrack(system, "muestras/piano.ogg", true, false);
	sound->play();
	
	while (true) {
		manager->update();
	}

	// cierre
	delete sound;
	delete manager;

	return 0;
}
