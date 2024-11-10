#pragma once
#include "Entity.h"
#include "Weapon.h"
#include "Stack.h"
#include <SFML/Audio.hpp>

typedef struct attacks {
	string name;
	int damage;
	attacks(string pName = "", int pDamage = 0) : name(pName), damage(pDamage) {}
}Attacks;

class Monster:public Entity
{
	private:
		Weapon* fWeapon; //Monster's weapon
		Stack<Attacks> fComboAttack; // Stack to hold combo attack actions
		Attacks fSkillSet[6];
	public:
		//Default Constructor
		Monster();
		
		//Overloaded Constructor
		Monster(string pName, int pAttackDamage, int pHealth, Weapon* pWeapon);

		//Destructor
		~Monster();
		
		//Getter for fWeapon
		Weapon* getWeapon();

		// Method to add an attack to the combo stack
		void addComboAttack(const string& actionName, int damage);

		// Method to execute the combo
		void executeCombo(Player& pPlayer);
		void selectRandomCombo();

		//Monster's Jumpscares
		void Jumpscare1();
		void Jumpscare2();

		//Ambush Player
		void Ambush(Player& pPlayer);

		//Disturb player while resting
		bool DisturbRest(Player& pPlayer, int pChance);
};