#include "Realtor.h"
#include "../services/PropertyViewer.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

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
        return p->getRealtorId() != this->id_;
        });
    return myRepo;
}

void Realtor::viewAllProperties(Repository<Property>& repo) {
    PropertyViewer::view(repo);
}

void Realtor::viewProperties(const Repository<Property>& repo) {
    Repository<Property> myRepo = ownProperties(repo);
    PropertyViewer::view(myRepo);
}

void Realtor::addProperty(IdGenerator& id_gen, Repository<Property>& repo) {
    PropertyViewer::add(id_gen, repo, this->id_);
}

void Realtor::editProperty(Repository<Property>& repo) {
    Repository<Property> myRepo = ownProperties(repo);
    PropertyViewer::edit(myRepo);
}

void Realtor::deleteProperty(Repository<Property>& repo) {
    // фильтруем только свои объявления
    Repository<Property> myRepo = ownProperties(repo);
    PropertyViewer::remove(myRepo);
}

void Realtor::report(Repository<Property>& repo) {
    // фильтруем только свои объявления
    Repository<Property> myRepo = repo;
    myRepo.remove([&](const PropertyPtr& p) {
        return p->getRealtorId() != id_;
        });

    if (myRepo.count() == 0) {
        ConsoleUI::pause_clear("У вас нет объявлений для отчёта.");
        return;
    }

    // формируем имя файла
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", std::localtime(&now));

    // просто формируем путь (папка должна существовать!)
    std::string filename = std::string("realtor_report_") + std::string(buf) + ".txt";

    std::ofstream ofs(filename);
    if (!ofs) {
        ConsoleUI::pause_clear("Ошибка: не удалось создать файл отчёта.");
        return;
    }

    // заголовок
    ofs << "Отчёт риэлтора\n";
    ofs << "Дата: " << std::ctime(&now);
    ofs << "Риэлтор ID: " << id_ << "\n";
    ofs << "Имя: " << name() << "\n";
    ofs << "Email: " << email() << "\n";
    ofs << "Телефон: " << phone() << "\n\n";

    // ширины колонок для таблицы
    std::vector<size_t> sizes = {
        5,   // id
        8,   // realtorId
        8,   // clientId
        20,  // title
        30,  // description
        25,  // address
        12,  // price
        10,  // areaTotal
        10,  // areaLiving
        10,  // areaKitchen
        6,   // rooms
        6,   // floor
        8,   // floorsTotal
        6,   // type
        8,   // status
        12,  // createdAt
        12,  // updatedAt
        20,  // seller name
        25,  // seller email
        15   // seller phone
    };

    // заголовок таблицы
    ofs << "|ID   |Realtor |Client |Title               |Description                   |Address                 |Price       |AreaTot   |AreaLiv   |AreaKit   |Rooms |Floor |FloorsTot |Type |Status   |Created     |Updated     |SellerName          |SellerEmail             |SellerPhone   |\n";
    ofs << std::string(200, '-') << "\n";

    // выводим каждое объявление в виде строки
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

    // фильтруем заявки только для этого риэлтора
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

        // находим клиента
        ClientPtr client = client_repo.get([&](const ClientPtr& c) {
            return c->id() == req->client_id();
            });

        // находим объект
        PropertyPtr prop = property_repo.get([&](const PropertyPtr& p) {
            return p->getId() == req->property_id();
            });

        std::string info = "Заявка:\n" +
            (client ? client->to_str() : "Клиент не найден") + "\n" +
            (prop ? prop->to_str() : "Объявление не найдено") + "\n\n" +
            std::to_string(current + 1) + " из " + std::to_string(reqs.size());

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
        case 2: { // подтвердить
            if (prop) {
                prop->setStatus(Status::Sold);
                prop->setClientId(req->client_id());
                request_repo.remove([&](const RequestPtr& r) {
                    return r->property_id() == prop->getId();
                    });
                ConsoleUI::pause_clear("Сделка подтверждена.");
                exit = true;
            }
        } break;
        case 3: { // отклонить
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
