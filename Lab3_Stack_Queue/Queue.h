#pragma once
#include <stdio.h>
#include <Main.h>
class Queue
{

private:
	struct element
	{
		Crate *crate;
		element *prev;

		element() {
			crate = nullptr;
			prev = nullptr;
		}

		element(element *copyFrom) {
			crate = copyFrom->crate;
			prev = copyFrom->prev;
		}
	};

	element *back, *front;
public:

	Queue() {
		element *t = new element();
		back = t;
		front = t;
	}

	~Queue() {
		while (front->prev != nullptr) {
			element *tfront = front->prev;
			delete front;
			front = tfront;
		}
		delete front;
		front = nullptr;
	}

	void Enqueue(Crate *i) {
		element *t = new element();
		t->crate = i;
		back->prev = t;
		back = t;
	}

	Crate *Dequeue() {
		if (!front->prev) {
			return nullptr;
		}
		element *t = new element();
		t = front->prev;
		Crate* ret = t->crate;
		delete front;
		front = t;
		return ret;
	}

	Crate* Back(){
		return back->crate;
	}

	Crate* Front() {
		if (!front->prev) {
			return nullptr;
		}
		return front->prev->crate;
	}

};

