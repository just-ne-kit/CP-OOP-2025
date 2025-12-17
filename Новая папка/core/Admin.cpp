#include "Admin.h"
#include "../ui/ConsoleUI.h"
#include "../security/PasswordHasher.h"
#include "../services/PropertyViewer.h"

Admin::Admin() {
	id_ = 0;
	strcpy_s(username_, auth_cfg::ADMIN_NAME.c_str());
	strcpy_s(hashed_password_, PasswordHasher::encrypt(auth_cfg::ADMIN_PASSWORD).c_str());
}

Role Admin::role() const { return Role::AdminRole; }

void Admin::serialize(std::ofstream& ofs) const {
	throw std::logic_error("Admin не сериализуется");
}
void Admin::deserialize(std::ifstream& ifs) {
	throw std::logic_error("Admin не десериализуется");
}

std::vector<std::string> Admin::to_lines() const
{
	std::vector<std::string> lines;
	lines.reserve(3);

	lines.push_back("Имя админа: " + std::string(name()));
	lines.push_back("Электронная почта админа: " + std::string(email()));
	lines.push_back("Телефонный номер админа: " + std::string(phone()));

	return lines;
}

void Admin::viewProperties(const Repository<Property>& repo) {
    PropertyViewer::view(repo);
}

void Admin::viewRealtors(const Repository<Realtor>& default_repo)
{
    ConsoleUI::clear();
    if (default_repo.count() <= 0) {
        ConsoleUI::pause_clear("Нет риэлторов. Нажмите любую клавишу для продолжения.");
        return;
    }

    bool is_asc = true;
    int current = 0;
    int choice = 0;
    Repository<Realtor> repo = default_repo;

    auto reset_repo = [&]() { repo = default_repo; current = 0; };

    bool exit = false;
    while (!exit) {
        if (repo.count() <= 0) {
            ConsoleUI::pause_clear("Нет риэлторов. Нажмите любую клавишу для сброса сортировки.");
            reset_repo();
        }

        int index = is_asc ? current : repo.count() - current - 1;

        choice = ConsoleUI::scroll({
            "Лево",
            "Право",
            "[По убыванию / По возрастанию]\n",
            "Назад" },
            ">",
            choice,
            repo[index]->to_str() + "\n" + std::to_string(current + 1) + "й из " + std::to_string(repo.count()) + "\n\n");

        switch (choice) {
        case 0: current = (current - 1 + repo.count()) % repo.count(); break;
        case 1: current = (current + 1) % repo.count(); break;
        case 2: is_asc = !is_asc; break;
        case 3: exit = true; break;
        default: break;
        }
    }
}

void Admin::removeRealtors(Repository<Realtor>& default_repo)
{
    ConsoleUI::clear();
    if (default_repo.count() < 1) {
        ConsoleUI::pause_clear("Нет риэлторов для удаления.");
        return;
    }

    unsigned int id = InputReader::read<unsigned int>(
        "Введите id риэлтора для удаления: ",
        input_cfg::ERR_UINT
    );

    bool success = default_repo.remove([&](const RealtorPtr& r) { return r->id() == id; });

    ConsoleUI::pause_clear(success
        ? "Риэлтор удалён."
        : "Риэлтор с таким id не найден.");
}

void Admin::viewClients(Repository<Client>& repo)
{
    ConsoleUI::clear();

    if (repo.count() == 0) {
        ConsoleUI::pause_clear("Нет зарегистрированных клиентов.");
        return;
    }

    int current = 0;
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Лево",
            "Право",
            "Назад"
            }, ">",
            0,
            repo[current]->to_str() + "\n" +
            std::to_string(current + 1) + "й из " + std::to_string(repo.count()) + "\n\n");

        switch (choice) {
        case 0: current = (current - 1 + repo.count()) % repo.count(); break;
        case 1: current = (current + 1) % repo.count(); break;
        case 2: exit = true; break;
        default: break;
        }
    }
}


void Admin::editProperty(Repository<Property>& repo) {
    PropertyViewer::edit(repo);
}

void Admin::deleteProperty(Repository<Property>& repo) {
    PropertyViewer::remove(repo);
}

void Admin::report(Repository<Property>& repo) {
	//todo
    std::string msg = "Всего объявлений: " + std::to_string(repo.count());
    ConsoleUI::pause_clear(msg);
}
