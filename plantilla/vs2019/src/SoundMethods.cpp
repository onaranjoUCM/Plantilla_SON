#include "SoundMethods.h"

void SoundMethods::fundidoManual(SoundTrack* sound1, SoundTrack* sound2, int ms, float volumeVariation)
{
	sound1->fadeInManual(ms, volumeVariation);
	sound2->fadeOutManual(ms, volumeVariation);
}

void SoundMethods::fundidoAuto(SoundTrack* sound1, SoundTrack* sound2, int ms, float volumeVariation)
{
	sound1->fadeInAuto(ms, volumeVariation);
	sound2->fadeOutAuto(ms, volumeVariation);
}
