#pragma once
#include "BTree.h"
#include "Player.h"
#include "Monster.h"
#include "Scene.h"
#include "Decision.h"

class Game{
    public:
        typedef BTree<Scene*> TreeScene;
	private:
		Player* fPlayer;		        //pointer to Player in the Game		
		Monster* fMonster;              //pointer to Monster in the Game
		List<Decision> fDecisions;      //List of Decisions available in the game
        TreeScene* fRootScene;          //RootNode of the Binary Tree
        TreeScene* fTreeTarget;         //TargetNode that points to the current node that the user is at
        int fTurnHunger;                //Number of hunger turns to increase the Hunger Level
        int fTurnThirst;                //Number of thirst turns to increase the thirst Level
        int fTurnStamina;               //Number of stamina turns to decrease the stamina Level
        bool isGameOver;                //Is game over
        bool isWin;                     //Is player win
    public:
        Game(Player* pPlayer, Monster* pMonster);   //Constructor
        ~Game();                                    //Destructor
        //Getters
        Player* getPlayer();                        
        Monster* getMonster();
		List<Decision> getDecisions() const;
        Scene* getCurrentScene();
        bool getIsGameOver();
        bool getIsWin();
        TreeScene* getTreeTarget();
        TreeScene* getRootScene() const;

        //Setters
        void setIsWin(bool pFlag);
        void setTreeTarget(TreeScene* pNewTarget);
        void setRootScene(TreeScene* pNewRoot);
        void setIsGameOver(bool pFlag);

        void IncreaseTurn();                            //Increase turn
        void AddDecisions(Decision& pDecision);         //Add decisions into the Game
        void ShowDecisions(List<Decision>& pDecision);  //Show decisions available in the game
        void AttachLeftScene(Scene* pScene);            //Attach to fTreeTarget's left node
        void AttachRightScene(Scene* pScene);           //Attach to fTreeTarget's right node
        void DettachLeftScene();                        //Detach from fTreeTarget's left node
        void DettachRightScene();                       //Detach from fTreeTarget's right node
        void PlayerMoveLeft();                          //Player Move Left
        void PlayerMoveRight();                         //Player Move Right
        void Left();                                    //Move Left for debugging purposes
        void Right();                                   //Move Right for debugging purposes
        void BackToRoot();                              //Move TargetNode back to Root
        void DiscoverMenu();                            //Discover new scene menu
        void PlaySceneEvent();                          //Play scene's event
        void DisplayPlayerMenu();                       //Player's default menu
        void DisplayInventoryMenu();                    //Player's inventory menu
        void PlayerPickUpLoot();                        //Player Pick up Loot
        void DisplayLootMenu();                         //Loot Menu
        void ShowLootDetails();                         //Show loot details
        void CheckReduceResources();                    //Reduce player's resources based on turns
        void Play();                                    //Start the game
        void SavePlayerDecisions();                     //Save the decisions made by player into a file
        void LoadPlayerDecisions();                     //Load the decisions made by player
};