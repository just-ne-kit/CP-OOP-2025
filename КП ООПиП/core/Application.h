#pragma once

#include "../core/Property.h"
#include "../storage/StorageManager.h"
#include "../services/AuthService.h"
#include "../ui/InputReader.h"
#include "conio.h"

class Application
{
private:
	StorageManager<Property> property_storage{ "data/properties/properties.bin" };
	Repository<Property> property_repo{ property_storage.load() };

	StorageManager<Realtor> realtor_storage{ "data/realtors/realtors.bin" };
	Repository<Realtor> realtor_repo{ realtor_storage.load() };
	AuthService authService{ realtor_repo, "data/realtors/id.bin" };

public:
	void pause() {
		_getch();
	}
	void clear() {
		system("cls");
	}
	void pause_clear(const std::string& msg)
	{
		std::cout << msg;
		pause();
		clear();
	}

	void realtor_prop()
	{

	}

	Status get_status() {
		std::cout << "Выберете статус объявления:\n";
		std::cout << "1 - Активно\n";
		std::cout << "2 - Продано\n";
		std::cout << "3 - Арендовано\n";
		std::cout << "4 - Архивировано\n";

		int choice = InputReader::read_int(1, 4, ">");

		clear();

		return Status(choice - 1);
	}

	template<typename T>
	bool between(const T& a, const std::pair<T, T>& pair) {
		return pair.first <= a && a <= pair.second;
	}

	void realtor_all_prop()
	{
		int count = property_repo.count();

		if (count <= 0) {
			pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
			return;
		}

		Repository<Property> repo = property_repo;

		bool exit = false;

		bool is_asc = true;

		bool filter_price = false;
		bool filter_area = false;
		bool filter_rooms = false;
		bool filter_floor = false;
		bool filter_status = false;

		std::pair<float, float> priceRange;
		std::pair<float, float> areaRange;
		std::pair<unsigned int, unsigned int> roomsRange;
		std::pair<unsigned int, unsigned int> floorRange;
		Status status;

		int current = 0;

		while (!exit) {
			std::cout << repo[current] << std::endl;
			std::cout << current << "й из " << count << "\n\n";

			std::cout << " 1 - Лево\n";
			std::cout << " 2 - Право\n";
			std::cout << " 3 - Сортировка по [Убыванию/Возрастанию]\n";
			std::cout << " 4 - Сортировать по цене\n";
			std::cout << " 5 - Сортировать по площади\n";
			std::cout << " 6 - Сортировать по количеству комнат\n";
			std::cout << " 7 - Сортировать по этажу\n";
			std::cout << " 8 - Сортировать по статусу\n";
			std::cout << " 9 - Фильтр по цене\n";
			std::cout << "10 - Фильтр по площади\n";
			std::cout << "11 - Фильтр по количеству комнат\n";
			std::cout << "12 - Фильтр по этажу\n";
			std::cout << "13 - Фильтр по статусу\n";
			std::cout << "14 - Сбросить фильтры\n";
			std::cout << " 0 - Выход\n";

			int choice = InputReader::read_int(">");

			switch (choice) {
			case 1: current = (current - 1 + count) % count; break;
			case 2: current = (current + 1) % count; break;
			case 3: is_asc = !is_asc; break;
			case 4: repo.sort([&](const auto& a, const auto& b) { return is_asc && (a->getPrice() < b->getPrice()); }); break;
			case 5: repo.sort([&](const auto& a, const auto& b) { return is_asc && (a->getAreaTotal() < b->getAreaTotal()); }); break;
			case 6: repo.sort([&](const auto& a, const auto& b) { return is_asc && (a->getRooms() < b->getRooms()); }); break;
			case 7: repo.sort([&](const auto& a, const auto& b) { return is_asc && (a->getFloor() < b->getFloor()); }); break;
			case 8: repo.sort([&](const auto& a, const auto& b) { return is_asc && (a->getStatus() < b->getStatus()); }); break;
			case 9:  filter_price = !filter_price;  repo = property_repo; break;
			case 10: filter_area = !filter_area;   repo = property_repo; break;
			case 11: filter_rooms = !filter_rooms;  repo = property_repo; break;
			case 12: filter_floor = !filter_floor;  repo = property_repo; break;
			case 13: filter_status = !filter_status; repo = property_repo; break;
			case 14:
				filter_price = false;
				filter_area = false;
				filter_rooms = false;
				filter_floor = false;
				filter_status = false;

				repo = property_repo;
				break;
			case 0: exit = true; break;
			default:break;
			}

			if (filter_price) repo.remove([&](const std::shared_ptr<Property>& a) { return !between(a->getPrice(), priceRange); });
			if (filter_area)  repo.remove([&](const std::shared_ptr<Property>& a) { return !between(a->getAreaTotal(), areaRange); });
			if (filter_rooms) repo.remove([&](const std::shared_ptr<Property>& a) { return !between(a->getRooms(), roomsRange); });
			if (filter_floor) repo.remove([&](const std::shared_ptr<Property>& a) { return !between(a->getFloor(), floorRange); });
			if (filter_status)repo.remove([&](const std::shared_ptr<Property>& a) { return a->getStatus() != status; });
		}
	}

	void realtor(std::shared_ptr<Realtor> realtor)
	{
		bool exit = false;

		while (!exit) {

			std::cout << "1 - Мои объявления\n";
			std::cout << "2 - Все объявления\n";
			std::cout << "3 - \n";
			std::cout << "4 - \n";

			int choice = InputReader::read_int(">");

			switch (choice)
			{
			case 1: realtor_prop(); break;
			case 2: realtor_all_prop(); break;
			case 3: break;
			case 4: break;
			default:break;
			}
		}
	}

	void admin(std::shared_ptr<Admin> admin)
	{

	}

	void register_user()
	{
		std::string login = InputReader::read_str("Введите новый логин:");
		std::string password1 = InputReader::read_password("Введите пароль:");
		std::string password2 = InputReader::read_password("Повторите пароль:");

		if (password1 != password2) {
			pause_clear("Пароли не совпадают. Нажмите любую клавишу для продолжения.");
			return;
		}

		AuthResult authRes = authService.registerUser(login, password1);

		if (authRes == AuthResult::AlreadyExists) {
			pause_clear("Логин уже занят. Нажмите любую клавишу для продолжения.");
			return;
		}

		pause_clear("Успешно зарегистрированы. Нажмите любую клавишу для продолжения.");
	}

	void login()
	{
		std::string login = InputReader::read_str("Введите логин:");
		std::string password = InputReader::read_password("Введите пароль:");

		std::shared_ptr<User> out_user;

		AuthResult authRes = authService.login(login, password, out_user);

		if (authRes != AuthResult::Success) {
			pause_clear("Логин или пароль неверный. Нажмите любую клавишу для продолжения.");
			return;
		}

		switch (out_user->role())
		{
		case Role::AdminRole: admin(std::dynamic_pointer_cast<Admin>(out_user)); break;
		case Role::RealtorRole: realtor(std::dynamic_pointer_cast<Realtor>(out_user)); break;
		default:break;
		}
	}

	void run()
	{
		bool exit_program = false;
		while (!exit_program) {

			std::cout << "1 - Регистрация\n";
			std::cout << "2 - Вход\n";
			std::cout << "3 - Выход из программы\n";

			int choice = InputReader::read_int(">");

			switch (choice)
			{
			case 1: register_user(); break;
			case 2: login(); break;
			case 3: exit_program = true; break;
			default: clear(); break;
			}
		}
	}
};