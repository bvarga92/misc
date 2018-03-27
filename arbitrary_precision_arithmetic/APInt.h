#ifndef _APINT_H_
#define _APINT_H_

	#include <vector>
	#include <ostream>

	class APInt{
		private:
			std::vector<unsigned> digits;
			bool negative;
		public:
			/* konstruktor es ertekadas */
			APInt() : negative(false) {};
			APInt(const APInt& k)=default;
			APInt(int k);
			APInt(const char* str);
			APInt& operator=(const APInt& rhs)=default;
			APInt& operator=(int k);
			APInt& operator=(const char* str);
			/* getter jellegu metodusok */
			friend std::ostream& operator<<(std::ostream& os, const APInt& k);
			unsigned getNumDigits() const;
			bool isNegative() const;
			/* relacios operatorok */
			bool operator==(const APInt& rhs) const;
			bool operator!=(const APInt& rhs) const;
			bool operator<(const APInt& rhs) const;
			bool operator<=(const APInt& rhs) const;
			bool operator>(const APInt& rhs) const;
			bool operator>=(const APInt& rhs) const;
			/* aritmetikai operatorok */
			APInt operator+() const;
			APInt operator-() const;
			APInt operator+(const APInt& rhs) const;
			APInt operator-(const APInt& rhs) const;
			APInt operator/(const APInt& rhs) const;
			APInt operator%(const APInt& rhs) const;
			APInt operator*(const APInt& rhs) const;
			APInt& operator+=(const APInt& rhs);
			APInt& operator-=(const APInt& rhs);
			APInt& operator/=(const APInt& rhs);
			APInt& operator%=(const APInt& rhs);
			APInt& operator*=(const APInt& rhs);
			APInt& operator++(int);
			APInt& operator--(int);
			APInt& operator++();
			APInt& operator--();
			/* egyeb */
			static APInt abs(const APInt& k);
			static APInt factorial(int k);
			static APInt gcd(APInt a, APInt b);
			static APInt lcm(APInt a, APInt b);
	};

#endif
