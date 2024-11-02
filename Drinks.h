#pragma once
#include "Item.h"
class Drinks :public Item{
    private:
        int fHydrationValue;
    public:
        Drinks();
        Drinks(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHydrationValue);
        bool Use(Player& pPlayer) override;
        void Inspect();
        Item* clone() const;
        int getHydrationValue();
        void setHydrationValue(int pHydrationValue);
};