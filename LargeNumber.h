#pragma once

class LargeNum
{
private:
	int* digits;
	int length;
	int sign;	

public:
	class DivisionByZero {};
	
	LargeNum();
	LargeNum(int sign, int length, const int* digits);
	LargeNum(const LargeNum&);
	LargeNum(int number);
	LargeNum(long number);
	~LargeNum();

	LargeNum& operator =(const LargeNum&);
	LargeNum operator +(const LargeNum&) const;
	LargeNum& operator +=(const LargeNum&);
	LargeNum operator -(const LargeNum&)const;
	LargeNum& operator -=(const LargeNum&);
	LargeNum operator *(const LargeNum&) const;
	LargeNum& operator *=(const LargeNum&);
	LargeNum operator /(const LargeNum&)const;
	LargeNum& operator /=(const LargeNum&);
	LargeNum& operator ++();
	LargeNum operator ++(int);
	LargeNum& operator --();
	LargeNum operator --(int);
	bool operator >(const LargeNum&)const;
	std::ostream& print(std::ostream&) const;
	friend std::ostream& operator <<(std::ostream&, const LargeNum&);
};