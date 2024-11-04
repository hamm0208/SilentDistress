#pragma once
#include "Entity.h"
#include "Weapon.h"
#include <SFML/Audio.hpp>

class Monster:public Entity
{
	private:
		Weapon* fWeapon;

	public:
		//Monster();
		//Monster(string pName, int pAttackDamage, int pHealth, Weapon* fWeapon);
		//Weapon* getWeapon();
		//void Jumpscare();
		//void Ambush(Player& pPlayer);
		//void DisturbRest(Player& pPlayer);
};