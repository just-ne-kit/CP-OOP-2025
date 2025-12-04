#pragma once
#include <string>

namespace input_config
{
    const std::string ERR_INT = "Необходимо ввести целое число";
    const std::string ERR_UINT = "Необходимо ввести целое число без знака";
    const std::string ERR_FLOAT = "Необходимо ввести число";
    const std::string ERR_STR = "Необходимо ввести строку";
}

namespace user_config
{
    const std::size_t USERNAME = 32;
    const std::size_t HASHED_PASSWORD = 32;
}

namespace prop_config
{
    const std::size_t TITLE_MAX_LEN = 64;
    const std::size_t DESCRIPTION_MAX_LEN = 256;
    const std::size_t ADDRESS_MAX_LEN = 128;

    const float PRICE_MIN = 0.0f;
    const float PRICE_MAX = 100'000'000.0f;
    const std::string PRICE_MIN_MSG = "Введите минимальную стоимость(BYN): ";
    const std::string PRICE_MAX_MSG = "Введите максимальную стоимость(BYN): ";
    const std::string PRICE_ERR_MSG =
        input_config::ERR_FLOAT + std::string(" от ") +
        std::to_string(PRICE_MIN) + " до " + std::to_string(PRICE_MAX);

    const float AREA_TOTAL_MIN = 0.0f;
    const float AREA_TOTAL_MAX = 10'000.0f;
    const std::string AREA_TOTAL_MIN_MSG = "Введите минимальную площадь(кв. м): ";
    const std::string AREA_TOTAL_MAX_MSG = "Введите максимальную площадь(кв. м): ";
    const std::string AREA_TOTAL_ERR_MSG =
        input_config::ERR_FLOAT + std::string(" от ") +
        std::to_string(AREA_TOTAL_MIN) + " до " + std::to_string(AREA_TOTAL_MAX);

    const float AREA_LIVING_MIN = 0.0f;
    const float AREA_LIVING_MAX = 5'000.0f;
    const std::string AREA_LIVING_MIN_MSG = "Введите минимальную площадь(кв. м): ";
    const std::string AREA_LIVING_MAX_MSG = "Введите максимальную площадь(кв. м): ";
    const std::string AREA_LIVING_ERR_MSG =
        input_config::ERR_FLOAT + std::string(" от ") +
        std::to_string(AREA_LIVING_MIN) + " до " + std::to_string(AREA_LIVING_MAX);

    const float AREA_KITCHEN_MIN = 0.0f;
    const float AREA_KITCHEN_MAX = 500.0f;
    const std::string AREA_KITCHEN_MIN_MSG = "Введите минимальную площадь(кв. м): ";
    const std::string AREA_KITCHEN_MAX_MSG = "Введите максимальную площадь(кв. м): ";
    const std::string AREA_KITCHEN_ERR_MSG =
        input_config::ERR_FLOAT + std::string(" от ") +
        std::to_string(AREA_KITCHEN_MIN) + " до " + std::to_string(AREA_KITCHEN_MAX);

    const unsigned int ROOMS_MIN = 0;
    const unsigned int ROOMS_MAX = 100;
    const std::string ROOMS_MIN_MSG = "Введите минимальное количество комнат: ";
    const std::string ROOMS_MAX_MSG = "Введите максимальное количество комнат: ";
    const std::string ROOMS_ERR_MSG =
        input_config::ERR_UINT + std::string(" от ") +
        std::to_string(ROOMS_MIN) + " до " + std::to_string(ROOMS_MAX);

    const unsigned int FLOOR_MIN = 0;
    const unsigned int FLOOR_MAX = 200;
    const std::string FLOOR_MIN_MSG = "Введите минимальный этаж: ";
    const std::string FLOOR_MAX_MSG = "Введите максимальный этаж: ";
    const std::string FLOOR_ERR_MSG =
        input_config::ERR_UINT + std::string(" от ") +
        std::to_string(FLOOR_MIN) + " до " + std::to_string(FLOOR_MAX);

    const unsigned int FLOORS_TOTAL_MIN = 0;
    const unsigned int FLOORS_TOTAL_MAX = 200;
    const std::string FLOORS_TOTAL_MIN_MSG = "Введите минимальное количество этажей: ";
    const std::string FLOORS_TOTAL_MAX_MSG = "Введите максимальное количество этажей: ";
    const std::string FLOORS_TOTAL_ERR_MSG =
        input_config::ERR_UINT + std::string(" от ") +
        std::to_string(FLOORS_TOTAL_MIN) + " до " + std::to_string(FLOORS_TOTAL_MAX);
}
