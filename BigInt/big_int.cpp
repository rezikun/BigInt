#include <string>
#include <regex>

#include "big_int.h"

namespace big_int {

	namespace {
		void TrimZeros(std::string* result) {
			int i = 0;
			for (; (*result)[i] == '0' && i < result->size() - 1; ++i);
			result->erase(0, i);
		}
	} //  namespace

	BigInt::BigInt(const std::string& number) : number_(number) {
		if (!std::regex_match(number, std::regex("-?[0-9]+"))) {
			throw std::invalid_argument(number + " is not a valid number.");
		}
		TrimZeros(&number_);
	}

	BigInt BigInt::operator+(const BigInt & other) const
	{
		if (this->number_[0] == '-') {
			if (other.number_[0] == '-') {
				return -(-*this + -other);
			}
			return other - (-*this);
		}
		// At this point we are sure that "this" is not negative.
		if (other.number_[0] == '-') {
			return *this - -other;
		}
		// Now we are sure that both numbers are not negative.
		auto bigger_number = other < *this ? *this : other;
		auto smaller_number = other == bigger_number ? *this : other;
		std::string result;
		int remember = 0;
		for (int i = 0; i < smaller_number.number_.size(); ++i) {
			char num = bigger_number.number_[bigger_number.number_.size() - i - 1];
			int bigger = std::atoi(&num);
			num = smaller_number.number_[smaller_number.number_.size() - i - 1];
			int smaller = std::atoi(&num);
			result += std::to_string((smaller + bigger + remember) % 10);

			remember = (smaller + bigger + remember) / 10;
		}
		for (int i = smaller_number.number_.size(); i < bigger_number.number_.size(); ++i) {
			char num = bigger_number.number_[bigger_number.number_.size() - i - 1];
			int bigger = std::atoi(&num);
			result += std::to_string((bigger + remember) % 10);

			remember = (bigger + remember) / 10;
		} 
		if (remember != 0) {
			result = result + std::to_string(remember);
		}
		std::reverse(result.begin(), result.end());
		return BigInt(result);
	}

	BigInt BigInt::operator-(const BigInt & other) const
	{
		if (this->number_[0] == '-') {
			if (other.number_[0] == '-') {
				return -other - -*this;
			}
			return -(-*this + other);
		}
		// At this point we are sure that "this" is not negative.
		if (other.number_[0] == '-') {
			return *this + -other;
		}
		if (other > * this) {
			return -(other - *this);
		}
		// Now we are sure that both numbers are not negative.
		auto bigger_number = *this;
		auto smaller_number = other;
		std::string result;
		int remember = 0;
		
		for (int i = 0; i < smaller_number.number_.size(); ++i) {
			char num = bigger_number.number_[bigger_number.number_.size() - i - 1];
			int bigger = std::atoi(&num);
			num = smaller_number.number_[smaller_number.number_.size() - i - 1];
			int smaller = std::atoi(&num);
			if (bigger - remember >= smaller) {
				result += std::to_string(bigger - remember - smaller);
				remember = 0;
			}
			else {
				result += std::to_string(bigger - remember - smaller + 10);
				remember = 1;
			}
		}

		for (int i = smaller_number.number_.size(); i < bigger_number.number_.size(); ++i) {
			char num = bigger_number.number_[bigger_number.number_.size() - i - 1];
			int bigger = std::atoi(&num);
			if (bigger - remember >= 0) {
				result += std::to_string(bigger - remember);
				remember = 0;
			}
			else {
				result += std::to_string(bigger - remember + 10);
				remember = 1;
			}
		}
		std::reverse(result.begin(), result.end());
		TrimZeros(&result);
		return BigInt(result);
	}

	BigInt BigInt::operator-() const
	{
		if (this->number_[0] == '-') {
			std::string new_number = number_;
			new_number.erase(0, 1);
			return BigInt(new_number);
		}
		return BigInt("-" + number_);
	}

