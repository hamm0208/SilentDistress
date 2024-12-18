#pragma once
#include <iostream>
using namespace std;

class Player;  // Forward declaration of Player class, to avoid circular dependencies (CHATGPT BTW FTW, but basically I asked ChatGPT why when i #include "Player" will cause an error)
class Item{
    private:
        string fName;           //Name of item
        string fDescription;    //Description of item
        int fWeight;            //Weight of the item
        bool fIsConsumable;     //If item is consumable
    public:
        Item(); //Default constructor
        Item(string pName, string pDescription, int pWeight, bool pIsConsumable); //Constructor to load the parameter into the attributes
        virtual bool Use(Player& pPlayer) = 0;  //Apply effects of the item to the Player
        virtual void Inspect();                 //Display all the attributes in Items
        virtual Item* clone() const = 0;        //Clone new item object

        //Getter and setter for fName
        string getName();
        void setName(string pName);

        //Getter and setter for fDescription
        string getDescription();
        void setDescription(string pDescription);

        //Getter and setter for fWeight
        int getWeight();
        void setWeight(int pWeight);

        //Getter and setter for fIsConsumable
        bool getIsConsumable();
        void setIsConsumable(bool pIsConsumable);

};