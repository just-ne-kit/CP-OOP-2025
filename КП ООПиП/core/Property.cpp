#include "Property.h"
#include <cstring>

// --- Конструктор по умолчанию ---
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
    m_currency[0] = '\0';
}

// --- Конструктор с параметрами ---
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

    std::strncpy(m_currency, currency.c_str(), sizeof(m_currency) - 1);
    m_currency[sizeof(m_currency) - 1] = '\0';
}

// --- Сериализация ---
void Property::serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&m_id), sizeof(m_id));
    ofs.write(reinterpret_cast<const char*>(&m_realtorId), sizeof(m_realtorId));
    ofs.write(reinterpret_cast<const char*>(m_title), sizeof(m_title));
    ofs.write(reinterpret_cast<const char*>(m_description), sizeof(m_description));
    ofs.write(reinterpret_cast<const char*>(m_address), sizeof(m_address));
    ofs.write(reinterpret_cast<const char*>(m_currency), sizeof(m_currency));
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

// --- Десериализация ---
void Property::deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    ifs.read(reinterpret_cast<char*>(&m_realtorId), sizeof(m_realtorId));
    ifs.read(reinterpret_cast<char*>(m_title), sizeof(m_title));
    ifs.read(reinterpret_cast<char*>(m_description), sizeof(m_description));
    ifs.read(reinterpret_cast<char*>(m_address), sizeof(m_address));
    ifs.read(reinterpret_cast<char*>(m_currency), sizeof(m_currency));
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

// --- Геттеры ---
unsigned int Property::getId() const { return m_id; }
unsigned int Property::getRealtorId() const { return m_realtorId; }
const char* Property::getTitle() const { return m_title; }
const char* Property::getDescription() const { return m_description; }
const char* Property::getAddress() const { return m_address; }
double Property::getPrice() const { return m_price; }
const char* Property::getCurrency() const { return m_currency; }
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

// --- Сеттеры ---
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
void Property::setPrice(double price) { m_price = static_cast<float>(price); }
void Property::setCurrency(const std::string& currency) {
    std::strncpy(m_currency, currency.c_str(), sizeof(m_currency) - 1);
    m_currency[sizeof(m_currency) - 1] = '\0';
}
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
