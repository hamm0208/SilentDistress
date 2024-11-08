#pragma once
#include "Queue.h"
#include "Event.h"
class Item;
class Scene
{
	private:
		string fName;					//Name of scene
		string fDescription;			//Description of the scene
		List<Item*> fLoot;				//Loot in the scene for players to add to inventory
		Queue<Event*> fEvents;			//Events of the scene
	public:
		Scene();
		Scene(string pName, string pDescription, int pMaxNumberOfEvent);
		~Scene();
		string getName() const;
		string getDescription() const;
		List<Item*>& getLoot();
		Queue<Event*> getEvent();
		void AddLoot(Item* pLoot);
		void AddEvent(Event* fEvent);
		void PlayEvent();
		bool IsEventEmpty();
		void ShowLoots();
        void ShowLootsDetails();
};