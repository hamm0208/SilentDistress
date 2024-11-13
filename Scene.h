#pragma once
#include "Queue.h"
#include "Event.h"
class Item; //Foward Declaration
class Scene{
	private:
		string fName;					//Name of scene
		string fDescription;			//Description of the scene
		List<Item*> fLoot;				//Loot in the scene for players to add to inventory (Usage of DoublyLinkedList)
		Queue<Event*> fEvents;			//Queue of the events (Usage of Queue)
	public:
		Scene(); //Default constructor
		Scene(string pName, string pDescription, int pMaxNumberOfEvent); //Overloaded constructor
		~Scene(); //Destructor of scenea
		//Getter for fName
		string getName() const;
		//Getter for fDescription
		string getDescription() const;
		//Getter for fLoot
		List<Item*>& getLoot();
		//Getter for fEvent
		Queue<Event*> getEvent();

		void AddLoot(Item* pLoot); 		//Add loot to scene
		void AddEvent(Event* fEvent);	//Add event to the queue
		void PlayEvent();				//Play the event
		bool IsEventEmpty();			//Check if the event is empty
		void ShowLoots();				//Show the loots in the scene
		void ShowLootDetails(Item* pItem);
        void ShowLootsDetails();		//Show the loot details
};