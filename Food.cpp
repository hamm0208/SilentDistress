#include "Food.h"
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
void Food::Use(Player& pPlayer){
    int player_hungerLevel = pPlayer.getHungerLevel(); //Player's hunger value
    int hunger_decreaseValue = fIsCooked?(fNutrition+2):fNutrition;  //If fIsCooked is true, +2 nutrition value
    if(player_hungerLevel == 0){
        cout<< "You're full right now" <<endl;
    }else{
        pPlayer.DecreaseHungerLevel(hunger_decreaseValue);  //Decrease player's hunger level
        pPlayer.IncreaseStamina(fStaminaValue);             //Increase player's stamina
        pPlayer.Heal(fHealthRestorationValue);              //Increase player's health
    }
}
//Display Food's attributes
void Food::Inspect(){
    Item::Inspect();
    cout << "Is Cookable:\t\t\t" << (fIsCookable ? "Yes" : "No") << endl;
    cout << "Health Restoration Value:\t" << fHealthRestorationValue << endl;
    cout << "Stamina Restoration Value:\t" << fStaminaValue << endl;
}