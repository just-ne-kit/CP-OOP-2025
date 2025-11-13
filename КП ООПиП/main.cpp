//Для начала работы программы необходимо во все файлы id.bin записать число 0 в стандарте unsigned int(4 байта)
#define NOMINMAX

#include <iostream>
#include <Windows.h>

#include "services/AuthService.h"

#include "storage/ClientStorageManager.h"
#include "storage/AdStorageManager.h"
#include "storage/FavoritesStorageManager.h"
#include "storage/UserAdsStorageManager.h"

#include "repositories/UserAdsRepository.h"
#include "repositories/AdRepository.h"

#include "ui/ConsoleInterface.h"
#include "ui/Screen.h"
#include "ui/InputReader.h"

void Test_Auth()
{
	IdGenerator ad_id_gen{ "data/ads/id.bin" };
	AdStorageManager adsm{ "data/ads/ads.bin" };
	AdRepository ar{ adsm.loadFromFile() };

	ClientStorageManager csm{ "data/clients/clients.bin" };
	ClientRepository cr( csm.loadFromFile() );

	FavoritesStorageManager fsm{ "data/favorites/favorites.bin" };
	FavoritesRepository fr = ( fsm.loadFromFile() );

	UserAdsStorageManager usm{ "data/userads/userads.bin" };
	UserAdsRepository ur( usm.loadFromFile() );

	std::shared_ptr<User> cur_user;

	std::string login, password;
	std::cout << "Регайтесь\n"; std::getline(std::cin, login); std::getline(std::cin, password);

	AuthService as{ cr, fr, ur, "data/clients/id.bin" };
	AuthResult res = as.registerUser(login, password);

	if (res == AuthResult::Success) std::cout << "Акк создан\n";
	else if (res == AuthResult::AlreadyExists) std::cout << "Сори уже есть такой тип\n";
	
	std::cout << "Вход, так что будь добр введи логин и пароль\n";
	std::getline(std::cin, login); std::getline(std::cin, password);

	res = as.login(login, password, cur_user);
	if (res == AuthResult::Success) std::cout << "Гуляй\n";
	else if (res == AuthResult::UserNotFound) std::cout << "Тебя не нашло\n";
	else if (res == AuthResult::WrongPassword) std::cout << "Говно пароль\n";

	

	//ar.addAd(std::make_shared<Ad>(ad_id_gen.next(), cur_user->id(), "Дом 1"));
	//ar.addAd(std::make_shared<Ad>(ad_id_gen.next(), cur_user->id(), "Дом 2"));

	//fr.getById(cur_user->id())->addFavorites(2);
	//fr.getById(cur_user->id())->addFavorites(1);
	//fr.getById(cur_user->id())->addFavorites(66);


	//for (const auto& a : ar.getAll())
	//{
	//	cout << a->id() << ' ' << a->ownerId() << ' ' << a->title() << std::endl;
	//}

	for (const auto& f : fr.getAll())
	{
		for (const auto i : f->favorites())
		{
			std::cout << i << std::endl;
		}
	}

	adsm.saveToFile(ar.getAll());
	csm.saveToFile(cr.getAll());
	fsm.saveToFile(fr.getAll());
	usm.saveToFile(ur.getAll());

	system("pause");
} 

void Test_Ad()
{
	
	AdStorageManager adsm{ "data/ads/ads.bin" };
	AdRepository ar{ adsm.loadFromFile() };
	
	//if(ar.addAd(std::make_shared<Ad>(2))) std::cout << "added_1\n";
	//if(ar.addAd(std::make_shared<Ad>(2))) std::cout << "added_2\n";

	adsm.saveToFile(ar.getAll());
}

#include <conio.h>
//int key = getch()

