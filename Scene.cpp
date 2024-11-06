#include "Scene.h"
#include "Item.h"
#include <thread>
#include <chrono>

Scene::Scene(): fName(""), fDescription(""), fEvents(5){
}
Scene::Scene(string pName, string pDescription, int pMaxNumberOfEvent) : fName(pName), fDescription(pDescription), fEvents(pMaxNumberOfEvent) {
    
}
string Scene::getName() const{
    return fName;
};
string Scene::getDescription() const{
    return fDescription;
};
List<Item*>& Scene::getLoot(){
    return fLoot;
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

void Scene::ShowLootsDetails(){
    system("CLS");
    bool isEmpty = false;							//Is inventory empty flag
    cout << "------------------------------------------------------------------" << endl;
    for (auto it = fLoot.getIteratorHead(); it != it.end(); ++it) {
        Item* currentItem = *it;
        cout << "Details of " << currentItem->getName() << endl;
        currentItem->Inspect();
        cout << "Total Weight:\t\t\t" << currentItem->getWeight() << "\n" << endl;
        cout << "==================================================================" << endl;

        isEmpty = true;
    }
    if (!isEmpty) {
        cout << "\t\t\tNo Loot!!" << endl;
    }
    cout << "------------------------------------------------------------------" << endl;
};
