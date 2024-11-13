#pragma once
#include "Entity.h"
#include <thread>
#include <chrono>
#include <functional>

class Game;
class Event{
private:
	Game* fGame;					//Responsible entity
    function<void(Game&)> fEvent; // Event function taking a Player reference
public:
    //Default constructor
    Event(); 
    //Overloaded constructor
    Event(Game* pGame, function<void(Game&)> pEvent = nullptr);
    //Getter for fEntity
    Game* getGame();
    //Play event (call the fEvent function)
    void playEvent();
};