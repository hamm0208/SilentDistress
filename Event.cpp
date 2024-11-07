#include "Event.h"

Event::Event() : fEntity(nullptr), fDialogue(""), hasSound(false), showEntity(true), fEvent(nullptr) {}

Event::Event(Entity* entity, bool pShowEntity, const string& dialogue, const string& soundFilePath, function<void(Entity&)> pEvent)
    : fEntity(entity), fDialogue(dialogue), hasSound(!soundFilePath.empty()), showEntity(pShowEntity),fEvent(pEvent) {
    if (hasSound) {
        if (!fSoundBuffer.loadFromFile(soundFilePath)) {
            cerr << "Error loading sound file!" << std::endl;
            hasSound = false;
            // Handle loading error if needed
        }
        fSound.setBuffer(fSoundBuffer);
    }
}

sf::Sound Event::getSound() {
    return fSound;
}

Entity* Event::getEntity() {
    return fEntity;
}

string Event::getDialogue() {
    return fDialogue;
}

void Event::playEvent() {
    if (showEntity) {
        cout << fEntity->getName()  <<": " << fDialogue << endl;
    }
    else {
        cout << fDialogue << endl;
        if (fEvent != nullptr) {
            fEvent(*fEntity);
        }
    }
    if (hasSound) {
        fSound.play();
        while (fSound.getStatus() == sf::Sound::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}