#include "SleepingBag.h"
#include "Player.h"

//Constructor
SleepingBag::SleepingBag() :Item("Unknown Bag", "No description available", 0, false), fRecoveryAmount(0) {};
//Overloaded constructor
SleepingBag::SleepingBag(string pName, string pDescription, int pWeight, bool pIsConsumable, int pRecoveryAmount)
    :Item(pName, pDescription, pWeight, pIsConsumable), fRecoveryAmount(pRecoveryAmount) {};

bool SleepingBag::Use(Player& pPlayer) {
    if(pPlayer.getCurrentStaminaLevel() <= pPlayer.getMaxStaminaLevel()){
        pPlayer.IncreaseStamina(fRecoveryAmount);
        pPlayer.IncreaseHungerLevel(2);
        pPlayer.IncreaseThirstLevel(2);
        cout<<"Your hunger level and thrist level has been incresed by 2 after your rest" <<endl;
        return true;
    }else{
        cout<< "Your stamina level is full!" <<endl;
        return false;
    }
}

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