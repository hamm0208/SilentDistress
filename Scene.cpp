#include "Scene.h"

Scene::Scene(): fName(""), fDescription(""), fPlayer(nullptr), fMonster(nullptr), fEvents(5){
}

Scene::Scene(string pName, string pDescription, Player* pPlayer, Monster* pMonster, int pMaxNumberOfEvent): fName(pName), fDescription(pDescription), fPlayer(pPlayer), fMonster(pMonster), fEvents(pMaxNumberOfEvent){
}