#include <iostream>
#include "Player.h"
#include "Inventory.h"
#include "Food.h"
#include "Drinks.h"
#include "SleepingBag.h"
#include "Weapon.h"
#include "Medical.h"
#include "Monster.h"
#include "Decision.h"
#include "Scene.h"
#include "Game.h"
#include "Iterator1D.h"
#include "Queue.h"
#include "SFML/Audio/Sound.hpp"
using namespace std;
const int ALL_ITEM_COUNT = 14;
const int ALL_SCENE_COUNT = 5;

//Loading Plane crash sound
void PlayPlaneCrashSound() {
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("plane_crash.wav")) {
		cerr << "Error loading plane_crash.wav" << endl;
		return;
	}

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	// Keep the sound active until it finishes playing
	while (sound.getStatus() == sf::Sound::Playing) {
		sf::sleep(sf::milliseconds(100)); // Small delay to keep the sound playing
	}
}

//Display Text with a delay
void DisplayDelayText(string fDialogue, int seconds) {
	cout << fDialogue << endl;
	this_thread::sleep_for(chrono::seconds(seconds));
}

void RulesOfTheGame() {
	system("PAUSE");
	system("CLS");
	cout << "Goal:\nPlayer needs to survive the aftermath of a plane crash in a hostile jungle by gathering resources,\n"
		<< "managing hunger and stamina. Players must explore the jungle to find the end of the jungle to meet the rescue team\n" << endl;

	this_thread::sleep_for(chrono::seconds(1));
	cout << "Information: " << endl;
	DisplayDelayText("1. Turn-Based Gameplay:\nThe game operates on turns where each player action (moving, searching, using/equipping/discarding items) counts as one turn.\n", 1);

	DisplayDelayText("2. Decision-Based Outcomes:\nEvery choice impacts the storyline, influencing endings based on survival, resource management, and decisions.\n", 1);

	DisplayDelayText("3. Victory Condition:\nReach the rescue team without succumbing to hunger, thirst, or the monster's attacks.\n", 1);

	DisplayDelayText("4. Defeat Condition:\nThe game ends if the player's health, hunger, or stamina drops to zero or if the monster defeats them.\n", 1);
	system("PAUSE");
	system("CLS");

	//Survival System Rules
	cout << "Survival System Rules:\n";
	DisplayDelayText("1. Hunger Effects: If hunger reaches certain levels, stamina decreases, thirst increases, or the player takes damage:\n", 1);
	DisplayDelayText("2. Thirst Effects: If thirst reaches certain levels, stamina decreases and the player may take damage:\n", 1);
	DisplayDelayText("3. Stamina Effects: Low stamina affects hunger, thirst, and may result in death if stamina reaches zero:\n", 1);
	system("PAUSE");
	system("CLS");
}

//Introduction to the game
bool Introduction(Game& pGame) {
	string GameTittle =
		"|\t\t _____ _____ _      _____ _   _ _____              |\n"
		"|\t\t/  ___|_   _| |    |  ___| \\ | |_   _|             |\n"
		"|\t\t\\ `--.  | | | |    | |__ |  \\| | | |               |\n"
		"|\t\t `--. \\ | | | |    |  __|| . ` | | |               |\n"
		"|\t\t/\\__/ /_| |_| |____| |___| |\\  | | |               |\n"
		"|\t\t\\____/ \\___/\\_____\\/____/\\_| \\_/ \\_/	   \t   |\n"
		"|\t                                                           |\n"
		"|\t______ _____ _____ ___________ _____ _____ _____           |\n"
		"|\t|  _  \\_   _/  ___|_   _| ___ \\  ___/  ___/  ___|          |\n"
		"|\t| | | | | | \\ `--.  | | | |_/ / |__ \\ `--.\\ `--.           |\n"
		"|\t| | | | | |  `--. \\ | | |    /|  __| `--. \\`--. \\          |\n"
		"|\t| |/ / _| |_\\/__/ / | | | |\\ \\| |___\\/__/ /\\__/ /          |\n"
		"|\t|___/  \\___/\\____/  \\_/ \\_| \\_\\____/\\____/\\____/           |\n";

	bool exitMenu = false;

	while (!exitMenu) {
		system("CLS");
		cout << "+------------------------------------------------------------------+" << endl;
		cout << GameTittle;
		cout << "+------------------------------------------------------------------+" << endl;
		cout << "\nSilent Distress is a horror survival text game where the player,\n"
			<< "as the lone survivor of a plane crash, must navigate a dark jungle,\n"
			<< "manage resources, and survive encounters with a lurking monster.\n" << endl;
		cout << "\nPlease select an option:\n";
		cout << "1. Start New Game\n";
		cout << "2. View Previous Decisions\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: ";

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "\nStarting a new game...\n";
			exitMenu = true;  // Exit menu loop and start the game
			RulesOfTheGame();
			return true;  // Proceed to the game
			break;
		case 2:
			cout << "\nLoading previous decisions...\n";
			pGame.LoadPlayerMenuDecisions();
			system("PAUSE");
			break;
		case 3:
			cout << "Exiting the game. Goodbye!\n";
			exitMenu = true;
			return false;  // Exit the game
			break;
		default:
			cout << "Invalid option. Please try again.\n";
			system("PAUSE");
			break;
		}
	}
	return false;
}

