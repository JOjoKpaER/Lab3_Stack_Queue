#pragma once

#define delay 250
#define EPS 0.0001f

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {

private:


public:
	std::string name;
	float price;
	unsigned int count;
	std::string origin;

	friend bool operator== (const Item &l, const Item &r);
	friend bool operator!= (const Item &l, const Item &r);

	Item() {
		name = "";
		price = NULL;
		count = NULL;
		origin = "";
	}

	Item(Item * copyFrom) {
		name = copyFrom->name;
		price = copyFrom->price;
		count = copyFrom->count;
		origin = copyFrom->origin;
	}

	Item(
		std::string _name,
		float _price,
		int _count,
		std::string _origin
	) {
		name = _name;
		price = _price;
		count = _count;
		origin = _origin;
	}

};

#endif // !ITEM_H

#ifndef CRATE
class Crate {
private:

public:
	
	unsigned int count;
	float price;

	Crate() {
		count = NULL;
		price = NULL;
	}

	Crate(unsigned int _count, float _price) {
		count = _count;
		price = _price;
	}

	Crate(Crate *copyFrom) {
		count = copyFrom->count;
		price = copyFrom->price;
	}
};

#endif // !CRATE

