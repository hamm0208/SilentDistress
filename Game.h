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
		Player* fPlayer;				
		Monster* fMonster;
		List<Decision> fDecisions;
        TreeScene* fRootScene;
        TreeScene* fTreeTarget;
        int fTurnHunger;
        int fTurnThirst;
        int fTurnStamina;
        bool isGameOver;
        bool isWin;
    public:
        Game(Player* pPlayer, Monster* pMonster);
        ~Game();
        Player* getPlayer();
        Monster* getMonster();
		List<Decision> getDecisions() const;
        Scene* getCurrentScene();
        int getTurn();
        void IncreaseTurn();
        bool getIsGameOver();
        void setIsGameOver(bool pFlag);
        bool getIsWin();
        void setIsWin(bool pFlag);
        TreeScene* getTreeTarget();
        void setTreeTarget(TreeScene* pNewTarget);
        TreeScene* getRootScene() const;
        void setRootScene(TreeScene* pNewRoot);
        //fDecisions
        void AddDecisions(Decision& pDecision);
        void ShowDecisions(List<Decision>& pDecision);

        //fRootScene & fTreeTarget
        void AttachLeftScene(Scene* pScene);  //Attach to fTreeTarget's left node
        void AttachRightScene(Scene* pScene); //Attach to fTreeTarget's right node
        void DettachLeftScene();  //Attach to fTreeTarget's left node
        void DettachRightScene(); //Attach to fTreeTarget's right node
        void PlayerMoveLeft();
        void PlayerMoveRight();
        void Left();
        void Right();
        void BackToRoot();
        void DiscoverMenu();

        void PlaySceneEvent();

        //fPlayer;
        void DisplayPlayerMenu();
        void DisplayInventoryMenu();
        void DisplayLootMenu();
        void PlayerPickUpLoot();
        void ShowLootDetails();
        void CheckReduceResources();
        //fMonsters
        void MonsterJumpscare1();
        void MonsterAmbush();
        void Play();
};