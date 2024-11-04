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
        function<void(Player&)> fEffect; // Effect function taking a Player reference
    public:
        Decision(const string& name, const string& description, function<void(Player&)> effect);
        string getName() const;
        string getDescription() const;
        void applyEffect(Player& player) const;
};