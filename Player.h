#pragma once
#include "Entity.h"
#include "Inventory.h"
#include "SinglyLinkedList.h"
#include <stdlib.h>
class Decision; 
class Monster;

class Player :public Entity{
     private:
        /*
            0 - 10 Hunger and thirst Level, the higher the level, the more hungry you are, will affect your fStamina, fThirst, and fHealth
            Stamina...TBD
        */
        int fMaxHungerLevel;                    //Player's Max Hunger Level
        int fMaxThirstLevel;                    //Player's Max Thirst Level
        int fMaxStaminaLevel;                   //Player's Max Stamina Level
        bool fIsResting;                        //Is Player Resting Flag
        int fCurrentHungerLevel;                //Current Hunger Level
        int fCurrentThirstLevel;                //Current Thirst Level
        int fCurrentStaminaLevel;               //Current Stamina Level
        Inventory fInventory;                   //Player's Inventory
        SinglyLinkedList<Decision> fDecisionsMade;  //Decisions made by the player
    public:
        Player();
        Player(string pName, int pAttackDamage, const int pHealth = 100, const int pHungerLevel = 10, const int pThirstLevel = 10 , const int pStamina = 10, const int pInventoryCapacity = 100);
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

        Inventory& getInventory();

        //Getter and setter for fIsresting
        bool getfIsResting();
        void setIsResting(bool pIsResting);
        
        void IncreaseHungerLevel(int pIncrementValue); //Increase hunger level
        void DecreaseHungerLevel(int pDecrementValue); //Decrease hunger level, If pDecrementValue is more than fMaxHungerLevel, then set fMaxHungerLevel back to 0

        void IncreaseThirstLevel(int pIncrementValue); //Increase thirst level
        void DecreaseThirstLevel(int pDecrementValue); //Decrease thirst level, If pDecrementValue is more than fMaxThirstLevel, then set fMaxThirstLevel back to 0

        void ShowAttributes();                          //Show player's attributes
        void IncreaseStamina(int pIncrementValue);      //Increase Stamina
        void DecreaseStamina(int pDecrementValue);      //Decrease Stamina
        void Heal(int pHealValue);                      //Heal Player
        void AddItem(Item* pItem);                      //Add item to fInventory
        bool EquipItem();                               //Equip item to use
        void ViewItems();                               //View all items in inventory
        void ViewItemsDetails();                        //View all items DETAILS in inventory
        void ViewItemDetails(Item& pItem);              //View A item in inventory
        bool DiscardItem();                             //Discard an item in inventory
        void SearchItems();                             //Search an item in inventory
        Item* getCurrentItem();                         //Get currently equiped item
        bool UseCurrentItem();                          //Use currently equiped item
        void MakeDecision(Decision& pDecision);
        void ShowDecision();
        void ApplyEffects(Monster& pMonster);
};