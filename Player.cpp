#include "Player.h"
#include "Weapon.h";
Player::Player():Entity(), fInventory(100) {
    fHungerLevel = 0;
    fThirstLevel = 0;
    fStamina = 0;
    fIsresting = false;
}

//Initialise all the parameter into the class's attributes
Player::Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina, int pInventoryCapacity) :
    Entity(pName, pAttackDamage, pHealth), fHungerLevel(pHungerLevel), fThirstLevel(pThirstLevel), fStamina(pStamina), fIsresting(false), fInventory(pInventoryCapacity){};

//Getter and setter for fHungerLevel
int Player::getHungerLevel() {
    return fHungerLevel;
};
void Player::setHungerLevel(int pHungerLevel) {
    fHungerLevel = pHungerLevel;
};

//Getter and setter for fThirstLevel
int Player::getThirstLevel() {
    return fThirstLevel;
};
void Player::setThirstLevel(int pThirstLevel) {
    fThirstLevel = pThirstLevel;
};

//Getter and setter for fStamina
int Player::getfStamina() {
    return fStamina;
};
void Player::setStamina(int pStamina) {
    fStamina = pStamina;
};

//Getter and setter for fIsresting
bool Player::getfIsresting() {
    return fIsresting;
};
void Player::setIsresting(bool pIsresting) {
    fIsresting = pIsresting;
};

//Increase and decreasing Hunger Level
void Player::IncreaseHungerLevel(int pIncrementValue) {
    fHungerLevel += pIncrementValue;
};
void Player::DecreaseHungerLevel(int pDecrementValue) {
    if(pDecrementValue>= fHungerLevel){
        fHungerLevel = 0;
    }else{
        fHungerLevel -= pDecrementValue;
    }
};

//Increase and decreasing Thirst Level
void Player::IncreaseThirstLevel(int pIncrementValue){
    fHungerLevel += pIncrementValue;
};

void Player::DecreaseThirstLevel(int pDecrementValue) {
    if(pDecrementValue>= fThirstLevel){
        fThirstLevel = 0;
    }else{
        fThirstLevel -= pDecrementValue;
    }
};

//Increase and decreasing Stamina Level
void Player::IncreaseStamina(int pIncrementValue) {
    fStamina += pIncrementValue;
};
void Player::DecreaseStamina(int pDecrementValue) {
    if(fStamina != 0){
        if(pDecrementValue <= fStamina){
            fStamina = 0;
        }else{
            fStamina -= pDecrementValue;
        }
    }
};

void Player::Heal(int pHealValue) {
    int player_currentHealth = this->getCurrentHealth();
    this->setCurrentHealth(player_currentHealth + pHealValue);
};
//Equip item to be used
void Player::EquipItem() {
    fInventory.ViewInventoryItems();
    string item_Name = "";
    cout << "Name of item to equip (Case sensitive and leave no blank space): ";
    cin.clear();
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
void Player::AddItem(Item& pItem) {
    fInventory.AddItem(&pItem);
};

void Player::ViewItems() {
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
        if (getIsFighting()) {
            weapon->Use(*this);
            setAttackDamage(getAttackDamage() - weapon->getDamage());
        }
        else {
            cout << "You are unable to use " << weapon->getName() << " right now, because you are not fighting" << endl;
        }
    }
    else {
        fInventory.UseCurrentItem(*this);
    }
};
