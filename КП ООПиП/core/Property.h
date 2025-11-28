#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstring>

namespace config
{
    const std::size_t TITLE_MAX_LEN = 64;
    const std::size_t DESCRIPTION_MAX_LEN = 256;
    const std::size_t ADDRESS_MAX_LEN = 128;

    const float PRICE_MIN = 0.0f;
    const float PRICE_MAX = 100'000'000.0f;

    const float AREA_TOTAL_MIN = 0.0f;
    const float AREA_TOTAL_MAX = 10'000.0f;

    const float AREA_LIVING_MIN = 0.0f;
    const float AREA_LIVING_MAX = 5'000.0f;

    const float AREA_KITCHEN_MIN = 0.0f;
    const float AREA_KITCHEN_MAX = 500.0f;

    const unsigned int ROOMS_MIN = 0;
    const unsigned int ROOMS_MAX = 100;

    const unsigned int FLOOR_MIN = 0;
    const unsigned int FLOOR_MAX = 200;

    const unsigned int FLOORS_TOTAL_MIN = 0;
    const unsigned int FLOORS_TOTAL_MAX = 200;
}

enum class PropertyType {
    Apartment,
    House,
    Office,
    Land
};

enum class Status {
    Active,
    Sold,
    Rented,
    Archived
};

class Property {
private:
    unsigned int m_id;                                      // ID
    unsigned int m_realtorId;                               // ID риэлтора
    char m_title[config::TITLE_MAX_LEN];                    // Заголовок объявления
    char m_description[config::DESCRIPTION_MAX_LEN];        // Описание
    char m_address[config::ADDRESS_MAX_LEN];                // Адрес
    float m_price;                                          // Цена
    float m_areaTotal;                                      // Общая площадь
    float m_areaLiving;                                     // Жилая площадь
    float m_areaKitchen;                                    // Площадь кухни
    unsigned int m_rooms;                                   // Количество комнат
    unsigned int m_floor;                                   // Этаж
    unsigned int m_floorsTotal;                             // Всего этажей в доме
    PropertyType m_type;                                    // Тип недвижимости
    Status m_status;                                        // Статус объявления
    std::time_t m_createdAt;                                // Дата создания
    std::time_t m_updatedAt;                                // Дата обновления

public:
    Property();
    Property(unsigned int id,
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
             unsigned int realtorId);

    void serialize(std::ofstream& ofs) const;
    void deserialize(std::ifstream& ifs);

    unsigned int getId() const;
    unsigned int getRealtorId() const;
    const char* getTitle() const;
    const char* getDescription() const;
    const char* getAddress() const;
    float getPrice() const;
    float getAreaTotal() const;
    float getAreaLiving() const;
    float getAreaKitchen() const;
    unsigned int getRooms() const;
    unsigned int getFloor() const;
    unsigned int getFloorsTotal() const;
    PropertyType getType() const;
    Status getStatus() const;
    std::time_t getCreatedAt() const;
    std::time_t getUpdatedAt() const;

    void setId(unsigned int id);
    void setRealtorId(unsigned int id);
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setAddress(const std::string& address);
    void setPrice(float price);
    void setAreaTotal(float area);
    void setAreaLiving(float area);
    void setAreaKitchen(float area);
    void setRooms(unsigned int rooms);
    void setFloor(unsigned int floor);
    void setFloorsTotal(unsigned int floors);
    void setType(PropertyType type);
    void setStatus(Status status);
    void setCreatedAt(std::time_t createdAt);
    void setUpdatedAt(std::time_t updatedAt);

    static Property create(unsigned int id, unsigned int realtorId);
};
