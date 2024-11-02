#include "Medical.h"
#include "Player.h"

//Default constructor
Medical::Medical():Item("Unknown Medical", "No description available", 0, true), fHealAmount(0){}

//Overloaded constructor
Medical::Medical(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHealAmount)
:Item(pName, pDescription, pWeight, pIsConsumable), fHealAmount(pHealAmount){};

//Use the Medical Item
bool Medical::Use(Player& pPlayer){
    int player_newHealth = pPlayer.getCurrentHealth() + fHealAmount;
    if(pPlayer.getCurrentHealth() == pPlayer.getHealth()){
        cout<< "You are full HP right now!" <<endl;
        return false;
    }else{
        pPlayer.Heal(fHealAmount);   //Increase Player's HP Level to player's max HP
        cout<< "You have been healed!!" <<endl;
        return true;
    }
}
//Display Medical's attributes
void Medical::Inspect(){
    Item::Inspect();
    cout << "Heal amount:\t\t\t" << fHealAmount << endl; //Display hydration value
}

//Clone new Medical
Item* Medical::clone() const {
    return new Medical(*this); // Use the copy constructor of Weapon
}

//Getter and setter for fHydrationValue
int Medical::getHealAmount(){
    return fHealAmount;
};
void Medical::setHealAmount(int pHealAmount){
    fHealAmount = pHealAmount;
};