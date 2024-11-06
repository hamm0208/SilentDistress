#pragma once
#include "Stack.h"
#include "Event.h"
class Item;
class Scene
{
	private:
		string fName;					//Name of scene
		string fDescription;			//Description of the scene
		List<Item*> fLoot;				//Loot in the scene for players to add to inventory
		Stack<Event*> fEvents;			//Events of the scene
	public:
		Scene();
		Scene(string pName, string pDescription, int pMaxNumberOfEvent);
		string getName() const;
		string getDescription() const;
		List<Item*>& getLoot();
		void AddLoot(Item* pLoot);
		//void AddDecisions(Decision pDecision);
		void AddEvent(Event* fEvent);
		void PlayEvent();
		bool IsEventEmpty();
		void ShowLoots();
        void ShowLootsDetails();
};
/*
List<Decision> Scene::getDecisions() const{
    return fDecisions;
};

void Scene::AddDecisions(Decision pDecision){
    fDecisions.pushBack(pDecision);
}
 
void Scene::ShowDecisions(){
    int x = 1;
    for (auto it = fDecisions.getIteratorHead(); it != it.end(); ++it) {
        cout << x << ". " << it.getCurrent()->getValue().getName() << endl;
        x++;
    }
};
bool Scene::PlayerPickUpLoot(){
    if (fLoot.isEmpty()) {
        cout << "This area has no loot!!" << endl;
        return false;
    }
    else {
        cout << "Please choose an item to add to your inventory:\n";
        cout << "--------------------------------------------------\n";
        cout << "Item List:\n";
        int index = 0;
        ShowLoots();
        cout << "--------------------------------------------------\n";
        cout << "\nType the number corresponding to the desired item and press Enter (e.g., 1): ";
        cin >> index;
        index--;
        if (index<0 || index > fLoot.size()) {
            cout << "Invalid choice!" << endl;
            cout << endl;
            return false;
        }
        else {
            fPlayer->AddItem(fLoot[index]);
            fLoot.popAt(index);
            cout << endl;
            return true;
        }
    }
};
void Scene::PlayerMenu(){
    system("CLS");
    cout << "\n--------------------------------------------------\n";
    cout << "\nHealth: \t" << fPlayer->getCurrentHealth() << "/" << fPlayer->getHealth() <<endl;
    cout << "Hunger: \t" << fPlayer->getCurrentHungerLevel() << "/" << fPlayer->getMaxHungerLevel() <<endl;
    cout << "Thirst: \t" << fPlayer->getCurrentThirstLevel() << "/" << fPlayer->getMaxThirstLevel() <<endl;
    cout << "Stamina: \t" << fPlayer->getCurrentStaminaLevel() << "/" << fPlayer->getMaxStaminaLevel() <<endl;
    cout << "Equiped Item: \t" << fPlayer->getCurrentItem()->getName() << endl;
    cout << "\nAvailable Decisions:\n";
    int index = 0;
    ShowDecisions();
    cout << "--------------------------------------------------\n";
    cout << "\nType the number corresponding to the desired decision and press Enter (e.g., 1): ";
    cin >> index;
    index--;
    cout << endl;

    if (index<0 || index > fDecisions.size()) {
        cout << "Invalid choice!" << endl;
    }
    else{
        fPlayer->MakeDecision(fDecisions[index]);
    }
};
void Scene::MonsterAmbush(){
    fMonster->Ambush(*fPlayer);
};
void Scene::MonsterJumpScare() {
    fMonster->Jumpscare();
}

void Scene::DisplayInventoryMenu() {
    bool inInventoryMenu = true;

    while (inInventoryMenu) {
        cout << "---------------- Inventory Menu ----------------" << endl;

        // Display player's inventory
        fPlayer->ViewItems();
        List<Decision> DecisionInInventory;
        DecisionInInventory.pushBack(Decision("View All Item Details",
            "Take a look at all of the item details in your inventory",
            [this](Player& player) { player.ViewItemsDetails(); }));
        DecisionInInventory.pushBack(Decision("Equip an item",
            "Equip an item from your inventory",
            [this](Player& player) { player.EquipItem(); }));
        DecisionInInventory.pushBack(Decision("Discard an item",
            "Discard an item from your inventory",
            [this](Player& player) { player.DiscardItem(); }));

        cout << "Select an option:" << endl;
        cout << "1. View All Item Details" << endl;
        cout << "2. Equip Item" << endl;
        cout << "3. Discard Item" << endl;
        cout << "4. Go back to previous menu" << endl;

        int choice;
        cout << "Choice (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            fPlayer->MakeDecision(DecisionInInventory[0]);
            cout << "Press Enter to go back to inventory";
            cin.ignore(); // Ignore leftover newline from previous input
            cin.ignore();
            break;
        case 2:
            fPlayer->MakeDecision(DecisionInInventory[1]);
            cout << "Press Enter to go back to inventory";
            cin.ignore(); // Ignore leftover newline from previous input
            break;
        case 3:
            fPlayer->MakeDecision(DecisionInInventory[2]);
            cout << "Press Enter to go back to inventory";
            cin.ignore(); // Ignore leftover newline from previous input
            break;
        case 4:
            inInventoryMenu = false; // Exit inventory menu
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
    PlayerMenu();
}

*/