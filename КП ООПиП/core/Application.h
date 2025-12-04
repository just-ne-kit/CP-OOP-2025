#pragma once

#include "../core/Property.h"
#include "../storage/StorageManager.h"
#include "../services/AuthService.h"
#include "../ui/InputReader.h"
#include "conio.h"

namespace Sort {
	void by_price(Repository<Property>& repo) {
		repo.sort([](const auto& a, const auto& b) {
			return a->getPrice() < b->getPrice();
			});
	}

	void by_area(Repository<Property>& repo) {
		repo.sort([](const auto& a, const auto& b) {
			return a->getAreaTotal() < b->getAreaTotal();
			});
	}

	void by_rooms(Repository<Property>& repo) {
		repo.sort([](const auto& a, const auto& b) {
			return a->getRooms() < b->getRooms();
			});
	}

	void by_floor(Repository<Property>& repo) {
		repo.sort([](const auto& a, const auto& b) {
			return a->getFloor() < b->getFloor();
			});
	}

	void by_status(Repository<Property>& repo) {
		repo.sort([](const auto& a, const auto& b) {
			return a->getStatus() < b->getStatus();
			});
	}
}

class Application
{
private:
	IdGenerator id_gen_prop{"data/properties/id.bin"};
	StorageManager<Property> property_storage{ "data/properties/properties.bin" };
	Repository<Property> property_repo{ property_storage.load() };

	StorageManager<Realtor> realtor_storage{ "data/realtors/realtors.bin" };
	Repository<Realtor> realtor_repo{ realtor_storage.load() };
	
	AuthService authService{ realtor_repo, "data/realtors/id.bin" };

	static void pause() {
		_getch();
	}
	static void clear() {
		system("cls");
	}
	static void pause_clear(const std::string& msg)
	{
		std::cout << msg;
		pause();
		clear();
	}

