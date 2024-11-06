#include "Game.h"
typedef BTree<Scene*> TreeScene;

Game::Game(Player* pPlayer, Monster* pMonster): fRootScene(&TreeScene::NIL), fPlayer(pPlayer),fMonster(pMonster){
    fTreeTarget = fRootScene;
    Decision ViewAttributes = Decision("View Character's Attributes","Take a look at all the attributes of your character.",[this](Player& player) { player.ShowAttributes(); });
    Decision ViewInvetory = Decision("View Inventory", "Take a look at all the items in your inventory.", [this](Player& player) { DisplayInventoryMenu(); });
    Decision UseItem = Decision("Use Equipped Item", "Use your currently equipped item.", [this](Player& player) { player.UseCurrentItem(); });
    Decision SearchForLoot = Decision("Search for loot","Search the area for loot.",[this](Player& player) { DisplayLootMenu(); });
    /*
    Decision GoToLeft = Decision("Go to the left route", "Move up to to left route.", [this](Player& player) { MoveLeft(); });
    Decision GoToRight= Decision("Go to the left route", "Move up to to right route.", [this](Player& player) { MoveRight(); });
    Decision GoBackToRoot = Decision("Head back to crashsite", "Head back to root location.", [this](Player& player) { BackToRoot(); });
    AddDecisions(GoToLeft);
    AddDecisions(GoToRight);
    AddDecisions(GoBackToRoot);

    Change this to Discover, which will bring up the discover menu, using an item is a turn, or every 2 turns higher the thirst level, every 3 turns, higher the hunger level, move, use will take up 10 stamina
    */
    Decision Exit = Decision("Exit Game", "Exit the game", [this](Player& player) { exit(0); });
    AddDecisions(ViewAttributes);
    AddDecisions(ViewInvetory);
    AddDecisions(UseItem);
    AddDecisions(SearchForLoot);

    AddDecisions(Exit);
};


//Getter for fPlayer
Player* Game::getPlayer(){
    return fPlayer;
};

//Getter for fMonster
Monster* Game::getMonster(){
    return fMonster;
};

//Getter for fDecisions
List<Decision> Game::getDecisions() const{
    return fDecisions;
};

//Getter for fRootScene
TreeScene* Game::getRootScene() const{
    return fRootScene;
};

//Getter for CurrentScene
Scene* Game::getCurrentScene(){
    return getTreeTarget()->key();
};

//Getter for fTreeTarget
TreeScene* Game::getTreeTarget(){
    return fTreeTarget;
};

//Setter for fTreeTarget
void Game::setTreeTarget(TreeScene* pNewTarget){
    fTreeTarget = pNewTarget;
};

void Game::setRootScene(TreeScene* pNewRoot) {
    fRootScene = pNewRoot;
};

//Adding Decision into fDecisions
void Game::AddDecisions(Decision& pDecision){
    fDecisions.pushBack(pDecision);
};

//Show all the available Decisions
void Game::ShowDecisions(List<Decision>& pDecision) {
    int x = 1;
    for (auto it = pDecision.getIteratorHead(); it != it.end(); ++it) {
        cout << x << ". " << it.getCurrent()->getValue().getName() << endl;
        x++;
    }
};

