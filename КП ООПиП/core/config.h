#pragma once
#include <string>

namespace input_cfg
{
    const std::string ERR_INT = "Необходимо ввести целое число";
    const std::string ERR_UINT = "Необходимо ввести целое число без знака";
    const std::string ERR_FLOAT = "Необходимо ввести число";
    const std::string ERR_STR = "Необходимо ввести строку";
}

namespace auth_cfg {
    const std::string ADMIN_NAME = "admin";
    const std::string ADMIN_PASSWORD = "1111";
}

namespace common_cfg
{
    const std::size_t USERNAME_LEN = 32;
    const std::size_t HASHED_PASSWORD_LEN = 32;

    const std::size_t NAME_MAX_LEN = 64;
    const std::string NAME_MSG = "Введите имя: ";
    const std::string NAME_ERR_MSG =
        input_cfg::ERR_STR + std::string(" не превышающую ") +
        std::to_string(NAME_MAX_LEN - 1) + " символов\n";

    const std::size_t EMAIL_MAX_LEN = 64;
    const std::string EMAIL_MSG = "Введите электронную почту: ";
    const std::string EMAIL_ERR_MSG =
        input_cfg::ERR_STR + std::string(" не превышающую ") +
        std::to_string(EMAIL_MAX_LEN - 1) + " символов\n";

    const std::size_t PHONE_MAX_LEN = 32;
    const std::string PHONE_MSG = "Введите телефонный номер: ";
    const std::string PHONE_ERR_MSG =
        input_cfg::ERR_STR + std::string(" не превышающую ") +
        std::to_string(PHONE_MAX_LEN - 1) + " символов\n";
}

namespace prop_cfg
{
    // Заголовок
    const std::size_t TITLE_MAX_LEN = 64;
    const std::string TITLE_ERR_MSG =
        input_cfg::ERR_STR + std::string(" не превышающую ") +
        std::to_string(TITLE_MAX_LEN - 1) + " символов\n";

    // Описание
    const std::size_t DESCRIPTION_MAX_LEN = 256;
    const std::string DESCRIPTION_ERR_MSG =
        input_cfg::ERR_STR + std::string(" не превышающую ") +
        std::to_string(DESCRIPTION_MAX_LEN - 1) + " символов\n";

    // Адрес
    const std::size_t ADDRESS_MAX_LEN = 128;
    const std::string ADDRESS_ERR_MSG =
        input_cfg::ERR_STR + std::string(" не превышающую ") +
        std::to_string(ADDRESS_MAX_LEN - 1) + " символов\n";

    // Цена
    const float PRICE_MIN = 0.0f;
    const float PRICE_MAX = 100'000'000.0f;
    const std::string PRICE_MIN_MSG = "Введите минимальную стоимость(BYN): ";
    const std::string PRICE_MAX_MSG = "Введите максимальную стоимость(BYN): ";
    const std::string PRICE_ERR_MSG =
        input_cfg::ERR_FLOAT + std::string(" от ") +
        std::to_string(PRICE_MIN) + " до " + std::to_string(PRICE_MAX) + "\n";

    // Общая площадь
    const float AREA_TOTAL_MIN = 0.0f;
    const float AREA_TOTAL_MAX = 10'000.0f;
    const std::string AREA_TOTAL_MIN_MSG = "Введите минимальную площадь(кв. м): ";
    const std::string AREA_TOTAL_MAX_MSG = "Введите максимальную площадь(кв. м): ";
    const std::string AREA_TOTAL_ERR_MSG =
        input_cfg::ERR_FLOAT + std::string(" от ") +
        std::to_string(AREA_TOTAL_MIN) + " до " + std::to_string(AREA_TOTAL_MAX) + "\n";

    // Жилая площадь
    const float AREA_LIVING_MIN = 0.0f;
    const float AREA_LIVING_MAX = 5'000.0f;
    const std::string AREA_LIVING_MIN_MSG = "Введите минимальную площадь(кв. м): ";
    const std::string AREA_LIVING_MAX_MSG = "Введите максимальную площадь(кв. м): ";
    const std::string AREA_LIVING_ERR_MSG =
        input_cfg::ERR_FLOAT + std::string(" от ") +
        std::to_string(AREA_LIVING_MIN) + " до " + std::to_string(AREA_LIVING_MAX) + "\n";

    // Площадь кухни
    const float AREA_KITCHEN_MIN = 0.0f;
    const float AREA_KITCHEN_MAX = 500.0f;
    const std::string AREA_KITCHEN_MIN_MSG = "Введите минимальную площадь(кв. м): ";
    const std::string AREA_KITCHEN_MAX_MSG = "Введите максимальную площадь(кв. м): ";
    const std::string AREA_KITCHEN_ERR_MSG =
        input_cfg::ERR_FLOAT + std::string(" от ") +
        std::to_string(AREA_KITCHEN_MIN) + " до " + std::to_string(AREA_KITCHEN_MAX) + "\n";

    // Количество комнат
    const unsigned int ROOMS_MIN = 0;
    const unsigned int ROOMS_MAX = 100;
    const std::string ROOMS_MIN_MSG = "Введите минимальное количество комнат: ";
    const std::string ROOMS_MAX_MSG = "Введите максимальное количество комнат: ";
    const std::string ROOMS_ERR_MSG =
        input_cfg::ERR_UINT + std::string(" от ") +
        std::to_string(ROOMS_MIN) + " до " + std::to_string(ROOMS_MAX) + "\n";

    // Этаж
    const unsigned int FLOOR_MIN = 0;
    const unsigned int FLOOR_MAX = 200;
    const std::string FLOOR_MIN_MSG = "Введите минимальный этаж: ";
    const std::string FLOOR_MAX_MSG = "Введите максимальный этаж: ";
    const std::string FLOOR_ERR_MSG =
        input_cfg::ERR_UINT + std::string(" от ") +
        std::to_string(FLOOR_MIN) + " до " + std::to_string(FLOOR_MAX) + "\n";

    // Всего этажей
    const unsigned int FLOORS_TOTAL_MIN = 0;
    const unsigned int FLOORS_TOTAL_MAX = 200;
    const std::string FLOORS_TOTAL_MIN_MSG = "Введите минимальное количество этажей: ";
    const std::string FLOORS_TOTAL_MAX_MSG = "Введите максимальное количество этажей: ";
    const std::string FLOORS_TOTAL_ERR_MSG =
        input_cfg::ERR_UINT + std::string(" от ") +
        std::to_string(FLOORS_TOTAL_MIN) + " до " + std::to_string(FLOORS_TOTAL_MAX) + "\n";

    // Тип недвижимости
    const unsigned int TYPE_MIN = 1;
    const unsigned int TYPE_MAX = 4;
    const std::string TYPE_MIN_MSG = "";
    const std::string TYPE_MAX_MSG = "";
    const std::string TYPE_ERR_MSG =
        input_cfg::ERR_INT + std::string(" от ") +
        std::to_string(TYPE_MIN) + " до " + std::to_string(TYPE_MAX) + "\n";

    // Статус
    const unsigned int STATUS_MIN = 1;
    const unsigned int STATUS_MAX = 4;
    const std::string STATUS_MIN_MSG = "";
    const std::string STATUS_MAX_MSG = "";
    const std::string STATUS_ERR_MSG =
        input_cfg::ERR_INT + std::string(" от ") +
        std::to_string(STATUS_MIN) + " до " + std::to_string(STATUS_MAX) + "\n";
}