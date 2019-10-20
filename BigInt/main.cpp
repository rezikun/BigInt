#include "big_int.h"
#include <iostream>

int main() {
	while (true) {
		std::string first_s, second_s;
		std::cin >> first_s >> second_s;
		big_int::BigInt first(first_s);
		big_int::BigInt second(second_s);
		std::cout << first / second << "\n";
	}
}