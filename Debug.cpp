#include<iostream>
#include<string>
#include "InventorySystem.h"
#include<fstream>

void writeToFile(std::string str, std::string display, bool overwrite);
void copyFile(std::string copy, std::string paste, bool overwrite, std::string format = "");

int main()
{
    // GBX::Inventory inv1;
    // GBX::Item* steak = new GBX::Item("Steak");
    // 
    // steak->addMetadata("Eat");
    // steak->addMetadata("Eating speed: 10");
    // steak->addMetadata("Saturation: 15");
    // steak->addMetadata("Hunger Points: 20");
    // 
    // inv1.addItem(steak);
    // inv1.print();

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