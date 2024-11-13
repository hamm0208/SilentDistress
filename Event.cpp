#include "Event.h"
//Constructor
Event::Event() : fGame(nullptr), fEvent(nullptr) {}

Event::Event(Game* pGame, function<void(Game&)> pEvent)
    : fGame(pGame),fEvent(pEvent) {
}

//Getter for fEnttiy
Game* Event::getGame() {
    return fGame;
}

//Call the fEvent method
void Event::playEvent() {
    if (fEvent != nullptr) {
        fEvent(*fGame);
    }
}