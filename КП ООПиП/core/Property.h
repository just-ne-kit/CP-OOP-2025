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
    unsigned int id_;                                
    unsigned int realtor_id_;                        
    unsigned int client_id_;                         

    char title_[prop_cfg::TITLE_MAX_LEN];            
    char description_[prop_cfg::DESCRIPTION_MAX_LEN];
    char address_[prop_cfg::ADDRESS_MAX_LEN];        
    
    float price_;                                    
    float area_total_;                               
    float area_living_;                              
    float area_kitchen_;                             
    
    unsigned int rooms_;                            
    unsigned int floor_;                            
    unsigned int floors_total_;                      
    
    std::time_t created_at_;                         
    std::time_t updated_at_;                         
    
    PropertyType type_;                             
    Status status_;                                 
    Seller seller_;

public:
    Property();

    void serialize(std::ofstream& ofs) const;
    void deserialize(std::ifstream& ifs);

    unsigned int id() const;
    unsigned int realtor_id() const;
    unsigned int client_id() const;
    const char* title() const;
    const char* description() const;
    const char* address() const;
    float price() const;
    float area_total() const;
    float area_living() const;
    float area_kitchen() const;
    unsigned int rooms() const;
    unsigned int floor() const;
    unsigned int floors_total() const;
    PropertyType type() const;
    Status status() const;
    std::time_t created_at() const;
    std::time_t updated_at() const;
    Seller seller() const;

    void set_id(unsigned int id);
    void set_realtor_id(unsigned int id);
    void set_client_id(unsigned int id);
    void set_title(const std::string& title);
    void set_description(const std::string& description);
    void set_address(const std::string& address);
    void set_price(float price);
    void set_area_total(float area);
    void set_area_living(float area);
    void set_area_kitchen(float area);
    void set_rooms(unsigned int rooms);
    void set_floor(unsigned int floor);
    void set_floors_total(unsigned int floors);
    void set_type(PropertyType type);
    void set_status(Status status);
    void set_created_at(std::time_t created_at);
    void set_updated_at(std::time_t updated_at);
    void set_seller(const Seller& seller);

    static unsigned int read_rooms();
    static std::string read_title();
    static std::string read_description();
    static std::string read_address();
    static float read_price();
    static float read_area_total();
    static float read_area_living(float area_total);
    static float read_area_kitchen(float area_total);
    static unsigned int read_floors_total();
    static unsigned int read_floor(unsigned int floors_total);
    static PropertyType read_type();
    static Status read_status();

    static Property create(unsigned int id, unsigned int realtor_id);

    std::vector<std::string> to_lines() const;
    std::string to_str() const;

    friend std::ostream& operator<<(std::ostream& out, const Property& property);

    std::string to_row(const std::vector<size_t>& sizes) const;
};

using PropertyPtr = std::shared_ptr<Property>;