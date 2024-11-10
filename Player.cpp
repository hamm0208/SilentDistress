#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "Decision.h"
#include "SleepingBag.h"
#include "Scene.h"
#include "List.h"
#include <thread>
#include <chrono>

//Default constructor
Player::Player():Entity(),  fInventory(100), fDecisionsMade(new SinglyLinkedList<Decision>()) {
    fMaxHungerLevel = 0;
    fMaxThirstLevel = 0;
    fMaxStaminaLevel = 0;
    fCurrentHungerLevel = fMaxHungerLevel;
    fCurrentThirstLevel = fMaxThirstLevel;
    fCurrentStaminaLevel = fMaxStaminaLevel;
    fIsResting = false;
}

//Initialise all the parameter into the class's attributes
Player::Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina, int pInventoryCapacity) :
Entity(pName, pAttackDamage, pHealth), fCurrentHungerLevel(pHungerLevel), fCurrentThirstLevel(pThirstLevel), fCurrentStaminaLevel(pStamina), fIsResting(false), fInventory(pInventoryCapacity), fDecisionsMade(new SinglyLinkedList<Decision>()) {
    fMaxHungerLevel = 10;
    fMaxThirstLevel = 10;
    fMaxStaminaLevel = 10;
};

Player::~Player(){
    if (fDecisionsMade != nullptr) {
        delete fDecisionsMade;
        fDecisionsMade = nullptr; // Set to nullptr to avoid dangling pointers
    }
}

//Getter and setter for fMaxHungerLevel
int Player::getMaxHungerLevel() {
    return fMaxHungerLevel;
};
void Player::setMaxHungerLevel(int pHungerLevel) {
    fMaxHungerLevel = pHungerLevel;
};
int Player::getCurrentHungerLevel() {
    return fCurrentHungerLevel;
};
void Player::setCurrentHungerLevel(int pHungerLevel) {
    fCurrentHungerLevel = pHungerLevel;
};

//Getter and setter for fMaxThirstLevel
int Player::getMaxThirstLevel() {
    return fMaxThirstLevel;
};
void Player::setMaxThirstLevel(int pThirstLevel) {
    fMaxThirstLevel = pThirstLevel;
};

//Getter and setter for fCurrentThirstLevel
int Player::getCurrentThirstLevel() {
    return fCurrentThirstLevel;
};
void Player::setCurrentThirstLevel(int pThirstLevel) {
    fCurrentThirstLevel = pThirstLevel;
};

//Getter and setter for fMaxStaminaLevel
int Player::getMaxStaminaLevel() {
    return fMaxStaminaLevel;
};
void Player::setMaxStaminaLevel(int pStamina) {
    fMaxStaminaLevel = pStamina;
};

//Getter and setter for fCurrentStaminaLevel
int Player::getCurrentStaminaLevel() {
    return fCurrentStaminaLevel;
};
void Player::setCurrentStaminaLevel(int pStamina) {
    fCurrentStaminaLevel = pStamina;
};

//Getter and setter for fDecisionsMade
SinglyLinkedList<Decision>* Player::getDecisionsMade() {
    return fDecisionsMade;
};

//Getter and setter for fIsresting
bool Player::getfIsResting() {
    return fIsResting;
};
void Player::setIsResting(bool pIsResting) {
    fIsResting = pIsResting;
};

//Increase and decreasing Hunger Level
void Player::IncreaseHungerLevel(int pIncrementValue) {
    if(fCurrentHungerLevel + pIncrementValue >= fMaxHungerLevel){   //If new hunger value is greater than the fMaxHungerLevel, then...
        fCurrentHungerLevel = fMaxHungerLevel;                      //fCurrentHungerLevel has reached the max hunger level
    }else{                                                          //else
        fCurrentHungerLevel += pIncrementValue;                     //Increase fCurrentHungerLevel by the increment
    }
};
void Player::DecreaseHungerLevel(int pDecrementValue) {     
    // Check if decrement value is greater than or equal to the current hunger level
    if (pDecrementValue >= fCurrentHungerLevel) {     
        fCurrentHungerLevel = 0;  // Set current hunger level to 0 if decrement value is too large
    } else {                                          
        fCurrentHungerLevel -= pDecrementValue;  // Otherwise, decrease hunger level by the decrement value
    }
};

// Increase Thirst Level
void Player::IncreaseThirstLevel(int pIncrementValue) {
    // Check if thirst level after increment exceeds maximum thirst level
    if (fCurrentThirstLevel + pIncrementValue >= fMaxThirstLevel) {
        fCurrentThirstLevel = fMaxThirstLevel;  // Set thirst level to maximum if it exceeds the limit
    } else {
        fCurrentThirstLevel += pIncrementValue;  // Otherwise, increase thirst level by the increment value
    }
};

