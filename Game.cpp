#include "Game.h"
#include "SinglyLinkedNodeIterator.h"
#include <fstream>
typedef BTree<Scene*> TreeScene;

//Constructor
Game::Game(Player* pPlayer, Monster* pMonster): fRootScene(&TreeScene::NIL), fPlayer(pPlayer),fMonster(pMonster), fTurnHunger(0), fTurnStamina(0), fTurnThirst(0), isGameOver(false), isWin(false) {
    fTreeTarget = fRootScene; //Set fTreeTarget to fRootScene (in this case it will be the sentinel node)
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
//Setter for fRootScene
void Game::setRootScene(TreeScene* pNewRoot) {
    fRootScene = pNewRoot;
};

//Increase turns
void Game::IncreaseTurn() {
    fTurnStamina++;
    fTurnThirst++;
    fTurnHunger++;
};
bool Game::getIsGameOver() {
    return isGameOver;
};
void Game::setIsGameOver(bool pFlag) {
    isGameOver = pFlag;
};
bool Game::getIsWin() {
    return isWin;
};
void Game::setIsWin(bool pFlag) {
    isWin = pFlag;
};

int Game::FightScene() {
    fPlayer->setIsFighting(true);	//Player is now fighting
    int choice = 0;					//What choice would the player do
    bool turnFinish = false;		//Is turn finish
    do {
        system("CLS");
        //Show Player's attributes
        CheckReduceResources();
        cout << "Your Attributes:";
        cout << "\nHealth: \t" << fPlayer->getCurrentHealth() << "/" << fPlayer->getHealth() << endl;
        cout << "Hunger: \t" << fPlayer->getCurrentHungerLevel() << "/" << fPlayer->getMaxHungerLevel() << endl;
        cout << "Thirst: \t" << fPlayer->getCurrentThirstLevel() << "/" << fPlayer->getMaxThirstLevel() << endl;
        cout << "Stamina: \t" << fPlayer->getCurrentStaminaLevel() << "/" << fPlayer->getMaxStaminaLevel() << endl;
        cout << "Damage: \t" << fPlayer->getAttackDamage() << endl;
        if (fPlayer->getCurrentItem() == nullptr) {
            cout << "Equiped Item: \tEmpty Slot" << endl;
        }
        else {
            cout << "Equiped Item: \t" << fPlayer->getCurrentItem()->getName() << endl;
        }
        cout << endl;

        //Show monster's attributes
        cout << fMonster->getName() << "'s Attributes:";
        cout << "\nHealth: \t" << fMonster->getCurrentHealth() << "/" << fMonster->getHealth() << endl;
        cout << "Damage: \t" << fMonster->getAttackDamage() + fMonster->getWeapon()->getDamage() << endl;
        cout << "Weapon Name: \t" << fMonster->getWeapon()->getName() << endl;
        cout << "Durability: \t" << fMonster->getWeapon()->getDurability() << endl;
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
            if (fPlayer->UseCurrentItem()) {	//If succesfully used the item, then...
                if (Weapon* weapon = dynamic_cast<Weapon*>(fPlayer->getCurrentItem())) {		//If current item is a weapon (it will increase the player's attack damage)
                    fMonster->TakeDamage(fPlayer->getAttackDamage());
                    string message = "\nYou have dealt " + to_string(fPlayer->getAttackDamage()) + " to " + fMonster->getName() + "!\n";
                    cout << message << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    fPlayer->setAttackDamage(fPlayer->getAttackDamage() - weapon->getDamage()); //Decrease the damage back down to the original damage
                }
                turnFinish = true;	//Finish turn
                IncreaseTurn();
            }
        }
        else if (choice == 2) { 	//Equip item
            fPlayer->EquipItem();	//Cal player's EquipItem method
        }
        else if (choice == 3) {		//Player give up
            turnFinish = true;
            return -1; //-1 means the player gave up
        }
    } while (!turnFinish);
    return 0; //0 player's turn finishred
    fPlayer->setIsFighting(false);	//Player stop fighting
};

//Remove all the decisions in fDecisions
void Game::RemoveDecisions() {
    while (!fDecisions.isEmpty()) {
        fDecisions.popFront();
    }
};

