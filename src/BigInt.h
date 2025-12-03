#ifndef LAB_BIGINT_H
#define LAB_BIGINT_H


#pragma once
#include <string>
#include <vector>
#include <iostream>

class BigInt {
private:
    static constexpr int BASE = 1000;
    static constexpr int BASE_DIGITS = 3;

    std::vector<int> digits;
    bool negative;

    void trim();
    static int compareAbs(const BigInt& a, const BigInt& b);
    static BigInt addAbs(const BigInt& a, const BigInt& b);
    static BigInt subAbs(const BigInt& a, const BigInt& b);
public:
    BigInt();
    BigInt(long long value);
    BigInt(const std::string& value);

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;

    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
};


#endif //LAB_BIGINT_H