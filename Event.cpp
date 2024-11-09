#include "Event.h"

Event::Event() : fEntity(nullptr), showEntity(true), fEvent(nullptr) {}

Event::Event(Entity* entity, bool pShowEntity, function<void(Entity&)> pEvent)
    : fEntity(entity), showEntity(pShowEntity),fEvent(pEvent) {
}


Entity* Event::getEntity() {
    return fEntity;
}

void Event::playEvent() {
    if (fEvent != nullptr) {
        fEvent(*fEntity);
    }
}