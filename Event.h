#pragma once
#include "Entity.h"
#include "SFML/Audio.hpp"
class Event
{
private:
	Entity* fEtntity;					//Responsible entity
	string fDialogue;					//Dialogue of the event
	sf::SoundBuffer jumpscareBuffer;	//Buffer for the jumpscare sound
	sf::Sound jumpscareSound;			//Sound object to play the sound
};

