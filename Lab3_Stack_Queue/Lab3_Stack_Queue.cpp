#include <iostream>;

#include "Main.h"
//#include "Stack.h"
//#include "Queue.h"
#include "CartMenu.h"
#include "StorageMenu.h"
#include "FileLoader.h"
#include "RNGLists.h"

void startCart() {
	Stack *Cart = new Stack();
	FileLoader FL = FileLoader(Cart, nullptr);
	FL.setCartFileInput("Cart.txt");
	if (FL.readCartFile()) {
		printf("((^u^(\n");
	}
	CartMenuHandler(Cart);
	delete Cart;
	Cart = nullptr;
}

void startStorage() {
	Queue *Storage = new Queue();
	StorageMenuHandler(Storage);
	delete Storage;
	Storage = nullptr;
};

int main()
{
	startCart();
	startStorage();
	return 0;
}

