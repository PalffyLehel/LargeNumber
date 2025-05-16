#include <iostream>

#include "LargeNumber.h";

LargeNum::LargeNum()
{
	length = 0;
	sign = 0;
	digits = new int[1] {};
}

LargeNum::LargeNum(int sign, int length, const int* digits)
{
	this->sign = sign;
	this->length = length;
	this->digits = new int[length];

	for (int i = 0; i < length; i++)
	{
		this->digits[i] = digits[i];
	}
}

LargeNum::LargeNum(const LargeNum& e)
{
	sign = e.sign;
	length = e.length;
	digits = new int[length];
	for (int i = 0; i < length; i++)
	{
		digits[i] = e.digits[i];
	}
}

LargeNum::LargeNum(int number)
{
	sign = 1;
	if (number == 0)
	{
		sign = 0;
	}

	else if (number < 0)
	{
		sign = -1;
		number *= -1;
	}

	int aux = number;
	int i = 0;
	while (aux != 0)
	{
		aux /= 10;
		i++;
	}

	length = i;
	this->digits = new int[length];

	while (number != 0)
	{
		this->digits[i - 1] = number % 10;
		number /= 10;
		i--;
	}
}

LargeNum::LargeNum(long number)
{
	sign = 1;
	if (number == 0)
	{
		sign = 0;
	}

	else if (number < 0)
	{
		sign = -1;
		number *= -1;
	}

	long aux = number;
	int i = 0;
	while (aux != 0)
	{
		aux /= 10;
		i++;
	}

	length = i;
	this->digits = new int[length];

	while (number != 0)
	{
		this->digits[i - 1] = number % 10;
		number /= 10;
		i--;
	}
}

LargeNum::~LargeNum()
{
	delete[] digits;
}

LargeNum& LargeNum::operator =(const LargeNum & num)
{
	sign = num.sign;
	length = num.length;
	delete[] digits;
	digits = new int[length];
	for (int i = 0; i < length; i++)
	{
		digits[i] = num.digits[i];
	}

	return *this;
}

LargeNum LargeNum::operator+(const LargeNum& num) const
{
	if (sign == 0)
	{
		return num;
	}

	if (num.sign == 0)
	{
		return *this;
	}

	if (sign == -1 && num.sign == 1)
	{
		LargeNum seged(*this);
		seged.sign = 1;
		LargeNum masolat(num);
		return masolat - seged;
	}

	if (sign == 1 && num.sign == -1)
	{
		LargeNum aux(num);
		aux.sign = 1;
		return *this - aux;
	}

	int max_length, min_length;
	int* greater, *smaller;

	if (length > num.length)
	{
		max_length = length;
		min_length = num.length;
		greater = digits;
		smaller = num.digits;
	}

	else
	{
		max_length = num.length;
		min_length = length;
		greater = num.digits;
		smaller = digits;
	}

	int new_length = max_length;

	int* new_digits = new int[new_length] {};
	for (int i = max_length - 1; i >= 0; i--)
	{
		new_digits[i] = greater[i];
	}

	int carry = 0;
	int i = new_length - 1;
	for (int i2 = min_length - 1; i2 >= 0; i--, i2--)
	{
		new_digits[i] += smaller[i2] + carry;
		carry = new_digits[i] / 10;
		new_digits[i] %= 10;
	}

	while (carry != 0)
	{
		if (i == -1)
		{
			int* aux = new int[new_length + 1];
			for (int i = 0; i < new_length; i++)
			{
				aux[i + 1] = new_digits[i];
			}
			aux[0] = 0;
			new_length++;
			delete[] new_digits;
			new_digits = aux;
			i = 0;
		}

		new_digits[i] += carry;
		carry = new_digits[i] / 10;
		new_digits[i] %= 10;

		i--;
	}

	return LargeNum(sign, new_length, new_digits);
}
LargeNum& LargeNum::operator+=(const LargeNum& num)
{
	*this = *this + num;
	return *this;
}

LargeNum& LargeNum::operator++()
{
	*this += LargeNum(1);
	return *this;
}
LargeNum LargeNum::operator++(int)
{
	LargeNum aux(*this);
	*this += LargeNum(1);
	return aux;
}

