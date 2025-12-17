#include "Property.h"
#include <cstring>
#include "../ui/InputReader.h"
#include <iostream>
#include <iomanip>
#include "utils.h"

using namespace prop_cfg;

Property::Property()
    : id_(0), realtor_id_(0), client_id_(0), price_(0.0f),
      area_total_(0.0f), area_living_(0.0f), area_kitchen_(0.0f),
      rooms_(0), floor_(0), floors_total_(0),
      type_(PropertyType::Apartment), status_(Status::Active),
      created_at_(std::time(nullptr)), updated_at_(std::time(nullptr))
{
    title_[0] = '\0';
    description_[0] = '\0';
    address_[0] = '\0';
}

void Property::serialize(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&id_), sizeof(id_));
    ofs.write(reinterpret_cast<const char*>(&realtor_id_), sizeof(realtor_id_));
    ofs.write(reinterpret_cast<const char*>(&client_id_), sizeof(client_id_));
    ofs.write(reinterpret_cast<const char*>(title_), sizeof(title_));
    ofs.write(reinterpret_cast<const char*>(description_), sizeof(description_));
    ofs.write(reinterpret_cast<const char*>(address_), sizeof(address_));
    ofs.write(reinterpret_cast<const char*>(&price_), sizeof(price_));
    ofs.write(reinterpret_cast<const char*>(&area_total_), sizeof(area_total_));
    ofs.write(reinterpret_cast<const char*>(&area_living_), sizeof(area_living_));
    ofs.write(reinterpret_cast<const char*>(&area_kitchen_), sizeof(area_kitchen_));
    ofs.write(reinterpret_cast<const char*>(&rooms_), sizeof(rooms_));
    ofs.write(reinterpret_cast<const char*>(&floor_), sizeof(floor_));
    ofs.write(reinterpret_cast<const char*>(&floors_total_), sizeof(floors_total_));
    ofs.write(reinterpret_cast<const char*>(&type_), sizeof(type_));
    ofs.write(reinterpret_cast<const char*>(&status_), sizeof(status_));
    ofs.write(reinterpret_cast<const char*>(&created_at_), sizeof(created_at_));
    ofs.write(reinterpret_cast<const char*>(&updated_at_), sizeof(updated_at_));

    ofs.write(reinterpret_cast<const char*>(seller_.name()), common_cfg::NAME_MAX_LEN);
    ofs.write(reinterpret_cast<const char*>(seller_.email()), common_cfg::EMAIL_MAX_LEN);
    ofs.write(reinterpret_cast<const char*>(seller_.phone()), common_cfg::PHONE_MAX_LEN);
}

void Property::deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&id_), sizeof(id_));
    ifs.read(reinterpret_cast<char*>(&realtor_id_), sizeof(realtor_id_));
    ifs.read(reinterpret_cast<char*>(&client_id_), sizeof(client_id_));
    ifs.read(reinterpret_cast<char*>(title_), sizeof(title_));
    ifs.read(reinterpret_cast<char*>(description_), sizeof(description_));
    ifs.read(reinterpret_cast<char*>(address_), sizeof(address_));
    ifs.read(reinterpret_cast<char*>(&price_), sizeof(price_));
    ifs.read(reinterpret_cast<char*>(&area_total_), sizeof(area_total_));
    ifs.read(reinterpret_cast<char*>(&area_living_), sizeof(area_living_));
    ifs.read(reinterpret_cast<char*>(&area_kitchen_), sizeof(area_kitchen_));
    ifs.read(reinterpret_cast<char*>(&rooms_), sizeof(rooms_));
    ifs.read(reinterpret_cast<char*>(&floor_), sizeof(floor_));
    ifs.read(reinterpret_cast<char*>(&floors_total_), sizeof(floors_total_));
    ifs.read(reinterpret_cast<char*>(&type_), sizeof(type_));
    ifs.read(reinterpret_cast<char*>(&status_), sizeof(status_));
    ifs.read(reinterpret_cast<char*>(&created_at_), sizeof(created_at_));
    ifs.read(reinterpret_cast<char*>(&updated_at_), sizeof(updated_at_));

    char name[common_cfg::NAME_MAX_LEN];
    char email[common_cfg::EMAIL_MAX_LEN];
    char phone[common_cfg::PHONE_MAX_LEN];

    ifs.read(reinterpret_cast<char*>(name), common_cfg::NAME_MAX_LEN);
    ifs.read(reinterpret_cast<char*>(email), common_cfg::EMAIL_MAX_LEN);
    ifs.read(reinterpret_cast<char*>(phone), common_cfg::PHONE_MAX_LEN);

    seller_.set_name(std::string(name));
    seller_.set_email(std::string(email));
    seller_.set_phone(std::string(phone));
}

Seller Property::seller() const { return seller_; }
void Property::set_seller(const Seller& seller) { seller_ = seller; }


