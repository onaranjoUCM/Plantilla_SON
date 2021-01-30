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
	sound->setVolume(1.0f);
	sound->setPositionAndVelocity({ 0, 0, 0 }, { 1, 0, 0 });
	
	while (true) {
		system->update();

		char c = ' ';
		std::cin >> c;

		if (!std::cin) {
			continue;
		}
		else {
			if (c == 'w') { // Aumentar volumen
				sound->changeVolume(0.1);
				sound->getVolume();
			}
			if (c == 's') { // Disminuir volumen
				sound->getVolume();
				sound->changeVolume(-0.1);
			}
			if (c == 'p') { // Pausar
				sound->togglePause();
			}
			if (c == 'm') { // Silenciar
				sound->toggleMute();
			}
			if (c == 'f') { // Fade in Auto
				sound->getVolume();
				sound->fadeInAuto(500, 0.05f);
			}
			if (c == 'o') { // Fade out Auto
				sound->getVolume();
				sound->fadeOutAuto(500, 0.05f);
			}
			if (c == 'q') {
				std::cout << "Quiting program\n";
				break;
			}
		}
	}

	// cierre
	delete sound;
	delete manager;

	return 0;
}
