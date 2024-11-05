#include "Event.h"

Event::Event() : fEntity(nullptr), fDialogue(""), hasSound(false) {}

Event::Event(Entity* entity, const string& dialogue, const string& soundFilePath)
    : fEntity(entity), fDialogue(dialogue), hasSound(!soundFilePath.empty())
{
    if (hasSound) {
        if (!fSoundBuffer.loadFromFile(soundFilePath)) {
            std::cerr << "Error loading sound file!" << std::endl;
            hasSound = false;
        }
        else {
            fSound.setBuffer(fSoundBuffer);
        }
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
    std::cout << fDialogue << std::endl;
    if (hasSound) {
        fSound.play();
        while (fSound.getStatus() == sf::Sound::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}