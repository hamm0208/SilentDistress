#include "Scene.h"
#include "Item.h"
#include <thread>
#include <chrono>

//Default constructor
Scene::Scene(): fName(""), fDescription(""), fEvents(5){
}
//Overloaded constructor
Scene::Scene(string pName, string pDescription, int pMaxNumberOfEvent) : fName(pName), fDescription(pDescription), fEvents(pMaxNumberOfEvent) {
}
//Destructor
Scene::~Scene() {
    //Delete fEvents
    if (!fEvents.IsEmpty()) {  // Check if fEvents is not empty
        for (int x = 0; x < fEvents.GetSize(); x++) {  // Loop through each element of fEvents
            if (fEvents[x] != nullptr) {  // Check if the event at index x is not nullptr
                delete fEvents[x];  // Deallocate memory of the object at index x
                fEvents[x] = nullptr;  // Set the pointer to nullptr to avoid dangling pointers
            }
        }
    }
};

//Getter fName
string Scene::getName() const{
    return fName;
};
//Getter fDescription
string Scene::getDescription() const{
    return fDescription;
};
//Getter fLoot
List<Item*>& Scene::getLoot(){
    return fLoot;
};
//Getter fEvents
Queue<Event*> Scene::getEvent() {
    return fEvents;
};

//Adding items to fLoot
void Scene::AddLoot(Item* pLoot){
    fLoot.pushBack(pLoot);
};

//Queueing event to fEvents
void Scene::AddEvent(Event* pEvent) {
    fEvents.queue(pEvent);
}


//Play all the events in the queue
void Scene::PlayEvent() {
    while (!IsEventEmpty()) {                       //While event is not empty...
        Event* currentEvent = fEvents.dequeue();    //Dequeue from fEvents and assign it a pointer to Event
        currentEvent->playEvent();                  //Play the event
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
