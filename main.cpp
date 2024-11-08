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
	cout << "\nSilent Distress is a horror survival text game where the player,\n"
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
		<<"The game ends if the player's health, hunger, or stamina drops to zero or if the monster defeats them.\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	system("PAUSE");
	system("CLS");

	//Survival System Rules
	cout << "Survival System Rules:\n";
	cout << "1. Hunger Effects: If hunger reaches certain levels, stamina decreases, thirst increases, or the player takes damage:\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "2. Thirst Effects: If thirst reaches certain levels, stamina decreases and the player may take damage:\n" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "3. Stamina Effects: Low stamina affects hunger, thirst, and may result in death if stamina reaches zero:\n" << endl;
	system("PAUSE");
	system("CLS");
}

void Scene1Event(Scene& pCrashSiteScene, Player* pPlayer, Monster* pMonster) {
	Event* event1 = new Event(pPlayer, false, "plane_crash.wav", [pPlayer](Entity& e) {
		cout << "You board the plane, settle into your seat, and stow your bag, feeling both excitement and fatigue.\n"
			<< "As you buckle up, you sigh in relief, home is just a flight away.\n" << endl;
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
		cout << "A sudden jolt rocks the plane.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << "From the corner of your eye,\nyou glimpse a dark figure outside the window just for a second,\nbefore it ram itself onto the plane.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << "The plane lurches as the engines sputter,\nknowing you're about to crash into the dense jungle of a small island, \n"
			<<"you brace for impact!\n" << endl;
	});
	Event* event2 = new Event(pPlayer, false, "", [pPlayer](Entity& e) {
		system("PAUSE");
		system("CLS");
		cout << "Your head aches as you wake, smoke and fire crackling around you.\n"
			<< "The plane is wrecked, debris everywhere.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));

		cout << "The jungle is still, then a deep growl echoes. Something huge moves nearby.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));

		cout << "The ground shakes with each step. You press against the plane, hoping it won’t notice.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));

		cout << "Through the window, you see a massive shape with glowing eyes, sniffing the air.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));

		cout << "It steps closer, its feet crushing the ground beneath you.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));

		cout << "The creature growls and moves away, the ground shaking as it disappears.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));

		cout << "You're alone in the wreckage, but you know the creature is still out there.\n" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		system("PAUSE");
		system("CLS");
		cout << "Suddenly, you hear a crackling voice through a broken radio.\n"<< endl;
		this_thread::sleep_for(chrono::seconds(1));

		cout << "Rescue Team: We've located the crash site. We're coming to save you.\nHead to the edge of the island and stay put, we'll meet you there.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		cout << "The static clears for a moment, and you can hear the distant sound of a helicopter overhead.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		cout << "A surge of hope fills you, but there's no time to waste.\nYou gather your strength and prepare to make your way to the edge of the island,\nyour heart racing with both fear and anticipation.\n" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		cout << e.getName() << ": I should loot the area and find the path to the outskirts of the island..." << endl;
		system("PAUSE");
		system("CLS");
	});
	pCrashSiteScene.AddEvent(event1);
	pCrashSiteScene.AddEvent(event2);
}
int main() {
	system("Color 0E");
	//Introduction to the game
	Introduction();

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

	Game newGame(player, dreadstalker);
	//Creating 1st Scene (Crash Site)
	Scene* crashSiteScene = new Scene("Crash Site", "You awaken amid the twisted wreckage of the plane, surrounded by smoke and dense jungle. Disoriented and alone, survival starts here.", 2);
	Scene1Event(*crashSiteScene, player, dreadstalker);
	BTree<Scene*>* rootScene = new BTree<Scene*>(crashSiteScene);
	Game* ptr;
	newGame.setRootScene(rootScene);
	newGame.setTreeTarget(newGame.getRootScene());
	
	Scene* jungleClearingScene = new Scene("Jungle Clearing", "A small clearing opens up before you, dappled sunlight breaking through the trees. The jungle seems deceptively calm here.", 2);
	Scene* ruinsScene = new Scene("Ruins","You come upon ancient ruins, moss-covered stones hinting at a long-lost civilization. It's quiet, but you feel like you're not alone.",1);
	Scene* villageScene = new Scene("Abandoned Village","The village is eerie, silent huts and remnants of fires hint at a hasty departure. You sense something watching you.",2);
	Scene* edgeOfIslandScene = new Scene("Edge of the Island","You see the rescue helicopter just ahead, its blades chopping through the air. But as you approach, the monster emerges from the jungle.",3);
	newGame.AttachLeftScene(jungleClearingScene);
	//FIRST THING FIRST COMPLETE ATTACHING

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