//fRootScene & fTreeTarget
void Game::AttachLeftScene(Scene* pScene){
    TreeScene* newScene= new TreeScene(pScene);
    fTreeTarget->attachLeft(newScene);
};
void Game::AttachRightScene(Scene* pScene){
    TreeScene* newScene = new TreeScene(pScene);
    fTreeTarget->attachRight(newScene);
};
void Game::DettachLeftScene(){
    fTreeTarget->detachLeft();
    
};
void Game::DettachRightScene(){
    fTreeTarget->detachRight();
};
void Game::MoveLeft(){
    if (fTreeTarget->left().isEmpty()) {
        cout << "No route to go to..." << endl;
    }
    else {
        system("CLS");
        cout<<"Moving to " << fTreeTarget->left().key()->getName();
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ". ";
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ". " << endl;
        this_thread::sleep_for(std::chrono::seconds(1));
        system("CLS");
        setTreeTarget(&fTreeTarget->left());
        PlaySceneEvent();
    }
};
void Game::MoveRight(){
    if (fTreeTarget->left().isEmpty()) {
        cout << "No route to go to..." << endl;
    }
    else {
        system("CLS");
        cout<<"Moving to " << fTreeTarget->right().key()->getName();
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ". ";
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ". " << endl;
        this_thread::sleep_for(std::chrono::seconds(1));
        system("CLS");
        setTreeTarget(&fTreeTarget->left());
        PlaySceneEvent();
    }
};

void Game::BackToRoot() {
    if (fTreeTarget == fRootScene) {
        cout << "I am already at the crash site!" << endl;
    }
    else {
        cout << "Moving back to " << fRootScene->key();
        setTreeTarget(fRootScene);
        PlaySceneEvent();
    }
}

void Game::PlaySceneEvent(){
    fTreeTarget->key()->PlayEvent();
};

//fPlayer;
void Game::DisplayPlayerMenu() {
    cout << "\n--------------------------------------------------\n";
    cout << "Current Location: " << getCurrentScene()->getName() << endl;
    cout << "\nHealth: \t" << fPlayer->getCurrentHealth() << "/" << fPlayer->getHealth() << endl;
    cout << "Hunger: \t" << fPlayer->getCurrentHungerLevel() << "/" << fPlayer->getMaxHungerLevel() << endl;
    cout << "Thirst: \t" << fPlayer->getCurrentThirstLevel() << "/" << fPlayer->getMaxThirstLevel() << endl;
    cout << "Stamina: \t" << fPlayer->getCurrentStaminaLevel() << "/" << fPlayer->getMaxStaminaLevel() << endl;
    if (fPlayer->getCurrentItem() == nullptr) {
        cout << "Equiped Item: \tEmpty Slot"<< endl;
    }
    else {
        cout << "Equiped Item: \t" << fPlayer->getCurrentItem()->getName() << endl;
    }
    cout << "\nAvailable Decisions:\n";
    int index = 0;
    ShowDecisions(fDecisions);
    cout << "--------------------------------------------------\n";
    cout << "\nType the number corresponding to the desired decision and press Enter (e.g., 1): ";
    cin >> index;
    index--;
    cout << endl;

    if (index < 0 || index >= fDecisions.size()) {
        system("CLS");
        cout << "Invalid choice!" << endl;
    }
    else {
        fPlayer->MakeDecision(fDecisions[index]);
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.ignore();
        system("CLS");
    }
};

