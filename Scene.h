#pragma once
#include "BTree.h"
#include "Player.h"
#include "Monster.h"
#include "Decision.h"
#include "Stack.h"
#include "Event.h"
class Scene
{
	private:
		string fName;					//Name of scene
		string fDescription;			//Description of the scene
		List<Decision> fDecisions;		//Decisions in the scene to be made by players
		List<Item*> fLoot;				//Loot in the scene for players to add to inventory
		Stack<Event*> fEvents;			//Events of the scene
		Player* fPlayer;				//Player is in all the scene
		Monster* fMonster;				//Monster is in all the scene
		BTree<Scene*> fSceneTree;	//Childs of this scene class
	public:
		Scene();
		Scene(string pName, string pDescription, Player* pPlayer, Monster* pMonster, int pMaxNumberOfEvent);
		string getName() const;
		string getDescription() const;
		List<Decision> getDecisions() const;
		Player* getPlayer();
		Monster* getMonster();
		void AddLoot(Item* pLoot);
		void AttachLeftChild(BTree<Scene*>* pSceneChild);
		void AttachRightChild(BTree<Scene*>* pSceneChild);
		void AddDecisions(Decision pDecision);
		void AddEvent(Event* fEvent);
		void PlayEvent();
		bool IsEventEmpty();
		void ShowLoots();
		BTree<Scene*>* DetachLeftChild();
		BTree<Scene*>* DetachRightChild();
		void ShowDecisions();
		bool PlayerPickUpLoot();
		void PlayerMenu();
		void PlayerMoveToNextScene();
		void MonsterAmbush();
		void MonsterJumpScare();
		void DisplayInventoryMenu();
};