#pragma once
#include <iostream>
#include <functional>
#include "Player.h"
using namespace std;

class Decision
{
private:
    string fName;
    string fDescription;
    function<void(Entity&)> fEffect; // Event function taking a Player reference
public:
    Decision();
    Decision(const string& name, const string& description, function<void(Entity&)> pEffect = nullptr);
    string getName() const;
    string getDescription() const;
    void applyEffect(Player& player) const;
};