#include <iostream>
#include "Inventory.h"
#include "Food.h"
#include "Drinks.h"
#include "SleepingBag.h"
#include "Weapon.h"
#include "Medical.h"
using namespace std;
const int ALL_ITEM_COUNT = 5;
int main() {
	Inventory player_Inventory(100);
	Item* game_AllItems[ALL_ITEM_COUNT] = {
		new Food("KFC", "Finger Lickin Good", 10, true, 5, false, true, 10, 10),
		new Drinks("Water Bottle", "Best hydration" , 5, true, 10),
		new SleepingBag("Cozy Bed", "Good comfy bed", 20, false, 20),
		new Weapon("Big Axe", "Slash down your foe with this axe", 40, false, 10, 10),
		new Medical("First Aid Kit", "Heal all your wounds", 10, true, 20)
	};
	player_Inventory.AddItem(game_AllItems[0]);
	player_Inventory.AddItem(game_AllItems[0]);
	player_Inventory.DisplayInventory();

	for (int x = 0; x < ALL_ITEM_COUNT; x++) {
		delete game_AllItems[x];
	}
	return 0;
}