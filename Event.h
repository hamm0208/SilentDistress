#pragma once
#include "Entity.h"
#include <thread>
#include <chrono>
#include "SFML/Audio.hpp"
class Event{
private:
	Entity* fEntity;					//Responsible entity
	string fDialogue;					//Dialogue of the event
	sf::SoundBuffer fSoundBuffer;		//Buffer for the sound
	sf::Sound fSound;					//Sound object to play the sound
    bool hasSound;
    bool showEntity;
public:
    Event();
    Event(Entity* entity, bool pShowEntity, const string& dialogue, const string& soundFilePath = "");
    sf::Sound getSound();
    Entity* getEntity();
    string getDialogue();
    void playEvent();
};