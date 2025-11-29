#include "InventorySystem.h"
#include <iostream>
#include <stdexcept>
#include<fstream>

// Initialize every static
GBX::ItemMetaDataDefinitions GBX::Item::definitions;
unsigned int GBX::Item::ItemID = 0;
unsigned int GBX::Inventory::InventoryID;
static GBX::Initialize InitializerInstance;

// Class ItemMetaDataDefinitions

/**
 * Uses arrays and writes to files.
 * @brief Takes an input array to find all definitions that have functionality through psuedo code.
 * @param Inputmetadata Dynamic array input which is compared to items.txt for definitions.
 * @param metadataSize_ Size of array used for defining its bounds.
 * @return void
 */
void GBX::ItemMetaDataDefinitions::findDefinition(std::string* Inputmetadata, unsigned int metadataSize_)
{
	// Set param to be Class's own array
	Inputmetadata_ = Inputmetadata;
	// Iterate through item metadata
	for (int i = 0; i < metadataSize_; i++)
	{
		// Open item metadata definitions file in each iteration
		std::fstream itemNames(itemsFile);
		std::string input;

		// Check starting category
		itemNames >> input;

		// Init 
		unsigned int maxArguments = 0;
		std::string definition;

		// Parse the file
		if (input == "Components:") {
			while (itemNames >> input)
			{
				// If current metadata is file contents
				if (input == Inputmetadata_[i])
				{
					// Keyword arguments which have set amounts of arguments
					if (input == "Attack") maxArguments = 1;
					if (input == "Eat") maxArguments = 3;
					// If keyword
					if (maxArguments > 0)
					{
						definition = input;
					}
				}
				// Parse arguments
				while (maxArguments > 0)
				{
					pushArgument(Inputmetadata_[i + maxArguments]);
					maxArguments--;
				}
				// Trigger event
				if (definition == "Attack") std::cout << "Damage Dealt: " << popArgument() << "\n";
				if (definition == "Eat") std::cout << "Ate for: " << popArgument() << ", With: " 
					<< popArgument() << ", At the rate of: " << popArgument() << "\n";
				// Reset current loop definition
				definition = "";
			}
		}
	}

}
/**
 * Meant only for arrays.
 * @brief Takes an argument and places it within a dynamic array.
 * @param Argument A line in the item's array under the keyword pushed onto the argument array.
 * @return void
 */
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

	// Update the array size
	this->argumentsSize_ = newSize;
}
/**
 * Meant only for arrays.
 * @brief Pops an argument while returning its value ignoring flavor text words.
 * @return unsigned int of the value of the argument
 */
unsigned int GBX::ItemMetaDataDefinitions::popArgument()
{
	// Declare size variables
	const unsigned int oldSize = this->argumentsSize_;
	const unsigned int newSize = oldSize - 1;

	unsigned int argumentValue = 0;

	// Value about to be popped
	const std::string& argToParse = this->arguments_[oldSize - 1];

	// Find the position of the ':' delimiter
	size_t delimiterPos = argToParse.find(':');

	// If delimiter exists
	if (delimiterPos != std::string::npos)
	{
		// Extract string after the delimiter
		std::string numStr = argToParse.substr(delimiterPos+1);

		try {
			// Convert the number string to an unsigned int
			argumentValue = std::stoul(numStr);
		}
		catch (const std::exception& e) {
			std::cerr << "Warning: Failed to parse integer value in argument: " << argToParse << std::endl;
			// argumentValue remains 0
		}
	}

	// Allocate new array with a smaller size
	std::string* tempData = nullptr;
	if (newSize > 0)
	{
		tempData = new std::string[newSize];

		// Iterate and place all elements within the temp obj EXCEPT the last
		for (unsigned int i = 0; i < newSize; i++)
		{
			tempData[i] = this->arguments_[i];
		}
	}

	// Deallocate arguments_
	if (arguments_ != nullptr)
	{
		delete[] arguments_;
	}

	// Set pointer value of arguments_ to temp 
	arguments_ = tempData;

	// Update the array size
	this->argumentsSize_ = newSize;

	return argumentValue;
};


// Class Item

/**
 * Constructor
 * Writes to files.
 * @brief Creates own save file, sets write mode, declares name, sets own ID, and stores file in obj.
 * @param name Item's name declaration.
 * @param overwriteFileLocation Sets write mode to overwrite or append.
 * @param buffer Determines to write 'Name: ' or not at start of file.
 * @return N/A
 */
GBX::Item::Item(std::string name, bool overwriteFileLocation, bool buffer) :
	name_(name), metadata_(nullptr), metadataSize_(0) 
{
	// Get own file
	std::ofstream myFile("game.data/items/gameItem_" + std::to_string(this->ItemID) + ".txt", 
		overwriteFileLocation == true ? std::ios::out : std::ios::app);
	// Set obj file to own item file
	itemFile = std::move(myFile);
	// If buffer then put the name into the file
	if (buffer)
		itemFile << "Name: " << name_ << std::endl;
	// Create own ID
	this->personalID = ItemID;
	// Increment global item ID
	this->ItemID++;
};
/**
 * Uses arrays and writes to files.
 * @brief Adds metadata to dynamic array and writes to file if append.
 * @param metadata Takes in string to add to dynamic array.
 * @param append Determines if metadata should append the file.
 * @return void
 */
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

	if (append == true)
		this->itemFile << metadata << std::endl;

	// Deallocate metadata_
	if (metadata_ != nullptr)
	{
		delete[] metadata_;
	}

	// Set pointer value of metadata_ to temp
	metadata_ = tempData;

	// Update array size
	this->metadataSize_ = newSize;
}
/**
 * Getter
 * @brief Gets obj's name.
 * @return string of the name of obj.
 */
