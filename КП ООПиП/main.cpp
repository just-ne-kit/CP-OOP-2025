#include <iostream>
#include <Windows.h>

#include "security/PasswordHasher.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string name = "Nikita";
	std::string ps = PasswordHasher::encrypt(name);
	std::cout << ps << std::endl;
	std::cout << PasswordHasher::decrypt(ps) << std::endl;

	return 0;
}