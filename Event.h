#pragma once
#include "Entity.h"
#include <thread>
#include <chrono>
#include "SFML/Audio.hpp"
#include <functional>
class Event{
private:
	Entity* fEntity;					//Responsible entity
	sf::SoundBuffer fSoundBuffer;		//Buffer for the sound
	sf::Sound fSound;					//Sound object to play the sound
    bool hasSound;
    bool showEntity;
    function<void(Entity&)> fEvent; // Event function taking a Player reference
public:
    Event();
    Event(Entity* entity, bool pShowEntity, const string& soundFilePath = "", function<void(Entity&)> pEvent = nullptr);
    sf::Sound getSound();
    Entity* getEntity();
    void playEvent();
};