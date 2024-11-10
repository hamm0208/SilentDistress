#pragma once
#include <iostream>
#include <functional>
#include "Player.h"
using namespace std;

class Decision
{
private:
    string fName;                    //Name of the decision
    string fDescription;             //Description of the decision
    function<void(Entity&)> fEffect; // Event function taking a Player reference
public:
    Decision();                      //Default Constructor
    Decision(const string& name, const string& description, function<void(Entity&)> pEffect = nullptr); //Overload Constructor
    string getName() const;         //Getter for fName
    string getDescription() const;  //Getter for fDecscription
    void applyEffect(Player& player) const; //Call fEffect function
};