void Game::DisplayInventoryMenu() {
    bool inInventoryMenu = true;
    while (inInventoryMenu) {
        cout << "---------------- Inventory Menu ----------------" << endl;
        // Display player's inventory
        fPlayer->ViewItems();
        List<Decision> DecisionInInventory;
        DecisionInInventory.pushBack(Decision("View All Item Details", "Take a look at all of the item details in your inventory", [this](Player& player) { player.ViewItemsDetails(); }));
        DecisionInInventory.pushBack(Decision("Equip an item", "Equip an item from your inventory", [this](Player& player) { player.EquipItem(); }));
        DecisionInInventory.pushBack(Decision("Discard an item", "Discard an item from your inventory", [this](Player& player) { player.DiscardItem(); }));

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
            system("CLS");
            cout << "Invalid choice, please try again." << endl;
        }
    }
};
void Game::DisplayLootMenu() {
    system("CLS");
    bool inLootMenu = true;
    Scene* currentScene = getCurrentScene();
    cout << "Searching " << currentScene->getName() <<"'s Loot. ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << ". ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << ". " << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    while (inLootMenu) {
        system("CLS");
        cout << "---------------- " << currentScene->getName() << "'s loot ----------------" << endl;
        currentScene->ShowLoots();
        cout << "---------------------------------------------------------" << endl;

        List<Decision> DecisionInLoot;
        DecisionInLoot.pushBack(Decision("View All Item Details", "Take a look at all of the item details in ", [this](Player& player) { ShowLootDetails(); }));
        DecisionInLoot.pushBack(Decision("Take an item", "Take an item from  the loot to your inventory", [this](Player& player) {PlayerPickUpLoot(); }));
        int choice;
        cout << "\nSelect an option:" << endl;
        cout << "1. View All Loot  Details" << endl;
        cout << "2. Add an Item to Inventory" << endl;
        cout << "3. Go back to previous menu" << endl;
        cout << "Choice (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:
            fPlayer->MakeDecision(DecisionInLoot[0]);
            cout << "Press Enter to go back to view all loot";
            cin.ignore(); // Ignore leftover newline from previous input
            cin.ignore();
            system("clear");
            break;
        case 2:
            if (currentScene->getLoot().isEmpty()) {
                cout << "Loot is empty!" << endl;
            }
            else {
                fPlayer->MakeDecision(DecisionInLoot[1]);
                cout << "Press Enter to go back to view all loot";
                cin.ignore(); // Ignore leftover newline from previous input
                cin.ignore(); // Ignore leftover newline from previous input
                system("clear");
            }
            break;
        case 3:
            inLootMenu = false; // Exit inventory menu
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
};
void Game::ShowLootDetails() {
    Scene* currentScene = getCurrentScene();
    currentScene->ShowLootsDetails();
}

void Game::PlayerPickUpLoot() {
    system("CLS");
    Scene* currentScene = getCurrentScene();
    int continuePicking = 1;  // Initialize to 1 (Yes) to start the loop

    while (continuePicking == 1) {  // Loop while the player chooses "Yes"
        int index = 0;

        cout << "---------------- " << currentScene->getName() << "'s loot ----------------" << endl;
        currentScene->ShowLoots();
        cout << "---------------------------------------------------------" << endl;
        cout << "\nType the number corresponding to the desired item and press Enter (e.g., 1): ";
        cin >> index;
        index--;  // Adjust for zero-based indexing

        // Validate the player's input for a valid index
        if (index < 0 || index >= currentScene->getLoot().size()) {
            cout << "Invalid choice!" << endl;
            cout << endl;
        }
        else {
            // Retrieve the selected item and add it to the player's inventory
            Item* selectedItem = currentScene->getLoot()[index];
            fPlayer->AddItem(selectedItem);

            // Remove the item from the scene's loot
            currentScene->getLoot().popAt(index);
        }

        // Prompt the player if they want to pick up another item
        if (currentScene->getLoot().isEmpty()) {
            cout << "No more loot left!" << endl;
            continuePicking = 2;
        }
        else {
            cout << "\nDo you want to pick up another item?" << endl;
            cout << "1. Yes\n2. No" << endl;
            cout << "Enter your choice: ";
            cin >> continuePicking;
        }

        // Clear the screen if the player chooses to continue
        if (continuePicking == 1) {
            system("CLS");
        }
    }

    cout << "Exiting loot pickup." << endl;
}

//fMonsters
void Game::MonsterJumpscare() {
    fMonster->Jumpscare();
};
void Game::MonsterAmbush() {
    fMonster->Ambush(*fPlayer);
};

void Game::Play() {
    if (fRootScene->isEmpty()) {
        cout << "There's no scene in the game!" << endl;
    }
    else {
        bool IsExit = false;
        while (!IsExit) {
            PlaySceneEvent();
            DisplayPlayerMenu();
        }
    }
};

Game::~Game() {
    if (fRootScene != &TreeScene::NIL) {
        delete fRootScene; // This deletes the allocated TreeScene
    }
}