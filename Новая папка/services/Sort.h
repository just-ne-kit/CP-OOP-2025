#pragma once

#include "../core/Property.h"
#include "../repositories/Repository.h"

class Sort {
private:
    // универсальный шаблон Ч остаЄтс€ в заголовке
    template<typename Key>
    static void sort_by(Repository<Property>& repo, Key key) {
        repo.sort([&](const auto& a, const auto& b) {
            return key(*a) < key(*b);
            });
    }
public:
    // объ€влени€ конкретных сортировок
    static void by_price(Repository<Property>& repo);
    static void by_area(Repository<Property>& repo);
    static void by_rooms(Repository<Property>& repo);
    static void by_floor(Repository<Property>& repo);
    static void by_status(Repository<Property>& repo);
};
