#include <Main.h>
#include <iostream>

bool operator== (const Item &l, const Item &r) {
	return ((l.count == r.count) && 
		(l.name == r.name) && 
		(l.origin[0] == r.origin[0]) && 
		(l.origin[1] == r.origin[1]) &&
		(l.origin[2] == r.origin[2]) &&
		(abs(r.price - l.price) < EPS));
}

bool operator!= (const Item &l, const Item &r) { 
	return !(l == r); 
}