//Fight Scene
int FightScene(Player& pPlayer, Monster& pMonster){
	pPlayer.setIsFighting(true);	//Player is now fighting
	int choice = 0;					//What choice would the player do
	bool turnFinish = false;		//Is turn finish
	do {
		system("CLS");
		//Show Player's attributes
		cout << "Your Attributes:";
		cout << "\nHealth: \t" << pPlayer.getCurrentHealth() << "/" << pPlayer.getHealth() << endl;
		cout << "Hunger: \t" << pPlayer.getCurrentHungerLevel() << "/" << pPlayer.getMaxHungerLevel() << endl;
		cout << "Thirst: \t" << pPlayer.getCurrentThirstLevel() << "/" << pPlayer.getMaxThirstLevel() << endl;
		cout << "Stamina: \t" << pPlayer.getCurrentStaminaLevel() << "/" << pPlayer.getMaxStaminaLevel() << endl;
		cout << "Damage: \t" << pPlayer.getAttackDamage()<< endl;
		if (pPlayer.getCurrentItem() == nullptr) {
			cout << "Equiped Item: \tEmpty Slot" << endl;
		}
		else {
			cout << "Equiped Item: \t" << pPlayer.getCurrentItem()->getName() << endl;
		}
		cout << endl;

		//Show monster's attributes
		cout << pMonster.getName() << "'s Attributes:";
		cout << "\nHealth: \t" << pMonster.getCurrentHealth() << "/" << pMonster.getHealth() << endl;
		cout << "Damage: \t" << pMonster.getAttackDamage() + pMonster.getWeapon()->getDamage() << endl; 
		cout << "Weapon Name: \t" << pMonster.getWeapon()->getName() << endl;
		cout << "Durability: \t" << pMonster.getWeapon()->getDurability() << endl;
		cout << "Is Badass?: \tYes" << endl;

		cout << "\nWhat will you do?" << endl;
		cout << "1. Use your item" << endl;  	//Use item
		cout << "2. Equip an item" << endl;  	//Equip item
		cout << "3. Give up" << endl;  			//Give up
		cout << "Choice: ";
		cin >> choice;

		// Check if the choice is invalid (neither 1 or )
		if (choice < 1 || choice > 3) {
			cout << "Invalid choice! Please select 1 - 3." << endl;
		}
		if (choice == 1) {	//Use item
			if (pPlayer.UseCurrentItem()) {	//If succesfully used the item, then...
				if (Weapon* weapon = dynamic_cast<Weapon*>(pPlayer.getCurrentItem())) {		//If current item is a weapon (it will increase the player's attack damage)
					pMonster.TakeDamage(pPlayer.getAttackDamage());
					string message = "\nYou have dealt " + to_string(pPlayer.getAttackDamage()) + " to " + pMonster.getName() + "!\n";
					DisplayDelayText(message, 1);
					pPlayer.setAttackDamage(pPlayer.getAttackDamage() - weapon->getDamage()); //Decrease the damage back down to the original damage
				}
				turnFinish = true;	//Finish turn
			}
		}
		else if (choice == 2) { 	//Equip item
			pPlayer.EquipItem();	//Cal player's EquipItem method
		}
		else if (choice == 3) {		//Player give up
			turnFinish = true;
			return -1; //-1 means the player gave up
		}
	} while (!turnFinish);
	return 0; //0 player's turn finishred
	pPlayer.setIsFighting(false);	//Player stop fighting
};

