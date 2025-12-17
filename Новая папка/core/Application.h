#pragma once

#include <conio.h>
#include <windows.h>

#include "Property.h"
#include "Request.h"
#include "../storage/StorageManager.h"
#include "../services/AuthService.h"

class Application
{
private:
    IdGenerator id_gen_prop;
    StorageManager<Property> property_storage;
    Repository<Property> property_repo;

    StorageManager<Realtor> realtor_storage;
    Repository<Realtor> realtor_repo;

    StorageManager<Client> client_storage;
    Repository<Client> client_repo;

    AuthService authService;

    StorageManager<Request> request_storage;
    Repository<Request> request_repo;

    void admin_prop(AdminPtr admin);
    void admin_realtor(AdminPtr admin);

    void realtor_prop(RealtorPtr realtor);
    void realtor_report();
    void realtor(RealtorPtr realtor);
    void admin_report();
    void admin(AdminPtr admin);
    void client(ClientPtr client);
    
    void register_user(AuthResult(AuthService::*sign_in)(const std::string&, const std::string&));
    void register_realtor();
    void register_client();
    void login();
    
    void save_data();

    static Application* instance;

public:
    Application() : 
        id_gen_prop     ("data/properties/id.bin"),
        property_storage("data/properties/properties.bin"),
        property_repo   (property_storage.load()),
        realtor_storage ("data/realtors/realtors.bin"),
        realtor_repo    (realtor_storage.load()),
        client_storage  ("data/clients/clients.bin"),
        client_repo     (client_storage.load()),
        request_storage ("data/requests/requests.bin"),
        request_repo    (request_storage.load()),
        authService     (client_repo, realtor_repo, "data/clients/id.bin", "data/realtors/id.bin") {
        instance = this;
    }

    static BOOL WINAPI ConsoleHandler(DWORD signal);
    void run();
};