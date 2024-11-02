#include "Drinks.h"
#include "Player.h"

Drinks::Drinks():Item("Unknown Drinks", "No description available", 0, true), //Default values for base class
fHydrationValue(0){}

//Initialize attributes and base class, Item
Drinks::Drinks(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHydrationValue)
:Item(pName, pDescription, pWeight, pIsConsumable),
fHydrationValue(pHydrationValue){};

//Use the Drinks
bool Drinks::Use(Player& pPlayer){
    if(pPlayer.getCurrentThirstLevel() == pPlayer.getMaxThirstLevel()){
        cout<< "You're not thirsty right now" <<endl;
        return false;
    }else{
        pPlayer.DecreaseThirstLevel(fHydrationValue);   //Decrease Player's Thirst Level
        return true;
    }
}
//Display Drinks's attributes
void Drinks::Inspect(){
    Item::Inspect();
    cout << "Hydration Value:\t\t" << fHydrationValue << endl; //Display hydration value
}
//Clone new Drinks
Item* Drinks::clone() const {
    return new Drinks(*this);  // Use the copy constructor of Drinks
}

//Getter and setter for fHydrationValue
int Drinks::getHydrationValue(){
            return fHydrationValue;
        };
void Drinks::setHydrationValue(int pHydrationValue){
    fHydrationValue = pHydrationValue;
};