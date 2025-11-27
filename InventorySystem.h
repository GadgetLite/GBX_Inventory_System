#ifndef INVENTORY_SYSTEM_CLASS_H
#define INVENTORY_SYSTEM_CLASS_H

#include<iostream>
#include<string>
#include<cstdint>

namespace GBX {
	class Item
	{

	};
	class Inventory
	{
	private:
		unsigned int slots_;
		Item* metadata_;
	public:
		Inventory(unsigned int slots) : slots_(slots) {};
		void addItem();
		void removeItem();
		void getItem();
		//potato

	};
};

#endif