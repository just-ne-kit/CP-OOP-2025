#include "Realtor.h"

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
    // простой отчёт: количество объявлений риэлтора
    Repository<Property> myRepo = ownProperties(repo);
    //todo
    std::string msg = "У вас " + std::to_string(myRepo.count()) + " объявлений.";
    ConsoleUI::pause_clear(msg);
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
