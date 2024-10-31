#include <iostream>
#include "Inventory.h"
#include "Food.h"
#include "Drinks.h"
using namespace std;

int main() {
	Inventory player_Inventory(100);
	Food* food_KFC = new Food("KFC", "Finger Lickin Good", 10, true, 5, false, true, 10, 10);
	Drinks* drink_WaterBottle = new Drinks("Water Bottle", "Best hydration" , 5, true, 10);

	player_Inventory.AddItem(food_KFC);
	player_Inventory.AddItem(drink_WaterBottle);
	player_Inventory.DisplayInventory();
	return 0;
}