	BigInt BigInt::operator*(const BigInt & other) const
	{
		if (this->number_[0] == '-') {
			if (other.number_[0] == '-') {
				return -other * -*this;
			}
			return -(-*this * other);
		}
		// At this point we are sure that "this" is not negative.
		if (other.number_[0] == '-') {
			return -(*this * -other);
		}
		auto bigger_number = other < *this ? *this : other;
		auto smaller_number = other == bigger_number ? *this : other;
		BigInt result("0");
		int remember = 0;
		for (int i = 0; i < smaller_number.number_.size(); ++i) {
			std::string curr_result;
			for (int k = 0; k < i; ++k) { curr_result += '0'; }
			for (int j = 0; j < bigger_number.number_.size(); ++j) {
				char num = bigger_number.number_[bigger_number.number_.size() - j - 1];
				int bigger = std::atoi(&num);
				num = smaller_number.number_[smaller_number.number_.size() - i - 1];
				int smaller = std::atoi(&num);
				curr_result += std::to_string((smaller * bigger + remember) % 10);

				remember = (smaller * bigger + remember) / 10;
			}
			if (remember != 0) {
				curr_result += std::to_string(remember);
				remember = 0;
			}
			std::reverse(curr_result.begin(), curr_result.end());
			TrimZeros(&curr_result);
			result = result + BigInt(curr_result);
		}
		
		return result;
	}

	int FindMult(const std::string& left, const BigInt& right) {
		int mult = 1;
		for (; BigInt(mult) * right <= BigInt(left); ++mult);
		return mult;
	}

	BigInt BigInt::operator/(const BigInt& other) const
	{
		if (other == BigInt("0")) {
			throw std::invalid_argument("Cannot divide by 0.");
		}
		if (this->number_[0] == '-') {
			if (other.number_[0] == '-') {
				return -*this / -other;
			}
			return -(-*this / other);
		}
		// At this point we are sure that "this" is not negative.
		if (other.number_[0] == '-') {
			return -(*this / -other);
		}
		if (*this < other) {
			return BigInt("0");
		}
		std::string result;
		std::string curr;
		for (int i = 0; i < this->number_.size()
			&& BigInt(curr += this->number_[i]) < other; ++i);
		int mult = FindMult(curr, other);
		for (int i = curr.size(); i < this->number_.size(); ++i) {
			result += std::to_string(mult - 1);
			std::string remember = BigInt(curr) - other * BigInt(mult - 1);
			curr = remember + this->number_[i];
			mult = FindMult(curr, other);
		}
		result += std::to_string(mult - 1);
		return BigInt(result);
	}

	BigInt BigInt::operator%(const BigInt& other) const
	{
		return *this - other*(*this / other);
	}

	BigInt BigInt::pow(const BigInt& other) const
	{
		BigInt res(1);
		BigInt other_copy = other;
		BigInt this_copy = *this;
		while (other_copy != 0) {
			if (other_copy % 2 != 0) {
				res = res * this_copy;
			}
			this_copy = this_copy * this_copy;
			other_copy = other_copy / 2;
		}	
		return res;
	}

	BigInt BigInt::wsqrt() const
	{
		BigInt xn(number_.substr(0, number_.size() / 2 + 1));
		while ((xn + BigInt("1")).pow(BigInt("2")) < *this ||
				xn.pow(BigInt("2")) > *this) {
			xn = (xn + *this / xn) / BigInt("2");
		}
		return xn;
	}

	bool BigInt::operator>(const BigInt & other) const
	{
		return other < *this;
	}

	bool BigInt::operator<(const BigInt & other) const
	{
		if (this->number_[0] == '-') {
			if (other.number_[0] == '-') {
				return -*this > -other;
			}
			return true;
		}
		// At this point we are sure that "this" is not negative.
		if (other.number_[0] == '-') {
			return false;
		}
		// Now we are sure that both numbers are not negative.
		if (number_.size() != other.number_.size()) {
			return number_.size() < other.number_.size();
		}

		for (int i = 0; i < number_.size(); ++i) {
			int first = std::atoi(&number_[i]);
			int second = std::atoi(&other.number_[i]);
			if (first != second) {
				return first < second;
			}
		}
		// Numbers are equal.
		return false;
	}

	bool BigInt::operator==(const BigInt & other) const
	{
		return number_ == other.number_;
	}

	std::ostream& operator<<(std::ostream & os, const BigInt & number)
	{
		os << number.number_;
		return os;
	}
} //  namespace big_int