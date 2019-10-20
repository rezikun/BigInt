#pragma once

#include <string>
#include <ostream>

namespace big_int {

	class BigInt {
	public:

		explicit BigInt(const std::string& number);
		BigInt(int number) : number_(std::to_string(number)) {}
		BigInt operator+(const BigInt& other) const;
		BigInt operator-(const BigInt& other) const;
		BigInt operator-() const;
		BigInt operator*(const BigInt& other) const;
		BigInt operator/(const BigInt& other) const;
		BigInt operator%(const BigInt& other) const;
		BigInt& operator=(const BigInt& other) { number_ = other.number_; return *this; }
		operator std::string() { return number_;  }

		BigInt pow(const BigInt& other) const;
		BigInt wsqrt() const;
		bool operator>(const BigInt& other) const;
		bool operator<(const BigInt& other) const;
		bool operator<=(const BigInt& other) const { return *this < other || *this == other; }
		bool operator==(const BigInt& other) const;
		bool operator!=(const BigInt& other) const { return !(*this == other); }

		friend std::ostream& operator<<(std::ostream& os, const BigInt& number);
	private:
		std::string number_;
	};
} //  namespace big_int