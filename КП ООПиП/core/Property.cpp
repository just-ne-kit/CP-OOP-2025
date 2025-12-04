#include "Property.h"
#include <cstring>
#include "../ui/InputReader.h"
#include <iostream>
#include <iomanip>

Property::Property()
    : m_id(0), m_realtorId(0), m_price(0.0f),
      m_areaTotal(0.0f), m_areaLiving(0.0f), m_areaKitchen(0.0f),
      m_rooms(0), m_floor(0), m_floorsTotal(0),
      m_type(PropertyType::Apartment), m_status(Status::Active),
      m_createdAt(std::time(nullptr)), m_updatedAt(std::time(nullptr))
{
    m_title[0] = '\0';
    m_description[0] = '\0';
    m_address[0] = '\0';
}

Property::Property(unsigned int id,
                   const std::string& title,
                   const std::string& description,
                   const std::string& address,
                   double price,
                   const std::string& currency,
                   float areaTotal,
                   float areaLiving,
                   float areaKitchen,
                   unsigned int rooms,
                   unsigned int floor,
                   unsigned int floorsTotal,
                   PropertyType type,
                   Status status,
                   unsigned int realtorId)
    : m_id(id), m_realtorId(realtorId), m_price(static_cast<float>(price)),
      m_areaTotal(areaTotal), m_areaLiving(areaLiving), m_areaKitchen(areaKitchen),
      m_rooms(rooms), m_floor(floor), m_floorsTotal(floorsTotal),
      m_type(type), m_status(status),
      m_createdAt(std::time(nullptr)), m_updatedAt(std::time(nullptr))
{
    std::strncpy(m_title, title.c_str(), sizeof(m_title) - 1);
    m_title[sizeof(m_title) - 1] = '\0';

    std::strncpy(m_description, description.c_str(), sizeof(m_description) - 1);
    m_description[sizeof(m_description) - 1] = '\0';

    std::strncpy(m_address, address.c_str(), sizeof(m_address) - 1);
    m_address[sizeof(m_address) - 1] = '\0';
}

void Property::serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&m_id), sizeof(m_id));
    ofs.write(reinterpret_cast<const char*>(&m_realtorId), sizeof(m_realtorId));
    ofs.write(reinterpret_cast<const char*>(m_title), sizeof(m_title));
    ofs.write(reinterpret_cast<const char*>(m_description), sizeof(m_description));
    ofs.write(reinterpret_cast<const char*>(m_address), sizeof(m_address));
    ofs.write(reinterpret_cast<const char*>(&m_price), sizeof(m_price));
    ofs.write(reinterpret_cast<const char*>(&m_areaTotal), sizeof(m_areaTotal));
    ofs.write(reinterpret_cast<const char*>(&m_areaLiving), sizeof(m_areaLiving));
    ofs.write(reinterpret_cast<const char*>(&m_areaKitchen), sizeof(m_areaKitchen));
    ofs.write(reinterpret_cast<const char*>(&m_rooms), sizeof(m_rooms));
    ofs.write(reinterpret_cast<const char*>(&m_floor), sizeof(m_floor));
    ofs.write(reinterpret_cast<const char*>(&m_floorsTotal), sizeof(m_floorsTotal));
    ofs.write(reinterpret_cast<const char*>(&m_type), sizeof(m_type));
    ofs.write(reinterpret_cast<const char*>(&m_status), sizeof(m_status));
    ofs.write(reinterpret_cast<const char*>(&m_createdAt), sizeof(m_createdAt));
    ofs.write(reinterpret_cast<const char*>(&m_updatedAt), sizeof(m_updatedAt));
}

void Property::deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    ifs.read(reinterpret_cast<char*>(&m_realtorId), sizeof(m_realtorId));
    ifs.read(reinterpret_cast<char*>(m_title), sizeof(m_title));
    ifs.read(reinterpret_cast<char*>(m_description), sizeof(m_description));
    ifs.read(reinterpret_cast<char*>(m_address), sizeof(m_address));
    ifs.read(reinterpret_cast<char*>(&m_price), sizeof(m_price));
    ifs.read(reinterpret_cast<char*>(&m_areaTotal), sizeof(m_areaTotal));
    ifs.read(reinterpret_cast<char*>(&m_areaLiving), sizeof(m_areaLiving));
    ifs.read(reinterpret_cast<char*>(&m_areaKitchen), sizeof(m_areaKitchen));
    ifs.read(reinterpret_cast<char*>(&m_rooms), sizeof(m_rooms));
    ifs.read(reinterpret_cast<char*>(&m_floor), sizeof(m_floor));
    ifs.read(reinterpret_cast<char*>(&m_floorsTotal), sizeof(m_floorsTotal));
    ifs.read(reinterpret_cast<char*>(&m_type), sizeof(m_type));
    ifs.read(reinterpret_cast<char*>(&m_status), sizeof(m_status));
    ifs.read(reinterpret_cast<char*>(&m_createdAt), sizeof(m_createdAt));
    ifs.read(reinterpret_cast<char*>(&m_updatedAt), sizeof(m_updatedAt));
}

