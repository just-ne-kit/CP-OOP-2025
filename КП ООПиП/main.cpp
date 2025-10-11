//Для начала работы программы необходимо во все файлы id.bin записать число 0 в стандарте unsigned int(4 байта)

#include <iostream>
#include <Windows.h>

#include "services/AuthService.h"

#include "storage/ClientStorageManager.h"
#include "storage/AdStorageManager.h"
#include "storage/FavoritesStorageManager.h"
#include "storage/UserAdsStorageManager.h"

#include "repositories//UserAdsRepository.h"
#include "repositories/AdRepository.h"

#include "ui/ConsoleInterface.h"

void Test_Auth()
{
	AdStorageManager adsm{ "data/ads/ads.bin" };
	AdRepository ar{ adsm.loadFromFile() };
	IdGenerator ad_id_gen{ "data/ads/id.bin" };

	ClientStorageManager csm{ "data/clients/clients.bin" };
	std::shared_ptr < ClientRepository> cr = std::make_shared<ClientRepository>( csm.loadFromFile() );

	FavoritesStorageManager fsm{ "data/favorites/favorites.bin" };
	std::shared_ptr<FavoritesRepository> fr = std::make_shared<FavoritesRepository>( fsm.loadFromFile() );

	UserAdsStorageManager usm{ "data/userads/userads.bin" };
	std::shared_ptr<UserAdsRepository> ur = std::make_shared<UserAdsRepository>( usm.loadFromFile() );

	std::cout << "Регайтесь\n";

	std::string login;
	std::string password;

	std::getline(std::cin, login);
	std::getline(std::cin, password);

	AuthService as{ cr, fr, ur, "data/clients/id.bin" };
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

	std::shared_ptr<User> cur_user;
	res = as.login(login, password, cur_user);
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

	//ar.addAd(std::make_shared<Ad>(ad_id_gen.next(), cur_user->id(), "Дом 1"));
	//ar.addAd(std::make_shared<Ad>(ad_id_gen.next(), cur_user->id(), "Дом 2"));

	std::shared_ptr<Favorites> fav = std::make_shared<Favorites>(cur_user->id());


	fr->getById(cur_user->id())->addFavorites(2);
	fr->getById(cur_user->id())->addFavorites(1);
	fr->getById(cur_user->id())->addFavorites(66);


	//for (const auto& a : ar.getAll())
	//{
	//	cout << a->id() << ' ' << a->ownerId() << ' ' << a->title() << std::endl;
	//}

	for (const auto& f : fr->getAll())
	{
		for (const auto i : f->favorites())
		{
			std::cout << i << std::endl;
		}
	}

	adsm.saveToFile(ar.getAll());
	csm.saveToFile(cr->getAll());
	fsm.saveToFile(fr->getAll());

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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Test_Auth();


	return 0;
}