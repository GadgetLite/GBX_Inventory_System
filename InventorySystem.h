#ifndef INVENTORY_SYSTEM_CLASS_H
#define INVENTORY_SYSTEM_CLASS_H

#include<iostream>
#include<string>
#include<cstdint>

namespace GBX {
	class ItemMetaDataDefinitions
	{
	private:
		std::string* Inputmetadata_;
		std::string metadataDefinitions_[1];
	public:
		ItemMetaDataDefinitions(std::string* Inputmetadata, unsigned int metadataSize_) :
			Inputmetadata_(Inputmetadata) { };
	};
	class Item
	{
	private:
		std::string name_;
		std::string* lore_;
		unsigned int loreSize_;
		std::string* metadata_;
		unsigned int metadataSize_;
	public:
		Item(std::string name = "Undefined") : 
			name_(name), lore_(nullptr), loreSize_(0), metadata_(nullptr), metadataSize_(0) {};
		void addLore(std::string lore);
		void addMetadata(std::string metadata);
		std::string name();
		void print();
		~Item();
	};
	class Inventory
	{
	private:
		unsigned int slots_;
		unsigned int size;
		Item** metadata_;
	public:
		Inventory(unsigned int slots = 9) : slots_(slots), size(0), metadata_(nullptr) {};
		void addItem(Item* item);
		void removeItem();
		void getItem();
		void setItem();
		void print();
		~Inventory();
	};
};

#endif