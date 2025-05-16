#include <iostream>

#include "LargeNumber.h";

int main()
{
	const int num1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	const int num2[] = { 2, 3, 4, 1, 6, 1, 8, 5, 9, 2, 0, 3, 0, 1, 8, 9, 6, 4, 1, 3 };
	LargeNum ln1(1, 20, num1);
	LargeNum ln2(-1, 20, num2);
	std::cout << ln1 + ln2 << std::endl;
	std::cout << ln1 - ln2 << std::endl;
	std::cout << ln1 * ln2 << std::endl;
	std::cout << ln2 / ln1 << std::endl;
	std::cout << ln1 / ln2 << std::endl;
	 
	std::cout << ++ln1+ln2-- << std::endl;
	std::cout << ln2 << std::endl;
	std::cout << ln1 << std::endl;
	
	return 0;
}