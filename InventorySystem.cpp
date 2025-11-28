#include "InventorySystem.h"
#include <iostream>
#include <stdexcept>
#include<fstream>

GBX::ItemMetaDataDefinitions GBX::Item::definitions;
unsigned int GBX::Item::ItemID = 0;
unsigned int GBX::Inventory::InventoryID;
static GBX::Initialize InitializerInstance;
/*
	std::string itemsFile = "Declarations/items.txt";
	std::string itemsClassFile = "Declarations/itemClasses.txt";
*/
void GBX::ItemMetaDataDefinitions::findDefinition(std::string* Inputmetadata, unsigned int metadataSize_)
{
	Inputmetadata_ = Inputmetadata;
	// Iterate through item metadata
	for (int i = 0; i < metadataSize_; i++)
	{
		// Open item metadata definitions file in each iteration
		std::fstream itemNames(itemsFile);
		std::string input;
		itemNames >> input;

		unsigned int maxArguments = 0;
		std::string definition;
		bool trigger = false;

		// Parse the file
		if (input == "Components:") {
			while (itemNames >> input)
			{
				// If current metadata is file contents
				if (input == Inputmetadata_[i])
				{
					if (input == "Attack") maxArguments = 1;
					if (maxArguments > 0)
					{
						trigger = true;
						definition = input;
					}
				}
			}
			while (maxArguments > 0)
			{
				pushArgument(Inputmetadata_[i + 1]);
				maxArguments--;
			}
			if (definition == "Attack") std::cout << "Damage Dealt: " << popArgument() << "\n";
		}
	}

}
void GBX::ItemMetaDataDefinitions::pushArgument(std::string argument)
{
	// Create temp obj with an increased array size by 1.
	const unsigned int newSize = this->argumentsSize_ + 1;
	std::string* tempData = new std::string[newSize];

	// Iterate through all elements of arguments_ and place them within temp obj.
	for (unsigned int i = 0; i < this->argumentsSize_; i++)
	{
		tempData[i] = arguments_[i];
	}

	// Set last element of temp to arguments_
	tempData[this->argumentsSize_] = argument;

	// Deallocate arguments_
	if (arguments_ != nullptr)
	{
		delete[] arguments_;
	}

	// Set pointer value of arguments_ to temp
	arguments_ = tempData;

	this->argumentsSize_ = newSize;
}
unsigned int GBX::ItemMetaDataDefinitions::popArgument()
{
	// --- 1. PRE-CONDITIONS / ERROR CHECK ---
	if (this->argumentsSize_ == 0 || this->arguments_ == nullptr)
	{
		// Safety check: Cannot pop from an empty array
		return 0;
	}

	const unsigned int oldSize = this->argumentsSize_;
	const unsigned int newSize = oldSize - 1;
	unsigned int returnValue = 0;

	// --- 2. VALUE EXTRACTION LOGIC (Simplified from your original loop) ---
	// You want to look at the argument being removed: arguments_[oldSize - 1]
	const std::string& argToParse = this->arguments_[oldSize - 1];

	// Find the position of the ':' delimiter
	size_t delimiterPos = argToParse.find(':');

	if (delimiterPos != std::string::npos)
	{
		// Extract the substring containing the number (starts after the delimiter)
		std::string numStr = argToParse.substr(delimiterPos+1);

		try {
			// Convert the number string to an unsigned int
			// std::stoul is the safe method for string-to-unsigned-integer conversion
			returnValue = std::stoul(numStr);
		}
		catch (const std::exception& e) {
			std::cerr << "Warning: Failed to parse integer value in argument: " << argToParse << std::endl;
			// returnValue remains 0
		}
	}

	// --- 3. DYNAMIC ARRAY SHRINK (The "Pop" Memory Management) ---

	// Allocate new array with the reduced size (newSize).
	std::string* tempData = nullptr;
	if (newSize > 0)
	{
		tempData = new std::string[newSize];

		// Copy all elements EXCEPT the last one into the new temporary array.
		// The loop must go up to newSize (which is oldSize - 1).
		for (unsigned int i = 0; i < newSize; i++)
		{
			tempData[i] = this->arguments_[i];
		}
	}

	// --- 4. CLEANUP AND SWAP ---

	// Deallocate arguments_ (the old memory block)
	if (arguments_ != nullptr)
	{
		delete[] arguments_;
	}

	// Set pointer value of arguments_ to temp (the new, smaller array)
	arguments_ = tempData;

	// Update the size member
	this->argumentsSize_ = newSize;

	return returnValue;
};

/*
	std::string name_;
	std::string* lore_;
	unsigned int loreSize_;
	std::string* metadata_;
	unsigned int metadataSize_;
*/


GBX::Item::Item(std::string name, bool overwriteFileLocation, bool buffer) :
	name_(name), lore_(nullptr), loreSize_(0), metadata_(nullptr), metadataSize_(0) 
{
	std::ofstream myFile("game.data/items/gameItem_" + std::to_string(ItemID) + ".txt", 
		overwriteFileLocation == true ? std::ios::out : std::ios::app);
	itemFile = std::move(myFile);
	if (buffer)
		itemFile << "Name: " << name_ << std::endl;
	this->personalID = ItemID;
	this->ItemID++;
};
/**
 * @brief Takes a string and adds it to lore_.
 * @param lore The lore declared for the item.
 * @return Void.
 */
