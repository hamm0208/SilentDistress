#pragma once
#include "Entity.h"
#include <thread>
#include <chrono>
#include <functional>
class Event{
private:
	Entity* fEntity;					//Responsible entity
    function<void(Entity&)> fEvent; // Event function taking a Player reference
public:
    //Default constructor
    Event(); 
    //Overloaded constructor
    Event(Entity* entity, function<void(Entity&)> pEvent = nullptr);
    //Getter for fEntity
    Entity* getEntity();
    //Play event (call the fEvent function)
    void playEvent();
};