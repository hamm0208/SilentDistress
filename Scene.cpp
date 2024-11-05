#include "Scene.h"

Scene::Scene(): fName(""), fDescription(""), fPlayer(nullptr), fMonster(nullptr), fEvents(5){
}

Scene::Scene(string pName, string pDescription, Player* pPlayer, Monster* pMonster, int pMaxNumberOfEvent): fName(pName), fDescription(pDescription), fPlayer(pPlayer), fMonster(pMonster), fEvents(pMaxNumberOfEvent){
}

string Scene::getName() const{
    return fName;
};
string Scene::getDescription() const{
    return fDescription;
};
List<Decision> Scene::getDecisions() const{
    return fDecisions;
};
Player* Scene::getPlayer(){
    return fPlayer;
};
Monster* Scene::getMonster(){
    return fMonster;
};
void Scene::AddDecisions(Decision& pDecision){
    fDecisions.pushBack(pDecision)
};
void Scene::AddLoot(Item* pLoot){
    fLoot.pushBack(pLoot);
};
void Scene::AttachScene(int pIndex, NTree<Scene, 3>* pSceneChild){
    fSceneTree.attachNTree(pIndex, pSceneChild);
};
void Scene::DetachScene(int pIndex){
    fSceneTree.detachNTree(pIndex);
};