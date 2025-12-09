#pragma once
#include "../repositories/Repository.h"
#include "../core/Property.h"
#include "../ui/ConsoleUI.h"
#include "../filters/PropertyFilter.h"
#include "../ui/InputReader.h"
#include "../services/Sort.h"

class PropertyViewer {
public:
    static void view(const Repository<Property>& default_repo) {
        ConsoleUI::clear();
        if (default_repo.count() <= 0) {
            ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
            return;
        }

        PropertyFilter filter;
        bool is_asc = true;
        int current = 0;
        int choice = 0;
        Repository<Property> repo = default_repo;

        auto reset_repo = [&]() { repo = default_repo; current = 0; };

        bool exit = false;
        while (!exit) {
            if (repo.count() <= 0) {
                ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для сброса фильтров.");
                filter.default_filters();
                reset_repo();
            }

            int index = is_asc ? current : repo.count() - current - 1;

            choice = ConsoleUI::scroll({
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
                "Назад" },
                ">",
                choice,
                repo[index]->to_str() + "\n" + std::to_string(current + 1) + "й из " + std::to_string(repo.count()) + "\n\n");

            switch (choice) {
            case 0: current = (current - 1 + repo.count()) % repo.count(); break;
            case 1: current = (current + 1) % repo.count(); break;
            case 2: find(repo); break;
            case 3: is_asc = !is_asc; break;
            case 4: Sort::by_price(repo);  current = 0; break;
            case 5: Sort::by_area(repo);   current = 0; break;
            case 6: Sort::by_rooms(repo);  current = 0; break;
            case 7: Sort::by_floor(repo);  current = 0; break;
            case 8: Sort::by_status(repo); current = 0; break;
            case 9: filter.flip_price();  if (filter.price)  filter.set_price_range();  break;
            case 10: filter.flip_area();   if (filter.area)   filter.set_area_range();   break;
            case 11: filter.flip_rooms();  if (filter.rooms)  filter.set_rooms_range();  break;
            case 12: filter.flip_floor();  if (filter.floor)  filter.set_floor_range();  break;
            case 13: filter.flip_status(); if (filter.status) filter.set_status();       break;
            case 14: filter.default_filters(); reset_repo(); break;
            case 15: exit = true; break;
            default: break;
            }

            if (8 <= choice && choice <= 12) {
                reset_repo();
                filter.apply_filters(repo);
            }
        }
    }

    static void edit(Repository<Property>& repo) {
        ConsoleUI::clear();
        if (repo.count() < 1) {
            ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
            return;
        }

        unsigned int id = InputReader::read<unsigned int>("Введите id редактируемого объявления: ", input_cfg::ERR_UINT);

        if (!repo.exists([&](const PropertyPtr& p) { return p->getId() == id; })) {
            ConsoleUI::pause_clear("Объявление с таким id не найдено. Нажмите любую клавишу для продолжения.");
            return;
        }

        auto edited = std::make_shared<Property>(
            *repo.get([&](const PropertyPtr& p) { return p->getId() == id; })
        );

        int choice = 0;
        bool exit = false;
        while (!exit) {
            std::vector<std::string> v = edited->to_lines();
            v.erase(v.begin(), v.begin() + 2);   // убираем id и риэлтора
            v.erase(v.end() - 2, v.end());       // убираем updatedAt и createdAt

            v.push_back("Закончить редактирование");
            v.push_back("Выход");

            choice = ConsoleUI::scroll(v, ">", choice, "Выберите поле для редактирования\n");
            ConsoleUI::clear();

            switch (choice) {
            case 0: edited->setTitle(Property::readTitle()); break;
            case 1: edited->setDescription(Property::readDescription()); break;
            case 2: edited->setAddress(Property::readAddress()); break;
            case 3: edited->setPrice(Property::readPrice()); break;
            case 4: edited->setRooms(Property::readRooms()); break;
            case 5: edited->setFloor(Property::readFloor(edited->getFloorsTotal())); break;
            case 6: edited->setAreaTotal(Property::readAreaTotal()); break;
            case 7: edited->setAreaLiving(Property::readAreaLiving(edited->getAreaTotal())); break;
            case 8: edited->setAreaKitchen(Property::readAreaKitchen(edited->getAreaTotal())); break;
            case 9: edited->setType(Property::readType()); break;
            case 10: edited->setStatus(Property::readStatus()); break;
            case 11:
                edited->setUpdatedAt(std::time(nullptr));
                repo.update([&](const PropertyPtr& p) { return p->getId() == edited->getId(); }, edited);
                return;
            case 12: return;
            default: break;
            }
        }
    }

    static void remove(Repository<Property>& repo) {
        ConsoleUI::clear();
        if (repo.count() < 1) {
            ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
            return;
        }

        unsigned int del_id = InputReader::read<unsigned int>("Введите id удаляемого объявления: ", input_cfg::ERR_UINT);

        bool isFound = repo.exists([&](const PropertyPtr& p) { return p->getId() == del_id; });

        repo.remove([&](const PropertyPtr& p) { return p->getId() == del_id; });

        ConsoleUI::pause_clear(std::string(isFound ? "Объявление удалено" : "Объявление не найдено")
            + ". Нажмите любую клавишу для продолжения.");
    }

    static void add(IdGenerator& id_gen, Repository<Property>& repo, unsigned int realtorId) {
        ConsoleUI::clear();

        Property prop = Property::create(id_gen.next(), realtorId);

        int choice = ConsoleUI::scroll(
            {
                "Подтвердить добавление",
                "Отменить"
            },
            ">",
            0,
            "Вы собираетесь добавить объявление:\n" + prop.to_str() + "\n"
        );

        if (choice == 1) return;

        repo.add(std::make_shared<Property>(prop), [&](const auto&) { return false; });

        ConsoleUI::pause_clear("Объявление успешно добавлено. Нажмите любую клавишу для продолжения.");
    }

private:
    static void find(const Repository<Property>& repo) {
        ConsoleUI::clear();
        unsigned int id = InputReader::read<unsigned int>("Введите id искомого объявления: ", input_cfg::ERR_UINT);

        bool isFound = repo.exists([&](const PropertyPtr& p) { return p->getId() == id; });

        if (isFound) {
            std::cout << std::endl << *repo.get([&](const PropertyPtr& p) { return p->getId() == id; });
            ConsoleUI::pause_clear("\nНажмите любую клавишу для продолжения.");
        }
        else {
            ConsoleUI::pause_clear("\nОбъявление не найдено. Нажмите любую клавишу для продолжения.");
        }
    }
};