unsigned int Property::getId() const { return m_id; }
unsigned int Property::getRealtorId() const { return m_realtorId; }
const char* Property::getTitle() const { return m_title; }
const char* Property::getDescription() const { return m_description; }
const char* Property::getAddress() const { return m_address; }
float Property::getPrice() const { return m_price; }
float Property::getAreaTotal() const { return m_areaTotal; }
float Property::getAreaLiving() const { return m_areaLiving; }
float Property::getAreaKitchen() const { return m_areaKitchen; }
unsigned int Property::getRooms() const { return m_rooms; }
unsigned int Property::getFloor() const { return m_floor; }
unsigned int Property::getFloorsTotal() const { return m_floorsTotal; }
PropertyType Property::getType() const { return m_type; }
Status Property::getStatus() const { return m_status; }
std::time_t Property::getCreatedAt() const { return m_createdAt; }
std::time_t Property::getUpdatedAt() const { return m_updatedAt; }

void Property::setId(unsigned int id)
{
    m_id = id;
}

void Property::setTitle(const std::string& title) {
    std::strncpy(m_title, title.c_str(), sizeof(m_title) - 1);
    m_title[sizeof(m_title) - 1] = '\0';
}
void Property::setDescription(const std::string& description) {
    std::strncpy(m_description, description.c_str(), sizeof(m_description) - 1);
    m_description[sizeof(m_description) - 1] = '\0';
}
void Property::setAddress(const std::string& address) {
    std::strncpy(m_address, address.c_str(), sizeof(m_address) - 1);
    m_address[sizeof(m_address) - 1] = '\0';
}
void Property::setPrice(float price) { m_price = static_cast<float>(price); }

void Property::setAreaTotal(float area) { m_areaTotal = area; }
void Property::setAreaLiving(float area) { m_areaLiving = area; }
void Property::setAreaKitchen(float area) { m_areaKitchen = area; }
void Property::setRooms(unsigned int rooms) { m_rooms = rooms; }
void Property::setFloor(unsigned int floor) { m_floor = floor; }
void Property::setFloorsTotal(unsigned int floors) { m_floorsTotal = floors; }
void Property::setType(PropertyType type) { m_type = type; }
void Property::setStatus(Status status) { m_status = status; }
void Property::setRealtorId(unsigned int realtorId) { m_realtorId = realtorId; }
void Property::setCreatedAt(std::time_t createdAt) { m_createdAt = createdAt; }
void Property::setUpdatedAt(std::time_t updatedAt) { m_updatedAt = updatedAt; }

template<typename T>
std::string create_err_msg(const std::string& msg, const T& min, const T& max)
{
    return msg + " от " + std::to_string(min) + " до " + std::to_string(max);
}

std::string create_str_err_msg(std::size_t maxCount) {
    return "Ошибка. Необходимо ввести строку не превышающую "
        + std::to_string(maxCount) + " символов";
}

