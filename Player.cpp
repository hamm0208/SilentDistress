#include "Player.h"
#include "Weapon.h"
#include "Decision.h"
#include "SleepingBag.h"
#include "Scene.h"
#include "List.h"
#include <thread>
#include <chrono>

Player::Player():Entity(),  fInventory(100){
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
Entity(pName, pAttackDamage, pHealth), fCurrentHungerLevel(pHungerLevel), fCurrentThirstLevel(pThirstLevel), fCurrentStaminaLevel(pStamina), fIsResting(false), fInventory(pInventoryCapacity){
    fMaxHungerLevel = 10;
    fMaxThirstLevel = 10;
    fMaxStaminaLevel = fCurrentStaminaLevel;
};

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
int Player::getCurrentStaminaLevel() {
    return fCurrentStaminaLevel;
};
void Player::setCurrentStaminaLevel(int pStamina) {
    fCurrentStaminaLevel = pStamina;
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
    if(fCurrentHungerLevel + pIncrementValue >= fMaxHungerLevel){
        fCurrentHungerLevel = fMaxHungerLevel;
    }else{
        fCurrentHungerLevel += pIncrementValue;
    }
};
void Player::DecreaseHungerLevel(int pDecrementValue) {
    if(pDecrementValue>= fMaxHungerLevel){
        fMaxHungerLevel = 0;
    }else{
        fMaxHungerLevel -= pDecrementValue;
    }
};

//Increase and decreasing Thirst Level
void Player::IncreaseThirstLevel(int pIncrementValue){
    if(fCurrentThirstLevel + pIncrementValue >= fMaxThirstLevel){
        fCurrentThirstLevel = fMaxThirstLevel;
    }else{
        fCurrentThirstLevel += pIncrementValue;
    }
};

void Player::DecreaseThirstLevel(int pDecrementValue) {
    if(pDecrementValue>= fMaxThirstLevel){
        fMaxThirstLevel = 0;
    }else{
        fMaxThirstLevel -= pDecrementValue;
    }
};

//Increase and decreasing Stamina Level
void Player::IncreaseStamina(int pIncrementValue) {
    if(fCurrentStaminaLevel + pIncrementValue >= fMaxStaminaLevel){
        fCurrentStaminaLevel = fMaxStaminaLevel;
    }else{
        fCurrentStaminaLevel += pIncrementValue;
    }
};
void Player::DecreaseStamina(int pDecrementValue) {
    if(fCurrentStaminaLevel != 0){
        if(pDecrementValue <= fMaxStaminaLevel){
            fCurrentStaminaLevel = 0;
        }else{
            fCurrentStaminaLevel -= pDecrementValue;
        }
    }
};

//Heal player
void Player::Heal(int pHealValue) {
    if(getCurrentHealth() + pHealValue >= getHealth()){ //If new health is more than max health
        this->setCurrentHealth(getHealth());            //Then set current health to max health
    }else{
        this->setCurrentHealth(getCurrentHealth() + pHealValue);  //Else set Current health to new health
    }
};

//Adding item to Inventory
void Player::AddItem(Item* pItem) {
    fInventory.AddItem(pItem);
};

//Equip item to be used
void Player::EquipItem() {
    string item_Name = "";
    cout << "Name of item to equip (Case sensitive and leave no blank space): ";
    cin.clear();
    cin.ignore();
    getline(cin, item_Name);
    Item* searched_Item = fInventory.SearchItem(item_Name);
    if (searched_Item != (Item*)0) {
        fInventory.setCurrentItem(searched_Item);
        cout << "You have equipped " << searched_Item->getName() << "!" << endl;
    }
    else {
        cout << item_Name << " is not in your inventory" << endl;
    }
}

void Player::ViewItems() {
    system("CLS");
    cout << "Viewing Inventory. ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << ". ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << ". " << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    system("CLS");
    fInventory.ViewInventoryItems();
}

void Player::ViewItemsDetails() {
    fInventory.ViewInventoryDetails();
}

void Player::ViewItemDetails(Item& pItem) {
    fInventory.ViewItemDetails(&pItem);
}

void Player::DiscardItem() {
    ViewItems();
    string item_Name = "";
    cout << "Name of item to remove (Case sensitive and leave no blank space): ";
    cin.ignore();
    cin.clear();
    getline(cin, item_Name);
    Item* searched_Item = fInventory.SearchItem(item_Name);
    if (searched_Item != (Item*)0) {
        fInventory.RemoveItem(searched_Item);
    }
    else {
        cout << item_Name << " is not in your inventory" << endl;
    }
};
void Player::SearchItems() {
    string item_Name = "";
    cout << "Name of item to search (Case sensitive and leave no blank space): ";
    cin.clear();
    getline(cin, item_Name);
    Item* searched_Item = fInventory.SearchItem(item_Name);
    if (searched_Item != (Item*)0) {
        cout << searched_Item->getName() << " has been found in your inventory:" << endl;
        searched_Item->Inspect();
    }
    else {
        cout << item_Name << " is not in your inventory" << endl;
    }
};
Item* Player::getCurrentItem() {
    return fInventory.getCurrentItem();
};

void Player::UseCurrentItem() {
    if (Weapon* weapon = dynamic_cast<Weapon*>(getCurrentItem())) { //If fCurrentItem is type of Weapon, it will decrease the durability instead of the quantity
        if (weapon->Use(*this)) {
            setAttackDamage(getAttackDamage() - weapon->getDamage());
        }
        else {
            cout << "You are unable to use " << weapon->getName() << " right now, because you are not fighting" << endl;
        }
    }
    else if (SleepingBag* sleepingBag = dynamic_cast<SleepingBag*>(getCurrentItem())) {
        if (sleepingBag->Use(*this)) {
            cout << "Your hunger level and thrist level has been incresed by 1 after your rest" << endl;
        }
        else {
            cout << "Your stamina level is full!" << endl;
        }
    }
    else {
        fInventory.UseCurrentItem(*this);
    }
};

void Player::MakeDecision(Decision& pDecision) {
    fDecisionsMade.pushBack(pDecision);
    pDecision.applyEffect(*this);
};

void Player::ShowDecision(){
    cout << "List of decisions made by " << getName();
    for (int x = 0; x < fDecisionsMade.size(); x++) {
        cout << x + 1 << ". " << fDecisionsMade[x].getName() << endl;
    }
};

void Player::ShowAttributes(){
    system("CLS");
    cout << "Viewing Attributes. ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << ". ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << ". " << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    system("CLS");
    cout << "--------------------------------------------------\n" <<endl;
    cout << "Player's Details" << endl;
    cout << "Name:\t\t " << getName() << endl;;
    cout << "Attack Damage: \t " << getAttackDamage() << endl;
    cout << "Max Health:\t " << getHealth() << endl;
    cout << "Current Health:\t " << getCurrentHealth() << endl;
    cout << "Hunger Level:\t " << getCurrentHungerLevel() << "/" << getMaxHungerLevel() << endl;
    cout << "Thirst Level:\t " << getCurrentThirstLevel() << "/" << getMaxThirstLevel() << endl;
    cout << "Stamina Level:\t " << getCurrentStaminaLevel() << "/" << getMaxStaminaLevel() << endl;
    cout << "Bag Capacity:\t " << getInventory().getCurrentCapacity() << "/" << getInventory().getMaxCapacity() << endl;
    cout << "\n--------------------------------------------------\n";
    cout << "Press Enter to go back to main menu";
    cin.ignore();
    cin.ignore();

}

Inventory& Player::getInventory() {
    return fInventory;
};