void VillageFightScene(Game& pGame) {
	int result = 0;
	Player* pPlayer = pGame.getPlayer();
	Monster* pMonster = pGame.getMonster();
	do {
		//If player's health reaches 0, means he lose
		if (pPlayer->getCurrentHealth() == 0) {
			break;
		}
		//In the village scene the monster will retreat when his Health reaches 170 or below
		if (pMonster->getCurrentHealth() <= 170) {
			system("CLS");
			DisplayDelayText("Suddenly, the monster lets out a guttural roar, its massive form staggering back!\n", 2);
			DisplayDelayText("With a final terrifying growl, the creature turns and begins to retreat into the jungle.\n", 2);
			DisplayDelayText("An uneasy chill settles over you. You know, deep down, that this creature will be back.\n", 2);
			break;
		}
		//Assign the result from FightScene fucntion to result
		result = pGame.FightScene();

		//If result is not -1, then the monster will deal damage to the player
		if (result == 0) {
			DisplayDelayText("", 1);
			pMonster->selectRandomCombo();
			pMonster->executeCombo(*pPlayer);
			system("PAUSE");
		}
	} while (result != -1);
	//Player stop fighting when the scene is over
	pPlayer->setIsFighting(false);

	//If result is -1, ...
	if (result == -1) {
		system("CLS");
		DisplayDelayText("Outmatched, you flee to the village, heart pounding.\n", 2);
		DisplayDelayText("You slip into a hut, pressing flat against the wall.\n", 2);

		this_thread::sleep_for(chrono::seconds(1));  // Suspense pause

		DisplayDelayText("The creature prowls outside, inches away, then finally leaves.\n", 2);
		DisplayDelayText("Safe for now... but it will return.\n", 2);

		DisplayDelayText("With the creature gone, you cautiously explore the abandoned village.\n", 2);
		system("PAUSE");
		system("CLS");
	}
}

