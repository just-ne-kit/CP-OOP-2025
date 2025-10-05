#include "PasswordHasher.h"

const std::string PasswordHasher::encryptionKey = "very STRONG encryption key 007";

std::string PasswordHasher::encrypt(const std::string& password)
{
    std::string result = password;
    for (size_t i = 0; i < password.size(); ++i) {
        result[i] ^= encryptionKey[i % encryptionKey.size()];
        //result[i] ^= encryptionKey[i % strlen(encryptionKey)];
    }
    return result;
}
std::string PasswordHasher::decrypt(const std::string& encrypted) { return encrypt(encrypted); }