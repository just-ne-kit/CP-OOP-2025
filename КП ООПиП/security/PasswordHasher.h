#pragma once

#include <string>

class PasswordHasher
{
private:
    static const std::string encryptionKey;
public:
    static std::string encrypt(const std::string& password);
    static std::string decrypt(const std::string& encrypted);
};