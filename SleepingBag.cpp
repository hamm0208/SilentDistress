#include "SleepingBag.h"
#include "Player.h"
#include "Monster.h"

//Constructor
SleepingBag::SleepingBag() :Item("Unknown Bag", "No description available", 0, false), fRecoveryAmount(0), fMonster(nullptr) {};
//Overloaded constructor
SleepingBag::SleepingBag(string pName, string pDescription, int pWeight, bool pIsConsumable, int pRecoveryAmount, Monster* pMonster)
:Item(pName, pDescription, pWeight, pIsConsumable), fRecoveryAmount(pRecoveryAmount), fMonster(pMonster) {};

//Use Sleeping Bag, increase player's stamina
bool SleepingBag::Use(Player& pPlayer) {
    if(pPlayer.getCurrentStaminaLevel() != pPlayer.getMaxStaminaLevel()){ //If player's current stamina is lower or equal than player's max stamina then...
        pPlayer.IncreaseStamina(fRecoveryAmount);   //Increase stamina
        pPlayer.setIsResting(true);
        fMonster->DisturbRest(pPlayer, 20);
        cout << "Your stamina has increased by " << fRecoveryAmount << endl;
        pPlayer.setIsResting(false);
        //you get hungry and thirsty when you wake up
        pPlayer.IncreaseHungerLevel(1);             //Increase hunger level 
        pPlayer.IncreaseThirstLevel(1);             //Increase thirst level
        return true;
    }else{
        return false;
    }
}

//Inspect SleepingBag attributes
void SleepingBag::Inspect() {
    Item::Inspect();
    cout << "Recovery Amount:\t\t" << fRecoveryAmount << endl;
}

//Clone new SleepingBag
Item* SleepingBag::clone() const {
    return new SleepingBag(*this); // Use the copy constructor of Weapon
}

//Getter and setter for fRecoveryAmount
int SleepingBag::getRecoveryAmount() {
    return fRecoveryAmount;
}
void SleepingBag::setRecoveryAmount(int  pRecoveryAmount) {
    fRecoveryAmount = pRecoveryAmount;
}