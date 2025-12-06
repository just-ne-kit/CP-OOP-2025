#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <memory>
#include "config.h"
#include "Seller.h"

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
    
    char m_title[prop_cfg::TITLE_MAX_LEN];               // Заголовок объявления
    char m_description[prop_cfg::DESCRIPTION_MAX_LEN];   // Описание
    char m_address[prop_cfg::ADDRESS_MAX_LEN];           // Адрес
    
    float m_price;                                          // Цена
    float m_areaTotal;                                      // Общая площадь
    float m_areaLiving;                                     // Жилая площадь
    float m_areaKitchen;                                    // Площадь кухни
    
    unsigned int m_rooms;                                   // Количество комнат
    unsigned int m_floor;                                   // Этаж
    unsigned int m_floorsTotal;                             // Всего этажей в доме
    
    std::time_t m_createdAt;                                // Дата создания
    std::time_t m_updatedAt;                                // Дата обновления
    
    PropertyType m_type;                                    // Тип недвижимости
    Status m_status;                                        // Статус объявления
    Seller m_seller;

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

    static unsigned int readRooms();
    static std::string readTitle();
    static std::string readDescription();
    static std::string readAddress();
    static float readPrice();
    static float readAreaTotal();
    static float readAreaLiving(float areaTotal);
    static float readAreaKitchen(float areaTotal);
    static unsigned int readFloorsTotal();
    static unsigned int readFloor(unsigned int floorsTotal);
    static PropertyType readType();
    static Status readStatus();

    static Property create(unsigned int id, unsigned int realtorId);

    std::vector<std::string> to_lines() const;
    std::string to_str() const;

    friend std::ostream& operator<<(std::ostream& out, const Property& prop);
};

using PropertyPtr = std::shared_ptr<Property>;