#include "Property.h"
#include <cstring>
#include "../ui/InputReader.h"
#include <iostream>
#include <iomanip>

using namespace prop_cfg;

Property::Property()
    : m_id(0), m_realtorId(0), m_clientId(0), m_price(0.0f),
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
                   unsigned int realtorId,
                   unsigned int clientId)
    : m_id(id), m_realtorId(realtorId), m_clientId(), m_price(static_cast<float>(price)),
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
    ofs.write(reinterpret_cast<const char*>(&m_clientId), sizeof(m_clientId));
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

    ofs.write(reinterpret_cast<const char*>(m_seller.name()), common_cfg::NAME_MAX_LEN);
    ofs.write(reinterpret_cast<const char*>(m_seller.email()), common_cfg::EMAIL_MAX_LEN);
    ofs.write(reinterpret_cast<const char*>(m_seller.phone()), common_cfg::PHONE_MAX_LEN);
}

void Property::deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    ifs.read(reinterpret_cast<char*>(&m_realtorId), sizeof(m_realtorId));
    ifs.read(reinterpret_cast<char*>(&m_clientId), sizeof(m_clientId));
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

    char name[common_cfg::NAME_MAX_LEN];
    char email[common_cfg::EMAIL_MAX_LEN];
    char phone[common_cfg::PHONE_MAX_LEN];

    ifs.read(reinterpret_cast<char*>(name), common_cfg::NAME_MAX_LEN);
    ifs.read(reinterpret_cast<char*>(email), common_cfg::EMAIL_MAX_LEN);
    ifs.read(reinterpret_cast<char*>(phone), common_cfg::PHONE_MAX_LEN);

    m_seller.set_name(std::string(name));
    m_seller.set_email(std::string(email));
    m_seller.set_phone(std::string(phone));
}

Seller Property::getSeller() const { return m_seller; }
void Property::setSeller(const Seller& seller) { m_seller = seller; }


unsigned int Property::getId() const { return m_id; }
unsigned int Property::getRealtorId() const { return m_realtorId; }
unsigned int Property::getClientId() const { return m_clientId; }
unsigned int Property::getRooms() const { return m_rooms; }
unsigned int Property::getFloor() const { return m_floor; }
unsigned int Property::getFloorsTotal() const { return m_floorsTotal; }

const char* Property::getTitle() const { return m_title; }
const char* Property::getDescription() const { return m_description; }
const char* Property::getAddress() const { return m_address; }

float Property::getPrice() const { return m_price; }
float Property::getAreaTotal() const { return m_areaTotal; }
float Property::getAreaLiving() const { return m_areaLiving; }
float Property::getAreaKitchen() const { return m_areaKitchen; }

PropertyType Property::getType() const { return m_type; }
Status Property::getStatus() const { return m_status; }
std::time_t Property::getCreatedAt() const { return m_createdAt; }
std::time_t Property::getUpdatedAt() const { return m_updatedAt; }

void Property::setId(unsigned int id) { m_id = id; }
void Property::setClientId(unsigned int id) { m_clientId = id; }
void Property::setRealtorId(unsigned int realtorId) { m_realtorId = realtorId; }
void Property::setRooms(unsigned int rooms) { m_rooms = rooms; }
void Property::setFloor(unsigned int floor) { m_floor = floor; }
void Property::setFloorsTotal(unsigned int floors) { m_floorsTotal = floors; }

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

void Property::setType(PropertyType type) { m_type = type; }
void Property::setStatus(Status status) { m_status = status; }
void Property::setCreatedAt(std::time_t createdAt) { m_createdAt = createdAt; }
void Property::setUpdatedAt(std::time_t updatedAt) { m_updatedAt = updatedAt; }


std::string Property::readTitle() {
     return InputReader::read<std::string>(
        TITLE_MAX_LEN - 1,
        "Введите заголовок объявления: ",
        TITLE_ERR_MSG);
}
std::string Property::readDescription() {
    return InputReader::read<std::string>(
        DESCRIPTION_MAX_LEN - 1,
        "Введите описание: ",
        DESCRIPTION_ERR_MSG);
}
std::string Property::readAddress() {
    return InputReader::read<std::string>(
        ADDRESS_MAX_LEN - 1,
        "Введите адрес: ",
        ADDRESS_ERR_MSG);
}

