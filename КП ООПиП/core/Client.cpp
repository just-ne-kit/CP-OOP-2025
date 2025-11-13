#include "Client.h"

void Client::serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) throw std::runtime_error("Ошибка открытия файла для записи");

    ofs.write(reinterpret_cast<const char*>(m_name), sizeof(m_name));
    ofs.write(reinterpret_cast<const char*>(&m_phoneNumber), sizeof(m_phoneNumber));
    ofs.write(reinterpret_cast<const char*>(m_email), sizeof(m_email));

    size_t adsSize = m_ads.size();
    ofs.write(reinterpret_cast<const char*>(&adsSize), sizeof(adsSize));
    ofs.write(reinterpret_cast<const char*>(m_ads.data()), adsSize * sizeof(int));

    size_t likedSize = m_liked.size();
    ofs.write(reinterpret_cast<const char*>(&likedSize), sizeof(likedSize));
    ofs.write(reinterpret_cast<const char*>(m_liked.data()), likedSize * sizeof(int));
}

void Client::deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) throw std::runtime_error("Ошибка открытия файла для чтения");

    ifs.read(reinterpret_cast<char*>(m_name), sizeof(m_name));
    ifs.read(reinterpret_cast<char*>(&m_phoneNumber), sizeof(m_phoneNumber));
    ifs.read(reinterpret_cast<char*>(m_email), sizeof(m_email));

    size_t adsSize;
    ifs.read(reinterpret_cast<char*>(&adsSize), sizeof(adsSize));
    m_ads.resize(adsSize);
    ifs.read(reinterpret_cast<char*>(m_ads.data()), adsSize * sizeof(int));

    size_t likedSize;
    ifs.read(reinterpret_cast<char*>(&likedSize), sizeof(likedSize));
    m_liked.resize(likedSize);
    ifs.read(reinterpret_cast<char*>(m_liked.data()), likedSize * sizeof(int));
}

const char* Client::getName() const {
    return m_name;
}
void Client::setName(const std::string& name) {
    strncpy(m_name, name.c_str(), sizeof(m_name) - 1);
    m_name[sizeof(m_name) - 1] = '\0';
}

unsigned int Client::getPhoneNumber() const {
    return m_phoneNumber;
}
void Client::setPhoneNumber(unsigned int phone) {
    m_phoneNumber = phone;
}

const char* Client::getEmail() const {
    return m_email;
}
void Client::setEmail(const std::string& email) {
    strncpy(m_email, email.c_str(), sizeof(m_email) - 1);
    m_email[sizeof(m_email) - 1] = '\0';
}

const std::vector<int>& Client::getAds() const {
    return m_ads;
}

const std::vector<int>& Client::getLiked() const {
    return m_liked;
}