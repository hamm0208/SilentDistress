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
#include "Iterator1D.h"
#include "Queue.h"
using namespace std;
const int ALL_ITEM_COUNT = 10;

void Introduction() {
	//Introduce the game
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
	cout << "+------------------------------------------------------------------+" << endl;
	cout << GameTittle;
	cout << "+------------------------------------------------------------------+" << endl;
	cout << "\nSilentDistress is a horror survival text game where the player,\n"
		<< "as the lone survivor of a plane crash, must navigate a dark jungle,\n"
		<< "manage resources, and survive encounters with a lurking monster.\n" << endl;
	system("PAUSE");
	system("CLS");

	//Rules and goals of the game
	cout << "Goal:\nPlayer needs to survive the aftermath of a plane crash in a hostile jungle by gathering resources,\n"
		<< "managing hunger and stamina. Players must explore the jungle to find the end of the jungle to meet the rescue team\n" << endl;

	this_thread::sleep_for(chrono::seconds(1));
	cout << "Information: " << endl;
	cout << "1. Turn-Based Gameplay:\n"
		<< "The game operates on turns where each player action (moving, searching, using/equipping/discarding items) counts as one turn.\n" <<endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "2. Decision-Based Outcomes:\n"
		<< "Every choice impacts the storyline, influencing endings based on survival, resource management, and decisions.\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "3. Victory Condition:\n"
		<<"Reach the rescue team without succumbing to hunger, thirst, or the monster's attacks.\n" <<endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "4. Defeat Condition:\n"
		<<"The game ends if the player’s health, hunger, or stamina drops to zero or if the monster defeats them.\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	system("PAUSE");
	system("CLS");

	//Survival System Rules
	cout << "Survival System Rules:\n";
	cout << "1. Hunger Effects: If hunger reaches certain levels, stamina decreases, thirst increases, or the player takes damage:\n";
	cout << "   - Hunger level between 8 and 9: Decrease stamina by 1 and increase thirst by 1.\n";
	cout << "   - Hunger level 10: Take 5 damage, decrease stamina by 2, and increase thirst by 1.\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "2. Thirst Effects: If thirst reaches certain levels, stamina decreases and the player may take damage:\n";
	cout << "   - Thirst level between 8 and 9: Decrease stamina by 2.\n";
	cout << "   - Thirst level 10: Take 5 damage and decrease stamina by 2.\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "3. Stamina Effects: Low stamina affects hunger, thirst, and may result in death if stamina reaches zero:\n";
	cout << "   - Stamina level between 1 and 5: Increase hunger and thirst by 2 each.\n";
	cout << "   - Stamina level 0: If resting, the player collapses and suffers a deeper hunger and thirst increase.\n   Stamina is restored, but a monster will disturb the rest.\n";
	cout << "   - If player is fighting and stamina reaches 0: The player dies from exhaustion in battle.\n" << endl;
	system("PAUSE");
	system("CLS");
}