float Property::readPrice() {
    return InputReader::read<float>(
        PRICE_MIN, PRICE_MAX,
        "Введите цену (BYN): ",
        PRICE_ERR_MSG);
}
float Property::readAreaTotal() {
    return InputReader::read<float>(
        AREA_TOTAL_MIN, AREA_TOTAL_MAX,
        "Введите общую площадь (кв. м): ",
        AREA_TOTAL_ERR_MSG);
}
float Property::readAreaLiving(float max_area) {
    while (true) {
        float living = InputReader::read<float>(
            AREA_LIVING_MIN, AREA_LIVING_MAX,
            "Введите жилую площадь (кв. м): ",
            AREA_LIVING_ERR_MSG);
        if (living <= max_area) return living;
        std::cout << "Ошибка. Жилая площадь не может превышать " << max_area << " (кв. м)" << std::endl;
    }
}
float Property::readAreaKitchen(float max_area) {
    while (true) {
        float kitchen = InputReader::read<float>(
            AREA_KITCHEN_MIN, AREA_KITCHEN_MAX,
            "Введите площадь кухни (кв. м): ",
            AREA_KITCHEN_ERR_MSG);

        if (kitchen <= max_area) return kitchen;

        std::cout << "Ошибка. Площадь кухни не может превышать " << max_area << " (кв. м)" << std::endl;
    }
}

unsigned int Property::readRooms() {
    return InputReader::read<unsigned int>(
        ROOMS_MIN, ROOMS_MAX,
        "Введите количество комнат: ",
        ROOMS_ERR_MSG);
}
unsigned int Property::readFloorsTotal() {
    return InputReader::read<unsigned int>(
        FLOORS_TOTAL_MIN, FLOORS_TOTAL_MAX,
        "Введите количество этажей в доме: ",
        FLOORS_TOTAL_ERR_MSG);
}
unsigned int Property::readFloor(unsigned int floorsTotal) {
    while (true) {
        unsigned int floor = InputReader::read<unsigned int>(
            FLOOR_MIN, FLOOR_MAX,
            "Введите этаж: ",
            FLOOR_ERR_MSG);
        if (floor <= floorsTotal) return floor;
        std::cout << "Ошибка. Этаж не может быть больше количества этажей" << std::endl;
    }
}

PropertyType Property::readType() {
    std::cout << "Выберите тип недвижимости:\n";
    std::cout << "1 - Квартира\n";
    std::cout << "2 - Дом\n";
    std::cout << "3 - Офис\n";
    std::cout << "4 - Земельный участок\n";

    int typeChoice = InputReader::read<int>(
        TYPE_MIN, TYPE_MAX,
        ">", TYPE_ERR_MSG);

    return static_cast<PropertyType>(typeChoice - 1);
}
Status Property::readStatus() {
    std::cout << "Выберите статус объявления:\n";
    std::cout << "1 - Активно\n";
    std::cout << "2 - Продано\n";
    std::cout << "3 - Сдано в аренду\n";
    std::cout << "4 - Архивировано\n";

    int choice = InputReader::read<int>(
        STATUS_MIN, STATUS_MAX,
        ">", STATUS_ERR_MSG);

    return static_cast<Status>(choice - 1);
}

Property Property::create(unsigned int id, unsigned int realtorId) {
    Property prop;

    prop.m_id = id;
    prop.m_realtorId = realtorId;

    prop.setTitle(readTitle());
    prop.setDescription(readDescription());
    prop.setAddress(readAddress());

    prop.m_price = readPrice();
    prop.m_areaTotal = readAreaTotal();
    prop.m_areaLiving = readAreaLiving(prop.m_areaTotal);
    prop.m_areaKitchen = readAreaKitchen(prop.m_areaTotal - prop.m_areaLiving);

    prop.m_rooms = readRooms();
    prop.m_floorsTotal = readFloorsTotal();
    prop.m_floor = readFloor(prop.m_floorsTotal);

    prop.m_type = readType();

    prop.m_status = Status::Active;
    prop.m_createdAt = std::time(nullptr);
    prop.m_updatedAt = std::time(nullptr);

    std::cout << "\nДанные продавца:\n";
    std::string sellerName = Seller::read_name();
    std::string sellerEmail = Seller::read_email();
    std::string sellerPhone = Seller::read_phone();
    Seller seller(sellerName, sellerEmail, sellerPhone);
    prop.setSeller(seller);

    return prop;
}

