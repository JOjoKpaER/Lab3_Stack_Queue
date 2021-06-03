#include<string>

#include<Main.h>
#include<Stack.h>

#define COUNTMIN 1
#define COUNTMAX 10
#define PRICEMIN 0.01f
#define PRICEMAX 10000.0f
#define STACKLIMIT 1000

static std::string name_array[] = { //15
	"Ball",
	"Candy",
	"Pen",
	"Flash card",
	"Book",
	"Apple",
	"Flower",
	"Laptop",
	"Bun",
	"Cell phone",
	"Magazine",
	"Cup",
	"Hare",
	"Watch",
	"Car"
};

static std::string origin_array[] = { //7
	"RUS",
	"CHN",
	"DEU",
	"USA",
	"POL",
	"KAZ",
	"GBR"
};


Stack* generateStack() {
	Stack* stk = new Stack();
	int stackLimit = std::rand() % STACKLIMIT;
	for (int i = 0; i < stackLimit; i++) {
		std::string name = name_array[std::rand()%15];
		std::string origin = origin_array[std::rand()%7];
		int count = rand() % COUNTMAX - COUNTMIN + 2;
		float price = ((float)(rand()) / (float)RAND_MAX) * PRICEMAX + PRICEMIN;
		Item *item = new Item(name, price, count, origin);
		stk->Push(item);
	}
	return stk;
}