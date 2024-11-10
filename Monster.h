#pragma once
#include "Entity.h"
#include "Weapon.h"
#include <SFML/Audio.hpp>

class Monster:public Entity
{
	private:
		Weapon* fWeapon; //Monster's weapon
	public:
		//Default Constructor
		Monster();
		
		//Overloaded Constructor
		Monster(string pName, int pAttackDamage, int pHealth, Weapon* pWeapon);

		//Destructor
		~Monster();
		
		//Getter for fWeapon
		Weapon* getWeapon();

		//Monster's Jumpscares
		void Jumpscare1();
		void Jumpscare2();

		//Ambush Player
		void Ambush(Player& pPlayer);

		//Disturb player while resting
		bool DisturbRest(Player& pPlayer, int pChance);
};