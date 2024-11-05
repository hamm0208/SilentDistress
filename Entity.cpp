#include "Entity.h"

//Default constructor
Entity::Entity(){
    fName =  "";
    fAttackDamage = 0;
    fHealth = 0;
    fCurrentHealth = 0;
    fIsAlive = true;
    fIsFighting = false;
}

//Constructor
Entity::Entity(string pName, int pAttackDamage, int pHealth): fName(pName), fAttackDamage(pAttackDamage), fHealth(pHealth), fCurrentHealth(pHealth), fIsAlive(true), fIsFighting(false){}

//Getter and seter for fName
string Entity::getName(){
    return fName;
}
void Entity::setName(string pName){
    fName = pName;
};

//Getter and seter for fAttackDamage
int Entity::getAttackDamage(){
    return fAttackDamage;
};
void Entity::setAttackDamage(int pAttackDamage){
    fAttackDamage = pAttackDamage;
};

//Getter and seter for fAttackDamage
int Entity::getHealth(){
    return  fHealth;
};
void Entity::setHealth(int pHealth){
    fHealth = pHealth;
};

//Getter and seter for fAttackDamage
int Entity::getCurrentHealth(){
    return fCurrentHealth; 
};
void Entity::setCurrentHealth(int pCurrentHealth){
    fCurrentHealth = pCurrentHealth;
};

//Getter and setter for fIsAlive
bool Entity::getIsAlive(){
    return fIsAlive;
}
void Entity::setIsAlive(bool pFlag){
    fIsAlive = pFlag;
}

//Getter and setter for fIsFighting
bool Entity::getIsFighting(){
    return fIsFighting;
}
void Entity::setIsFighting(bool pFlag){
    fIsFighting = pFlag;
}

void Entity::Die(){
    setIsAlive(false);
}

//This Entity class take damage from Attacker
void Entity::TakeDamage(int pAttackDamage){
    //If attacker's damage is more than this Entity's current health
    if(pAttackDamage >= this->getCurrentHealth()){
        this->setCurrentHealth(0);
        this->Die();
    }else{
        this->fCurrentHealth-= pAttackDamage; //Minus this Entity's current health with Attacker's Attacker Damage
    }
}

//This entity attack an opponent
void Entity::Attack(Entity& pOpponent){
    pOpponent.TakeDamage(pOpponent.getAttackDamage());
}

