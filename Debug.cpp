#include<iostream>
#include<string>
#include "InventorySystem.h"
#include<fstream>

void writeToFile(std::string str, std::string display, bool overwrite);
void copyFile(std::string copy, std::string paste, bool overwrite, std::string format = "");

int main()
{
    // GBX::Inventory inv;
    // GBX::Item* apple = new GBX::Item("Apple");
    // GBX::Item* golden_sword = new GBX::Item("Golden Sword");
    // 
    // apple->addMetadata("Eat");
    // apple->addMetadata("Eating speed: 4");
    // apple->addMetadata("Saturation: 2");
    // apple->addMetadata("Hunger Points: 2");
    // golden_sword->addMetadata("Attack");
    // golden_sword->addMetadata("Damage: 3");
    // 
    // inv.addItem(apple);
    // inv.addItem(golden_sword);
    // 
    // inv.print();
    // inv.triggerItemEvent(0);
    // std::string str = "Declarations/items.txt";
    // std::string str1 = "Declarations/itemClasses.txt";

    //writeToFile(str1, "Classes", 0);
    //copyFile(str, str1, 1);

    return 0;
}











void writeToFile(std::string str, std::string display, bool overwrite)
{
    std::ofstream myFile(str, overwrite == true ? std::ios::out : std::ios::app);
    
    if (!myFile.is_open()) {
        std::cerr << "Error: Could not open/create the file at: " << str << std::endl;
    }
    else {
        std::string itemDef;
        std::cin.ignore(1, 1);
        do 
        {
            std::cout << "Write " << display << " definiton: ";
            getline(std::cin, itemDef);
            if (itemDef != "-1")
                myFile << itemDef << std::endl;
        } while (itemDef != "-1");

        if (myFile.fail()) {
            std::cerr << "Error: Failed to write data to the file." << std::endl;
        }
    }
    myFile.close();
}


void copyFile(std::string copy, std::string paste, bool overwrite, std::string format)
{

    std::fstream inputFile(copy);
    std::ofstream outputFile(paste, overwrite == true ? std::ios::out : std::ios::app);

    std::string input;
    while (inputFile >> input)
    {
        outputFile << format << input << std::endl;
    }

}