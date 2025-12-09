#include "Application.h"
#include "../ui/ConsoleUI.h"


Application* Application::instance = nullptr;


// ================== Sign on ==================

void Application::register_user(AuthResult(AuthService::* sign_in)(const std::string&, const std::string&)) {
    ConsoleUI::clear();
    std::string login = InputReader::read<std::string>("Введите новый логин:");
    std::string password1 = InputReader::read_password("Введите пароль:");
    std::string password2 = InputReader::read_password("Повторите пароль:");

    int choice = ConsoleUI::scroll({
        "Завершить регистрацию",
        "Отмена"
        }, ">");

    if (choice == 1) return;

    if (password1 != password2) {
        ConsoleUI::pause_clear("Пароли не совпадают. Нажмите любую клавишу для продолжения.");
        return;
    }

    AuthResult authRes = (authService.*sign_in)(login, password1);

    if (authRes == AuthResult::AlreadyExists) {
        ConsoleUI::pause_clear("Логин уже занят. Нажмите любую клавишу для продолжения.");
        return;
    }

    ConsoleUI::pause_clear("Успешно зарегистрированы. Нажмите любую клавишу для продолжения.");
}

void Application::register_client() {
    register_user(&AuthService::register_client);
}

void Application::register_realtor() {
    register_user(&AuthService::register_realtor);
}

// ================== Realtor ==================

void Application::realtor_prop(RealtorPtr realtor) {
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Просмотр объявлений",
            "Добавление",
            "Редактирование",
            "Удаление",
            "Назад"
            }, ">");

        switch (choice) {
        case 0: realtor->viewProperties(property_repo); break;
        case 1: realtor->addProperty(id_gen_prop, property_repo); break;
        case 2: realtor->editProperty(property_repo); break;
        case 3: realtor->deleteProperty(property_repo); break;
        case 4: exit = true; break;
        default: break;
        }
    }
}

void Application::realtor_report() {
    // TODO: генерация отчёта
    ConsoleUI::pause_clear("Нажмите любую клавишу для продолжения.");
}

void Application::realtor(RealtorPtr realtor) {
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Мои объявления",
            "Все объявления",
            "Заявки",
            "Создать отчет",
            "Выйти из учетной записи"
            }, ">");

        switch (choice) {
        case 0: realtor_prop(realtor); break;
        case 1: realtor->viewAllProperties(property_repo); break;
        case 2: realtor->viewRequests(request_repo, property_repo, client_repo); break;
        case 3: realtor_report(); break;
        case 4: exit = true; break;
        default: break;
        }
    }
}

// ================== Client ==================

void Application::client(ClientPtr client)
{
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Просмотреть все объявления",
            "Мои запросы",
            "Отправить запрос на покупку",
            "Отменить запрос на покупку",
            "Купленные объекты",
            "Выйти из учетной записи"
            }, ">");

        switch (choice) {
        case 0: client->viewProperties(property_repo); break;
        case 1: client->viewRequests(property_repo, request_repo); break;
        case 2: client->add(property_repo, request_repo); break;
        case 3: client->discard(request_repo); break;
        case 4: client->viewBought(property_repo, request_repo); break;
        case 5: exit = true; break;
        default: break;
        }
    }
}

// ================== Admin ==================

void Application::admin_report() {
    // TODO: генерация отчёта
}

void Application::admin_prop(AdminPtr admin)
{
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Просмотр объявлений",
            "Редактирование",
            "Удаление",
            "Назад"
            }, ">");

        switch (choice) {
        case 0: admin->viewProperties(property_repo); break;
        case 1: admin->editProperty(property_repo); break;
        case 2: admin->deleteProperty(property_repo); break;
        case 3: exit = true; break;
        default: break;
        }
    }
}

void Application::admin_realtor(AdminPtr admin)
{
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Просмотр риэлторов",
            "Создать риэлтора",
            "Удалить риэлтора",
            "Назад"
            }, ">");

        switch (choice) {
        case 0: admin->viewRealtors(realtor_repo); break;
        case 1: register_realtor(); break;
        case 2: admin->removeRealtors(realtor_repo); break;
        case 3: exit = true; break;
        default: break;
        }
    }
}

void Application::admin(AdminPtr admin) {
    bool exit = false;

    while (!exit) {
        int choice = ConsoleUI::scroll({
            "Управление риэлторами",
            "Управление объявлениями",
            "Все клиенты",
            "Создать отчет",
            "Выйти из учетной записи"
            }, ">");

        switch (choice) {
        case 0: admin_realtor(admin); break;
        case 1: admin_prop(admin); break;
        case 2: admin->viewClients(client_repo); break;
        case 3: admin_report(); break;
        case 4: exit = true; break;
        default: break;
        }
    }
}

// ================== Sign in ==================

void Application::login() {
    ConsoleUI::clear();
    std::string login = InputReader::read<std::string>("Введите логин:");
    std::string password = InputReader::read_password("Введите пароль:");

    std::shared_ptr<User> out_user;

    AuthResult authRes = authService.login(login, password, out_user);

    if (authRes != AuthResult::Success) {
        ConsoleUI::pause_clear("Логин или пароль неверный. Нажмите любую клавишу для продолжения.");
        return;
    }

    switch (out_user->role()) {
    case Role::AdminRole: admin(std::dynamic_pointer_cast<Admin>(out_user)); break;
    case Role::RealtorRole: realtor(std::dynamic_pointer_cast<Realtor>(out_user)); break;
    case Role::ClientRole: client(std::dynamic_pointer_cast<Client>(out_user)); break;
    default: ConsoleUI::pause_clear("Такой роли нет. Нажмите любую клавишу для продолжения."); break;
    }
}

// ================== Data ==================

void Application::save_data() {
    realtor_storage.save(realtor_repo.getAll());
    property_storage.save(property_repo.getAll());
    client_storage.save(client_repo.getAll());
    request_storage.save(request_repo.getAll());
}

// ================== Console Handler ==================

BOOL WINAPI Application::ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_SHUTDOWN_EVENT) {
        if(instance != nullptr) instance->save_data();
        return TRUE;
    }
    return FALSE;
}

// ================== Run ==================

void Application::run() {
    bool exit_program = false;
    while (!exit_program) {
        int choice = ConsoleUI::scroll({
            "Регистрация",
            "Вход",
            "Выход из программы\n\n\n"
            "\nУправление:\n"
            "  ^ / v  - стрелки для перемещения по пунктам меню\n"
            "  Enter  - выбор пункта\n"
            }, ">");

        switch (choice) {
        case 0: register_client(); break;
        case 1: login(); break;
        case 2: exit_program = true; break;
        default: ConsoleUI::clear(); break;
        }
    }
    save_data();
}
