#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstring>

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
    unsigned int m_id;                // Уникальный ID
    unsigned int m_realtorId;         // ID владельца/риэлтора
    char m_title[32];                 // Заголовок объявления
    char m_description[32];           // Описание
    char m_address[32];               // Адрес
    char m_currency[4];               // Валюта (BYN, USD, EUR)
    float m_price;                    // Цена
    float m_areaTotal;                // Общая площадь
    float m_areaLiving;               // Жилая площадь
    float m_areaKitchen;              // Площадь кухни
    unsigned int m_rooms;             // Количество комнат
    unsigned int m_floor;             // Этаж
    unsigned int m_floorsTotal;       // Всего этажей в доме
    PropertyType m_type;              // Тип недвижимости
    Status m_status;                  // Статус объявления
    std::time_t m_createdAt;          // Дата создания
    std::time_t m_updatedAt;          // Дата обновления

public:
    // --- Конструкторы ---
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

    // --- Сериализация / десериализация ---
    void serialize(std::ofstream& ofs) const;
    void deserialize(std::ifstream& ifs);

    // --- Геттеры ---
    unsigned int getId() const;
    unsigned int getRealtorId() const;
    const char* getTitle() const;
    const char* getDescription() const;
    const char* getAddress() const;
    double getPrice() const;
    const char* getCurrency() const;
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

    // --- Сеттеры ---
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setAddress(const std::string& address);
    void setPrice(double price);
    void setCurrency(const std::string& currency);
    void setAreaTotal(float area);
    void setAreaLiving(float area);
    void setAreaKitchen(float area);
    void setRooms(unsigned int rooms);
    void setFloor(unsigned int floor);
    void setFloorsTotal(unsigned int floors);
    void setType(PropertyType type);
    void setStatus(Status status);
    void setRealtorId(unsigned int realtorId);
    void setCreatedAt(std::time_t createdAt);
    void setUpdatedAt(std::time_t updatedAt);
};
