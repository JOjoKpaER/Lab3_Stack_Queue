#pragma once

#include <Main.h>

class Stack
{
private:

	struct element
	{
		Item *item;
		element *next;

		element() {
			item = nullptr;
			next = nullptr;
		}

		element(element *copyFrom) {
			item = copyFrom->item;
			next = copyFrom->next;
		}
	};

	element *current;

public:

	Stack() {
		current = new element();
	}

	~Stack() {
		while (current->next != nullptr) {
			element *t = new element(current->next);
			delete current;
			current = t;
		}
		delete current;
	}

	void Push(Item *i) {
		element *t = new element();
		t->item = i;
		t->next = current;
		current = t;
	}

	Item* Pop() {
		if (!current->next)
		{
			//printf("Pop was called in empty stack\n");
			return nullptr;
		}
		element *t = new element(current->next);
		Item *ret = current->item;
		delete current;
		current = t;
		return ret;
	}

	Item* Peek() {
		if (!current->next)
		{
		//	printf("Peek was called in empty stack\n");
			return nullptr;
		}
		return current->item;
	}

	Stack* Reverse() {
		Stack *newStack = new Stack();
		while (this->Peek()) {
			newStack->Push(this->Pop());
		}
		return newStack;
	}
};

