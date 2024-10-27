#include "Food.h"
//Default Constructor
Food::Food():Item("Unknown Food", "No description available", 0, true), // Default values for base class
    fNutrition(0),                                                      // Default nutrition value
    fIsCooked(false),                                                   // Default to uncooked
    fIsCookable(true),                                                  // Default to cookable
    fHealthRestorationValue(0){                                         //Default to 0
}

//Initialize attributes and base class, Item
Food::Food(string pName, string pDescription, int pWeight, bool pIsConsumable, int pNutrition, bool pIsCooked, bool pIsCookable, int pHealthRestorationValue):Item(pName, pDescription, pWeight, pIsConsumable),
fNutrition(pNutrition), fIsCookable(pIsCookable), fIsCooked(pIsCooked), fHealthRestorationValue(pHealthRestorationValue){}

void Food::Use(Player& pPlayer){
    int player_hungerLevel = pPlayer.getHungerLevel();
    /*
    If player hunger level is 0, then you cant eat the food, errr then also increase their stamina when you the food. errr maybe increase their health also lah
    */
}