void Game::LoadPlayerMenuDecision() {
    RemoveDecisions(); //Remove all decisions
    Decision ViewAttributes = Decision("View Character's Attributes", "Take a look at all the attributes of your character.", [this](Entity& fEntity) { fPlayer->ShowAttributes(); });
    Decision ViewInvetory = Decision("View Inventory", "Take a look at all the items in your inventory.", [this](Entity& fEntity) { DisplayInventoryMenu(); });
    Decision UseItem = Decision("Use Equipped Item", "Use your currently equipped item.", [this](Entity& fEntity) {if (fPlayer->UseCurrentItem()) IncreaseTurn();  });
    Decision SearchForLoot = Decision("Search for loot", "Search the area for loot.", [this](Entity& fEntity) {IncreaseTurn(); DisplayLootMenu(); });
    Decision Discover = Decision("Discover more areas", "Moving to next location", [this](Entity& fEntity) { DiscoverMenu(); });
    Decision Exit = Decision("Exit Game", "Exit the game", [this](Entity& fEntity) { setIsGameOver(true); });
    AddDecisions(ViewAttributes);   //Add view attributes Decisions
    AddDecisions(ViewInvetory);     //View Inventory menu
    AddDecisions(UseItem);          //Use Item
    AddDecisions(SearchForLoot);    //Search Foor Loot menu
    AddDecisions(Discover);         //Discover Menu
    AddDecisions(Exit);             //Exit game
}
void Game::LoadInventoryMenuDecision(){
    RemoveDecisions(); //Remove all decisions
    //View all item details decisions
    fDecisions.pushBack(Decision("View All Item Details", "Take a look at all of the item details in your inventory", [this](Entity& pEntity) { fPlayer->ViewItemsDetails(); }));
    //Equip an item decisions
    fDecisions.pushBack(Decision("Equip an item", "Equip an item from your inventory", [this](Entity& pEntity) {  if (fPlayer->EquipItem()) IncreaseTurn(); }));
    //Discard an item
    fDecisions.pushBack(Decision("Discard an item", "Discard an item from your inventory", [this](Entity& pEntity) {  if (fPlayer->DiscardItem()) IncreaseTurn(); }));
};
void Game::LoadLootMenuDecision() {
    RemoveDecisions(); //Remove all decisions
    Scene* currentScene = getCurrentScene();
    if (!currentScene->getLoot().isEmpty()){ //If currentScene's loot is not empty, then...
        //Add View ALl Item Decision
        fDecisions.pushBack(Decision("View All Item Details", "Take a look at all of the item details in ", [this](Entity& pEntity) { ShowLootDetails(); }));
        //Take an item decision
        fDecisions.pushBack(Decision("Take an item", "Take an item from  the loot to your inventory", [this](Entity& pEntity) {PlayerPickUpLoot(); }));
    }
};
void Game::LoadDiscoverMenuDecision() {
    RemoveDecisions(); //Remove all decisions
    //Check if left route is available
    if (!fTreeTarget->left().isEmpty()) {
        //Add move to left route option
        fDecisions.pushBack(Decision("Move left to " + fTreeTarget->left().key()->getName(),
            "Move to the left route to discover " + fTreeTarget->left().key()->getName(),
            [this](Entity& fEntity) { PlayerMoveLeft(); }));
    }

    // Check if right route is available
    if (!fTreeTarget->right().isEmpty()) {
        //Add move to right route option
        fDecisions.pushBack(Decision("Move right to " + fTreeTarget->right().key()->getName(),
            "Move to the right route to discover " + fTreeTarget->right().key()->getName(),
            [this](Entity& fEntity) { PlayerMoveRight(); }));
    }
    //Head back to root node
    fDecisions.pushBack(Decision("Head back to Crash Site",
        "Take a look at all of the item details in your inventory",
        [this](Entity& fEntity) { BackToRoot(); }));
};

//Adding Decision into fDecisions
void Game::AddDecisions(Decision& pDecision){
    fDecisions.pushBack(pDecision);
};

//Show all the available Decisions
void Game::ShowDecisions(List<Decision>& pDecision) {
    int x = 1;
    for (DoublyLinkedNodeIterator<Decision> it = pDecision.getIteratorHead(); it != it.end(); ++it) {
        cout << x << ". " << it.getCurrent()->getValue().getName() << endl;
        x++;
    }
};

//Attach Left Tree to fTreeTarget
void Game::AttachLeftScene(Scene* pScene){
    TreeScene* newScene= new TreeScene(pScene);
    fTreeTarget->attachLeft(newScene);
};

//Attach Right Tree to fTreeTarget
void Game::AttachRightScene(Scene* pScene){
    TreeScene* newScene = new TreeScene(pScene);
    fTreeTarget->attachRight(newScene);
};

//Detach Left Tree of fTreeTarget
void Game::DettachLeftScene(){
    fTreeTarget->detachLeft();
};

//Detach Right Tree of fTreeTarget
void Game::DettachRightScene(){
    fTreeTarget->detachRight();
};

