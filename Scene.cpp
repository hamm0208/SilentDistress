#include "Scene.h"
#include "Item.h"
#include <thread>
#include <chrono>

Scene::Scene(): fName(""), fDescription(""), fEvents(5){
}
Scene::Scene(string pName, string pDescription, int pMaxNumberOfEvent) : fName(pName), fDescription(pDescription), fEvents(pMaxNumberOfEvent) {
    
}
/*
Scene::Scene() : fName(""), fDescription(""), fPlayer(nullptr), fMonster(nullptr), fEvents(5) {
}
Scene::Scene(string pName, string pDescription, Player* pPlayer, Monster* pMonster, int pMaxNumberOfEvent): fName(pName), fDescription(pDescription), fPlayer(pPlayer), fMonster(pMonster), fEvents(pMaxNumberOfEvent){
    fDecisions.pushBack(Decision("View Character's Attributes",
        "Take a look at all the attributes of your character.",
        [this](Player& player) { player.ShowAttributes(); })); //Calling this fPlayer's ShowAttributes() method
    fDecisions.pushBack(Decision("View Inventory",
        "Take a look at all the items in your inventory.",
        [this](Player& player) { DisplayInventoryMenu(); })); //Calling this fPlayer's ViewItems() method
    fDecisions.pushBack(Decision("Exit Game",
        "Exit the game",
        [this](Player& player) { exit(0); })); //Exit Program
}
*/
string Scene::getName() const{
    return fName;
};
string Scene::getDescription() const{
    return fDescription;
};

void Scene::AddLoot(Item* pLoot){
    fLoot.pushBack(pLoot);
};
void Scene::AddEvent(Event* pEvent) {
    fEvents.Push(pEvent);
}

void Scene::PlayEvent() {
    while (!IsEventEmpty()) {
        Event* currentEvent = fEvents.Pop();
        currentEvent->playEvent();
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
};
bool Scene::IsEventEmpty(){
    return  fEvents.IsEmpty();
};
void Scene::ShowLoots(){
    int x = 1; 
    for (auto it = fLoot.getIteratorHead(); it != it.end(); ++it) {
        Item* currentItem = *it;
        cout << x << ". " << currentItem->getName() << endl;
        x++;
    }
};
