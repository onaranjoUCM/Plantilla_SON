#include "fmod.hpp"
#include "../common.h"
#include <conio.h>

#include "SoundManager.h"
#include "Sound.h"
#include "SoundMethods.h"

using namespace FMOD;

int FMOD_Main()
{
	System* system;
	System_Create(&system);
	system->init(128, FMOD_INIT_NORMAL, 0);

	// Situar el listener en la posición (0, 0,−1), orientado en posición vertical y mirando hacia adelante.
	FMOD_VECTOR pos = { 0, 0, -1 };
	FMOD_VECTOR vel = { 0, 0, 0 };
	FMOD_VECTOR up = { 0, 1, 0 };
	FMOD_VECTOR at = { 1, 0, 0 };
	system->set3DListenerAttributes(0, &pos, &vel, &up, &at);

	// Cargar la muestra en loop y asociarla a un canal emisor.
	Sound* sound;
	system->createSound("./muestras/footstep.wav", FMOD_3D | FMOD_LOOP_NORMAL, 0, &sound);

	Channel* channel;
	FMOD_VECTOR soundPos = { 0, 0, 4 };
	system->playSound(sound, 0, false, &channel);
	channel->set3DAttributes(&soundPos, &vel);

	float pitch = 1;

	// Reverb
	Reverb3D* reverb;
	system->createReverb3D(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL;
	reverb->setProperties(&prop);
	FMOD_VECTOR reverbPos = { 2, 0, 6 };
	reverb->set3DAttributes(&reverbPos, 1, 10);

	// Geometry / Occlussion
	Geometry* geometry;
	system->createGeometry(1, 4, &geometry);
	FMOD_VECTOR* vertices = new FMOD_VECTOR[4];
		vertices[0] = { -2, 2, 0 };
		vertices[1] = { 2, 2, 0 };
		vertices[2] = { 2, -2, 0 };
		vertices[3] = { -2, -2, 0 };
	int polygonIndex;
	geometry->addPolygon(1, 1, true, 4, vertices, &polygonIndex);

	bool playing = true;
	while (playing) {
		if (_kbhit()) {
			// Listener movement
			if (_getch() == 'w') pos.z += 1.0f;
			if (_getch() == 'a') pos.x -= 1.0f;
			if (_getch() == 's') pos.z -= 1.0f;
			if (_getch() == 'd') pos.x += 1.0f;

			// Pitch
			if (_getch() == 'P') pitch += 0.01;
			if (_getch() == 'p') pitch -= 0.01;

			// Reverb
			if (_getch() == 'R') reverb->setActive(true);
			if (_getch() == 'r') reverb->setActive(false);

			// Geometry and Oclution
			if (_getch() == 'O') geometry->setActive(true);
			if (_getch() == 'o') geometry->setActive(false);

			// Quit
			if (_getch() == 'q')
				playing = false;

			channel->setPitch(pitch);
			system->set3DListenerAttributes(0, &pos, &vel, &up, &at);
		}

		system->update();

		// Debug
		std::cout << "Listener: " << pos.x << " " << pos.z << " ";
		bool active;
		reverb->getActive(&active);
		std::cout << "Pitch: " << pitch << " Revervb: " << active;
		geometry->getActive(&active);
		std::cout << " Occlusion: " << active << "\n";
	}

	return 0;
}