//Player Move Left
void Game::PlayerMoveLeft(){
    //If left is empty then...
    if (fTreeTarget->left().isEmpty()) {
        cout << "No route to go to..." << endl;
    }else { //else...
        fPlayer->DecreaseStamina(1); //Decrease stamina by 1
        IncreaseTurn(); //Increase player's turn
        system("CLS");
        cout<<"Moving to " << fTreeTarget->left().key()->getName();
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". ";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". " << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
        setTreeTarget(&fTreeTarget->left()); //Set TreeTarget to current TreeTarget's left
        PlaySceneEvent(); //Play event in the Scene
    }
};

//Player Move right
void Game::PlayerMoveRight(){
    //if fTreeTarget's right node is empty = no route to go
    if (fTreeTarget->right().isEmpty()) {
        cout << "No route to go to..." << endl;
    }
    else {
        fPlayer->DecreaseStamina(1); //Decrease stamina by 1
        IncreaseTurn(); //Increase player's turn
        system("CLS");
        cout<<"Moving to " << fTreeTarget->right().key()->getName();
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". ";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". " << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
        setTreeTarget(&fTreeTarget->right()); //Set TreeTarget to current TreeTarget's right
        PlaySceneEvent(); //Play events in the scene
    }
};

//Go Left (For debugging purposes)
void Game::Left() {
    setTreeTarget(&fTreeTarget->left());
};

//Go Right (For debugging purposes)
void Game::Right() {
    setTreeTarget(&fTreeTarget->right());
};

