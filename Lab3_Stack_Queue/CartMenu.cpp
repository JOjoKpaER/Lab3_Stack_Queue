#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <Windows.h>

#include <Main.h>
#include <CartMenu.h>
#include <Stack.h>

static Stack* Cart;

static enum Function {
	ADD,
	REMOVE,
	CLEAR,
	END,
	NONE
};

void Add(Item* item);
void Remove(Item* item);
void Clear();

void CartMenuHandler(Stack* _Cart) {
	Cart = _Cart;

	std::string Actions[] = { //4
		"Add new item",
		"Remove item",
		"Clear cart",
		"Close"
	};
	std::string SelectionMessage = "Select next action:\n";
	for (int i = 0; i < 4; i++) {
		SelectionMessage += "		" + Actions[i];
	}
	SelectionMessage += "\n";
	std::string SelectedAction;
	////////////////////////////////////////////////////////////////////////////////////////
	bool cls = true;
	while (cls) {
		std::cout << SelectionMessage;
		std::getline(std::cin, SelectedAction);
		Function func = NONE;
		for (int i = 0; i < 4; i++) {
			if (SelectedAction == Actions[i]) {
				func = Function(i);
				break;
			}
		}
		switch (func) {
		case(ADD): {
			std::string name, origin;
			float price;
			int count;
			std::cout << "\nLabel of item: ";
			std::cin >> name;
			std::cout << "Origin of item: ";
			std::cin >> origin;
			bool b = true;
			do {
				std::cout << "Quantity of item: ";
				std::cin >> count;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			b = true;
			do {
				std::cout << "Price of item: ";
				std::cin >> price;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
				if (price <= 0.0f)
				{
					std::cin.clear();
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
			} while (b);
			Add(new Item(name, price, count, origin));
			break;
		}
		case(REMOVE): {
			std::string name, origin;
			float price;
			int count;
			std::cout << "\nLabel of item: ";
			std::cin >> name;
			std::cout << "Origin of item: ";
			std::cin >> origin;
			bool b = true;
			do {
				std::cout << "Quantity of item: ";
				std::cin >> count;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			b = true;
			do {
				std::cout << "Price of item: ";
				std::cin >> price;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			Remove(new Item(name, price, count, origin));
			break;
		}
		case(CLEAR): {
			Clear();
			break;
		}
		case(END): {
			cls = false;
			printf("Cart program is closing now\n");
			Sleep(delay);
			break;
		}
		default: {
			printf("Cannot procceed inputed function\n");
			Sleep(delay);
		}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////
}

std::string GetItemDescription(Item *item) {
	std::string ret = "";
	if (item)
		ret += " Label: " + item->name + " Origin: " + item->origin + " Count: x" + std::to_string(item->count) + " Price: " + std::to_string(item->price);
	return ret;
}

void Add(Item* item) {
	Cart->Push(item);
	std::cout << "Item" << GetItemDescription(item) << " was added to cart\n";
	Sleep(delay);
}

void Remove(Item* item) {
	bool b = false;
	Stack *t = new Stack();
	while (Cart->Peek() != nullptr) {
		Item* i;
		if (*(i = Cart->Pop()) != *item) {
			t->Push(i);
		}
		else {
			b = true;
		}
	}
	while (t->Peek() != nullptr) {
		Cart->Push(t->Pop());
	}
	delete t;
	t = nullptr;
	if (b) {
		std::cout << "Item " << GetItemDescription(item) << " was removed from cart\n";
	}
	if (!b) {
		std::cout << "Cannot find item " << GetItemDescription(item) << " in cart\n";
	}
	Sleep(delay);
}

void Clear() {
	do {
		if (Cart->Peek())
			std::cout << "Item " << GetItemDescription(Cart->Peek()) << " was removed from cart\n";
		Sleep(delay / 25);
	} while (Cart->Pop() != nullptr);
	printf("Cart was cleared\n");
	Sleep(delay);
}