std::string GBX::Item::name()
{
	return this->name_;
}
/**
 * @brief Triggers item event by calling global definition and passing metadata.
 * @return void
 */
void GBX::Item::triggerItemEvent()
{
	this->definitions.findDefinition(this->metadata_, this->metadataSize_);
}
/**
 * Debug
 * @brief Prints metadata of obj with formatting.
 * @return void
 */
void GBX::Item::print()
{
	std::cout << "---" << this->name_ << "---\n";
	if (metadataSize_ > 0) {
		std::cout << "MetaData: [ ";
		// Iterate through metadata
		for (int i = 0; i < this->metadataSize_; i++)
		{
			// If iteration less than max metadata print with ", "
			// Else end formatting with " ]\n"
			i < this->metadataSize_ - 1 ? std::cout << metadata_[i] 
				<< ", " : std::cout << metadata_[i] << " ]\n";
		}
	}
	// Make size of formatting on top and bottom bars identical
	for (char c : this->name_)
		std::cout << "-";
	std::cout << "------\n\n";
}
/**
 * Destructor
 * @brief Dealloc memory from metadata pointer and set to nullptr.
 * @return N/A
 */
GBX::Item::~Item()
{
	delete[] metadata_;
	metadata_ = nullptr;
}

// Class Inventory

/**
 * Constructor 
 * Writes to files.
 * @brief Gets own file, sets write mode, updates legend, creates all nested items.
 * @param overwriteFileLocation Sets write mode to overwrite or append.
 * @return void
 */
GBX::Inventory::Inventory(bool overwriteFileLocation) : size(0), metadata_(nullptr)
{
	// Get own inventory file
	std::ofstream myFile("game.data/inventories/inventory_" + std::to_string(InventoryID) + ".txt",
		overwriteFileLocation == true ? std::ios::out : std::ios::app);
	// Set obj file to own inventory file
	inventoryFile = std::move(myFile);

	// Gets inventory legend
	std::ofstream legend("game.data/inventories/inventory_legend.txt", std::ios::out);
	// Set global inventoryID to first line of legend
	legend << this->InventoryID;

	// Open own inventory file in read mode
	std::fstream gameInventoryFile("game.data/inventories/inventory_" + std::to_string(InventoryID) + ".txt");
	std::string itemID;

	// Parse through own file
	while (std::getline(gameInventoryFile, itemID))
	{
		// Open item file based on own contents
		std::fstream gameItemFile("game.data/items/gameItem_" + itemID + ".txt");
		std::string gameItemData;

		// Get name of item
		std::getline(gameItemFile, gameItemData);
		size_t delimiterPos = gameItemData.find(':');
		std::string name = gameItemData.substr(delimiterPos+1);

		// Set name of file with no overwrite and no buffer 
		GBX::Item* itemPtr = new GBX::Item(name, false, false);

		// Parse through game file
		while (std::getline(gameItemFile, gameItemData))
		{
			// Set new item's metadata
			itemPtr->addMetadata(gameItemData, false);
		}

		// Add item to own metadata without appending item file
		this->addItem(itemPtr, false);
	}

	// Overwrite own file with all item IDs
	std::ofstream overwriteFile("game.data/inventories/inventory_" + std::to_string(InventoryID) + ".txt");
	for (int i = 0; i < size; i++)
	{
		overwriteFile << this->metadata_[i]->personalID << std::endl;
	}

	// Update global InventoryID
	this->InventoryID++;
}
/**
 * @brief Takes an Item obj and adds it to Inventory metadata_.
 * @param item The a pointer reference of a Item obj.
 * @param append Choose to write itemID now or later.
 * @return void
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
	tempData[this->size]->triggerItemEvent(); // Testing purposes only
	if (append)
		this->inventoryFile << item->personalID << std::endl;

	// Deallocate metadata_
	if (metadata_ != nullptr)
	{
		delete[] metadata_;
	}

	// Set pointer value of metadata_ to temp
	metadata_ = tempData;

	// Update metadata size
	this->size = newSize;
}

// Not yet defined
void GBX::Inventory::removeItem()
{

}
void GBX::Inventory::getItem()
{

}
void GBX::Inventory::setItem()
{

}

/**
 * @brief Takes a slot and triggers item event.
 * @param slot The element of the metadata dynamic array.
 * @return void
 */
void GBX::Inventory::triggerItemEvent(unsigned int slot)
{
	this->metadata_[slot]->triggerItemEvent();
}
/**
 * Debug
 * @brief Iterates through metadata and prints formatted item metadata.
 * @return void
 */
void GBX::Inventory::print()
{
	for (int i = 0; i < this->size; i++)
	{
		metadata_[i]->print();
	}
}
/**
 * Destructor
 * @brief Iterates through metadata deleting objs, setting to nullptr, delete self, set to nullptr.
 * @return N/A
 */
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

// Class Initialize

/**
 * Destructor
 * @brief Uses inventory legend to create inventory objs.
 * @temporary Prints inventory.
 * @return N/A
 */
GBX::Initialize::Initialize()
{
	// Open inventory legend file in read only
	std::fstream legend("game.data/inventories/inventory_legend.txt");

	// Max inventory objs to create
	unsigned int inventoryID = 0;

	// If legend increment max inventoryIDs 
	// Else ignore rest
	if (legend >> inventoryID) inventoryID++;

	// Create inventory objs on stack in append mode
	for (int i = 0; i < inventoryID; i++)
	{
		GBX::Inventory inv(false);
		inv.print(); // Temporary
	}
}