void InitScene1(Scene& pCrashSiteScene, Game* pGame, Item* AllItems[ALL_ITEM_COUNT]) {
	pCrashSiteScene.AddLoot(AllItems[0]);  // Water Bottle
	pCrashSiteScene.AddLoot(AllItems[0]);  // Water Bottle
	pCrashSiteScene.AddLoot(AllItems[2]);  // MRE Pack
	pCrashSiteScene.AddLoot(AllItems[2]);  // MRE Pack
	pCrashSiteScene.AddLoot(AllItems[6]);  // First Aid Kit
	pCrashSiteScene.AddLoot(AllItems[4]);  // Survival Knife
	pCrashSiteScene.AddLoot(AllItems[8]);  // Sleeping Bag
	//Events for scene1
	Event* event1 = new Event(pGame, [pGame](Game& e) {
		system("CLS");
		DisplayDelayText("You board the plane, settle into your seat, and stow your bag, feeling both excitement and fatigue.\n"
                     "As you buckle up, you sigh in relief, home is just a flight away.\n", 1);
		DisplayDelayText("The plane's engines roar as it ascends. You gaze out the window, watching the city shrink below.\n", 1);
		system("PAUSE");
		system("CLS");

		// Transition and suspense
		DisplayDelayText("30 Minutes Later. . .", 2);

		DisplayDelayText("A sudden jolt rocks the plane.\n", 2);
		DisplayDelayText("From the corner of your eye,\n"
                     "you glimpse a dark figure outside the window just for a second,\n"
                     "before it rams itself onto the plane.\n", 2);

		PlayPlaneCrashSound();
		DisplayDelayText("The plane lurches as the engines sputter,\n"
                     "knowing you're about to crash into the dense jungle of a small island,\n"
                     "you brace for impact!\n", 2);
		system("PAUSE");
		system("CLS");

	});
	//2nd event of scene 2
	Event* event2 = new Event(pGame, [pGame](Game& e) {
		DisplayDelayText("Your head aches as you wake, smoke and fire crackling around you.\n"
                     "The plane is wrecked, debris everywhere.\n", 2);
		DisplayDelayText("The jungle is still, then a deep growl echoes. Something huge moves nearby.\n", 2);
		DisplayDelayText("The ground shakes with each step. You press against the plane, hoping it won't notice.\n", 2);
		DisplayDelayText("Through the window, you see a massive shape with glowing eyes, sniffing the air.\n", 2);
		DisplayDelayText("It steps closer, its feet crushing the ground beneath you.\n", 2);
		DisplayDelayText("The creature growls and moves away, the ground shaking as it disappears.\n", 2);
		DisplayDelayText("You're alone in the wreckage, but you know the creature is still out there.\n", 2);
		system("PAUSE");
		system("CLS");
		// Radio communication and planning
		DisplayDelayText("Suddenly, you hear a crackling voice through a broken radio.\n", 2);
		DisplayDelayText("Rescue Team: We've located the crash site. We're coming to save you.\nHead to the edge of the island and stay put, we'll meet you there.\n", 2);
		DisplayDelayText("The static clears for a moment, and you can hear the distant sound of a helicopter overhead.\n", 2);
		DisplayDelayText("A surge of hope fills you, but there's no time to waste.\nYou gather your strength and prepare to make your way to the edge of the island,\n"
						 "your heart racing with both fear and anticipation.\n", 2);
		DisplayDelayText(e.getPlayer()->getName() + ": I should loot the area and find the path to the outskirts of the island...\n", 2);
		system("PAUSE");
		system("CLS");
	});
	//Add events to the scene
	pCrashSiteScene.AddEvent(event1);
	pCrashSiteScene.AddEvent(event2);
}
void InitScene2(Scene& pJungleClearingScene, Game* pGame, Item* AllItems[ALL_ITEM_COUNT]) {
	pJungleClearingScene.AddLoot(AllItems[11]); // Bamboo Water
	pJungleClearingScene.AddLoot(AllItems[11]); // Bamboo Water
	pJungleClearingScene.AddLoot(AllItems[3]);  // Bananas
	pJungleClearingScene.AddLoot(AllItems[10]); // Jungle Roots
	pJungleClearingScene.AddLoot(AllItems[9]); // Dull Machete
	pJungleClearingScene.AddLoot(AllItems[7]);  // Wild Mint
	pJungleClearingScene.AddLoot(AllItems[7]);  // Wild Mint
	//Scene2's event
	Event* event1 = new Event(pGame, [pGame](Game& e) {
		DisplayDelayText("Suddenly, out of the shadows, the creature emerges with a loud, terrifying roar!", 1);
		pGame->getMonster()->Jumpscare1();
		DisplayDelayText("Panic sets in as you sprint into the jungle, desperate to escape.\n", 2);
		DisplayDelayText("As you push through the dense jungle, your breath heavy, every rustle in the trees makes you jump.\n", 2);
		DisplayDelayText("Finally, after what feels like an eternity, you break through the trees and find yourself in a small clearing.\n", 2);
		DisplayDelayText("You burst into the clearing, heart racing, and look back.\n", 2);
		DisplayDelayText("To your relief, the creature is gone, but you can't shake the feeling it's still watching.\n", 2);
		system("PAUSE");
		system("CLS");
		DisplayDelayText("As you catch your breath, you notice two distinct paths ahead.\n", 2);
		DisplayDelayText("One leads to what seems to be a distant village,\n", 2);
		DisplayDelayText("The other plunges deeper into the dense jungle, where the unknown waits.\n", 2);
		DisplayDelayText("But the deep jungle might also lead you closer to the edge of the island,\nwhere rescue could be possible.\n", 2);
		DisplayDelayText("The decision weighs heavily on you should you head towards the village to find more loot, or venture deeper into the jungle,\nhoping it leads to the edge of the island?\n", 2);
		system("PAUSE");
		system("CLS");
	});
	pJungleClearingScene.AddEvent(event1);
}
void InitScene3(Scene& pVillage, Game* pGame, Item* AllItems[ALL_ITEM_COUNT]) {
	pVillage.AddLoot(AllItems[1]);  // Coconut Water
	pVillage.AddLoot(AllItems[13]); // Cooked Meat
	pVillage.AddLoot(AllItems[5]);  // Axe
	pVillage.AddLoot(AllItems[12]); // Hammock
	pVillage.AddLoot(AllItems[6]);  // First Aid Kit
	//Scene3's event
	Event* event1 = new Event(pGame,[pGame](Game& e) {
		DisplayDelayText("After another long trek through the jungle, you finally stumble upon an abandoned village.\n", 2);
		DisplayDelayText("It's eerily quiet, but the hairs on the back of your neck stand on end.\n", 2);
		DisplayDelayText("Something feels wrong here.\n", 2);
		pGame->getMonster()->Ambush(*pGame->getPlayer());
		DisplayDelayText("Your pulse races as you weigh your options. The creature is fast, but you might have a chance if you fight.\n", 2);

		int choice = 0;
		while (choice != 1 && choice != 2) {
			// Prompt the player for a decision
			DisplayDelayText("What are you going to do?\n1.Fight the monster\n2.Run deeper into the village", 0);
			cout << "Choice: ";
			cin >> choice;
			// Validate the player's input
			if (choice != 1 && choice != 2) {
				cout << "\nInvalid choice. Please enter 1 to fight or 2 to run." << endl;
			}
		}
		//If player decide to fight...
		if (choice == 1) {
			VillageFightScene(e); //Call FightScene method
		}else {
			system("CLS");
			DisplayDelayText("You dash deeper into the village, heart racing.\n", 2);
			DisplayDelayText("Old houses and twisted paths blur as you run, the monster close behind.\n", 2);
			DisplayDelayText("Ahead, an abandoned house looms with its door ajar. You dive in, hiding in the shadows.\n", 2);
			DisplayDelayText("The monster's heavy footsteps approach, pausing just outside. You hold your breath.\n", 2);
			this_thread::sleep_for(chrono::seconds(2));
			DisplayDelayText("After a tense moment, it growls in frustration and moves on.\n", 2);
			DisplayDelayText("Relieved, you slip out and continue through the village, searching for supplies.\n", 2);
			system("PAUSE");
			system("CLS");
		}
	});
	//Add events to Scene3
	pVillage.AddEvent(event1);
}
void InitScene4(Scene& pDeepJungle, Game* pGame, Item* AllItems[ALL_ITEM_COUNT]) {
	pDeepJungle.AddLoot(AllItems[7]);	//Wild mint
	pDeepJungle.AddLoot(AllItems[11]);	// Bamboo Water
	pDeepJungle.AddLoot(AllItems[3]);	// Bananas
	pDeepJungle.AddLoot(AllItems[10]);	// Jungle Roots
	//Scene4's event
	Event* event1 = new Event(pGame, [pGame](Game& e) {
		pGame->getMonster()->Jumpscare2();
		system("CLS");
		DisplayDelayText("The jungle around you seems silent.\nYou see little movement as you make your way through the dense foliage,\n", 2);
		DisplayDelayText("Only the sound of your footsteps breaking the silence.\n", 2);
		DisplayDelayText("But suddenly, a chilling voice echoes from the shadows: 'You think you can escape? I'll be waiting for you at the edge of the island.'\n", 2);
		DisplayDelayText("The voice sends a cold shiver down your spine, and you realize the monster is lurking, watching your every move.\n", 2);
		DisplayDelayText(pGame->getPlayer()->getName() + ":I better get everything ready first before I go to the edge of the island... There's no turning back from there.\n", 2);
		system("PAUSE");
		system("CLS");
	});
	//Adding event1 to scene4
	pDeepJungle.AddEvent(event1);
}