	class Filter {
	private:
		std::pair<float, float> priceRange{ 0.0f, 5'000'000.0f };
		std::pair<float, float> areaRange{ 0.0f, 1'000.0f };
		std::pair<unsigned int, unsigned int> roomsRange{ 0, 99 };
		std::pair<unsigned int, unsigned int> floorRange{ 0, 99 };
		Status statusValue{};

		template<typename T>
		std::pair<T, T> set_pair(const T& min, const T& max, const std::string& msg1, const std::string& msg2, const std::string& errMsg = "")
		{
			std::pair<T, T> p;
			
			clear();
			p.first = InputReader::read<T>(min, max, msg1, errMsg);
			p.second = InputReader::read<T>(min, max, msg2, errMsg);
			clear();

			if (p.first > p.second)
			{
				T temp = p.first;
				p.first = p.second;
				p.second = temp;
			}

			return p;
		}

		Status get_status() {
			clear();
			std::cout << "Выберете статус объявления:\n";
			std::cout << "1 - Активно\n";
			std::cout << "2 - Продано\n";
			std::cout << "3 - Арендовано\n";
			std::cout << "4 - Архивировано\n";

			int choice = InputReader::read<int>(1, 4, ">");
			clear();

			return Status(choice - 1);
		}

	public:
		bool price = false;
		bool area = false;
		bool rooms = false;
		bool floor = false;
		bool status = false;

		void default_filters() {
			price = area = rooms = floor = status = false;
			priceRange = { 0.0f, 5'000'000.0f };
			areaRange = { 0.0f, 1'000.0f };
			roomsRange = { 0, 99 };
			floorRange = { 0, 99 };
			statusValue = Status{};
		}

		void flip_price() { price = !price; }
		void flip_area() { area = !area; }
		void flip_rooms() { rooms = !rooms; }
		void flip_floor() { floor = !floor; }
		void flip_status() { status = !status; }

		void set_price_range() {
			priceRange = set_pair<float>(
				prop_config::PRICE_MIN,
				prop_config::PRICE_MAX,
				prop_config::PRICE_MIN_MSG,
				prop_config::PRICE_MAX_MSG,
				prop_config::PRICE_ERR_MSG);
		}

		void set_area_range() {
			areaRange = set_pair<float>(
				prop_config::AREA_TOTAL_MIN,
				prop_config::AREA_TOTAL_MAX,
				prop_config::AREA_TOTAL_MIN_MSG,
				prop_config::AREA_TOTAL_MAX_MSG,
				prop_config::AREA_TOTAL_ERR_MSG);
		}

		void set_rooms_range() {
			roomsRange = set_pair<unsigned int>(
				prop_config::ROOMS_MIN,
				prop_config::ROOMS_MAX,
				prop_config::ROOMS_MIN_MSG,
				prop_config::ROOMS_MAX_MSG,
				prop_config::ROOMS_ERR_MSG);
		}

		void set_floor_range() {
			floorRange = set_pair<unsigned int>(
				prop_config::FLOOR_MIN,
				prop_config::FLOOR_MAX,
				prop_config::FLOOR_MIN_MSG,
				prop_config::FLOOR_MAX_MSG,
				prop_config::FLOOR_ERR_MSG);
		}

		void set_status() {
			statusValue = get_status();
		}

		void apply_filters(Repository<Property>& repo) {
			if (price)  repo.remove([&](const auto& a) { return !between(a->getPrice(), priceRange); });
			if (area)   repo.remove([&](const auto& a) { return !between(a->getAreaTotal(), areaRange); });
			if (rooms)  repo.remove([&](const auto& a) { return !between(a->getRooms(), roomsRange); });
			if (floor)  repo.remove([&](const auto& a) { return !between(a->getFloor(), floorRange); });
			if (status) repo.remove([&](const auto& a) { return a->getStatus() != statusValue; });
		}
	};

	int scroll(const std::vector<std::string>& s, const std::string choice, int cur = 0, const std::string str = "")
	{
		bool exit = false;

		int count = s.size();

		while (!exit) {
			clear();
			std::string result = str;

			for (int i = 0; i < count; i++)
				result += (i == cur ? choice : std::string("")) + s[i] + "\n";
			std::cout << result;

			int res = _getch();
			//up
			if (res == 72)
			{
				cur = (cur - 1 + count) % count;
			}
			//down
			else if (res == 80)
			{
				cur = (cur + 1) % count;
			}
			else if (res == '\r')
			{
				exit = true;
				return cur;
			}
		}
	}

	void view_prop(const Repository<Property>& default_repo)
	{
		if (default_repo.count() <= 0) {
			pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
			return;
		}

		Filter filter;

		bool is_asc = true;
		int current = 0;
		Repository<Property> repo = default_repo;
		auto reset_repo = [&]() {repo = default_repo; current = 0; };
		int choice = 0;

		bool exit = false;
		while (!exit) {
			if (repo.count() <= 0) {
				pause_clear("Нет объявлений. Нажмите любую клавишу для сброса фильтров.");
				filter.default_filters();
				reset_repo();
			}

			int index = is_asc ? current : repo.count() - current - 1;

			choice = scroll({
				"Лево",
				"Право",
				"[По убыванию / По возрастанию]",
				"Сортировать по цене",
				"Сортировать по площади",
				"Сортировать по количеству комнат",
				"Сортировать по этажу",
				"Сортировать по статусу",
				"Фильтр по цене",
				"Фильтр по площади",
				"Фильтр по количеству комнат",
				"Фильтр по этажу",
				"Фильтр по статусу",
				"Сбросить сортировки и фильтры",
				"Назад"},
				">", 
				choice,
				repo[index]->to_str() + "\n" + std::to_string(current + 1) + "й из " + std::to_string(repo.count())+ "\n\n");

			switch (choice) {
			case 0: current = (current - 1 + repo.count()) % repo.count(); break;
			case 1: current = (current + 1) % repo.count(); break;
			case 2: is_asc = !is_asc; break;
			case 3: Sort::by_price(repo);  current = 0; break;
			case 4: Sort::by_area(repo);   current = 0; break;
			case 5: Sort::by_rooms(repo);  current = 0; break;
			case 6: Sort::by_floor(repo);  current = 0; break;
			case 7: Sort::by_status(repo); current = 0; break;
			case 8:  filter.flip_price();  if (filter.price)  filter.set_price_range();  break;
			case 9: filter.flip_area();   if (filter.area)   filter.set_area_range();   break;
			case 10: filter.flip_rooms();  if (filter.rooms)  filter.set_rooms_range();  break;
			case 11: filter.flip_floor();  if (filter.floor)  filter.set_floor_range();  break;
			case 12: filter.flip_status(); if (filter.status) filter.set_status();       break;
			case 13: filter.default_filters(); reset_repo(); break;
			case 14: exit = true; break;
			default:break;
			}

			if (8 <= choice && choice <= 12)
			{
				reset_repo();
				filter.apply_filters(repo);
			}
		}
	}

	void view_my_prop(std::shared_ptr<Realtor> realtor)
	{
		Repository<Property> default_repo = property_repo;

		default_repo.remove([&](const std::shared_ptr<Property>& r) { return r->getRealtorId() != realtor->id(); });

		view_prop(default_repo);
	}

	void add_prop(std::shared_ptr<Realtor> realtor)
	{
		Property prop = Property::create(id_gen_prop.next(), realtor->id());

		property_repo.add(std::make_shared<Property>(prop), [&](const auto& obj) { return false; });
	}

	void edit_prop(std::shared_ptr<Realtor> realtor)
	{
		Repository<Property> default_repo = property_repo;

		default_repo.remove([&](const std::shared_ptr<Property>& p) { return p->getRealtorId() != realtor->id(); });

		if (default_repo.count() < 1) {
			pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
			return;
		}

		unsigned int id = InputReader::read<unsigned int>("Введите id редактированного объявления: ", input_config::ERR_UINT);


	}

	void delete_prop(std::shared_ptr<Realtor> realtor)
	{
		unsigned int del_id = InputReader::read<unsigned int>(">");

		bool isFound = property_repo.exists([&](const std::shared_ptr<Property>& p) { return p->getId() == del_id; });

		//todo

		std::cout << (isFound ? 
			"Удален" :
			"Не найден") << std::endl;

		property_repo.remove([&](const std::shared_ptr<Property>& p) { return p->getId() == del_id; });
	}

	void realtor_prop(std::shared_ptr<Realtor> realtor)
	{
		bool exit = false;

		while (!exit)
		{
			std::cout << "Выберете операцию:\n";
			std::cout << "1 - Просмотр объявлений\n";
			std::cout << "2 - Добавление\n";
			std::cout << "3 - Редактирование\n";
			std::cout << "4 - Удаление\n";
			std::cout << "0 - Назад\n";

			int choice = InputReader::read<int>(0, 4, ">");

			switch (choice)
			{
			case 1: view_my_prop(realtor); break;
			case 2: add_prop(realtor); break;
			case 3: edit_prop(realtor); break;
			case 4: delete_prop(realtor); break;
			case 0: exit = true; break;
			default: break;
			}
		}
	}

	template<typename T>
	static bool between(const T& a, const std::pair<T, T>& pair) {
		return pair.first <= a && a <= pair.second;
	}

	void realtor_all_prop()
	{
		view_prop(property_repo);
	}

	void realtor_report()
	{
		//создание отчета

		//вывод в консоль

		pause_clear("Нажмите любую клавишу для продолжения.");
	}

	void realtor(std::shared_ptr<Realtor> realtor)
	{
		bool exit = false;

		while (!exit) {

			int choice = scroll({
				"Мои объявления",
				"Все объявления",
				"Создать отчет",
				"Выйти из учетной записи"},
				">");
;
			switch (choice)
			{
			case 0: realtor_prop(realtor); break;
			case 1: realtor_all_prop(); break;
			case 2: realtor_report(); break;
			case 3: exit = true; break;
			default: break;
			}
		}
	}

	void admin(std::shared_ptr<Admin> admin)
	{

	}

	void register_user()
	{
		clear();
		std::string login = InputReader::read<std::string>("Введите новый логин:");
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
		clear();
		std::string login = InputReader::read<std::string>("Введите логин:");
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
		default: pause_clear("Такой роли нет. Нажмите любую клавишу для продолжения."); break;
		}
	}

public:
	void run()
	{
		bool exit_program = false;
		while (!exit_program) {
			int choice = scroll({
				"Регистрация",
				"Вход",
				"Выход из программы" },
				">");

			switch (choice)
			{
			case 0: register_user(); break;
			case 1: login(); break;
			case 2: exit_program = true; break;
			default: clear(); break;
			}
		}

		realtor_storage.save(realtor_repo.getAll());
		property_storage.save(property_repo.getAll());
	}
};