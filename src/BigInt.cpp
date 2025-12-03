#include "BigInt.h"
#include <algorithm>
#include <iomanip>

BigInt::BigInt() : digits(1, 0), negative(false) {}

BigInt::BigInt(long long value) {
    negative = value < 0;
    if (value < 0) value = -value;

    while (value > 0) {
        digits.push_back(value % BASE);
        value /= BASE;
    }

    if (digits.empty()) digits.push_back(0);
}

BigInt::BigInt(const std::string& str) {
    negative = false;
    digits.clear();

    int start = 0;
    if (str[0] == '-') {
        negative = true;
        start = 1;
    }

    for (int i = str.length(); i > start; i -= BASE_DIGITS) {
        int end = i;
        int begin = std::max(start, i - BASE_DIGITS);

        int block = std::stoi(str.substr(begin, end - begin));
        digits.push_back(block);
    }

    trim();
}

void BigInt::trim() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();

    if (digits.size() == 1 && digits[0] == 0)
        negative = false;
}

int BigInt::compareAbs(const BigInt& a, const BigInt& b) {
    if (a.digits.size() != b.digits.size())
        return (a.digits.size() < b.digits.size()) ? -1 : 1;

    for (int i = a.digits.size() - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i])
            return (a.digits[i] < b.digits[i]) ? -1 : 1;
    }
    return 0;
}

BigInt BigInt::addAbs(const BigInt& a, const BigInt& b) {
    BigInt result;
    result.digits.clear();

    int carry = 0;
    size_t n = std::max(a.digits.size(), b.digits.size());

    for (size_t i = 0; i < n || carry; i++) {
        int sum = carry;

        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];

        carry = sum >= BASE;
        if (carry) sum -= BASE;

        result.digits.push_back(sum);
    }

    return result;
}

BigInt BigInt::subAbs(const BigInt& a, const BigInt& b) {
    BigInt result;
    result.digits.clear();

    int carry = 0;

    for (size_t i = 0; i < a.digits.size(); i++) {
        int diff = a.digits[i] - carry - (i < b.digits.size() ? b.digits[i] : 0);
        carry = 0;

        if (diff < 0) {
            diff += BASE;
            carry = 1;
        }

        result.digits.push_back(diff);
    }

    result.trim();
    return result;
}


BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;
    if (negative == other.negative) {
        result = addAbs(*this, other);
        result.negative = this->negative;
        return result;
    }

    int cmp = compareAbs(*this, other);
    if (cmp == 0) {
        return BigInt(0);
    }

    if (cmp > 0) {
        result = subAbs(*this, other);
        result.negative = negative;
    } else {
        result = subAbs(other, *this);
        result.negative = other.negative;
    }

    return result;
}


BigInt BigInt::operator-(const BigInt& other) const {
    BigInt temp = other;
    temp.negative = !temp.negative;
    return *this + temp;
}


BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.digits.assign(digits.size() + other.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); i++) {
        long long carry = 0;

        for (size_t j = 0; j < other.digits.size() || carry; j++) {
            long long cur =
                result.digits[i + j] +
                digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) +
                carry;

            result.digits[i + j] = cur % BASE;
            carry = cur / BASE;
        }
    }

    result.negative = negative != other.negative;
    result.trim();
    return result;
}

bool BigInt::operator==(const BigInt& other) const {
    return digits == other.digits && negative == other.negative;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative != other.negative)
        return negative;

    int cmp = compareAbs(*this, other);
    if (!negative)
        return cmp < 0;

    return cmp > 0;
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

std::string BigInt::toString() const {
    if (digits.empty()) return "0";

    std::string s;
    if (negative)
        s.push_back('-');

    s += std::to_string(digits.back());

    for (int i = digits.size() - 2; i >= 0; i--) {
        std::string block = std::to_string(digits[i]);
        s += std::string(BASE_DIGITS - block.length(), '0') + block;
    }

    return s;
}


std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
    return os << bi.toString();
}

