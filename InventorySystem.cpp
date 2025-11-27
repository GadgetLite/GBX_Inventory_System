#include "InventorySystem.h"
#include <iostream>
#include <stdexcept>

/*
	std::string* Inputmetadata_;
	std::string metadataDefinitions_[1];
*/


/*
	std::string name_;
	std::string* lore_;
	unsigned int loreSize_;
	std::string* metadata_;
	unsigned int metadataSize_;
*/


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
void GBX::Item::addMetadata(std::string metadata)
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

/**
 * @brief Takes a Item obj and adds it to Inventory metadata_.
 * @param item The a pointer reference of a Item obj.
 * @return Void.
 */

void GBX::Inventory::addItem(Item* item)
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

