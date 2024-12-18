#include "Item.h"
#include "Player.h"

//Default constructor
Item::Item(){
    fName = "";
    fDescription = "";
    fWeight = 0;
    fIsConsumable = false;
}
Item::Item( string pName, string pDescription, int pWeight, bool pIsConsumable):fName(pName),fDescription(pDescription),fWeight(pWeight), fIsConsumable(pIsConsumable){}

//Getter and setter for fName
string Item::getName(){
    return fName;
};
void Item::setName(string pName){
    fName = pName;
};

//Getter and setter for fDescription
string Item::getDescription(){
    return fDescription;
};
void Item::setDescription(string pDescription){
    fDescription = pDescription;
};

//Getter and setter for fWeight
int Item::getWeight(){
    return fWeight;
};
void Item::setWeight(int pWeight){
    fWeight = pWeight;
};

//Getter and setter for fIsConsumable
bool Item::getIsConsumable(){
    return fIsConsumable;
};
void Item::setIsConsumable(bool pIsConsumable){
    fIsConsumable = pIsConsumable;
};

//Inspect Item, virtual function
void Item::Inspect() {
    cout << "Name:\t\t\t\t" << fName << "\n";
    cout << "Description:\t\t\t" << fDescription << "\n";
    cout << "Weight:\t\t\t\t" << fWeight << "\n";
    cout << "Consumable:\t\t\t" << (fIsConsumable ? "Yes" : "No") << endl;
}

