#include "Decision.h"

// Default constructor
Decision::Decision() : fName(""), fDescription(""), fEffect(nullptr) {}

// Constructor with name, description, and effect
Decision::Decision(const string& name, const string& description, function<void(Entity&)> pEffect)
    : fName(name), fDescription(description), fEffect(pEffect) {}

// Getter for name
string Decision::getName() const {
    return fName;
}

// Getter for description
string Decision::getDescription() const {
    return fDescription;
}

// Method to apply the effect, taking Player, Scene, and Monster
void Decision::applyEffect(Player& player) const {
    if (fEffect) {
        fEffect(player); // Apply the effect with Player, Scene, and Monster
    }
}
