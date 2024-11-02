/*
Remove this when youre done broooo
Maybe sleeping will count as 2 turns, and will increase hunger and thirst
*/
#pragma once
#include "Entity.h"
#include "Inventory.h"
class Player :public Entity{
     private:
        /*
            0 - 10 Hunger and thirst Level, the higher the level, the more hungry you are, will affect your fStamina, fThirst, and fHealth
            Stamina...TBD
        */
        int fMaxHungerLevel;        //Player's Max Hunger Level
        int fMaxThirstLevel;        //Player's Max Thirst Level
        int fMaxStaminaLevel;       //Player's Max Stamina Level
        bool fIsresting;            //Is Player Resting Flag
        int fCurrentHungerLevel;    //Current Hunger Level
        int fCurrentThirstLevel;    //Current Thirst Level
        int fCurrentStaminaLevel;   //Current Stamina Level
        Inventory fInventory;       //Player's Inventory
        //List<Decision> fDecisions; 
    public:
        Player();
        Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina, int pInventoryCapacity);
        //Getter and setter for fMaxHungerLevel
        int getMaxHungerLevel();
        void setMaxHungerLevel(int pHungerLevel);

        //Getter and setter for fCurrentHungerLevel 
        int getCurrentHungerLevel();
        void setCurrentHungerLevel(int pHungerLevel);

        //Getter and setter for fMaxThirstLevel
        int getMaxThirstLevel();
        void setMaxThirstLevel(int pThirstLevel);

        //Getter and setter for fCurrentThirstLevel 
        int getCurrentThirstLevel();
        void setCurrentThirstLevel(int pThirstLevel);

        //Getter and setter for fMaxStaminaLevel
        int getMaxStaminaLevel();
        void setMaxStaminaLevel(int pStamina);

        //Getter and setter for fCurrentStaminaLevel 
        int getCurrentStaminaLevel();
        void setCurrentStaminaLevel(int pStamina);

        //Getter and setter for fIsresting
        bool getfIsresting();
        void setIsresting(bool pIsresting);
        
        void IncreaseHungerLevel(int pIncrementValue); //Increase hunger level
        void DecreaseHungerLevel(int pDecrementValue); //Decrease hunger level, If pDecrementValue is more than fMaxHungerLevel, then set fMaxHungerLevel back to 0

        void IncreaseThirstLevel(int pIncrementValue); //Increase thirst level
        void DecreaseThirstLevel(int pDecrementValue); //Decrease thirst level, If pDecrementValue is more than fMaxThirstLevel, then set fMaxThirstLevel back to 0

        void IncreaseStamina(int pIncrementValue);      //Increase Stamina
        void DecreaseStamina(int pDecrementValue);      //Decrease Stamina
        void Heal(int pHealValue);                      //Heal Player
        void AddItem(Item* pItem);                      //Add item to fInventory
        void EquipItem();                               //Equip item to use
        void ViewItems();                               //View all items in inventory
        void ViewItemsDetails();                        //View all items DETAILS in inventory
        void ViewItemDetails(Item& pItem);              //View A item in inventory
        void DiscardItem();                             //Discard an item in inventory
        void SearchItems();                             //Search an item in inventory
        Item* getCurrentItem();                         //Get currently equiped item
        void UseCurrentItem();                          //Use currently equiped item
        // void ApplyEffects(); This function will run every turn to check for the Hunger level, thirst level, and stamina
};