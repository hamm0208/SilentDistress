#pragma once
#include <iostream>

using namespace std;
class Entity
{
	private:
		string fName; //Name of entity
		int fAttackDamage; //Entity Attack Damage
		int fHealth; //Entity max health
		int fCurrentHealth; //Entity's current health
		bool fIsAlive; //Is the Entity Alive
	public:
		Entity(); //Default Constructor To set a default value for the attributes
		Entity(string pName, int pAttackDam, int pHealth); //Constructor to load the parameter into the attributes
		//Getter and seter for fName
		string getName();
		void setName(string pName);

		//Getter and seter for fAttackDamage
		int getAttackDamage();
		void setAttackDamage(int pAttackDamage);

		//Getter and seter for fAttackDamage
		int getHealth();
		void setHealth(int pHealth);

		//Getter and seter for fAttackDamage
		int getCurrentHealth();
		void setCurrentHealth(int pCurrentHealth);

		//Getter and setter for fIsAlive
		bool getIsAlive();
		void setIsAlive(bool flag);

		//Entity dies
		void Die();

		//This entity will take damage that will take in an Attacker's fAttackDamage
		void TakeDamage(Entity& pAttacker);

		//Attack opponent Entity
		void Attack(Entity& pOpponent);
};

