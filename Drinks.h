#pragma once
#include "Item.h"
class Drinks :public Item{
    private:
        int fHydrationValue;
    public:
        Drinks();
        Drinks(string pName, string pDescription, int pWeight, bool pIsConsumable, int pHydrationValue);
        void Use(Player& pPlayer) override;
        void Inspect() override;
        int getHydrationValue();
        void setHydrationValue(int pHydrationValue);
};