unsigned int Property::id() const { return id_; }
unsigned int Property::realtor_id() const { return realtor_id_; }
unsigned int Property::client_id() const { return client_id_; }
unsigned int Property::rooms() const { return rooms_; }
unsigned int Property::floor() const { return floor_; }
unsigned int Property::floors_total() const { return floors_total_; }

const char* Property::title() const { return title_; }
const char* Property::description() const { return description_; }
const char* Property::address() const { return address_; }

float Property::price() const { return price_; }
float Property::area_total() const { return area_total_; }
float Property::area_living() const { return area_living_; }
float Property::area_kitchen() const { return area_kitchen_; }

PropertyType Property::type() const { return type_; }
Status Property::status() const { return status_; }
std::time_t Property::created_at() const { return created_at_; }
std::time_t Property::updated_at() const { return updated_at_; }

void Property::set_id(unsigned int id) { id_ = id; }
void Property::set_client_id(unsigned int id) { client_id_ = id; }
void Property::set_realtor_id(unsigned int realtorId) { realtor_id_ = realtorId; }
void Property::set_rooms(unsigned int rooms) { rooms_ = rooms; }
void Property::set_floor(unsigned int floor) { floor_ = floor; }
void Property::set_floors_total(unsigned int floors) { floors_total_ = floors; }

void Property::set_title(const std::string& title) {
    std::strncpy(title_, title.c_str(), sizeof(title_) - 1);
    title_[sizeof(title_) - 1] = '\0';
}
void Property::set_description(const std::string& description) {
    std::strncpy(description_, description.c_str(), sizeof(description_) - 1);
    description_[sizeof(description_) - 1] = '\0';
}
void Property::set_address(const std::string& address) {
    std::strncpy(address_, address.c_str(), sizeof(address_) - 1);
    address_[sizeof(address_) - 1] = '\0';
}

void Property::set_price(float price) { price_ = static_cast<float>(price); }
void Property::set_area_total(float area) { area_total_ = area; }
void Property::set_area_living(float area) { area_living_ = area; }
void Property::set_area_kitchen(float area) { area_kitchen_ = area; }

void Property::set_type(PropertyType type) { type_ = type; }
void Property::set_status(Status status) { status_ = status; }
void Property::set_created_at(std::time_t createdAt) { created_at_ = createdAt; }
void Property::set_updated_at(std::time_t updatedAt) { updated_at_ = updatedAt; }


std::string Property::read_title() {
     return InputReader::read<std::string>(
        TITLE_MAX_LEN - 1,
        "Введите заголовок объявления: ",
        TITLE_ERR_MSG);
}
std::string Property::read_description() {
    return InputReader::read<std::string>(
        DESCRIPTION_MAX_LEN - 1,
        "Введите описание: ",
        DESCRIPTION_ERR_MSG);
}
std::string Property::read_address() {
    return InputReader::read<std::string>(
        ADDRESS_MAX_LEN - 1,
        "Введите адрес: ",
        ADDRESS_ERR_MSG);
}

float Property::read_price() {
    return InputReader::read<float>(
        PRICE_MIN, PRICE_MAX,
        "Введите цену (BYN): ",
        PRICE_ERR_MSG);
}
float Property::read_area_total() {
    return InputReader::read<float>(
        AREA_TOTAL_MIN, AREA_TOTAL_MAX,
        "Введите общую площадь (кв. м): ",
        AREA_TOTAL_ERR_MSG);
}
float Property::read_area_living(float max_area) {
    while (true) {
        float living = InputReader::read<float>(
            AREA_LIVING_MIN, AREA_LIVING_MAX,
            "Введите жилую площадь (кв. м): ",
            AREA_LIVING_ERR_MSG);
        if (living <= max_area) return living;
        std::cout << "Ошибка. Жилая площадь не может превышать " << max_area << " (кв. м)" << std::endl;
    }
}
float Property::read_area_kitchen(float max_area) {
    while (true) {
        float kitchen = InputReader::read<float>(
            AREA_KITCHEN_MIN, AREA_KITCHEN_MAX,
            "Введите площадь кухни (кв. м): ",
            AREA_KITCHEN_ERR_MSG);

        if (kitchen <= max_area) return kitchen;

        std::cout << "Ошибка. Площадь кухни не может превышать " << max_area << " (кв. м)" << std::endl;
    }
}

unsigned int Property::read_rooms() {
    return InputReader::read<unsigned int>(
        ROOMS_MIN, ROOMS_MAX,
        "Введите количество комнат: ",
        ROOMS_ERR_MSG);
}
unsigned int Property::read_floors_total() {
    return InputReader::read<unsigned int>(
        FLOORS_TOTAL_MIN, FLOORS_TOTAL_MAX,
        "Введите количество этажей в доме: ",
        FLOORS_TOTAL_ERR_MSG);
}
unsigned int Property::read_floor(unsigned int floorsTotal) {
    while (true) {
        unsigned int floor = InputReader::read<unsigned int>(
            FLOOR_MIN, FLOOR_MAX,
            "Введите этаж: ",
            FLOOR_ERR_MSG);
        if (floor <= floorsTotal) return floor;
        std::cout << "Ошибка. Этаж не может быть больше количества этажей" << std::endl;
    }
}

