#include "AuthService.h"
#include "../security/PasswordHasher.h"

bool AuthService::username_exists(const std::string& username) {
    if (username == auth_cfg::ADMIN_NAME) return true;

    if (client_repo_.exists([&](const ClientPtr& obj) { return obj->username() == username; }))
        return true;

    if (realtor_repo_.exists([&](const RealtorPtr& obj) { return obj->username() == username; }))
        return true;

    return false;
}

AuthResult AuthService::login(const std::string& username, const std::string& password, std::shared_ptr<User>& out_user)
{
    if (username == auth_cfg::ADMIN_NAME) {
        if (PasswordHasher::encrypt(password) != PasswordHasher::encrypt(auth_cfg::ADMIN_PASSWORD))
            return AuthResult::WrongPassword;
        
        out_user = std::make_shared<Admin>();
        return AuthResult::Success;
    }

    {
        RealtorPtr realtor = realtor_repo_.get([&](const RealtorPtr& obj) {
            return obj && obj->username() == username;});

        if (realtor) {
            if (PasswordHasher::encrypt(password) != realtor->hashed_password()) 
                return AuthResult::WrongPassword;
            
            out_user = realtor;
            return AuthResult::Success;
        }
    }

    {
        ClientPtr client = client_repo_.get([&](const ClientPtr& obj) {
            return obj && obj->username() == username; });

        if (client) {
            if (PasswordHasher::encrypt(password) != client->hashed_password())
                return AuthResult::WrongPassword;

            out_user = client;
            return AuthResult::Success;
        }
    }

    out_user.reset();
    return AuthResult::UserNotFound;
}
AuthResult AuthService::register_client(const std::string& username, const std::string& password) {
    if (username_exists(username)) return AuthResult::AlreadyExists;

    unsigned int id = client_id_gen_.next();
    auto new_client = std::make_shared<Client>(id, username, PasswordHasher::encrypt(password));
    client_repo_.add(new_client, [](const ClientPtr&) { return false; });

    return AuthResult::Success;
}

AuthResult AuthService::register_realtor(const std::string& username, const std::string& password) {
    if (username_exists(username)) return AuthResult::AlreadyExists;

    unsigned int id = realtor_id_gen_.next();
    auto new_realtor = std::make_shared<Realtor>(id, username, PasswordHasher::encrypt(password));
    realtor_repo_.add(new_realtor, [](const RealtorPtr&) { return false; });

    return AuthResult::Success;
}