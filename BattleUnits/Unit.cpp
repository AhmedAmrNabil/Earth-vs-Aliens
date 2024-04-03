#include "Unit.h"
#include <iostream>

std::ostream& operator << (std::ostream& out, const Unit* unit) {
	out << unit->getId();
	return out;
}