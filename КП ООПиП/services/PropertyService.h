#pragma once
#include "../repositories/Repository.h"
#include "../core/Property.h"
#include "../ui/ConsoleUI.h"
#include "../filters/PropertyFilter.h"
#include "../ui/InputReader.h"
#include "../services/Sort.h"
#include "../id/IdGenerator.h"
#include <sstream>
#include <iomanip>

class PropertyService {
public:
    static void view(const Repository<Property>& default_repo) {
        ConsoleUI::clear();
        if (default_repo.count() <= 0) {
            ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
            return;
        }
        int choice = ConsoleUI::scroll(
            {
                "Карточный вывод",
                "Табличный вывод"
            },
            ">");

        if (choice == 0) card_view(default_repo);
        else if (choice == 1) table_view(default_repo);
    }

    static void edit(Repository<Property>& repo) {
        ConsoleUI::clear();
        if (repo.count() < 1) {
            ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для продолжения.");
            return;
        }

        unsigned int id = InputReader::read<unsigned int>("Введите id редактируемого объявления: ", input_cfg::ERR_UINT);

        if (!repo.exists([&](const PropertyPtr& p) { return p->id() == id; })) {
            ConsoleUI::pause_clear("Объявление с таким id не найдено. Нажмите любую клавишу для продолжения.");
            return;
        }

        auto edited = std::make_shared<Property>(
            *repo.get([&](const PropertyPtr& p) { return p->id() == id; })
        );
        Seller seller;

        int choice = 0;
        bool exit = false;
        while (!exit) {
            std::vector<std::string> v = edited->to_lines();
            v.erase(v.begin(), v.begin() + 2);

            v.push_back("Закончить редактирование");
            v.push_back("Выход");

            choice = ConsoleUI::scroll(v, ">", choice, "Выберите поле для редактирования\n");
            ConsoleUI::clear();

            switch (choice) {
            case 0: edited->set_title(Property::read_title()); break;
            case 1: edited->set_description(Property::read_description()); break;
            case 2: edited->set_address(Property::read_address()); break;
            case 3: edited->set_price(Property::read_price()); break;
            case 4: edited->set_rooms(Property::read_rooms()); break;
            case 5: edited->set_floor(Property::read_floor(edited->floors_total())); break;
            case 6: edited->set_area_total(Property::read_area_total()); break;
            case 7: edited->set_area_living(Property::read_area_living(edited->area_total())); break;
            case 8: edited->set_area_kitchen(Property::read_area_kitchen(edited->area_total())); break;
            case 9: edited->set_type(Property::read_type()); break;
            case 10: edited->set_status(Property::read_status()); break;
            case 13: seller = edited->seller(); seller.set_name(Seller::read_name()); edited->set_seller(seller); break;
            case 14: seller = edited->seller(); seller.set_email(Seller::read_email()); edited->set_seller(seller); break;
            case 15: seller = edited->seller(); seller.set_phone(Seller::read_phone()); edited->set_seller(seller); break;
            case 16:
                edited->set_updated_at(std::time(nullptr));
                repo.update([&](const PropertyPtr& p) { return p->id() == edited->id(); }, edited);
                return;
            case 17: return;
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

        PropertyPtr prop = repo.get([&](const PropertyPtr& p) { return p->id() == del_id; });
        bool isFound = prop != nullptr;

        if (!isFound)
        {
            ConsoleUI::pause_clear("Объявление не найдено. Нажмите любую клавишу для продолжения.");
            return;
        }

        int choice = ConsoleUI::scroll(
            {
                "Подтвердить удаление",
                "Отменить"
            },
            ">",
            0,
            "Вы собираетесь удалить объявление:\n" + prop->to_str() + "\n"
        );

        if (choice == 1) return;

        repo.remove([&](const PropertyPtr& p) { return p->id() == del_id; });

        ConsoleUI::pause_clear("Объявление удалено. Нажмите любую клавишу для продолжения.");
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

        bool isFound = repo.exists([&](const PropertyPtr& p) { return p->id() == id; });

        if (isFound) {
            std::cout << std::endl << *repo.get([&](const PropertyPtr& p) { return p->id() == id; });
            ConsoleUI::pause_clear("\nНажмите любую клавишу для продолжения.");
        }
        else {
            ConsoleUI::pause_clear("\nОбъявление не найдено. Нажмите любую клавишу для продолжения.");
        }
    }
    static void card_view(const Repository<Property>& default_repo)
    {
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

            if (9 <= choice && choice <= 13) {
                reset_repo();
                filter.apply_filters(repo);
            }
        }
    }
    static void table_view(const Repository<Property>& default_repo)
    {
        PropertyFilter filter;
        bool is_asc = true;
        int choice = 0;
        Repository<Property> repo = default_repo;

        auto reset_repo = [&]() { repo = default_repo; };

        bool exit = false;
        while (!exit) {
            if (repo.count() <= 0) {
                ConsoleUI::pause_clear("Нет объявлений. Нажмите любую клавишу для сброса фильтров.");
                filter.default_filters();
                reset_repo();
            }

            std::vector<size_t> sizes = {
                4,7,6,10,10,10,11,8,8,8,4,4,6,10,9,24,24,10,25,15
            };
            std::vector<std::string> headers = {
                "ID",        // ID
                "Риэлтор",   // Realtor
                "Клиент",    // Client
                "Заголовок", // Title
                "Описание",  // Description
                "Адрес",     // Address
                "Цена",      // Price
                "ПлОбщ",     // AreaTot
                "ПлЖил",     // AreaLiv
                "ПлКух",     // AreaKit
                "Комн",      // Rooms
                "Этаж",      // Floor
                "МаксЭт",    // FloorsTot
                "Тип",       // Type
                "Статус",    // Status
                "Создано",   // Created
                "Обновленно",// Updated
                "Продавец",  // SellerName
                "Email",     // SellerEmail
                "Телефон"    // SellerPhone
            };


            std::ostringstream preview;
            preview << "|";
            for (size_t i = 0; i < headers.size() && i < sizes.size(); ++i) {
                preview << std::left << std::setw(sizes[i]) << headers[i] << "|";
            }
            preview << "\n";

            size_t total_width = 1;
            for (size_t w : sizes) total_width += w + 1;
            preview << std::string(total_width, '-') << "\n";

            auto all = repo.getAll();

            if (!is_asc) {
                std::reverse(all.begin(), all.end());
            }

            for (const auto& prop : all) {
                preview << prop->to_row(sizes) << "\n";
            }

            choice = ConsoleUI::scroll({
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
                "Назад"
                }, ">", choice, preview.str() + "\n");

            switch (choice) {
            case 0: find(repo); break;
            case 1: is_asc = !is_asc; break;
            case 2: Sort::by_price(repo); break;
            case 3: Sort::by_area(repo); break;
            case 4: Sort::by_rooms(repo); break;
            case 5: Sort::by_floor(repo); break;
            case 6: Sort::by_status(repo); break;
            case 7: filter.flip_price();  if (filter.price)  filter.set_price_range();  break;
            case 8: filter.flip_area();   if (filter.area)   filter.set_area_range();   break;
            case 9: filter.flip_rooms();  if (filter.rooms)  filter.set_rooms_range();  break;
            case 10: filter.flip_floor(); if (filter.floor)  filter.set_floor_range();  break;
            case 11: filter.flip_status(); if (filter.status) filter.set_status();       break;
            case 12: filter.default_filters(); reset_repo(); break;
            case 13: exit = true; break;
            default: break;
            }

            if (6 <= choice && choice <= 11) {
                reset_repo();
                filter.apply_filters(repo);
            }
        }
    }
};
