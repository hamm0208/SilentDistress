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
    public:
        Game(Player* pPlayer, Monster* pMonster);
        ~Game();
        Player* getPlayer();
        Monster* getMonster();
		List<Decision> getDecisions() const;
        Scene* getCurrentScene();

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
        void MoveLeft();
        void MoveRight();

        void PlaySceneEvent();

        //fPlayer;
        void DisplayPlayerMenu();
        void DisplayInventoryMenu();
        //void DisplayLootMenu();
        //bool PlayerPickUpLoot();

        //fMonsters
        void MonsterJumpscare();
        void MonsterAmbush();

        void Play();
};

/*
fDecisions.pushBack(Decision("View Character's Attributes",
        "Take a look at all the attributes of your character.",
        [this](Player& player) { player.ShowAttributes(); })); //Calling this fPlayer's ShowAttributes() method
    fDecisions.pushBack(Decision("View Inventory",
        "Take a look at all the items in your inventory.",
        [this](Player& player) { DisplayInventoryMenu(); })); //Calling this fPlayer's ViewItems() method
    fDecisions.pushBack(Decision("Exit Game",
        "Exit the game",
        [this](Player& player) { exit(0); })); //Exit Program
*/