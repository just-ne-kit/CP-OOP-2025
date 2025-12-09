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
    lines.reserve(3);

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
