#include "Decision.h"

Decision::Decision(): fName(""), fDescription(""), fEffect(nullptr) {}
Decision::Decision(const string& name, const string& description, function<void(Player&)> effect): fName(name), fDescription(description), fEffect(effect) {}

string Decision::getName() const {
    return fName;
}

string Decision::getDescription() const {
    return fDescription;
}

void Decision::applyEffect(Player& player) const {
    if (fEffect) {
         fEffect(player); // Call the effect function with the player
    }
}