//Go back to fSceneRoot
void Game::BackToRoot() {
    //If fTreeTarget is equal to fRootScene then the player is already in the Root node
    if (fTreeTarget == fRootScene) {
        cout << "You're already at the crash site!" << endl;
        system("PAUSE");
    }
    else {
        fPlayer->DecreaseStamina(1); //Decrease stamina by 1
        IncreaseTurn(); //Increase player's turn
        cout << "Moving back to " << fRootScene->key()->getName() << endl;
        setTreeTarget(fRootScene); //Set Tree Target to fRootScene
        PlaySceneEvent();
    }
}
void Game::DiscoverMenu() {
    if (!getIsGameOver()) {
        system("CLS");
        bool inDiscoveringMenu = true;
        cout << "Discovering. ";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". ";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". " << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");

        LoadDiscoverMenuDecision();

        // Check if there are routes available to the left and right and show them
        string availableWays = "\t\tNo route available, head back to crash site"; // Default message

        // Check if left route is available
        if (!fTreeTarget->left().isEmpty()) {
            availableWays = "Left Route: " + fTreeTarget->left().key()->getName() + "\t\t"; // Update if left route is found
        }

        // Check if right route is available
        if (!fTreeTarget->right().isEmpty()) {
            // If left route was also found, append to existing routes
            if (availableWays != "No route available, head back to crash site") {
                availableWays += "Right Route: " + fTreeTarget->right().key()->getName() + "\t\t";
            }
            else {
                availableWays = "Right Route: " + fTreeTarget->right().key()->getName() + "\t\t";
            }
        }

        while (inDiscoveringMenu) {
            cout << "-------------------------------- Discover Routes Menu --------------------------------" << endl;
            cout << endl;
            cout << "\t" << availableWays << "\n" << endl;
            cout << "---------------------------------------------------------------------------------------\n";
            int choice = 0;
            cout << "Select an option:" << endl;
            ShowDecisions(fDecisions);
            cout << fDecisions.size() + 1 << ". Go back to previous menu" << endl;
            cout << "---------------------------------------------------------------------------------------\n";
            cout << "Choice (1-" << fDecisions.size() + 1 << "): ";
            cin >> choice;

            // Adjust for zero-based indexing and validate the choice
            if (choice > 0 && choice <= fDecisions.size() + 1) {
                choice--; // Convert to zero-based index

                if (choice == fDecisions.size()) {
                    inDiscoveringMenu = false; // Exit discovering menu
                }
                else {
                    fPlayer->MakeDecision(fDecisions[choice]);
                    inDiscoveringMenu = false;
                }
            }
            else {
                system("CLS");
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }
}

//Play current scene's event
void Game::PlaySceneEvent(){
    fTreeTarget->key()->PlayEvent();
};

//fPlayer;
void Game::DisplayPlayerMenu() {
    if (!getIsGameOver()) {
        LoadPlayerMenuDecision(); //Load player menu
        //Player's stats
        cout << "\n---------------- Player Menu ----------------" << endl;
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
            system("CLS");
        }
    }
};

void Game::DisplayInventoryMenu() {
    if (!getIsGameOver()) {
        bool inInventoryMenu = true;

        while (inInventoryMenu) {
            // Display player's inventory
            fPlayer->ViewItems();
            cout << "Select an option:" << endl;
            LoadInventoryMenuDecision();
            ShowDecisions(fDecisions);
            cout << fDecisions.size() + 1 << ". Go back to previous menu" << endl;
            cout << "--------------------------------------------------\n";

            int choice;
            cout << "Choice (1-" << fDecisions.size() + 1 << "): ";
            cin >> choice;

            // Check if the choice is within valid range
            if (choice > 0 && choice <= fDecisions.size() + 1) {
                choice--; // Convert to zero-based index

                if (choice == fDecisions.size()) {
                    inInventoryMenu = false; // Exit inventory menu
                }else {
                    // Execute the selected decision
                    fPlayer->MakeDecision(fDecisions[choice]);
                }
            }else{
                system("CLS");
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }
};

//Display loot menu
void Game::DisplayLootMenu() {
    system("CLS");
    if (!getIsGameOver()) {
        bool inLootMenu = true;
        Scene* currentScene = getCurrentScene();
        cout << "Searching " << currentScene->getName() <<"'s Loot. ";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". ";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ". " << endl;
        this_thread::sleep_for(chrono::seconds(1));
        while (inLootMenu) {
            system("CLS");
            LoadLootMenuDecision();     //Load loot menu's decisions
            int choice;
            cout << "---------------- " << currentScene->getName() << "'s loot ----------------" << endl;
            if (currentScene->getLoot().isEmpty()) {
                cout << "\t\t" << currentScene->getName() <<" has no  loot!" << endl;
            }
            else {
                currentScene->ShowLoots();
            }
            cout << "---------------------------------------------------------" << endl;
            cout << "\nSelect an option:" << endl;
            ShowDecisions(fDecisions);
            cout << fDecisions.size() + 1 <<". Go back to previous menu" << endl;
            cout << "Choice (1-" << fDecisions.size() + 1 << "): ";
            cin >> choice;
            if (choice > 0 && choice <= fDecisions.size() + 1) {
                choice--;
                if (choice == fDecisions.size()) {
                    inLootMenu = false; // Exit loot menu
                }
                else {
                    fPlayer->MakeDecision(fDecisions[choice]);  //Player make decision
                }
            }
            else {
                system("CLS");
                cout << "Invalid choice, please try again." << endl;
            }
        }
    }
};

//Show look details
void Game::ShowLootDetails() {
    Scene* currentScene = getCurrentScene();
    currentScene->ShowLootsDetails();
    system("PAUSE");
}

//Reduce player's resources
void Game::CheckReduceResources() {
    //Every 3 turn, increase thirst level
    if (fTurnThirst % 3 == 0 && fTurnThirst != 0) {
        fPlayer->IncreaseThirstLevel(1);
        fTurnThirst = 0;
    }
    //Every 4 turns, decrease stamina
    if (fTurnStamina % 4 == 0 && fTurnStamina != 0) {
        fPlayer->DecreaseStamina(1);
        fTurnStamina = 0;
    }
    //Every 5 turns, increase hunger level
    if (fTurnHunger % 5 == 0 && fTurnHunger != 0) {
        fPlayer->IncreaseHungerLevel(1);
        fTurnHunger = 0;
    }
    fPlayer->ApplyEffects(*fMonster);
    if (!fPlayer->getIsAlive()) {
        setIsGameOver(true);
    }
};

void Game::PlayerPickUpLoot() {
    system("CLS");
    Scene* currentScene = getCurrentScene(); //Current Scene the player is in
    // Check if there's any loot in the current scene
    if (currentScene->getLoot().isEmpty()) {
        cout << "There's no loot here!" << endl;
        return;
    }
    // Initialize iterator and index
    DoublyLinkedNodeIterator<Item*> it = currentScene->getLoot().getIteratorHead();
    int index = 0;

    // Start interaction loop
    while (true) {
        // Display the current loot item
        Item* currentItem = *it;
        cout << "-------------------------------- " << currentScene->getName() << "'s loot --------------------------------" << endl;
        currentScene->ShowLootDetails(currentItem);
        cout << "-----------------------------------------------------------------------------------------" << endl;

        // Display options for the player
        cout << "Options:\n";
        cout << "1. Next Item\n";       // Option to move to the next item
        cout << "2. Previous Item\n";   // Option to move to the previous item
        cout << "3. Take Item\n";       // Option to take the current item
        cout << "4. Exit Menu\n";       // Option to exit the loot menu
        cout << "Choice: ";             // Prompt the player for their choice
        // Get player choice
        int choice;
        cin >> choice;

        //If choice is to move to next item, and currentItem is not the last then...
        if (choice == 1 && it != currentScene->getLoot().getIteratorLast()) {
            ++it;  // Move to the next item
            index++; //Increase index by 1
        }
        //If choice is to move to previous item, and currentItem is not the head then...
        else if (choice == 2 && it != currentScene->getLoot().getIteratorHead()) {
            --it;  // Move to the previous item
            index--; //Decrease index by 1
        }
        else if (choice == 3) {
            // Take (remove) the current item from loot
            Item* selectedItem = currentScene->getLoot()[index];

            //if player's succesfully added the item, then...
            if (fPlayer->AddItem(selectedItem)) {
                currentScene->getLoot().popAt(index); // Remove the item from the scene's loot
                if (currentScene->getLoot().isEmpty()) {
                    cout << "All loot has been taken!\n";
                    break;
                }
                // Reinitialize iterator after modification
                else if (index >= currentScene->getLoot().size()) {
                    // If we removed the last item, reset to the previous one
                    index = currentScene->getLoot().size() - 1;
                    it = currentScene->getLoot().getIteratorHead();
                    for (int i = 0; i < index; ++i) {
                        ++it;
                    }
                }
                else {
                    // Otherwise, reset iterator to the current index
                    it = currentScene->getLoot().getIteratorHead();
                    for (int i = 0; i < index; ++i) {
                        ++it;
                    }
                }
            }else {
                system("PAUSE");
            }
        }
        else if (choice == 4) {
            cout << "Exiting loot view.\n";
            system("PAUSE");
            break;  // Exit the loop
        }
        else {
            cout << "Invalid choice or no more items in that direction.\n";
            system("PAUSE");
        }
        system("CLS");
    }
}

//Play game
void Game::Play() {
    if (fRootScene->isEmpty()) {
        cout << "There's no scene in the game!" << endl;
    }
    else {
        while (!isGameOver && !isWin) {
            if (fPlayer->getCurrentHealth() == 0) {
                setIsGameOver(true);
            }
            else if (fMonster->getCurrentHealth() == 0) {
                setIsWin(true);
            }else {
                PlaySceneEvent(); //Play scene's event
                CheckReduceResources(); //Check for flags to reduce resources
                DisplayPlayerMenu();    //Display Menu
            }
        }
        if (isWin) {
            cout << "Congratulation " << fPlayer->getName() << ", you have survived the silent distress... for now" << endl;
        }
        if (isGameOver) {
            cout << "Game Over...You were always meant to lose..." << endl;
        }
    }
};

//Save Player's Decision
void Game::SavePlayerDecisions() {
    // Open a file to save decisions
    ofstream outFile("PlayerDecisions.txt");
    if (!outFile) {
        cerr << "Error opening file to save decisions!" << endl;
        return;
    }
    outFile << fPlayer->getName() << "'s Decisions Log:\n\n";
    if (isWin) { //If Win then...
        outFile << "Status: Win\n\n"; //Show Status: Win
    }
    if (isGameOver) { //If Game Over then...
        outFile << "Status: Lose\n\n"; //Show Status: Lose
    }
    SinglyLinkedList<Decision>* decisions = fPlayer->getDecisionsMade(); //fPLayer's Made Decision
    //Write the Decisions Made into PlayerDecisions.txt
    for (SinglyLinkedNodeIterator<Decision> iter = decisions->getIteratorHead(); iter != iter.end(); ++iter) { //Iterate through the SLL
        Decision currentDecision = *iter;
        outFile << "Decision: " << currentDecision.getName() << "\n";
        outFile << "Description: " << currentDecision.getDescription() << "\n\n";
    }
    outFile << "End of decisions.\n";
    outFile.close();
    cout << "All decisions have been saved to PlayerDecisions.txt" << endl;
}

//Load Player's previous decisions
void Game::LoadPlayerMenuDecisions() {
    system("CLS");
    ifstream inFile("PlayerDecisions.txt");

    // Check if the file opened successfully
    if (!inFile) {
        cout << "No previous decisions found.\n";
        return;
    }

    // Check if the file is empty
    inFile.seekg(0, ios::end);  // Move to the end of the file
    if (inFile.tellg() == 0) {       // Check if the position is at 0 (meaning it's empty)
        cout << "Decision file exists but is empty.\n";
        inFile.close();
        return;
    }
    inFile.seekg(0, ios::beg);  // Move back to the start of the file
    string line;
    // Read each line from the file and display it
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}
Game::~Game() {
    if (fRootScene != &TreeScene::NIL) {
        delete fRootScene; // This deletes the allocated TreeScene
    }
}