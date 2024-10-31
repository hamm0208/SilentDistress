#include "Medical.h"
//Default constructor
Medical::Medical():Item("Unknown Medical", "No description available", 0, true), fHealAmount(0){}
//Overloaded constructor
Medical::Medical(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHealAmount)
:Item(pName, pDescription, pWeight, pIsConsumable), fHealAmount(pHealAmount){};

//Use the Medical Item
void Medical::Use(Player& pPlayer){
    int player_newHealth = pPlayer.getCurrentHealth() + fHealAmount;
    if( player_newHealth >= pPlayer.getHealth()){
        pPlayer.setCurrentHealth(pPlayer.getHealth());   //Increase Player's HP Level to player's max HP
    }else{
        pPlayer.setCurrentHealth(player_newHealth);     //Increase Player's HP Level
    }
}
//Display Medical's attributes
void Medical::Inspect(){
    Item::Inspect();
    cout << "Heal amount:\t\t\t" << fHealAmount << endl; //Display hydration value
}
//Getter and setter for fHydrationValue
int Medical::getHealAmount(){
            return fHealAmount;
        };
void Medical::setHealAmount(int pHealAmount){
    fHealAmount = pHealAmount;
};