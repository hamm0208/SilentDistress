#include "Food.h"
#include "Player.h"

//Default Constructor
Food::Food():Item("Unknown Food", "No description available", 0, true), //Default values for base class
    fNutrition(0),                                                      //Default nutrition value
    fIsCooked(false),                                                   //Default to uncooked
    fIsCookable(true),                                                  //Default to cookable
    fHealthRestorationValue(0),                                         //Default health restoration to 0
    fStaminaValue(0){                                                   //Default stamina value to 0
}

//Initialize attributes and base class, Item
Food::Food(string pName, string pDescription, int pWeight, bool pIsConsumable, int pNutrition, bool pIsCooked, bool pIsCookable, int pHealthRestorationValue, int pStaminaValue):
Item(pName, pDescription, pWeight, pIsConsumable),
fNutrition(pNutrition), fIsCookable(pIsCookable), fIsCooked(pIsCooked), fHealthRestorationValue(pHealthRestorationValue), fStaminaValue(pStaminaValue){}

//Eat the food
bool Food::Use(Player& pPlayer){
    int hunger_decreaseValue = fIsCooked?(fNutrition+2):fNutrition;  //If fIsCooked is true, +2 nutrition value
    if(pPlayer.getCurrentHungerLevel() == 0){
        cout<< "You're full right now" <<endl;
        system("PAUSE");
        return false;
    }else{
        pPlayer.DecreaseHungerLevel(hunger_decreaseValue);  //Decrease player's hunger level
        pPlayer.IncreaseStamina(fStaminaValue);             //Increase player's stamina
        pPlayer.Heal(fHealthRestorationValue);              //Increase player's health
        system("PAUSE");
        return true;
    }
}
//Display Food's attributes
void Food::Inspect(){
    Item::Inspect();
    cout << "Is Cookable:\t\t\t" << (fIsCookable ? "Yes" : "No") << endl;
    cout << "Health Restoration Value:\t" << fHealthRestorationValue << endl;
    cout << "Stamina Restoration Value:\t" << fStaminaValue << endl;
}

//Clone new Food
Item* Food::clone() const {
    return new Food(*this); // Use the copy constructor of Weapon
}

//Getter and setter for fNutrition
int Food::getNutrition() {
    return fNutrition;
}
void Food::setNutrition(int  pNutrition) {
    fNutrition = pNutrition;
}

//Getter and setter for fHealthRestorationValue
int Food::getHealthRestorationValue() {
    return fHealthRestorationValue;
}
void Food::setHealthRestorationValue(int  pHealthRestorationValue) {
    fHealthRestorationValue = pHealthRestorationValue;
}
//Getter and setter for fStaminaValue
int Food::getStaminaValue() {
    return fStaminaValue;
}
void Food::setStaminaValue(int  pStaminaValue) {
    fStaminaValue = pStaminaValue;
}

//Getter and setter for fIsCooked
bool Food::getIsCooked() {
    return fIsCooked;
}
void Food::setIsCooked(bool pIsCooked) {
    fIsCooked = pIsCooked;
}

//Getter and setter for fIsCookable
bool Food::getIsCookable() {
    return fIsCookable;
}
void Food::setIsCookable(bool pIsCookable) {
    fIsCookable = pIsCookable;
}