// Decrease Thirst Level
void Player::DecreaseThirstLevel(int pDecrementValue) {
    // Check if decrement value is greater than or equal to the current thirst level
    if (pDecrementValue >= fCurrentThirstLevel) {
        fCurrentThirstLevel = 0;  // Set thirst level to 0 if decrement value is too large
    } else {
        fCurrentThirstLevel -= pDecrementValue;  // Otherwise, decrease thirst level by the decrement value
    }
};

// Increase and decrease Stamina Level
void Player::IncreaseStamina(int pIncrementValue) {
    // Check if stamina level after increment would exceed maximum stamina level
    if (fCurrentStaminaLevel + pIncrementValue >= fMaxStaminaLevel) {
        fCurrentStaminaLevel = fMaxStaminaLevel;  // Set stamina to max if it exceeds the limit
    } else {
        fCurrentStaminaLevel += pIncrementValue;  // Otherwise, increase by increment value
    }
};

void Player::DecreaseStamina(int pDecrementValue) {
    if (fCurrentStaminaLevel != 0) {  // Only decrease if stamina is not already zero
        // Check if decrement value would reduce stamina below zero
        if (pDecrementValue >= fCurrentStaminaLevel) {
            fCurrentStaminaLevel = 0;  // Set to zero if decrement is too large
        } else {
            fCurrentStaminaLevel -= pDecrementValue;  // Otherwise, decrease by decrement value
        }
    }
};

// Heal player
void Player::Heal(int pHealValue) {
    // Check if heal amount would exceed max health
    if (getCurrentHealth() + pHealValue >= getHealth()) {
        this->setCurrentHealth(getHealth());  // Set current health to max if heal exceeds it
    } else {
        this->setCurrentHealth(getCurrentHealth() + pHealValue);  // Otherwise, increase by heal value
    }
};

// Add item to Inventory
bool Player::AddItem(Item* pItem) {
    return fInventory.AddItem(pItem);  // Attempt to add item to inventory and return success status
};

// Equip item to be used
bool Player::EquipItem() {
    ViewItems();  // Display current items in inventory
    string item_Name = "";
    cout << "Name of item to equip (Case sensitive and leave no blank space): ";
    cin.clear();
    cin.ignore();
    getline(cin, item_Name);
    
    // Search for the item by name in the inventory
    Item* searched_Item = fInventory.SearchItem(item_Name);
    if (searched_Item != nullptr) {
        if (searched_Item == getCurrentItem()) {
            cout << "You have already equipped " << getCurrentItem()->getName() << endl;
            system("PAUSE");
            return false;  // Item is already equipped
        } else {
            fInventory.setCurrentItem(searched_Item);  // Set as current equipped item
            cout << "You have equipped " << searched_Item->getName() << "!" << endl;
            system("PAUSE");
            return true;
        }
    } else {
        cout << item_Name << " is not in your inventory" << endl;
        system("PAUSE");
        return false;  // Item not found in inventory
    }
}

// View list of items in Inventory
void Player::ViewItems() {
    system("CLS");
    cout << "Viewing Inventory. ";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ". ";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ". " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("CLS");
    fInventory.ViewInventoryItems();  // Call to display inventory items
}

// View detailed information of all items in Inventory
void Player::ViewItemsDetails() {
    fInventory.ViewInventoryDetails();  // Call to display inventory item details
}

// View details of a specific item in Inventory
void Player::ViewItemDetails(Item& pItem) {
    fInventory.ViewItemDetails(&pItem);  // Display details for specified item
}

// Discard item from Inventory
bool Player::DiscardItem() {
    ViewItems();  // Show items before selection
    string item_Name = "";
    cout << "Name of item to remove (Case sensitive and leave no blank space): ";
    cin.ignore();
    cin.clear();
    getline(cin, item_Name);
    
    // Search for item by name in inventory
    Item* searched_Item = fInventory.SearchItem(item_Name);
    if (searched_Item != nullptr) {
        fInventory.RemoveItem(searched_Item);  // Remove item from inventory
        system("PAUSE");
        return true;
    } else {
        cout << item_Name << " is not in your inventory" << endl;
        system("PAUSE");
        return false;  // Item not found in inventory
    }
};

// Search for an item in Inventory
void Player::SearchItems() {
    string item_Name = "";
    cout << "Name of item to search (Case sensitive and leave no blank space): ";
    cin.clear();
    getline(cin, item_Name);
    
    // Search for item by name in inventory
    Item* searched_Item = fInventory.SearchItem(item_Name);
    if (searched_Item != nullptr) {
        cout << searched_Item->getName() << " has been found in your inventory:" << endl;
        searched_Item->Inspect();  // Display item details
    } else {
        cout << item_Name << " is not in your inventory" << endl;
    }
};