//Last Fight Scene
void LastFightScene(Game& pGame) {
	Player* pPlayer = pGame.getPlayer();
	Monster* pMonster = pGame.getMonster();
	int result = 0;
	do {
		//When player dies
		if (pPlayer->getCurrentHealth() == 0) {
			break;
		}
		//When monster dies
		if (pMonster->getCurrentHealth() == 0) {
			system("CLS");
			DisplayDelayText("The monster lets out a pained roar, staggering back from the fight!\n", 2);
			DisplayDelayText("Seizing the opportunity, the creature turns and quickly retreats into the jungle.\n", 2);
			DisplayDelayText("Not wasting any time, you sprint towards the helicopter awaiting your escape.\n", 2);
			DisplayDelayText("As the rotors spin up, you feel a rush of relief. You've been rescued, for now...\n", 2);
			system("PAUSE");
			break;
		}
		//Call FightScene function
		result = pGame.FightScene();
		if (result == 0) {
			pMonster->selectRandomCombo();
			pMonster->executeCombo(*pPlayer);
			system("PAUSE");
		}
	} while (result != -1 ||  pPlayer->getCurrentHealth() == 0);
	//Player stop fighting
	pPlayer->setIsFighting(false);
	if (result == -1) {
		system("CLS");
		DisplayDelayText("Outmatched, you fight with everything you have...\n", 2);
		DisplayDelayText("But the creature overpowers you, its grip tightening around your throat.\n", 2);
		this_thread::sleep_for(chrono::seconds(1));  // Suspense pause
		DisplayDelayText("You struggle to breathe, but it's hopeless.\n", 2);
		DisplayDelayText("Your vision fades... everything goes black.\n", 2);
		DisplayDelayText("The last thing you hear is the creature's chilling growl as the darkness consumes you.\n", 2);
		system("PAUSE");
		system("CLS");
		pPlayer->Die();
	}
}

