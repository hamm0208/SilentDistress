#include "Weapon.h"
#include "Player.h"

//Default Constructor
Weapon::Weapon():Item("Unknown Weapon", "No description available", 0, false){
    fDamage = 0;
    fDurability = 0;
    fCurrentDurability = fDurability;
}
//Overloaded constructor
Weapon::Weapon(string pName, string pDescription, int pWeight, bool pIsConsumable, int pDamage, int pDurability)
:Item(pName, pDescription, pWeight, pIsConsumable), fDamage(pDamage), fDurability(pDurability){
    fCurrentDurability = fDurability;
};

//Weapon will increase Player's damage
bool Weapon::Use(Player& pPlayer){
    int player_newDamage = 0; 
    if(pPlayer.getIsFighting()){
        player_newDamage = pPlayer.getAttackDamage()+fDamage; //Else, it will increase the damage
        pPlayer.setAttackDamage(player_newDamage);   //Increase player's attack damage, if player Use weapon, it will decrease the durability by 1
        return true;
    }else{
        return false;
    }
}

//Display Weapon's attributes
void Weapon::Inspect(){
    Item::Inspect();
    cout <<"Damage:\t\t\t\t" << fDamage << endl;
    cout <<"Durability:\t\t\t" << "(" << fCurrentDurability << "/" << fDurability << ")" << endl;
}

//Clone new weapon
Item* Weapon::clone() const {
    return new Weapon(*this); // Use the copy constructor of Weapon
}

//Getter and setter for fDamage
int Weapon::getDamage(){
    return fDamage;
}
void Weapon::setDamage(int pDamage){
    fDamage = pDamage;
}
//Getter and setter for fDurability
int Weapon::getDurability(){
    return fDurability;
}
void Weapon::setDurability(int pDurability){
    fDurability = pDurability;
}
//Getter and setter for fCurrentDurability
int Weapon::getCurrentDurability(){
    return fCurrentDurability;
}
void Weapon::setCurrentDurability(int pCurrentDurability) {
    fCurrentDurability = pCurrentDurability;
}
void Weapon::decreaseCurrentDurability(int pDecrementValue){
    fCurrentDurability -= pDecrementValue;
}