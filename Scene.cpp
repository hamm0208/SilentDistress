#include "Scene.h"
#include "Item.h"
#include <thread>
#include <chrono>

Scene::Scene(): fName(""), fDescription(""), fEvents(5){
}
Scene::Scene(string pName, string pDescription, int pMaxNumberOfEvent) : fName(pName), fDescription(pDescription), fEvents(pMaxNumberOfEvent) {
}
Scene::~Scene() {
    if (!fEvents.IsEmpty()) {  // Check if fEvents is not empty
        for (int x = 0; x < fEvents.GetSize(); x++) {  // Loop through each element of fEvents
            if (fEvents[x] != nullptr) {  // Check if the event at index x is not nullptr
                delete fEvents[x];  // Deallocate memory of the object at index x
                fEvents[x] = nullptr;  // Set the pointer to nullptr to avoid dangling pointers
            }
        }
    }
};

string Scene::getName() const{
    return fName;
};
string Scene::getDescription() const{
    return fDescription;
};
List<Item*>& Scene::getLoot(){
    return fLoot;
};
Queue<Event*> Scene::getEvent() {
    return fEvents;
};


void Scene::AddLoot(Item* pLoot){
    fLoot.pushBack(pLoot);
};
void Scene::AddEvent(Event* pEvent) {
    fEvents.queue(pEvent);
}

void Scene::PlayEvent() {
    while (!IsEventEmpty()) {
        Event* currentEvent = fEvents.dequeue();
        currentEvent->playEvent();
        if (currentEvent != nullptr) {
            delete currentEvent;
            currentEvent = nullptr;
        }
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