void GBX::Item::addLore(std::string lore)
{
	// Create temp obj with an increased array size by 1.
	const unsigned int newSize = this->loreSize_ + 1;
	std::string* tempData = new std::string [newSize];

	// Iterate through all elements of lore_ and place them within temp obj.
	for (unsigned int i = 0; i < this->loreSize_; i++)
	{
		tempData[i] = lore_[i];
	}

	// Set last element of temp to lore
	tempData[this->loreSize_] = lore;

	// Deallocate lore_
	if (lore_ != nullptr)
	{
		delete[] lore_;
	}

	// Set pointer value of lore_ to temp
	lore_ = tempData;

	this->loreSize_ = newSize;
}
void GBX::Item::addMetadata(std::string metadata, bool append)
{
	// Create temp obj with an increased array size by 1.
	const unsigned int newSize = this->metadataSize_ + 1;
	std::string* tempData = new std::string[newSize];

	// Iterate through all elements of metadata_ and place them within temp obj.
	for (unsigned int i = 0; i < this->metadataSize_; i++)
	{
		tempData[i] = metadata_[i];
	}

	// Set last element of temp to metadata
	tempData[this->metadataSize_] = metadata;

	if(append == true)
		this->itemFile << metadata << std::endl;

	// Deallocate metadata_
	if (metadata_ != nullptr)
	{
		delete[] metadata_;
	}

	// Set pointer value of metadata_ to temp
	metadata_ = tempData;

	this->metadataSize_ = newSize;
}
std::string GBX::Item::name()
{
	return this->name_;
}
void GBX::Item::triggerItemEvent()
{
	this->definitions.findDefinition(this->metadata_, this->metadataSize_);
}
void GBX::Item::print()
{
	std::cout << "---" << this->name_ << "---\n";
	if (loreSize_ > 0) {
		std::cout << "Lore: [ ";
		for (int i = 0; i < this->loreSize_; i++)
		{
			i < this->loreSize_ - 1 ? std::cout << lore_[i] << ", " : std::cout << lore_[i] << " ]\n";
		}
	}
	if (metadataSize_ > 0) {
		std::cout << "MetaData: [ ";
		for (int i = 0; i < this->metadataSize_; i++)
		{
			i < this->metadataSize_ - 1 ? std::cout << metadata_[i] << ", " : std::cout << metadata_[i] << " ]\n";
		}
	}
	for (char c : this->name_)
		std::cout << "-";
	std::cout << "------\n\n";
}

GBX::Item::~Item()
{
	delete[] lore_;
	lore_ = nullptr;
	delete[] metadata_;
	metadata_ = nullptr;
}

/* 
	unsigned int slots_;
	Item** metadata_ = nullptr;
	unsigned int size = 0;
*/ 

GBX::Inventory::Inventory(bool overwriteFileLocation) : size(0), metadata_(nullptr)
{
	std::ofstream myFile("game.data/inventories/inventory_" + std::to_string(InventoryID) + ".txt",
		overwriteFileLocation == true ? std::ios::out : std::ios::app);
	inventoryFile = std::move(myFile);
	std::ofstream legend("game.data/inventories/inventory_legend.txt", std::ios::out);
	legend << this->InventoryID;

	std::fstream gameInventoryFile("game.data/inventories/inventory_" + std::to_string(InventoryID) + ".txt");
	std::string itemID;

	while (std::getline(gameInventoryFile, itemID))
	{
		std::fstream gameItemFile("game.data/items/gameItem_" + itemID + ".txt");
		std::string gameItemData;

		std::getline(gameItemFile, gameItemData);
		size_t delimiterPos = gameItemData.find(':');
		std::string name = gameItemData.substr(delimiterPos+1);

		GBX::Item* itemPtr = new GBX::Item(name, false, false);

		while (std::getline(gameItemFile, gameItemData))
		{
			itemPtr->addMetadata(gameItemData, false);
		}
		this->addItem(itemPtr, false);
	}
	std::ofstream overWriteFile("game.data/inventories/inventory_" + std::to_string(InventoryID) + ".txt");
	for (int i = 0; i < size; i++)
	{
		overWriteFile << this->metadata_[i]->personalID << std::endl;
	}
	this->InventoryID++;
}
/**
 * @brief Takes a Item obj and adds it to Inventory metadata_.
 * @param item The a pointer reference of a Item obj.
 * @return Void.
 */

void GBX::Inventory::addItem(Item* item, bool append)
{
	// Create temp obj with an increased array size by 1.
	const unsigned int newSize = this->size + 1;
	GBX::Item** tempData = new GBX::Item*[newSize];

	// Iterate through all elements of metadata_ and place them within temp obj.
	for (unsigned int i = 0; i < this->size; i++)
	{
		tempData[i] = metadata_[i];
	}

	// Set last element of temp to newItem
	tempData[this->size] = item;
	if (append)
		this->inventoryFile << item->personalID << std::endl;

	// Deallocate metadata_
	if (metadata_ != nullptr)
	{
		delete[] metadata_;
	}

	// Set pointer value of metadata_ to temp
	metadata_ = tempData;

	this->size = newSize;
}
void GBX::Inventory::removeItem()
{

}
void GBX::Inventory::getItem()
{

}
void GBX::Inventory::setItem()
{

}
void GBX::Inventory::triggerItemEvent(unsigned int itemSlot)
{
	this->metadata_[itemSlot]->triggerItemEvent();
}
void GBX::Inventory::print()
{
	for (int i = 0; i < this->size; i++)
	{
		metadata_[i]->print();
	}
}
GBX::Inventory::~Inventory()
{
	for (int i = 0; i < this->size; i++)
	{
		delete metadata_[i];
		metadata_[i] = nullptr;
	}
	delete[] metadata_;
	metadata_ = nullptr;
}

GBX::Initialize::Initialize()
{
	std::fstream legend("game.data/inventories/inventory_legend.txt");

	std::string inventoryID;

	while (std::getline(legend, inventoryID))
	{
		GBX::Inventory inv(false);
		inv.print();
	}
}