LargeNum LargeNum::operator-(const LargeNum& num) const
{
	if (sign == 0)
	{
		LargeNum aux(num);
		aux.sign *= -1;
		return aux;
	}

	if (num.sign == 0)
	{
		return *this;
	}

	if (sign != num.sign)
	{	
		LargeNum aux(num);
		aux.sign = sign;
		return *this + aux;
	}

	int max_length, min_length;
	int* greater, * smaller;
	int new_sign = 0;
	greater = digits;
	smaller = digits;
	if (length > num.length)
	{
		max_length = length;
		min_length = num.length;
		greater = digits;
		smaller = num.digits;
		new_sign = sign;
	}

	else if (num.length > length)
	{
		max_length = num.length;
		min_length = length;
		greater = num.digits;
		smaller = digits;
		new_sign = num.sign * -1;
	}

	else
	{
		for (int i = 0; i < length && new_sign == 0; i++)
		{
			if (digits[i] > num.digits[i])
			{
				max_length = length;
				min_length = num.length;
				greater = digits;
				smaller = num.digits;
				new_sign = sign;
			}

			else if (digits[i] < num.digits[i])
			{
				max_length = num.length;
				min_length = length;
				greater = num.digits;
				smaller = digits;
				new_sign = num.sign * -1;	
			}
		}
	}

	if (new_sign == 0)
	{
		return LargeNum(0);
	}

	int new_length = max_length;
	int* new_digits = new int[max_length];
	for (int i = 0; i < max_length; i++)
	{
		new_digits[i] = greater[i];
	}

	int i2 = max_length - 1;
	int carry = 0;
	for (int i = min_length - 1; i >= 0; i--, i2--)
	{
		new_digits[i2] -= smaller[i] + carry;
		carry = new_digits[i2] < 0;
		if (new_digits[i2] < 0)
		{
			new_digits[i2] += 10;
		}
	}

	while (carry != 0)
	{
		new_digits[i2] -= carry;
		carry = new_digits[i2] < 0;
		if (new_digits[i2] < 0)
		{
			new_digits[i2] += 10;
		}

		i2--;
	}

	i2 = 0;
	while (new_digits[i2] == 0)
	{
		i2++;
	}

	new_length = max_length - i2;
	int* aux = new int[new_length];
	for (int i = 0; i < new_length; i++, i2++)
	{
		aux[i] = new_digits[i2];
	}
	delete[] new_digits;
	new_digits = aux;

	return LargeNum(new_sign, new_length, new_digits);
}
LargeNum& LargeNum::operator-=(const LargeNum& num)
{
	LargeNum seged(num);
	*this = *this - num;
	return *this;
}

LargeNum& LargeNum::operator--()
{
	*this -= LargeNum(1);
	return *this;
}
LargeNum LargeNum::operator--(int)
{
	LargeNum aux(*this);
	*this -= LargeNum(1);
	return aux;
}

LargeNum LargeNum::operator*(const LargeNum& number) const
{
	if (sign == 0 || number.sign == 0)
	{
		return LargeNum(0);
	}

	int max_length, min_length;
	int* greater, * smaller;
	if (length > number.length)
	{
		max_length = length;
		min_length = number.length;
		greater = digits;
		smaller = number.digits;
	}

	else
	{
		max_length = number.length;
		min_length = length;
		greater = number.digits;
		smaller = digits;
	}

	int new_length = max_length + min_length;
	int* new_digits = new int[new_length] {};
	int pivot = 0;
	int carry = 0;
	int i2;
	for (int i = min_length - 1; i >= 0; i--)
	{
		i2 = 0;
		for (int j = max_length - 1; j >= 0; j--, i2++)
		{
			new_digits[new_length - 1 - pivot - i2] += greater[j] * smaller[i] + carry;
			carry = new_digits[new_length - 1 - pivot - i2] / 10;
			new_digits[new_length - 1 - pivot - i2] %= 10;
		}

		while (carry != 0)
		{
			new_digits[new_length - 1 - pivot - i2] += carry;
			carry = new_digits[new_length - 1 - pivot - i2] / 10;
			new_digits[new_length - 1 - pivot - i2] %= 10;
			i2++;
		}

		pivot++;
	}

	int i = 0;
	while (new_digits[i] == 0)
	{
		i++;
	}

	new_length -= i;
	int* aux = new int[new_length];
	for (int j = 0; j < new_length; j++, i++)
	{
		aux[j] = new_digits[i];
	}

	delete[] new_digits;
	new_digits = aux;

	int new_sign = sign * number.sign;

	return LargeNum(new_sign, new_length, new_digits);
}
LargeNum& LargeNum::operator*=(const LargeNum& num)
{
	*this = *this * num;
	return *this;
}

bool LargeNum::operator >(const LargeNum& num) const
{
	if (sign == 1 && num.sign < 1)
	{
		return true;
	}

	if (sign == 0)
	{
		return num.sign < 0;
	}

	if (sign == -1 && num.sign > -1)
	{
		return false;
	}

	if (length > num.length)
	{
		return true;
	}

	if (num.length > length)
	{
		return false;
	}

	int i = 0;
	while (i < length && digits[i] == num.digits[i])
	{
		i++;
	}

	if (i == length)
	{
		return false;
	}

	return digits[i] > num.digits[i];
}

LargeNum LargeNum::operator/(const LargeNum& number)const 
{
	if (number.sign == 0)
	{
		throw DivisionByZero();
	}

	if (sign == 0)
	{
		return *this;
	}

	if (length < number.length)
	{
		return LargeNum(0);
	}

	LargeNum aux(number);
	aux.sign = 1;

	LargeNum aux_result(1, number.length, digits);
	LargeNum result(0);
	int pivot = 0;
	while (number.length + pivot <= length)
	{
		LargeNum multiplier(9);

		while (multiplier * aux > aux_result)
		{
			multiplier--;
		}

		aux_result -= multiplier * aux;
		aux_result *= 10;
		aux_result += LargeNum(digits[number.length + pivot]);

		result *= LargeNum(10);
		result += multiplier;

		pivot++;
	}
	int new_sign = sign * number.sign;
	if (result.length == 0)
	{
		new_sign = 0;
	}

	result.sign = new_sign;
	return result;
}

LargeNum& LargeNum::operator/=(const LargeNum& num)
{
	*this = *this / num;
	return *this;
}

std::ostream& LargeNum::print(std::ostream& stream) const
{
	switch (sign)
	{
	case -1:
		stream << '-';
		break;
	case 0:
		stream << 0;
		break;
	default:
		break;
	}

	for (int i = 0; i < length; i++)
	{
		stream << digits[i];
	}

	return stream;
}

std::ostream& operator <<(std::ostream& stream, const LargeNum& num)
{
	return num.print(stream);
}