//Scene5
void InitScene5(Scene& pHelicopterRescue, Game* pGame, Item* AllItems[ALL_ITEM_COUNT]) {
	//Scene5's event
	Event* event1 = new Event(pGame, [pGame](Game& e) {
		DisplayDelayText("As you push through the dense jungle, your ears catch the faint sound of helicopter blades cutting through the air.\n", 2);
		DisplayDelayText("You force your legs to move faster, adrenaline kicking in as the sound becomes unmistakable.\n", 2);
		DisplayDelayText("Then, suddenly, a figure steps out from the shadows, blocking your path. The monster stands tall, its eyes locked on you.\n", 2);
		DisplayDelayText("With no choice left, you prepare for the final battle. It's him or you. You must fight to survive.\n", 2);
		system("PAUSE");
		system("CLS");
		LastFightScene(e);
	});
	//Add event to Scene5
	pHelicopterRescue.AddEvent(event1);
}

int main() {
	system("Color 0E");

	//Initialise Variable
	Player* player;
	Weapon* playerDefaultWeapon = new Weapon("Bare Hands", "Good Ole Bare Knuckles", 0, false, 1, 1000); //Default player weapon
	Weapon* monsterDefaultWeapon = new Weapon("Claw of the Damned", "A razor-sharp claw imbued with dark energy. It causes deep wounds and instills fear in its victims.", 10, false, 10, 100); //Default monster weapon
	Monster* dreadstalker = new Monster("Dreadstalker", 20, 200, monsterDefaultWeapon); //Allocate memory for Monster variable on the heap
	//All Items of the game
	Item* AllItems[ALL_ITEM_COUNT] = {
		new Drinks("Water Bottle", "A lifeline in the wilderness, quench your thirst.", 5, true, 5),
		new Drinks("Coconut Water", "Natural hydration straight from the source", 7, true, 4),
		new Food("MRE Pack", "Ready-to-eat meal for survival", 10, true, 4, false, true, 20, 4),
		new Food("Bananas", "These wild bananas are rich in carbohydrates and easy to find in the jungle.", 8, true, 7, false, false, 15, 4),
		new Weapon("Survival Knife", "A versatile blade for hunting and self-defense", 10, false, 8, 20),
		new Weapon("Axe", "A powerful tool for defense, but won't last long.", 20, false, 25, 7),
		new Medical("First Aid Kit", "Everything you need to tend to your wounds and stay alive.", 10, true, 80),
		new Medical("Wild Mint", "Wild mint leaves can relieve headaches and stomach aches. A natural way to ease discomfort.", 1, false, 20),
		new SleepingBag("Sleeping Bag", "Compact and warm, ideal for the wild", 15, false, 8, dreadstalker),
		new Weapon("Dull Machete", "A worn machete, useful for defense but fragile and short-lived.", 15, false, 10, 6),
		new Food("Jungle Roots", "Tough but edible roots. Chewy, but keeps hunger at bay.", 2, true, 3, false, true, 5, 2),
		new Drinks("Bamboo Water", "Natural hydration straight from the source", 3, true, 4),
		new SleepingBag("Hammock", "A lightweight hammock, provides less stamina restoration than the sleeping bag.", 10, false, 6, dreadstalker),
		new Food("Cooked Meat", "This freshly cooked meat provides a hearty meal, rich in protein to restore your strength.", 10, true, 10, false, false, 30, 6),
	};
	
	Scene* AllScenes[ALL_SCENE_COUNT] = {
	   new Scene("Crash Site", "You awaken amid the twisted wreckage of the plane, surrounded by smoke and dense jungle. Disoriented and alone, survival starts here.", 2),
	   new Scene("Jungle Clearing", "A small clearing opens up before you, dappled sunlight breaking through the trees. The jungle seems deceptively calm here.", 1),
	   new Scene("Abandoned Village", "The village is eerie, silent huts and remnants of fires hint at a hasty departure. You sense something watching you.", 1),
	   new Scene("Deep Jungle", "The jungle grows darker and more foreboding.", 1),
	   new Scene("Edge of the Island", "You see the rescue helicopter just ahead, its blades chopping through the air. But as you approach, the monster emerges from the jungle.", 3),
	};

	//Dimensionalise Player Object
	
	player = new Player("empty", 10, 100, 0, 0, 10, 100); //Allocate memory for Player variable on the heap
	
	player->AddItem(playerDefaultWeapon);	//Add the weapon the the inventory
	player->getInventory().setCurrentItem(player->getInventory().SearchItem("Bare Hands")); //Set current item to the default weapon
	system("CLS");

	//Dimensionalise Game object
	Game newGame(player, dreadstalker);
	//Introduction to the game
	if (Introduction(newGame)) {
		string playerName = "";
		cout << "Enter your name: ";
		cin >> playerName;
		newGame.getPlayer()->setName(playerName);

		//All available scenes in the game
		InitScene1(*AllScenes[0], &newGame, AllItems);	//Initialise Scene1
		InitScene2(*AllScenes[1], &newGame, AllItems);	//Initialise Scene2
		InitScene3(*AllScenes[2], &newGame, AllItems);	//Initialise Scene3
		InitScene4(*AllScenes[3], &newGame, AllItems);	//Initialise Scene4
		InitScene5(*AllScenes[4], &newGame, AllItems);	//Initialise Scene5
		//Attach all the scene to the binary tree of scene in newGame
		BTree<Scene*>* rootScene = new BTree<Scene*>(AllScenes[0]); //Root Scene of the game
		newGame.setRootScene(rootScene);							//Setting root scene
		newGame.setTreeTarget(newGame.getRootScene());				//Set tree target to point to the new root scene
		newGame.AttachLeftScene(AllScenes[1]);						//Attach Jungle Clearing  to Crash Site
		newGame.Left();												//Move to Jungle Clearing Scene
		newGame.AttachLeftScene(AllScenes[2]);						//Attach Abandoned Village the left child of Jungle Clearing
		newGame.AttachRightScene(AllScenes[3]);						//Attach Deep Jungle to the right child of Jungle Clearing
		newGame.Right();											//Move to Right Child (Deep Jungle)
		newGame.AttachLeftScene(AllScenes[4]);						//Attach Waterfall Cave to Left Child of Deep Jungle
		newGame.setTreeTarget(newGame.getRootScene());				//Set the TreeTarget back to the RootScene

		//Play the game
		newGame.Play();
		newGame.SavePlayerDecisions();

	}

	//Delete the allocated memory
	for (Iterator1D<Scene*> iter(AllScenes, ALL_SCENE_COUNT, 0); iter != iter.end(); ++iter) {
		if (*iter != nullptr) {
			delete* iter;
		}
	}
	for (Iterator1D<Item*> iter(AllItems, ALL_ITEM_COUNT, 0); iter != iter.end(); ++iter) {
		if (*iter != nullptr) {
			delete *iter;
		}
	}
	delete player;
	delete dreadstalker;
	delete playerDefaultWeapon;
	return 0;
}