void DrawAd(const Ad& ad, const ClientRepository& cr)
{
	std::cout << std::endl << "Продавец: " << cr.getById(ad.ownerId())->login();
	std::cout << std::endl << "Цена: " << ad.price();
	std::cout << std::endl << "Название: " << ad.title();
	std::cout << std::endl << "Описание: " << ad.description();
	std::cout << std::endl << "Команты: " << ad.rooms();
	std::cout << std::endl << "Этаж: " << ad.floor();
	std::cout << std::endl << "Площадь: " << ad.area();
	std::cout << std::endl << "Балкон: " << ad.hasBalcony() ? "Да" : "Нет";
	std::cout << std::endl << "Новостройка: " << ad.isNewBuilding() ? "Да" : "Нет";
	std::cout << std::endl << "Адрес: " << ad.address();
}

Ad CreateAd(IdGenerator gen, const InputReader& input)
{
	unsigned int id = input.ReadInt("");
	unsigned int ownerId = input.ReadInt("");
	std::string title = input.ReadString("");
	std::string description = input.ReadString("");
	float price = input.ReadInt("");
	unsigned int floor = input.ReadInt("");
	unsigned int rooms = input.ReadInt("");
	float area = input.ReadInt("");
	bool hasBalcony = input.ReadInt("");
	bool isNewBuilding = input.ReadInt("");
	std::string address = input.ReadString("");

	return Ad();
}

void Run()
{
	InputReader input;

	IdGenerator ad_id_gen{ "data/ads/id.bin" };
	AdStorageManager adsm{ "data/ads/ads.bin" };
	AdRepository ar{ adsm.loadFromFile() };

	ClientStorageManager csm{ "data/clients/clients.bin" };
	ClientRepository cr(csm.loadFromFile());

	FavoritesStorageManager fsm{ "data/favorites/favorites.bin" };
	FavoritesRepository fr = (fsm.loadFromFile());

	UserAdsStorageManager usm{ "data/userads/userads.bin" };
	UserAdsRepository ur(usm.loadFromFile());

	AuthService as{ cr, fr, ur, "data/clients/id.bin" };
	
	std::shared_ptr<User> cur_user;

	int choise = input.ReadInt("Регистрация - 1, Вход - 2: ", "Целое число\n");
	std::string login = input.ReadString("Логин: ");
	std::string password = input.ReadString("Пароль: ");

	if (choise == 1){
		AuthResult res = as.registerUser(login, password);
		if (res == AuthResult::Success) std::cout << "Акк создан\n";
		else if (res == AuthResult::AlreadyExists) std::cout << "Сори уже есть такой тип\n";
	}
	else if(choise == 2) {
		AuthResult res = as.login(login, password, cur_user);
		if (res == AuthResult::Success) {
			if (cur_user->role() == Role::Client)
			{
				std::cout << "1 - любимое\n";
				std::cout << "2 - мои объявления\n";
				std::cout << "3 - \n";
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "Выбор: "; std::cin >> choise;
				
				if (choise == 1) {

				}
				else if (choise == 2) {
					std::cout << "1 - Добавить\n";
					std::cout << "2 - Удалить\n";
					std::cout << "3 - Редактировать\n";
					std::cout << "Выбор: "; std::cin >> choise;

					if (choise == 1) {
						
					}
					else if (choise == 2) {
						//ur.getById(cur_user->id())->addUserAds(1);
					}
					else if (choise == 3) {

					}
				}
				else if (choise == 3) {

				}
			}
			else if (cur_user->role() == Role::Admin)
			{

			}
			else
			{
				std::cout << "Ошибка. У пользователя нет роли";
			}
		}
		else if (res == AuthResult::UserNotFound) std::cout << "Тебя не нашло\n";
		else if (res == AuthResult::WrongPassword) std::cout << "Говно пароль\n";
	}

	adsm.saveToFile(ar.getAll());
	csm.saveToFile(cr.getAll());
	fsm.saveToFile(fr.getAll());
	usm.saveToFile(ur.getAll());

	system("pause");
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Test();

	Screen s;

	std::string s1, s2;
	//s.auth_1(s1, s2);
	s.test_screen();
	return 0;
}