Property Property::create(unsigned int id, unsigned int realtorId)
{
    using namespace prop_config;

    Property prop;

    prop.m_id = id;
    prop.m_realtorId = realtorId;

    prop.m_rooms = InputReader::read<unsigned int>(
        ROOMS_MIN, ROOMS_MAX,
        "Введите количество комнат: ",
        create_err_msg(input_config::ERR_UINT, ROOMS_MIN, ROOMS_MAX));

    std::string title = InputReader::read<std::string>(
        TITLE_MAX_LEN - 1,
        "Введите заголовок объявления: ",
        create_str_err_msg(TITLE_MAX_LEN - 1));
    std::strncpy(prop.m_title, title.c_str(), TITLE_MAX_LEN);

    std::string description = InputReader::read<std::string>(
        DESCRIPTION_MAX_LEN - 1,
        "Введите описание: ",
        create_str_err_msg(DESCRIPTION_MAX_LEN - 1));
    std::strncpy(prop.m_description, description.c_str(), DESCRIPTION_MAX_LEN);

    std::string address = InputReader::read<std::string>(
        ADDRESS_MAX_LEN - 1,
        "Введите адрес: ",
        create_str_err_msg(ADDRESS_MAX_LEN - 1));
    std::strncpy(prop.m_address, address.c_str(), ADDRESS_MAX_LEN);

    prop.m_price = InputReader::read<float>(
        PRICE_MIN, PRICE_MAX,
        "Введите цену (BYN): ",
        create_err_msg(input_config::ERR_FLOAT, PRICE_MIN, PRICE_MAX));

    // площади с проверкой
    while (true) {
        prop.m_areaTotal = InputReader::read<float>(
            AREA_TOTAL_MIN, AREA_TOTAL_MAX,
            "Введите общую площадь (кв. м): ",
            create_err_msg(float_error, AREA_TOTAL_MIN, AREA_TOTAL_MAX));

        prop.m_areaLiving = InputReader::read<float>(
            AREA_LIVING_MIN, AREA_LIVING_MAX,
            "Введите жилую площадь (кв. м): ",
            create_err_msg(float_error, AREA_LIVING_MIN, AREA_LIVING_MAX));

        if (prop.m_areaLiving <= prop.m_areaTotal) break;
        std::cout << "Ошибка. Жилая площадь не может превышать общую!" << std::endl;
    }

    prop.m_areaKitchen = InputReader::read<float>(
        AREA_KITCHEN_MIN, AREA_KITCHEN_MAX,
        "Введите площадь кухни (кв. м): ",
        create_err_msg(float_error, AREA_KITCHEN_MIN, AREA_KITCHEN_MAX));

    // этажи с проверкой
    while (true) {
        prop.m_floorsTotal = InputReader::read<unsigned int>(
            FLOORS_TOTAL_MIN, FLOORS_TOTAL_MAX,
            "Введите количество этажей в доме: ",
            create_err_msg(uint_error, FLOORS_TOTAL_MIN, FLOORS_TOTAL_MAX));

        prop.m_floor = InputReader::read<unsigned int>(
            FLOOR_MIN, FLOOR_MAX,
            "Введите этаж: ",
            create_err_msg(uint_error, FLOOR_MIN, FLOOR_MAX));

        if (prop.m_floor <= prop.m_floorsTotal) break;
        std::cout << "Ошибка. Этаж не может быть больше количества этажей!" << std::endl;
    }

    // тип недвижимости
    std::cout << "Выберите тип недвижимости:\n";
    std::cout << "1 - Квартира\n";
    std::cout << "2 - Дом\n";
    std::cout << "3 - Офис\n";
    std::cout << "4 - Земельный участок\n";

    int typeChoice = InputReader::read<int>(
        1, 4,
        ">",
        create_err_msg(input_config::ERR_INT, 1, 4));
    prop.m_type = static_cast<PropertyType>(typeChoice - 1);

    prop.m_status = Status::Active;
    prop.m_createdAt = std::time(nullptr);
    prop.m_updatedAt = std::time(nullptr);

    return prop;
}

std::ostream& operator<<(std::ostream& out, const Property& prop)
{
    out << "=== Объявление недвижимости ===\n";
    out << "ID: " << prop.getId() << "\n";
    out << "Риэлтор ID: " << prop.getRealtorId() << "\n";
    out << "Заголовок: " << prop.getTitle() << "\n";
    out << "Описание: " << prop.getDescription() << "\n";
    out << "Адрес: " << prop.getAddress() << "\n";
    out << "Цена: " << std::fixed << std::setprecision(2) << prop.getPrice() << " BYN\n";
    out << "Комнат: " << prop.getRooms() << "\n";
    out << "Этаж: " << prop.getFloor() << " из " << prop.getFloorsTotal() << "\n";
    out << "Общая площадь: " << prop.getAreaTotal() << " кв.м\n";
    out << "Жилая площадь: " << prop.getAreaLiving() << " кв.м\n";
    out << "Площадь кухни: " << prop.getAreaKitchen() << " кв.м\n";

    // Тип недвижимости
    out << "Тип: ";
    switch (prop.getType()) {
    case PropertyType::Apartment: out << "Квартира"; break;
    case PropertyType::House:     out << "Дом"; break;
    case PropertyType::Office:    out << "Офис"; break;
    case PropertyType::Land:      out << "Земельный участок"; break;
    }
    out << "\n";

    // Статус
    out << "Статус: ";
    switch (prop.getStatus()) {
    case Status::Active:   out << "Активно"; break;
    case Status::Sold:     out << "Продано"; break;
    case Status::Rented:   out << "Сдано в аренду"; break;
    case Status::Archived: out << "Архивировано"; break;
    }
    out << "\n";

    // Даты
    std::time_t created = prop.getCreatedAt();
    std::time_t updated = prop.getUpdatedAt();

    out << "Создано: " << std::ctime(&created);
    out << "Обновлено: " << std::ctime(&updated);

    return out;
}