std::vector<std::string> Property::to_lines() const {
    std::vector<std::string> lines;
    lines.reserve(16);

    lines.push_back("ID: " + std::to_string(getId()));
    lines.push_back("Риэлтор ID: " + std::to_string(getRealtorId()));
    lines.push_back("Заголовок: " + std::string(getTitle()));
    lines.push_back("Описание: " + std::string(getDescription()));
    lines.push_back("Адрес: " + std::string(getAddress()));

    lines.push_back("Цена: " + std::to_string(getPrice()) + " BYN");

    lines.push_back("Комнат: " + std::to_string(getRooms()));
    lines.push_back("Этаж: " + std::to_string(getFloor()) + " из " + std::to_string(getFloorsTotal()));
    lines.push_back("Общая площадь: " + std::to_string(getAreaTotal()) + " кв.м");
    lines.push_back("Жилая площадь: " + std::to_string(getAreaLiving()) + " кв.м");
    lines.push_back("Площадь кухни: " + std::to_string(getAreaKitchen()) + " кв.м");

    // Тип
    std::string typeStr = "Тип: ";
    switch (getType()) {
    case PropertyType::Apartment: typeStr += "Квартира"; break;
    case PropertyType::House:     typeStr += "Дом"; break;
    case PropertyType::Office:    typeStr += "Офис"; break;
    case PropertyType::Land:      typeStr += "Земельный участок"; break;
    }
    lines.push_back(typeStr);

    // Статус
    std::string statusStr = "Статус: ";
    switch (getStatus()) {
    case Status::Active:   statusStr += "Активно"; break;
    case Status::Sold:     statusStr += "Продано"; break;
    case Status::Rented:   statusStr += "Сдано в аренду"; break;
    case Status::Archived: statusStr += "Архивировано"; break;
    }
    lines.push_back(statusStr);

    // Даты
    std::time_t created = getCreatedAt();
    std::time_t updated = getUpdatedAt();
    lines.push_back("Создано: " + std::string(std::ctime(&created)));
    lines.push_back("Обновлено: " + std::string(std::ctime(&updated)));

    auto sellerLines = m_seller.to_lines();
    lines.insert(lines.end(), sellerLines.begin(), sellerLines.end());

    return lines;
}

std::string Property::to_str() const {
    auto lines = to_lines();
    std::string result;
    result.reserve(512);

    for (const auto& line : lines) {
        result += line;
        if (line.empty() || line.back() != '\n') {
            result += "\n";
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Property& prop) {
    return os << prop.to_str();
}

#include <sstream>

std::string Property::to_row(const std::vector<size_t>& sizes) const {
    std::ostringstream oss;
    oss << "|";

    // все поля Property в строковом виде
    std::vector<std::string> fields = {
        std::to_string(m_id),
        std::to_string(m_realtorId),
        std::to_string(m_clientId),
        std::string(m_title),
        std::string(m_description),
        std::string(m_address),
        std::to_string(m_price),
        std::to_string(m_areaTotal),
        std::to_string(m_areaLiving),
        std::to_string(m_areaKitchen),
        std::to_string(m_rooms),
        std::to_string(m_floor),
        std::to_string(m_floorsTotal),
        std::to_string(static_cast<int>(m_type)),
        std::to_string(static_cast<int>(m_status)),
        std::to_string(m_createdAt),
        std::to_string(m_updatedAt),
        m_seller.name(),
        m_seller.email(),
        m_seller.phone()
    };

    // вывод с учётом ширины колонок
    for (size_t i = 0; i < fields.size() && i < sizes.size(); ++i) {
        oss << std::left << std::setw(sizes[i]) << fields[i] << "|";
    }

    return oss.str();
}