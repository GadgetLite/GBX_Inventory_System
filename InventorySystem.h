#ifndef INVENTORY_SYSTEM_CLASS_H
#define INVENTORY_SYSTEM_CLASS_H

#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>

namespace GBX {
	class ItemMetaDataDefinitions
	{
	private:
		std::string itemsFile = "Declarations/items.txt";
		std::string itemsClassFile = "Declarations/itemClasses.txt";
		std::string* arguments_ = nullptr;
		unsigned int argumentsSize_ = 0;
		std::string* Inputmetadata_ = nullptr;
	public:
		std::string gameItems = "game.data/items/gameItem_";
		void findDefinition(std::string* Inputmetadata, unsigned int metadataSize_);
		void pushArgument(std::string argument);
		unsigned int popArgument();
	};
	class Item
	{
	private:
		std::string name_;
		std::string* metadata_;
		unsigned int metadataSize_;
		static ItemMetaDataDefinitions definitions;
		std::ofstream itemFile; // File of item
		static unsigned int ItemID;
	public:
		unsigned int personalID;
		Item(std::string name = "Undefined", bool overwriteFileLocation = true, bool buffer = true);
		void addMetadata(std::string metadata, bool append = true);
		std::string name();
		void triggerItemEvent();
		void print();
		~Item();
	};
	class Inventory
	{
	private:
		unsigned int size;
		Item** metadata_;
		std::ofstream inventoryFile; // File of inventory
		static unsigned int InventoryID;
	public:
		Inventory(bool overwriteFileLocation = true);
		void addItem(Item* item, bool append = true);
		void removeItem();
		void getItem();
		void setItem();
		void triggerItemEvent(unsigned int slot);
		void print();
		~Inventory();
	};
	struct Initialize
	{
		Initialize();
	};
}; 


#endif