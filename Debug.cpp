#include<iostream>
#include<string>
#include "InventorySystem.h"

int main()
{
    GBX::Inventory inv;
    GBX::Item* i = new GBX::Item("Poatato");

    i->addLore("NukeBombOnStick");
    i->addLore("Wow");
    i->addMetadata("Nuke");
    i->addMetadata("Bomb");
    i->addMetadata("On");
    i->addMetadata("Stick");

    inv.addItem(i);
    inv.addItem(new GBX::Item("Poatato"));
    inv.addItem(new GBX::Item("Poatato"));
    inv.addItem(new GBX::Item("Poatato"));
    inv.addItem(new GBX::Item("Poatato"));

    inv.print();

    return 0;
}