// Get currently equipped item
Item* Player::getCurrentItem() {
    return fInventory.getCurrentItem();  // Return the current equipped item
};

// Use the currently equipped item
bool Player::UseCurrentItem() {
    // Check if the current item is a weapon
    if (Weapon* weapon = dynamic_cast<Weapon*>(getCurrentItem())) {
        if (fInventory.UseCurrentItem(*this)) {
            return true;
        } else {
            cout << "You are unable to use " << weapon->getName() << " right now, because you are not fighting" << endl;
            system("PAUSE");
            return false;
        }
    }
    // Check if the current item is a sleeping bag
    else if (SleepingBag* sleepingBag = dynamic_cast<SleepingBag*>(getCurrentItem())) {
        if (fInventory.UseCurrentItem(*this)) {
            cout << "Your hunger level and thirst level has been increased by 1 after your rest" << endl;
            system("PAUSE");
            return true;
        } else {
            cout << "Your stamina level is full!" << endl;
            system("PAUSE");
            return false;
        }
    } else {
        return fInventory.UseCurrentItem(*this);  // Use item if it's neither weapon nor sleeping bag
    }
};

// Record decision made by player
void Player::MakeDecision(Decision& pDecision) {
    fDecisionsMade->pushBack(pDecision);  // Add decision to list of decisions
    pDecision.applyEffect(*this);  // Apply the effects of the decision on the player
};

// Show player's attributes (health, hunger, thirst, etc.)
void Player::ShowAttributes() {
    system("CLS");
    cout << "Viewing Attributes. ";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ". ";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ". " << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("CLS");
    
    cout << "--------------------------------------------------\n" << endl;
    cout << "Player's Details" << endl;
    cout << "Name:\t\t " << getName() << endl;
    cout << "Attack Damage:\t " << getAttackDamage() << endl;
    cout << "Max Health:\t " << getHealth() << endl;
    cout << "Current Health:\t " << getCurrentHealth() << endl;
    cout << "Hunger Level:\t " << getCurrentHungerLevel() << "/" << getMaxHungerLevel() << endl;
    cout << "Thirst Level:\t " << getCurrentThirstLevel() << "/" << getMaxThirstLevel() << endl;
    cout << "Stamina Level:\t " << getCurrentStaminaLevel() << "/" << getMaxStaminaLevel() << endl;
    cout << "Bag Capacity:\t " << getInventory().getCurrentCapacity() << "/" << getInventory().getMaxCapacity() << endl;
    cout << "\n--------------------------------------------------\n";
    system("PAUSE");
}

// Accessor for player's inventory
Inventory& Player::getInventory() {
    return fInventory;
};

// Apply effects of hunger, thirst, stamina, etc., on the player
void Player::ApplyEffects(Monster& pMonster) {
    if (getCurrentHealth() <= 0) {
        Entity::Die();
        cout << "Your vision fades... Darkness envelops you as life slips away." << endl;
        return;
    }

    // Hunger effects
    if (fCurrentHungerLevel >= 8) {
        DecreaseStamina(1);
        IncreaseThirstLevel(1);
        cout << (fCurrentHungerLevel == 10
            ? "Starvation claws at you mercilessly. Weak and fading, your body is shutting down."
            : "Your stomach growls with a fierce emptiness... Every step feels heavier.") << endl;
        if (fCurrentHungerLevel == 10) TakeDamage(3);
    }

    // Thirst effects
    if (fCurrentThirstLevel >= 8) {
        DecreaseStamina(1);
        cout << (fCurrentThirstLevel == 10
            ? "Dehydration sets in. Your vision blurs as intense thirst ravages your body."
            : "Your mouth is parched, and each breath feels like fire. You desperately need water.") << endl;
        if (fCurrentThirstLevel == 10) TakeDamage(5);
    }

    // Stamina effects
    if (fCurrentStaminaLevel <= 5) {
        IncreaseHungerLevel(1);
        IncreaseThirstLevel(1);
        cout << "Fatigue overwhelms you, making survival feel impossible. Hunger and thirst surge as your energy wanes." << endl;

        if (fCurrentStaminaLevel == 0) {
            if (getIsFighting()) {
                Entity::Die();
                cout << "With the last of your strength drained, you collapse in battle... Darkness claims you." << endl;
            } else {
                cout << "Exhaustion takes its toll. You collapse, forced into a deep slumber...\n";
                cout << "As you sleep, hunger and thirst intensify, clawing at your insides. (+2 Hunger, +2 Thirst)" << endl;
                setIsResting(true);
                pMonster.DisturbRest(*this, 100);
                IncreaseHungerLevel(2);
                IncreaseThirstLevel(2);
                IncreaseStamina(5);
            }
        }
    }
}