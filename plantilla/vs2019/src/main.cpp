#include "fmod.hpp"
#include "../common.h"
#include <conio.h>

#include "SoundManager.h"
#include "Sound.h"
#include "SoundMethods.h"

using namespace FMOD;

Reverb3D* createReverb3D(System* system_, FMOD_VECTOR pos, float mindist, float maxdist, FMOD_REVERB_PROPERTIES prop) {
	Reverb3D* reverb;
	system_->createReverb3D(&reverb);
	reverb->setProperties(&prop);
	reverb->set3DAttributes(&pos, mindist, maxdist);
	return reverb;
}

Geometry* createGeometry(System* system_, FMOD_VECTOR pos, FMOD_VECTOR scale, const FMOD_VECTOR* numvertices) {
	Geometry* geometry;
	system_->createGeometry(1, 4, &geometry);
	geometry->addPolygon(1.0f, 0.1f, true, 4, numvertices, 0);
	geometry->setActive(false);
	geometry->setPosition(&pos);
	geometry->setScale(&scale);
	return geometry;
}

int FMOD_Main()
{
	// inicializacion
	System* system;
	System_Create(&system);
	SoundManager* manager = new SoundManager(system);

	FMOD_VECTOR pos = { 0.0f, 0.0f, -1.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR at = { 1.0f, 0.0f, 0.0f };
	system->set3DListenerAttributes(0, &pos, &vel, &up, &at);

	// Geometry
	const FMOD_VECTOR vertices = { 0.0f, 0.0f, 0.0f };

	SoundTrack* motor = new SoundTrack(system, "./muestras/footstep.wav", true, true);
	motor->setPositionAndVelocity({ 0, 0, 4 }, { 0, 0, 0 });
	motor->play();

	float pitch = 1;

	Reverb3D* reverb = createReverb3D(system, {2, 0, 6}, 1, 10, FMOD_PRESET_CONCERTHALL);
	Geometry* geometry = createGeometry(system, pos, { 4, 4, 0 }, &vertices);

	// Main loop
	bool playing = true;
	while (playing) {
		if (_kbhit()) {
			// Listener movement
			if (_getch() == 'w') pos.x += 1.0f;
			if (_getch() == 'a') pos.z += 1.0f; 
			if (_getch() == 's') pos.x -= 1.0f;
			if (_getch() == 'd') pos.z -= 1.0f; 

			// Pitch
			if (_getch() == 'P') {
				pitch += 0.01;
				motor->setPitch(pitch);
			}

			if (_getch() == 'p') {
				pitch -= 0.01;
				motor->setPitch(pitch);
			}

			// Reverb
			if (_getch() == 'R') reverb->setActive(true);
			if (_getch() == 'r') reverb->setActive(false);

			// Geometry and Oclution
			if (_getch() == 'O') geometry->setActive(true);
			if (_getch() == 'o') geometry->setActive(false);

			// Quit
			if (_getch() == 'q')
				playing = false;
		}

		system->set3DListenerAttributes(0, &pos, &vel, &up, &at);
		manager->update();

		// Debug
		std::cout << "Listener: " << pos.x << " " << pos.z << " ";
		bool active;
		reverb->getActive(&active);
		std::cout << "Pitch: " << pitch << " Revervb: " << active;
		geometry->getActive(&active);
		std::cout << " Occlusion: " << active << "\n";
	}

	// Closing
	delete motor;
	delete manager;

	return 0;
}