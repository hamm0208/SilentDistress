#pragma once
#include "Entity.h"
#include "Weapon.h"
#include <SFML/Audio.hpp>

class Monster:public Entity
{
	private:
		Weapon* fWeapon;
	public:
		Monster();
		Monster(string pName, int pAttackDamage, int pHealth, Weapon* pWeapon);
		~Monster();
		Weapon* getWeapon();
		void Jumpscare1();
		void Jumpscare2();
		void Ambush(Player& pPlayer);
		bool DisturbRest(Player& pPlayer, int pChance);
};