void Scene1Event(Scene& pCrashSiteScene, Player* pPlayer, Monster* pMonster) {
	Queue<Event*> Events(pCrashSiteScene.getEvent().getMax());
	Event* event1 = new Event(pPlayer, false, "plane_crash.wav", [pPlayer](Entity& e) {
		cout << "You file into the plane, the hum of the engines almost drowning out the low chatter of passengers settling in.\n"
			<< "A flight attendant directs you to your seat, and you stow your bag, feeling a mix of excitement and fatigue.\n" 
			<<"The plane's interior is cozy, and as you buckle up, you can’t help but let out a small sigh of relief,\nhome is just a flight away.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "The plane's engines roar as it ascends. You gaze out the window, watching the city shrink below.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("PAUSE");
		system("CLS");
		cout << "30 Minutes Later. ";
		this_thread::sleep_for(chrono::seconds(1));
		cout << ". ";
		this_thread::sleep_for(chrono::seconds(1));
		cout << ". " << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "A sudden jolt rocks the plane. You grip the armrests as the 'Fasten Seatbelt' sign dings on.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "From the corner of your eye, you glimpse a dark figure outside the window, just for a second, before it ram itself onto the plane.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "The plane lurches as the engines begin to sputter. The sound of panicked passengers fills the cabin!\n" << endl;
	});
	Event* event2 = new Event(pPlayer, false, "", [pPlayer](Entity& e) {
		cout << "The plane lurches as the engines begin to sputter. The sound of panicked passengers fills the cabin!\n" << endl;
	});
	Events.queue(event1);
	Events.queue(event2);

	pCrashSiteScene.AddEvent(Events.dequeue());
	pCrashSiteScene.AddEvent(Events.dequeue());
}
int main() {
	system("Color 0E");
	//Introduction to the game
	//Introduction();

	//Initialise Variable
	string playerName = "";
	Weapon* playerDefaultWeapon = new Weapon("Bare Hands", "Good Ole Bare Knuckles", 0, false, 1, 1000); //Default player weapon
	Weapon* monsterDefaultWeapon = new Weapon("Claw of the Damned", "A razor-sharp claw imbued with dark energy. It causes deep wounds and instills fear in its victims.", 10, false, 50, 100); //Default monster weapon
	Player* player;
	Monster* dreadstalker = new Monster("Scary Monster", 50, 200, monsterDefaultWeapon); //Allocate memory for Monster variable on the heap
	Item* AllItems[ALL_ITEM_COUNT] = {
		new Drinks("Water Bottle", "A lifeline in the wilderness, quench your thirst.", 5, true, 5),
		new Drinks("Coconut Water", "Natural hydration straight from the source", 7, true, 4),
		new Food("MRE Pack", "Ready-to-eat meal for survival", 10, true, 4, false, true, 20, 4),
		new Food("Wild Berries", "These berries are small but pack a punch of nutrients.", 2, true, 5, false, true, 5, 2),
		new Food("Bananas", "These wild bananas are rich in carbohydrates and easy to find in the jungle.", 8, true, 7, false, false, 15, 4),
		new Weapon("Survival Knife", "A versatile blade for hunting and self-defense", 5, false, 8, 20),
		new Weapon("Axe", "A powerful tool for defense, but won't last long.", 30, false, 10, 6),
		new SleepingBag("Sleeping Bag", "Compact and warm, ideal for the wild", 15, false, 7, dreadstalker),
		new Medical("First Aid Kit", "Everything you need to tend to your wounds and stay alive.", 10, true, 80),
		new Medical("Wild Mint", "Wild mint leaves can relieve headaches and stomach aches. A natural way to ease discomfort.", 1, false, 5)
	};

	//Dimensionalise Player Object
	cout << "Enter your name: ";
	cin >> playerName;
	player = new Player(playerName, 10, 100, 0, 0, 10, 100); //Allocate memory for Player variable on the heap
	player->AddItem(playerDefaultWeapon);	//Add the weapon the the inventory
	player->getInventory().setCurrentItem(player->getInventory().SearchItem("Bare Hands")); //Set current item to the default weapon
	system("CLS");
	//Creating 1st Scene (Crash Site)
	Scene* crashSiteScene = new Scene("Crash Site", "You awaken amid the twisted wreckage of the plane, surrounded by smoke and dense jungle. Disoriented and alone, survival starts here.", 3);
	Scene1Event(*crashSiteScene, player, dreadstalker);
	
	Game newGame(player, dreadstalker);
	BTree<Scene*>* rootScene = new BTree<Scene*>(crashSiteScene);
	newGame.setRootScene(rootScene);
	newGame.setTreeTarget(newGame.getRootScene());
	newGame.Play();

	delete crashSiteScene;
	for (Iterator1D<Item*> iter(AllItems, ALL_ITEM_COUNT, 0); iter != iter.end(); ++iter) {
		if (*iter != nullptr) {
			delete *iter;
		}
	}
	delete player;
	delete dreadstalker;
	return 0;
}
/*
int main() {
	system("Color 0E");
	Weapon* defaultWeapon = new Weapon("Bare Hands", "Good Ole Bare Knuckles", 0, false, 1, 1000);
	Weapon* monsterWeapon = new Weapon("Claw of the Damned",  "A razor-sharp claw imbued with dark energy. It causes deep wounds and instills fear in its victims.", 10, false, 50, 100);
	Monster* monster = new Monster("Scary Monster", 50, 200, monsterWeapon);
	Player* newPlayer = new Player("John Wick", 10, 100, 0, 0, 10, 100);
	Item* game_AllItems[ALL_ITEM_COUNT] = {
		new Food("KFC", "Finger Lickin Good", 10, true, 5, false, true, 10, 10),
		new Drinks("Water Bottle", "Best hydration" , 5, true, 10),
		new SleepingBag("Cozy Bed", "Good comfy bed", 20, false, 4, monster),
		new Weapon("Big Axe", "Slash down your foe with this axe", 40, false, 10, 10),
		new Medical("First Aid Kit", "Heal all your wounds", 10, true, 20),
	};

	newPlayer->AddItem(defaultWeapon);
	newPlayer->getInventory().setCurrentItem(newPlayer->getInventory().SearchItem("Bare Hands"));
	system("CLS");
	Scene* scene1 = new Scene("Plane Crashsite", "Plane Crashsite", 6);
	Scene* scene2 = new Scene("Plane Crashsite1", "Plane Crashsite", 6);
	Scene* scene3 = new Scene("Plane Crashsite2", "Plane Crashsite", 6);
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
	Event scene1_event1(monster, false, "", [monster](Entity& e) { monster->Jumpscare(); });
	//scene1->AddEvent(&scene1_event1);
	BTree<Scene*>* rootScene = new BTree<Scene*>(scene1);
	Game newGame(newPlayer, monster);
	newGame.setRootScene(rootScene);
	newGame.setTreeTarget(newGame.getRootScene());
	newGame.AttachLeftScene(scene2);
	newGame.AttachRightScene(scene3);
	newGame.Play();

	
	delete scene3;
	delete scene2;
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
*/