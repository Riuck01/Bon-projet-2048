#include <iostream>
#include "Cell.h"


void Cell::display() const {
	std::cout << value << "\t";
}

int Cell::getValue() const {
	return value;
}

void Cell::setValue(int val) {
	value = val;
}

bool Cell:: isEmpty() const {
	return value == 0;
}