#include <iostream>
#include "Player.h"
#include "Inventory.h" //Finish commenting on the .cpp 
#include "Food.h"
#include "Drinks.h"
#include "SleepingBag.h"
#include "Weapon.h"
#include "Medical.h"
#include "Monster.h"
#include "Decision.h"
#include "Scene.h"
#include "Game.h"
using namespace std;
const int ALL_ITEM_COUNT = 10;
int main() {
	system("Color 0E");
	Item* game_AllItems[ALL_ITEM_COUNT] = {
		new Food("KFC", "Finger Lickin Good", 10, true, 5, false, true, 10, 10),
		new Drinks("Water Bottle", "Best hydration" , 5, true, 10),
		new SleepingBag("Cozy Bed", "Good comfy bed", 20, false, 20),
		new Weapon("Big Axe", "Slash down your foe with this axe", 40, false, 10, 10),
		new Medical("First Aid Kit", "Heal all your wounds", 10, true, 20),
	};
	Weapon* defaultWeapon = new Weapon("Bare Hands", "Good Ole Bare Knuckles", 0, false, 1, 1000);
	Weapon* monsterWeapon = new Weapon("Claw of the Damned",  "A razor-sharp claw imbued with dark energy. It causes deep wounds and instills fear in its victims.", 10, false, 50, 100);
	Monster* monster = new Monster("Scary Monster", 50, 200, monsterWeapon);
	Player* newPlayer = new Player("John Wick", 10, 100, 0, 0, 100, 100);

	newPlayer->AddItem(defaultWeapon);
	newPlayer->getInventory().setCurrentItem(newPlayer->getInventory().SearchItem("Bare Hands"));
	system("CLS");

	Scene* scene1 = new Scene("Plane Crashsite", "Plane Crashsite", 6);
	Item* scene1_loot[6]{
		game_AllItems[0],
		game_AllItems[1],
		game_AllItems[1],
		game_AllItems[2],
		game_AllItems[3],
		game_AllItems[4],
	};
	for (int x = 0; x < 6; x++) {
		scene1->AddLoot(scene1_loot[x]);
	}
	BTree<Scene*>* rootScene = new BTree<Scene*>(scene1);
	Game newGame(newPlayer, monster);
	newGame.setRootScene(rootScene);
	newGame.setTreeTarget(newGame.getRootScene());
	newGame.Play();


	delete scene1;
	delete monsterWeapon;
	delete defaultWeapon;
	for (int x = 0; x < ALL_ITEM_COUNT; x++) {
		if (game_AllItems[x] != nullptr) {
			delete game_AllItems[x];
			game_AllItems[x] = nullptr;
		}
	}
	return 0;
}
