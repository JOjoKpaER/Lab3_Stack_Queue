#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <Windows.h>

#include <Main.h>
#include <Queue.h>

static Queue *Storage;

static enum Function {
	ADD,
	SELL,
	REPORT,
	END,
	NONE
};

void Add(Crate* crate);
void Sell(Crate* crate);
void Report();

float proceeds = 0;

void StorageMenuHandler(Queue *_Storage) {
	Storage = _Storage;

	std::string Actions[] = { //4
		"Add new",
		"Sell current",
		"Report",
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
			unsigned int count;
			float price;
			bool b = true;
			do {
				std::cout << "\nQuantity: ";
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
				}while (b);
			b = true;
			do {
				std::cout << "Price: ";
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
			Add(new Crate(count, price));
			break;
		}
		case(SELL): {
			unsigned int count;
			float price;
			bool b = true;
			do {
				std::cout << "\nQuantity: ";
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
				std::cout << "Price: ";
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
			Sell(new Crate(count, price));
			break;
		}
		case(REPORT): {
			Report();
			break;
		}
		case(END): {
			cls = false;
			printf("Storage program is closing now\n");
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

std::string GetCrateDescription(Crate *crate) {
	std::string ret = "";
	if (crate)
		ret += "x" + std::to_string(crate->count) + " " + " by price: " + std::to_string(crate->price);
	return ret;
}

void Add(Crate *crate) {
	if (!crate) return;
	Storage->Enqueue(crate);
	std::cout << GetCrateDescription(crate) << " was added to storage\n";
	Sleep(delay);
}


void Sell(Crate *crate) {
	if (!crate) return;
	Crate *front = Storage->Front();
	if (crate->count > front->count)
	{
		std::cout << "Cannot sell " << GetCrateDescription(crate) << " due to lack quantity in current group\n";
		front = nullptr;
		Sleep(delay);
		return;
	}
	if (crate->price < front->price) {
		std::cout << "Cannot sell " << GetCrateDescription(crate) << " due to inadequate selling price\n";
		front = nullptr;
		Sleep(delay);
		return;
	}
	if (crate->count < front->count) {
		front->count -= crate->count;
		proceeds += crate->count * (-front->price + crate->price);
		std::cout << GetCrateDescription(crate) << " was sold\n";
		front = nullptr;
		Sleep(delay);
		return;
	}
	if (crate->count == front->count) {
		proceeds += crate->count * (-front->price + crate->price);
		Storage->Dequeue();
		std::cout << GetCrateDescription(crate) << " was sold\nWhole stack of current group was sold\n";
		front = nullptr;
		Sleep(delay);
		return;
	}
}

void Report() {
	if (!Storage->Front())
	{
		printf("The storage is empty\n");
		printf("Proceeds were: %f\n", proceeds);
		Sleep(delay);
		return;
	}
	Queue *t = new Queue();
	unsigned int count = 0;
	float cost = 0;
	printf("Stockpile:\n");
	do {
		Crate *crate = Storage->Dequeue();
		t->Enqueue(crate);
		count += crate->count;
		cost += crate->count * crate->price;
		std::cout << GetCrateDescription(crate) << "\n";
		Sleep(delay / 25);
	} while (Storage->Front());
	do {
		Storage->Enqueue(t->Dequeue());
	} while (t->Front());
	delete t;
	t = nullptr;
	printf("Whole storage consists of: %i goods\nTotal cost: %f\nProceeds: %f\n", count, cost, proceeds);
	Sleep(delay);
}