#include "Admin.h"
#include "../ui/ConsoleUI.h"
#include "../security/PasswordHasher.h"
#include "../services/PropertyService.h"
#include "sstream"
#include <iomanip>

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
    PropertyService::view(repo);
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
    int choice = 0;
    while (!exit) {
        choice = ConsoleUI::scroll({
            "Лево",
            "Право",
            "Назад"
            }, ">",
            choice,
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
    PropertyService::edit(repo);
}

void Admin::deleteProperty(Repository<Property>& repo) {
    PropertyService::remove(repo);
}

void Admin::report(Repository<Realtor>& realtorRepo,
    Repository<Client>& clientRepo,
    Repository<Property>& propertyRepo)
{
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", std::localtime(&now));

    std::string filename = std::string("data/reports/admin_report_") + std::string(buf) + ".txt";

    std::ofstream ofs(filename);
    if (!ofs) {
        ConsoleUI::pause_clear("Ошибка: не удалось создать файл отчёта.");
        return;
    }

    ofs << "Отчёт администратора\n";
    ofs << "Дата: " << std::ctime(&now) << "\n\n";

    ofs << "Риэлторы:\n";
    {
        std::vector<std::string> headers = { "ID", "Риэлтор", "Email", "Телефон" };
        std::vector<size_t> sizes = { 4, 20, 25, 15 };

        std::ostringstream header;
        header << "|";
        for (size_t i = 0; i < headers.size(); ++i)
            header << std::left << std::setw(sizes[i]) << headers[i] << "|";
        ofs << header.str() << "\n";

        size_t total_width = 1;
        for (size_t w : sizes) total_width += w + 1;
        ofs << std::string(total_width, '-') << "\n";

        for (auto& realtor : realtorRepo.getAll())
            ofs << realtor->to_row(sizes) << "\n";

        ofs << "\n";
    }

    ofs << "Клиенты:\n";
    {
        std::vector<std::string> headers = { "ID", "Клиент", "Email", "Телефон" };
        std::vector<size_t> sizes = { 4, 20, 25, 15 };

        std::ostringstream header;
        header << "|";
        for (size_t i = 0; i < headers.size(); ++i)
            header << std::left << std::setw(sizes[i]) << headers[i] << "|";
        ofs << header.str() << "\n";

        size_t total_width = 1;
        for (size_t w : sizes) total_width += w + 1;
        ofs << std::string(total_width, '-') << "\n";

        for (auto& client : clientRepo.getAll())
            ofs << client->to_row(sizes) << "\n";

        ofs << "\n";
    }

    ofs << "Объекты недвижимости:\n";
    {
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
        for (size_t i = 0; i < headers.size(); ++i)
            header << std::left << std::setw(sizes[i]) << headers[i] << "|";
        ofs << header.str() << "\n";

        size_t total_width = 1;
        for (size_t w : sizes) total_width += w + 1;
        ofs << std::string(total_width, '-') << "\n";

        for (auto& property : propertyRepo.getAll())
            ofs << property->to_row(sizes) << "\n";

        ofs << "\n";
    }

    ofs.close();
    ConsoleUI::pause_clear("Отчёт администратора сохранён в файл: " + filename);
}

void Admin::editRealtors(Repository<Realtor>& repo)
{
    ConsoleUI::clear();
    if (repo.count() < 1) {
        ConsoleUI::pause_clear("Нет риэлторов. Нажмите любую клавишу для продолжения.");
        return;
    }

    unsigned int id = InputReader::read<unsigned int>(
        "Введите id редактируемого риэлтора: ",
        input_cfg::ERR_UINT
    );

    if (!repo.exists([&](const std::shared_ptr<Realtor>& r) { return r->id() == id; })) {
        ConsoleUI::pause_clear("Риэлтор с таким id не найден. Нажмите любую клавишу для продолжения.");
        return;
    }

    auto edited = std::make_shared<Realtor>(
        *repo.get([&](const std::shared_ptr<Realtor>& r) { return r->id() == id; })
    );

    int choice = 0;
    bool exit = false;
    while (!exit) {
        std::vector<std::string> v = {
            std::string("Имя: ") + edited->name(),
            std::string("Email: ") + edited->email(),
            std::string("Телефон: ") + edited->phone(),
            "Закончить редактирование",
            "Выход"
        };

        choice = ConsoleUI::scroll(v, ">", choice, "Выберите поле для редактирования\n");
        ConsoleUI::clear();

        switch (choice) {
        case 0: edited->set_name(Realtor::read_name()); break;
        case 1: edited->set_email(Realtor::read_email()); break;
        case 2: edited->set_phone(Realtor::read_phone()); break;
        case 3:
            repo.update([&](const std::shared_ptr<Realtor>& r) { return r->id() == edited->id(); }, edited);
            return;
        case 4: return;
        default: break;
        }
    }
}
