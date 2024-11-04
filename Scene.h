#pragma once
#include "Player.h"
#include "Monster.h"
#include "Decision.h"
#include "Stack.h"
#include "NTree.h"
class Scene
{
	private:
		string fName;					//Name of scene
		string fDescription;			//Description of the scene
		List<Decision> fDecisions;		//Decisions in the scene to be made by players
		List<Item*> fLoot;				//Loot in the scene for players to add to inventory
		Player* fPlayer;				//Player is in all the scene
		Monster* fMonster;				//Monster is in all the scene
		NTree<Scene, 3> fSceneChilds;	//Childs of this scene class
	public:
		Scene(string pName, string pDescription, Player* pPlayer, Monster* pMonster);
		string getName() const;
		string getDescription() const;
		List<Decision> getDecisions() const;
		Player* getPlayer();
		Monster* getMonster();
		void AddDecisions();
		void AddLoot();
		void AttachScene(int pIndex, NTree<Scene, 3>* pSceneChild);
		void DetachScene(int pIndex);



};