PropertyType Property::read_type() {
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
Status Property::read_status() {
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

    prop.id_ = id;
    prop.realtor_id_ = realtorId;

    prop.set_title(read_title());
    prop.set_description(read_description());
    prop.set_address(read_address());

    prop.price_ = read_price();
    prop.area_total_ = read_area_total();
    prop.area_living_ = read_area_living(prop.area_total_);
    prop.area_kitchen_ = read_area_kitchen(prop.area_total_ - prop.area_living_);

    prop.rooms_ = read_rooms();
    prop.floors_total_ = read_floors_total();
    prop.floor_ = read_floor(prop.floors_total_);

    prop.type_ = read_type();

    prop.status_ = Status::Active;
    prop.created_at_ = std::time(nullptr);
    prop.updated_at_ = std::time(nullptr);

    std::cout << "\nДанные продавца:\n";
    Seller seller;
    std::cin >> seller;
    prop.set_seller(seller);

    return prop;
}

std::vector<std::string> Property::to_lines() const {
    std::vector<std::string> lines;
    lines.reserve(16);

    lines.push_back("ID: " + std::to_string(id()));
    lines.push_back("Риэлтор ID: " + std::to_string(realtor_id()));
    lines.push_back("Заголовок: " + std::string(title()));
    lines.push_back("Описание: " + std::string(description()));
    lines.push_back("Адрес: " + std::string(address()));

    lines.push_back("Цена: " + utils::float_to_str(price()) + " BYN");
    
    lines.push_back("Комнат: " + std::to_string(rooms()));
    lines.push_back("Этаж: " + std::to_string(floor()) + " из " + std::to_string(floors_total()));
    lines.push_back("Общая площадь: " + utils::float_to_str(area_total()) + " кв.м");
    lines.push_back("Жилая площадь: " + utils::float_to_str(area_living()) + " кв.м");
    lines.push_back("Площадь кухни: " + utils::float_to_str(area_kitchen()) + " кв.м");

    std::string typeStr = "Тип: ";
    switch (type()) {
    case PropertyType::Apartment: typeStr += "Квартира"; break;
    case PropertyType::House:     typeStr += "Дом"; break;
    case PropertyType::Office:    typeStr += "Офис"; break;
    case PropertyType::Land:      typeStr += "Земельный участок"; break;
    }
    lines.push_back(typeStr);

    std::string statusStr = "Статус: ";
    switch (status()) {
    case Status::Active:   statusStr += "Активно"; break;
    case Status::Sold:     statusStr += "Продано"; break;
    case Status::Rented:   statusStr += "Сдано в аренду"; break;
    case Status::Archived: statusStr += "Архивировано"; break;
    }
    lines.push_back(statusStr);

    std::time_t created = created_at();
    std::time_t updated = updated_at();
    lines.push_back("Создано: " + std::string(std::ctime(&created)));
    lines.push_back("Обновлено: " + std::string(std::ctime(&updated)));

    auto sellerLines = seller_.to_lines();
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

std::string property_type_to_str(PropertyType type) {
    switch (type) {
    case PropertyType::Apartment: return "Квартира";
    case PropertyType::House:     return "Дом";
    case PropertyType::Office:    return "Офис";
    case PropertyType::Land:      return "Земельный участок";
    }
    return "Неизвестно";
}

std::string status_to_str(Status status) {
    switch (status) {
    case Status::Active:   return "Активно";
    case Status::Sold:     return "Продано";
    case Status::Rented:   return "Сдано в аренду";
    case Status::Archived: return "Архивировано";
    }
    return "Неизвестно";
}

std::string time_to_str(const std::time_t& t) {
    std::string s = std::ctime(&t);
    if (!s.empty() && s.back() == '\n') {
        s.pop_back();
    }
    return s;
}

std::string Property::to_row(const std::vector<size_t>& sizes) const {
    std::ostringstream oss;
    oss << "|";

    std::vector<std::string> fields = {
        std::to_string(id_),
        std::to_string(realtor_id_),
        std::to_string(client_id_),
        std::string(title_),
        std::string(description_),
        std::string(address_),
        utils::float_to_str(price_),
        utils::float_to_str(area_total_),
        utils::float_to_str(area_living_),
        utils::float_to_str(area_kitchen_),
        std::to_string(rooms_),
        std::to_string(floor_),
        std::to_string(floors_total_),
        property_type_to_str(type_),
        status_to_str(status_),
        time_to_str(created_at_),
        time_to_str(updated_at_),
        seller_.name(),
        seller_.email(),
        seller_.phone()
    };

    for (size_t i = 0; i < fields.size() && i < sizes.size(); ++i) {
        std::string field = fields[i];

        field = utils::shorten(field, sizes[i]);

        oss << std::left << std::setw(sizes[i]) << field << "|";
    }

    return oss.str();
}