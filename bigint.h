#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <vector>

namespace ACA
{

class BigInt
{

public:
	BigInt(unsigned long long n = 0);
	BigInt(std::string& s);
	BigInt(const BigInt&);

	/* * * * Operator Overloading * * * */

	// assignment
	BigInt& operator()( std::string&);
	BigInt& operator=(const BigInt&);
    // assignment: copy and swap idiom (strong exception safety guarantee)
    // BigInt& operator=(BigInt) noexcept;

	//Post/Pre - Incrementation
	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);

	void fit();
	//Comparison operators
	friend bool operator==(const BigInt&, const BigInt&);
	friend bool operator!=(const BigInt&, const BigInt&);

	friend bool operator>(const BigInt&, const BigInt&);
	friend bool operator>=(const BigInt&, const BigInt&);
	friend bool operator<(const BigInt&, const BigInt&);
	friend bool operator<=(const BigInt&, const BigInt&);

    //Addition and Subtraction
	BigInt& operator+=(const BigInt&);
	friend BigInt operator+(const BigInt&, const BigInt&);
    BigInt& operator-=(const BigInt&);
	friend BigInt operator-(BigInt, const BigInt&);

	//Multiplication and Division
	BigInt& operator*=(const BigInt&);
	friend BigInt operator*(const BigInt&, const BigInt&);
	BigInt& operator/=(const BigInt&);
	friend BigInt operator/(const BigInt&, const BigInt&);

	//Modulo
	BigInt& operator%=(const BigInt&);
	friend BigInt operator%(const BigInt&, const BigInt&);

	//Power Function
	BigInt& operator^=(const BigInt&);
	friend BigInt operator^(BigInt, const BigInt&);

	std::vector<char> num_get() const { return num; }

    friend std::ostream& operator<<(std::ostream&, const BigInt&);
	friend std::istream& operator>>(std::istream&, BigInt&);
private:
	std::vector<char> num;

};

//Read and Write
std::ostream& operator<<(std::ostream&, const BigInt&);
std::istream& operator>>(std::istream&, BigInt&);

} // namespace ACA

#endif