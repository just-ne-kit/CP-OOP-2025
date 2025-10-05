//Для начала работы программы необходимо во все файлы id.bin записать число 0 в стандарте unsigned int(4 байта)

#include <iostream>
#include <Windows.h>

#include "services/AuthService.h"
#include "storage/ClientStorageManager.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Регайтесь\n";

	std::string login;
	std::string password;

	std::getline(std::cin, login);
	std::getline(std::cin, password);

	ClientStorageManager csm{"data/clients/clients.bin"};
	ClientRepository cr{csm.loadFromFile()};

	AuthService as{cr,"data/clients/id.bin"};

	AuthResult res = as.registerUser(login, password);

	if (res == AuthResult::Success)
	{
		std::cout << "Акк создан\n";
	}
	else if (res == AuthResult::AlreadyExists)
	{
		std::cout << "Сори уже есть такой тип\n";
	}

	std::cout << "Вход, так что будь добр введи логин и пароль\n";

	std::getline(std::cin, login);
	std::getline(std::cin, password);

	res = as.login(login, password);

	if (res == AuthResult::Success)
	{
		std::cout << "Гуляй\n";
	}
	else if (res == AuthResult::UserNotFound)
	{
		std::cout << "Тебя не нашло\n";
	}
	else if (res == AuthResult::WrongPassword)
	{
		std::cout << "Говно пароль\n";
	}

	csm.saveToFile(cr.getAll());

	return 0;
}