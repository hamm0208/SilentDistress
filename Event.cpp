#include "Event.h"
//Constructor
Event::Event() : fEntity(nullptr), fEvent(nullptr) {}

Event::Event(Entity* entity, function<void(Entity&)> pEvent)
    : fEntity(entity),fEvent(pEvent) {
}

//Getter for fEnttiy
Entity* Event::getEntity() {
    return fEntity;
}

//Call the fEvent method
void Event::playEvent() {
    if (fEvent != nullptr) {
        fEvent(*fEntity);
    }
}