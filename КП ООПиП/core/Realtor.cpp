#include "Realtor.h"
#include "../services/PropertyService.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "utils.h"

Realtor::Realtor()
    : User() {}

Realtor::Realtor(unsigned int id, const std::string& login, const std::string& hashedPassword)
    : User(id, login, hashedPassword) {}

Realtor::Realtor(unsigned int id, const std::string& username, const std::string& hashed_password,
                 const std::string &name, const std::string &email, const std::string &phone)
    : User(id, username, hashed_password, name, email, phone) {}

Realtor::Realtor(const Realtor& realtor)
    : User(realtor) {}

Role Realtor::role() const { return Role::RealtorRole; }

std::vector<std::string> Realtor::to_lines() const
{
    std::vector<std::string> lines;
    lines.reserve(5);

    lines.push_back("ID риэлтора: " + std::to_string(id_));
    lines.push_back("Логин риэлтора: " + std::string(username()));
    lines.push_back("Имя риэлтора: " + std::string(name()));
    lines.push_back("Электронная почта риэлтора: " + std::string(email()));
    lines.push_back("Телефонный номер риэлтора: " + std::string(phone()));

    return lines;
}

Repository<Property> Realtor::ownProperties(const Repository<Property>& repo) const {
    Repository<Property> myRepo = repo;
    myRepo.remove([&](const PropertyPtr& p) {
        return p->realtor_id() != this->id_;
        });
    return myRepo;
}

void Realtor::viewAllProperties(Repository<Property>& repo) {
    PropertyService::view(repo);
}

void Realtor::viewProperties(const Repository<Property>& repo) {
    Repository<Property> myRepo = ownProperties(repo);
    PropertyService::view(myRepo);
}

void Realtor::addProperty(IdGenerator& id_gen, Repository<Property>& repo) {
    PropertyService::add(id_gen, repo, this->id_);
}

void Realtor::editProperty(Repository<Property>& repo) {
    Repository<Property> myRepo = ownProperties(repo);
    PropertyService::edit(myRepo);
}

void Realtor::deleteProperty(Repository<Property>& repo) {
    Repository<Property> myRepo = ownProperties(repo);
    PropertyService::remove(myRepo);
}

void Realtor::report(Repository<Property>& repo) {
    Repository<Property> myRepo = repo;
    myRepo.remove([&](const PropertyPtr& p) {
        return p->realtor_id() != id_;
        });

    if (myRepo.count() == 0) {
        ConsoleUI::pause_clear("У вас нет объявлений для отчёта.");
        return;
    }

    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", std::localtime(&now));

    std::string filename = std::string("data/reports/realtor_report_") + std::string(buf) + ".txt";

    std::ofstream ofs(filename);
    if (!ofs) {
        ConsoleUI::pause_clear("Ошибка: не удалось создать файл отчёта.");
        return;
    }

    ofs << "Отчёт риэлтора\n";
    ofs << "Дата: " << std::ctime(&now);
    ofs << "Риэлтор ID: " << id_ << "\n";
    ofs << "Имя: " << name() << "\n";
    ofs << "Email: " << email() << "\n";
    ofs << "Телефон: " << phone() << "\n\n";

    std::vector<size_t> sizes = {
    4,7,6,40,40,40,11,8,8,8,4,4,6,10,9,24,24,10,25,15
    };
    std::vector<std::string> headers = {
        "ID",        // ID
        "Риэлтор",   // Realtor
        "Клиент",    // Client
        "Заголовок", // Title
        "Описание",  // Description
        "Адрес",     // Address
        "Цена",      // Price
        "ПлОбщ",     // AreaTot
        "ПлЖил",     // AreaLiv
        "ПлКух",     // AreaKit
        "Комн",      // Rooms
        "Этаж",      // Floor
        "МаксЭт",    // FloorsTot
        "Тип",       // Type
        "Статус",    // Status
        "Создано",   // Created
        "Обновленно",// Updated
        "Продавец",  // SellerName
        "Email",     // SellerEmail
        "Телефон"    // SellerPhone
    };

    std::ostringstream header;
    header << "|";
    for (size_t i = 0; i < headers.size() && i < sizes.size(); ++i) {
        header << std::left << std::setw(sizes[i]) << headers[i] << "|";
    }
    ofs << header.str() << "\n";

    size_t total_width = 1;
    for (size_t w : sizes) total_width += w + 1;
    ofs << std::string(total_width, '-') << "\n";

    for (const auto& prop : myRepo.getAll()) {
        ofs << prop->to_row(sizes) << "\n";
    }

    ofs.close();

    ConsoleUI::pause_clear("Отчёт сохранён в файл: " + filename);
}

void Realtor::viewRequests(Repository<Request>& request_repo,
    Repository<Property>& property_repo,
    Repository<Client>& client_repo)
{
    ConsoleUI::clear();

    Repository<Request> myRequests = request_repo;
    myRequests.remove([&](const RequestPtr& r) { return r->realtor_id() != id_; });

    if (myRequests.count() == 0) {
        ConsoleUI::pause_clear("Нет заявок на ваши объявления.");
        return;
    }

    int current = 0;
    bool exit = false;

    while (!exit) {
        auto reqs = myRequests.getAll();
        RequestPtr req = reqs[current];

        ClientPtr client = client_repo.get([&](const ClientPtr& c) {
            return c->id() == req->client_id();
            });

        PropertyPtr prop = property_repo.get([&](const PropertyPtr& p) {
            return p->id() == req->property_id();
            });

        std::string info = "Заявка:\n" +
            (client ? client->to_str() : "Клиент не найден") + "\n" +
            (prop ? prop->to_str() : "Объявление не найдено") + "\n\n" +
            std::to_string(current + 1) + " из " + std::to_string(reqs.size()) + "\n";

        int choice = ConsoleUI::scroll({
            "Лево",
            "Право",
            "Подтвердить сделку",
            "Отклонить заявку",
            "Назад"
            }, ">", 0, info);

        switch (choice) {
        case 0: current = (current - 1 + reqs.size()) % reqs.size(); break;
        case 1: current = (current + 1) % reqs.size(); break;
        case 2: {
            if (prop) {
                prop->set_status(Status::Sold);
                prop->set_client_id(req->client_id());
                request_repo.remove([&](const RequestPtr& r) {
                    return r->property_id() == prop->id();
                    });
                ConsoleUI::pause_clear("Сделка подтверждена.");
                exit = true;
            }
        } break;
        case 3: {
            request_repo.remove([&](const RequestPtr& r) {
                return r->property_id() == req->property_id() &&
                    r->client_id() == req->client_id();
                });
            ConsoleUI::pause_clear("Заявка отклонена.");
            exit = true;
        } break;
        case 4: exit = true; break;
        default: break;
        }
    }
}

std::string Realtor::to_row(const std::vector<size_t>& sizes) const {
    std::ostringstream oss;
    oss << "|";

    std::vector<std::string> fields = {
        std::to_string(id_),   // ID риэлтора
        name_,                 // Имя
        email_,                // Email
        phone_                 // Телефон
    };

    for (size_t i = 0; i < fields.size() && i < sizes.size(); ++i) {
        std::string field = utils::shorten(fields[i], sizes[i]);
        oss << std::left << std::setw(sizes[i]) << field << "|";
    }

    return oss.str();
}
