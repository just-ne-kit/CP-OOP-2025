#include "Client.h"

Client::Client()
    : User() {
}

Client::Client(unsigned int id, const std::string& login, const std::string& hashedPassword)
    : User(id, login, hashedPassword) {
}

Client::Client(unsigned int id, const std::string& username, const std::string& hashed_password,
    const std::string& name, const std::string& email, const std::string& phone)
    : User(id, username, hashed_password, name, email, phone) {
}

Client::Client(const Client& client)
    : User(client) {
}

Role Client::role() const {
	return Role::ClientRole;
}

std::vector<std::string> Client::to_lines() const
{
    std::vector<std::string> lines;
    lines.reserve(3);

    lines.push_back("Имя клиента: " + std::string(name()));
    lines.push_back("Электронная почта клиента: " + std::string(email()));
    lines.push_back("Телефонный номер клиента: " + std::string(phone()));

    return lines;
}

void Client::viewProperties(const Repository<Property>& repo) {
    Repository<Property> activeRepo = repo;
    activeRepo.remove([&](const PropertyPtr& p) {
        return p->getStatus() != Status::Active;
        });

    PropertyViewer::view(activeRepo);
}

void Client::viewRequests(const Repository<Property>& repo, const Repository<Request>& request_repo) {
    Repository<Property> activeRepo;
    Repository<Request> reqRepo = request_repo;

    reqRepo.remove([&](const RequestPtr& r) { return r->client_id() != id_; });

    for (const auto& obj : reqRepo.getAll())
    {
        auto ptr = repo.get([&](const PropertyPtr& p) { return p->getStatus() == Status::Active && p->getId() == obj->property_id(); });
        
        if (ptr)
            activeRepo.add(ptr, [&](const PropertyPtr& p) { return p->getId() == ptr->getId(); });
    }

    PropertyViewer::view(activeRepo);
}
void Client::viewBought(const Repository<Property>& repo, const Repository<Request>& request_repo)
{
    Repository<Property> boughtRepo;

    // фильтруем только купленные этим клиентом объекты
    for (const auto& prop : repo.getAll())
    {
        if (prop->getStatus() == Status::Sold && prop->getClientId() == id_) {
            boughtRepo.add(prop, [&](const PropertyPtr& p) {
                return p->getId() == prop->getId();
                });
        }
    }

    if (boughtRepo.count() == 0) {
        ConsoleUI::pause_clear("У вас нет купленных объектов.");
        return;
    }

    PropertyViewer::view(boughtRepo);
}

void Client::discard(Repository<Request>& repo)
{
    Repository<Request> temp = repo;
    temp.remove([&](const RequestPtr& r) { return r->client_id() != id_; });

    ConsoleUI::clear();
    if (temp.count() < 1) {
        ConsoleUI::pause_clear("У вас нет заявок. Нажмите любую клавишу для продолжения.");
        return;
    }

    unsigned int del_id = InputReader::read<unsigned int>(
        "Введите id объявления для удаления заявки: ",
        input_cfg::ERR_UINT
    );

    bool isFound = temp.exists([&](const RequestPtr& p) {
        return p->property_id() == del_id;
        });

    if (!isFound)
    {
        ConsoleUI::pause_clear("Заявка не найдена. Нажмите любую клавишу для продолжения.");
        return;
    }

    repo.remove([&](const RequestPtr& p) {
        return p->property_id() == del_id && p->client_id() == id_;
        });

    ConsoleUI::pause_clear("Заявка удалена. Нажмите любую клавишу для продолжения.");
}

void Client::add(Repository<Property>& property_repo, Repository<Request>& request_repo)
{
    ConsoleUI::clear();
    if (property_repo.count() < 1) {
        ConsoleUI::pause_clear("Нет доступных объявлений. Нажмите любую клавишу для продолжения.");
        return;
    }

    unsigned int id = InputReader::read<unsigned int>(
        "Введите id объявления: ",
        input_cfg::ERR_UINT
    );

    PropertyPtr property = property_repo.get([&](const PropertyPtr& p) {
        return p->getId() == id && p->getStatus() == Status::Active;
        });

    if (!property) {
        ConsoleUI::pause_clear("Объявление не найдено или недоступно. Нажмите любую клавишу для продолжения.");
        return;
    }

    RequestPtr request = std::make_shared<Request>(Request(id_, property->getId(), property->getRealtorId()));
    bool success = request_repo.add(request, [&](const RequestPtr& r) {
        return r->client_id() == id_ && r->property_id() == property->getId();
        });

    if (!success) {
        ConsoleUI::pause_clear("Вы уже отправили запрос на это объявление. Нажмите любую клавишу для продолжения.");
        return;
    }

    ConsoleUI::pause_clear("Запрос успешно отправлен. Нажмите любую клавишу для продолжения.");
}
