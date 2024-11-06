#include "Game.h"
typedef BTree<Scene*> TreeScene;

Game::Game(Player* pPlayer, Monster* pMonster): fRootScene(&TreeScene::NIL), fPlayer(pPlayer),fMonster(pMonster){
    fTreeTarget = fRootScene;
    Decision ViewAttributes = Decision("View Character's Attributes","Take a look at all the attributes of your character.",[this](Player& player) { player.ShowAttributes(); });
    Decision ViewInvetory = Decision("View Inventory","Take a look at all the items in your inventory.",[this](Player& player) { DisplayInventoryMenu(); });
    Decision Exit = Decision("Exit Game", "Exit the game", [this](Player& player) { exit(0); });
    AddDecisions(ViewAttributes);
    AddDecisions(ViewInvetory);
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
};
void Game::MoveRight(){
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
};

void Game::PlaySceneEvent(){
    fTreeTarget->key()->PlayEvent();
};

//fPlayer;
void Game::DisplayPlayerMenu() {
    system("CLS");
    cout << "\n--------------------------------------------------\n";
    cout << "Current Location: \t" << getCurrentScene()->getName() << endl;
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

    if (index<0 || index > fDecisions.size()) {
        cout << "Invalid choice!" << endl;
    }
    else {
        fPlayer->MakeDecision(fDecisions[index]);
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
            cout << "Invalid choice, please try again." << endl;
        }
    }
};
/*
void Game::DisplayLootMenu() {
    bool inLootMenu = true;

    while (inLootMenu) {
        Scene* currentScene = getCurrentScene();
        cout << "---------------- " << currentScene->getName() << "'s loot ----------------" << endl;
        currentScene->ShowLoots();
        List<Decision> DecisionInLoot;
        DecisionInLoot.pushBack(Decision("View All Item Details", "Take a look at all of the item details in ", nullptr, [this](Scene& currentScene) { currentScene.ShowLootsDetails(); }, nullptr));
        DecisionInLoot.pushBack(Decision("Take an item", "Take an item from  the loot to your inventory", [this](Player& player) {PlayerPickUpLoot(); }, nullptr, nullptr));
        int choice;
        cout << "Choice (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:
            fPlayer->MakeDecision(DecisionInLoot[0]);
            cout << "Press Enter to go back to view all loot";
            cin.ignore(); // Ignore leftover newline from previous input
            cin.ignore();
            break;
        case 2:
            fPlayer->MakeDecision(DecisionInLoot[1]);
            cout << "Press Enter to go back to view all loot";
            cin.ignore(); // Ignore leftover newline from previous input
            cin.ignore(); // Ignore leftover newline from previous input
            break;
        case 3:
            inLootMenu = false; // Exit inventory menu
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
};

bool Game::PlayerPickUpLoot() {
    Scene* currentScene = getCurrentScene();
    int index = 0;
    currentScene->ShowLoots();
    cout << "\nType the number corresponding to the desired item and press Enter (e.g., 1): ";
    cin >> index;
    index--;
    if (index<0 || index > currentScene->getLoot().size()) {
        cout << "Invalid choice!" << endl;
        cout << endl;
        return false;
    }
    else {
        fPlayer->AddItem(currentScene->getLoot()[index]);
        currentScene->getLoot().popAt(index);
        cout << endl;
        return true;
    }
};
*/

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