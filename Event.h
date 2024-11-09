#pragma once
#include "Entity.h"
#include <thread>
#include <chrono>
#include <functional>
class Event{
private:
	Entity* fEntity;					//Responsible entity
    bool showEntity;
    function<void(Entity&)> fEvent; // Event function taking a Player reference
public:
    Event();
    Event(Entity* entity, bool pShowEntity, function<void(Entity&)> pEvent = nullptr);
    Entity* getEntity();
    void playEvent();
};