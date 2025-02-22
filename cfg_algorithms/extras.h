#pragma once
#include <iostream>

void clear_cin() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max());
}