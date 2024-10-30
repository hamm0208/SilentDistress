#include "Player.h"

Player::Player():Entity() {
    fHungerLevel = 0;
    fThirstLevel = 0;
    fStamina = 0;
    fIsresting = false;
}

//Initialise all the parameter into the class's attributes
Player::Player(string pName, int pAttackDamage, int pHealth, int pHungerLevel, int pThirstLevel, int pStamina) :
    Entity(pName, pAttackDamage, pHealth), fHungerLevel(pHungerLevel), fThirstLevel(pThirstLevel), fStamina(pStamina), fIsresting(false) {};

//Getter and setter for fHungerLevel
int Player::getHungerLevel() {
    return fHungerLevel;
};
void Player::setHungerLevel(int pHungerLevel) {
    fHungerLevel = pHungerLevel;
};

//Getter and setter for fThirstLevel
int Player::getThirstLevel() {
    return fThirstLevel;
};
void Player::setThirstLevel(int pThirstLevel) {
    fThirstLevel = pThirstLevel;
};

//Getter and setter for fStamina
int Player::getfStamina() {
    return fStamina;
};
void Player::setStamina(int pStamina) {
    fStamina = pStamina;
};

//Getter and setter for fIsresting
bool Player::getfIsresting() {
    return fIsresting;
};
void Player::setIsresting(bool pIsresting) {
    fIsresting = pIsresting;
};

//Increase and decreasing Hunger Level
void Player::IncreaseHungerLevel(int pIncrementValue) {
    fHungerLevel += pIncrementValue;
};
void Player::DecreaseHungerLevel(int pDecrementValue) {
    if(pDecrementValue>= fHungerLevel){
        fHungerLevel = 0;
    }else{
        fHungerLevel -= pDecrementValue;
    }
};

void Player::IncreaseThirstLevel(int pIncrementValue){
    fHungerLevel += pIncrementValue;
};

void Player::DecreaseThirstLevel(int pDecrementValue) {
    if(pDecrementValue>= fThirstLevel){
        fThirstLevel = 0;
    }else{
        fThirstLevel -= pDecrementValue;
    }
};

//Increase and decreasing Stamina Level
void Player::IncreaseStamina(int pIncrementValue) {
    fStamina += pIncrementValue;
};
void Player::DecreaseStamina(int pDecrementValue) {
    if(fStamina != 0){
        if(pDecrementValue <= fStamina){
            fStamina = 0;
        }else{
            fStamina -= pDecrementValue;
        }
    }
};

void Player::Heal(int pHealValue) {
    int player_currentHealth = this->getCurrentHealth();
    this->setCurrentHealth(player_currentHealth + pHealValue);
};