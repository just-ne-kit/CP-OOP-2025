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
	static IdGenerator id_gen_prop;
	static StorageManager<Property> property_storage;
	static Repository<Property> property_repo;

	static StorageManager<Realtor> realtor_storage;
	static Repository<Realtor> realtor_repo;
	
	static AuthService authService;

	template<typename T>
	static bool between(const T& a, const std::pair<T, T>& pair) {
		return pair.first <= a && a <= pair.second;
	}
	static void pause() {
		_getch();
	}
	static void clear() {
		std::cout << "\033[2J" << "\033[H";
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
			statusValue = Property::readStatus();
		}

		void apply_filters(Repository<Property>& repo) {
			if (price)  repo.remove([&](const auto& a) { return !between(a->getPrice(), priceRange); });
			if (area)   repo.remove([&](const auto& a) { return !between(a->getAreaTotal(), areaRange); });
			if (rooms)  repo.remove([&](const auto& a) { return !between(a->getRooms(), roomsRange); });
			if (floor)  repo.remove([&](const auto& a) { return !between(a->getFloor(), floorRange); });
			if (status) repo.remove([&](const auto& a) { return a->getStatus() != statusValue; });
		}
	};

	static int scroll(const std::vector<std::string>& s, const std::string choice, int cur = 0, const std::string str = "")
	{
		bool exit = false;

		int count = s.size();

		while (!exit) {
			std::string result = str;

			for (int i = 0; i < count; i++)
				result += (i == cur ? choice : std::string("")) + s[i] + "\n";
			
			clear();
			std::cout << result << std::flush;

			int res = _getch();
			if (res == 72) cur = (cur - 1 + count) % count;
			else if (res == 80) cur = (cur + 1) % count;
			else if (res == '\r') return cur;
		}
	}

	static void find(const Repository<Property>& repo)
	{
		clear();
		unsigned int id = InputReader::read<unsigned int>("Введите id искомого объявления: ", input_config::ERR_UINT);

		bool isFound = repo.exists([&](const PropertyPtr& p) { return p->getId() == id; });

		if (isFound)
		{
			std::cout << std::endl << *repo.get([&](const PropertyPtr& p) { return p->getId() == id; });
			pause_clear("\nНажмите любую клавишу для продолжения.");
		}
		else {
			pause_clear("\nОбъявление не найдено. Нажмите любую клавишу для продолжения.");
		}
	}

	static void view_prop(const Repository<Property>& default_repo)
	{
		clear();
		if (default_repo.count() <= 0) {
			pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
			return;
		}

		Filter filter;
		bool is_asc = true;
		int current = 0;
		int choice = 0;
		Repository<Property> repo = default_repo;
		
		auto reset_repo = [&]() {repo = default_repo; current = 0; };

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
				"Поиск\n",
				"[По убыванию / По возрастанию]\n",
				"Сортировать по цене",
				"Сортировать по площади",
				"Сортировать по количеству комнат",
				"Сортировать по этажу",
				"Сортировать по статусу\n",
				"Фильтр по цене",
				"Фильтр по площади",
				"Фильтр по количеству комнат",
				"Фильтр по этажу",
				"Фильтр по статусу\n",
				"Сбросить сортировки и фильтры",
				"Назад"},
				">", 
				choice,
				repo[index]->to_str() + "\n" + std::to_string(current + 1) + "й из " + std::to_string(repo.count())+ "\n\n");

			switch (choice) {
			case  0: current = (current - 1 + repo.count()) % repo.count(); break;
			case  1: current = (current + 1) % repo.count(); break;
			case  2: find(repo); break;
			case  3: is_asc = !is_asc; break;
			case  4: Sort::by_price(repo);  current = 0; break;
			case  5: Sort::by_area(repo);   current = 0; break;
			case  6: Sort::by_rooms(repo);  current = 0; break;
			case  7: Sort::by_floor(repo);  current = 0; break;
			case  8: Sort::by_status(repo); current = 0; break;
			case  9: filter.flip_price();  if (filter.price)  filter.set_price_range();  break;
			case 10: filter.flip_area();   if (filter.area)   filter.set_area_range();   break;
			case 11: filter.flip_rooms();  if (filter.rooms)  filter.set_rooms_range();  break;
			case 12: filter.flip_floor();  if (filter.floor)  filter.set_floor_range();  break;
			case 13: filter.flip_status(); if (filter.status) filter.set_status();       break;
			case 14: filter.default_filters(); reset_repo(); break;
			case 15: exit = true; break;
			default:break;
			}

			if (8 <= choice && choice <= 12) {
				reset_repo();
				filter.apply_filters(repo);
			}
		}
	}

	static void view_my_prop(RealtorPtr realtor)
	{
		Repository<Property> default_repo = property_repo;

		default_repo.remove([&](const PropertyPtr& r) { return r->getRealtorId() != realtor->id(); });

		view_prop(default_repo);
	}

	static void add_prop(RealtorPtr realtor)
	{
		Property prop = Property::create(id_gen_prop.next(), realtor->id());

		property_repo.add(std::make_shared<Property>(prop), [&](const auto& obj) { return false; });
	}

	static void edit_prop(RealtorPtr realtor)
	{
		Repository<Property> default_repo = property_repo;

		default_repo.remove([&](const PropertyPtr& p) { return p->getRealtorId() != realtor->id(); });

		if (default_repo.count() < 1) {
			pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
			return;
		}

		unsigned int id = InputReader::read<unsigned int>("Введите id редактированного объявления: ", input_config::ERR_UINT);

		if (!default_repo.exists([&](const PropertyPtr& p) { return p->getId() == id; })) {
			pause_clear("У вас нет такого объявления с таким id. Нажмите любую клавишу для продолжения.");
			return;
		}

		auto edited = std::make_shared<Property>(
			*default_repo.get([&](const PropertyPtr& p) { return p->getId() == id; })
		);

		int choice = 0;
		bool exit = false;
		while (!exit) {
			std::vector<std::string> v = edited->to_lines();
			v.erase(v.begin(), v.begin() + 2);
			v.erase(v.end() - 2, v.end());

			v.push_back("Закончить редактирование");
			v.push_back("Выход");

			choice = scroll(v, ">", choice, "Выберете поле для редактирования\n");
			clear();
			switch (choice)
			{
			case 0: edited->setTitle(Property::readTitle());break;
			case 1: edited->setDescription(Property::readDescription());break;
			case 2: edited->setAddress(Property::readAddress());break;
			case 3: edited->setPrice(Property::readPrice());break;
			case 4: edited->setRooms(Property::readRooms());break;
			case 5:
				//todo floor <= floortotal
				edited->setFloor(Property::readFloor(edited->getFloorsTotal()));
				break;
			case 6: edited->setAreaTotal(Property::readAreaTotal());break;
			case 7:
				edited->setAreaLiving(Property::readAreaLiving(edited->getAreaTotal()));
				break;
			case 8:
				edited->setAreaKitchen(Property::readAreaKitchen(edited->getAreaTotal()));
				break;
			case 9: edited->setType(Property::readType());break;
			case 10:edited->setStatus(Property::readStatus()); break;
			case 11: 
				edited->setUpdatedAt(std::time(nullptr));
				property_repo.update([&](const PropertyPtr& p) { return p->getId() == edited->getId(); }, edited);
				return;
			case 12: return;
			default: break;
			}
		}
	}

	static void delete_prop(RealtorPtr realtor)
	{
		clear();
		unsigned int del_id = InputReader::read<unsigned int>("Введите id удаляемого объявления: ", input_config::ERR_UINT);

		bool isFound = property_repo.exists([&](const PropertyPtr& p) { return p->getId() == del_id; });

		property_repo.remove([&](const PropertyPtr& p) { return p->getId() == del_id; });

		clear();
		pause_clear(std::string((isFound ? "Объявление удалено" : "Объявление не найдено"))
			+ ". Нажмите любую клавишу для продолжения.");
	}

	static void realtor_prop(RealtorPtr realtor)
	{
		bool exit = false;

		while (!exit)
		{
			int choice = scroll({
				"Просмотр объявлений",
				"Добавление",
				"Редактирование",
				"Удаление",
				"Назад"
				}, ">");

			switch (choice)
			{
			case 0: view_my_prop(realtor); break;
			case 1: add_prop(realtor); break;
			case 2: edit_prop(realtor); break;
			case 3: delete_prop(realtor); break;
			case 4: exit = true; break;
			default: break;
			}
		}
	}

	static void realtor_all_prop()
	{
		view_prop(property_repo);
	}

	static void realtor_report()
	{
		//создание отчета

		//вывод в консоль

		pause_clear("Нажмите любую клавишу для продолжения.");
	}

	//todo queue
	static void realtor(RealtorPtr realtor)
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

	static void admin(std::shared_ptr<Admin> admin)
	{

	}

	static void register_user()
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

	static void login()
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

	static void save_data()
	{
		realtor_storage.save(realtor_repo.getAll());
		property_storage.save(property_repo.getAll());
	}
public:
	static BOOL WINAPI ConsoleHandler(DWORD signal) {
		if (signal == CTRL_CLOSE_EVENT || signal == CTRL_SHUTDOWN_EVENT) {
			save_data();
			return TRUE;
		}
		return FALSE;
	}
	static void run()
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
		save_data();
	}
};

IdGenerator Application::id_gen_prop{ "data/properties/id.bin" };
StorageManager<Property> Application::property_storage{ "data/properties/properties.bin" };
Repository<Property> Application::property_repo{ property_storage.load() };
StorageManager<Realtor> Application::realtor_storage{ "data/realtors/realtors.bin" };
Repository<Realtor> Application::realtor_repo{ realtor_storage.load() };
AuthService Application::authService{ realtor_repo, "data/realtors/id.bin" };