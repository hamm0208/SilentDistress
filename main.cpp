#include <iostream>
#include "Player.h"
#include "Inventory.h" //Finish commenting on the .cpp 
#include "Food.h"
#include "Drinks.h"
#include "SleepingBag.h"
#include "Weapon.h"
#include "Medical.h"
#include "Monster.h"

using namespace std;
const int ALL_ITEM_COUNT = 10;
int main() {
	Item* game_AllItems[ALL_ITEM_COUNT] = {
		new Food("KFC", "Finger Lickin Good", 10, true, 5, false, true, 10, 10),
		new Drinks("Water Bottle", "Best hydration" , 5, true, 10),
		new SleepingBag("Cozy Bed", "Good comfy bed", 20, false, 20),
		new Weapon("Big Axe", "Slash down your foe with this axe", 40, false, 10, 10),
		new Medical("First Aid Kit", "Heal all your wounds", 10, true, 20)
	};
	Weapon* monster_weapon = new Weapon("Claw of the Damned",  "A razor-sharp claw imbued with dark energy. It causes deep wounds and instills fear in its victims.", 10, false, 50, 100);
	Monster monster = Monster("Scary Monster", 50, 200, monster_weapon);

	monster.Jumpscare();

	for (int x = 0; x < ALL_ITEM_COUNT; x++) {
		if (game_AllItems[x] != nullptr) {
			delete game_AllItems[x];
			game_AllItems[x] = nullptr;
		}
	}

	/*
	Player newPlayer = Player("John Wick", 10, 100, 0, 0, 100, 100);
	

	newPlayer.AddItem(game_AllItems[0]);
	newPlayer.AddItem(game_AllItems[1]);
	newPlayer.AddItem(game_AllItems[2]);
	newPlayer.AddItem(game_AllItems[3]);
	newPlayer.AddItem(game_AllItems[4]);
	newPlayer.DiscardItem();
	newPlayer.ViewItems();
	
	*/
	return 0;
}
