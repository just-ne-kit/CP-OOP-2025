#include "Realtor.h"

Realtor::Realtor()
    : User(), m_phoneNumber(0)
{
    m_lastName[0] = '\0';
    m_firstName[0] = '\0';
    m_middleName[0] = '\0';
    m_email[0] = '\0';
}
Realtor::Realtor(const User &base,
                 const std::string &lastName,
                 const std::string &firstName,
                 const std::string &middleName,
                 const std::string &email,
                 unsigned int phoneNumber)
    : User(base), m_phoneNumber(phoneNumber)
{
    std::strncpy(m_lastName, lastName.c_str(), sizeof(m_lastName) - 1);
    m_lastName[sizeof(m_lastName) - 1] = '\0';

    std::strncpy(m_firstName, firstName.c_str(), sizeof(m_firstName) - 1);
    m_firstName[sizeof(m_firstName) - 1] = '\0';

    std::strncpy(m_middleName, middleName.c_str(), sizeof(m_middleName) - 1);
    m_middleName[sizeof(m_middleName) - 1] = '\0';

    std::strncpy(m_email, email.c_str(), sizeof(m_email) - 1);
    m_email[sizeof(m_email) - 1] = '\0';
}
Realtor::Realtor(const User &user)
    : User(user), m_phoneNumber(0)
{
    m_lastName[0] = '\0';
    m_firstName[0] = '\0';
    m_middleName[0] = '\0';
    m_email[0] = '\0';
}
Realtor::Realtor(const Realtor &other)
    : User(other), m_phoneNumber(other.m_phoneNumber), m_properties(other.m_properties)
{
    std::strncpy(m_lastName, other.m_lastName, sizeof(m_lastName));
    std::strncpy(m_firstName, other.m_firstName, sizeof(m_firstName));
    std::strncpy(m_middleName, other.m_middleName, sizeof(m_middleName));
    std::strncpy(m_email, other.m_email, sizeof(m_email));
}

void Realtor::serialize(std::ofstream &ofs) const
{
    ofs.write(reinterpret_cast<const char*>(&m_id), sizeof(m_id));
    ofs.write(reinterpret_cast<const char*>(m_login), sizeof(m_login));
    ofs.write(reinterpret_cast<const char*>(m_hashedPassword), sizeof(m_hashedPassword));
    ofs.write(reinterpret_cast<const char*>(&m_role), sizeof(m_role));

    ofs.write(reinterpret_cast<const char*>(m_lastName), sizeof(m_lastName));
    ofs.write(reinterpret_cast<const char*>(m_firstName), sizeof(m_firstName));
    ofs.write(reinterpret_cast<const char*>(m_middleName), sizeof(m_middleName));
    ofs.write(reinterpret_cast<const char*>(m_email), sizeof(m_email));
    ofs.write(reinterpret_cast<const char*>(&m_phoneNumber), sizeof(m_phoneNumber));

    size_t adsSize = m_properties.size();
    ofs.write(reinterpret_cast<const char*>(&adsSize), sizeof(adsSize));
    ofs.write(reinterpret_cast<const char*>(m_properties.data()), adsSize * sizeof(int));
}
void Realtor::deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    ifs.read(reinterpret_cast<char*>(m_login), sizeof(m_login));
    ifs.read(reinterpret_cast<char*>(m_hashedPassword), sizeof(m_hashedPassword));
    ifs.read(reinterpret_cast<char*>(&m_role), sizeof(m_role));
    ifs.read(reinterpret_cast<char*>(m_lastName), sizeof(m_lastName));
    ifs.read(reinterpret_cast<char*>(m_firstName), sizeof(m_firstName));
    ifs.read(reinterpret_cast<char*>(m_middleName), sizeof(m_middleName));
    ifs.read(reinterpret_cast<char*>(m_email), sizeof(m_email));
    ifs.read(reinterpret_cast<char*>(&m_phoneNumber), sizeof(m_phoneNumber));

    size_t adsSize = 0;
    ifs.read(reinterpret_cast<char*>(&adsSize), sizeof(adsSize));

    if (!ifs) return; // если не удалось прочитать Ч выходим

    m_properties.resize(adsSize);
    ifs.read(reinterpret_cast<char*>(m_properties.data()), adsSize * sizeof(int));
}


void Realtor::addProperty(unsigned int id) {
    m_properties.push_back(id);
}
void Realtor::removeProperty(unsigned int id) {
    m_properties.erase(std::remove_if(m_properties.begin(), m_properties.end(), [&](unsigned int x) { return x == id; }), m_properties.end());
}

const char* Realtor::lastName() const { return m_lastName; }
const char* Realtor::firstName() const { return m_firstName; }
const char* Realtor::middleName() const { return m_middleName; }
const char* Realtor::email() const { return m_email; }
unsigned int Realtor::phoneNumber() const { return m_phoneNumber; }
const std::vector<unsigned int>& Realtor::properties() const { return m_properties; }

void Realtor::setLastName(const std::string& lastName) {
    std::strncpy(m_lastName, lastName.c_str(), sizeof(m_lastName) - 1);
    m_lastName[sizeof(m_lastName) - 1] = '\0';
}
void Realtor::setFirstName(const std::string& firstName) {
    std::strncpy(m_firstName, firstName.c_str(), sizeof(m_firstName) - 1);
    m_firstName[sizeof(m_firstName) - 1] = '\0';
}
void Realtor::setMiddleName(const std::string& middleName) {
    std::strncpy(m_middleName, middleName.c_str(), sizeof(m_middleName) - 1);
    m_middleName[sizeof(m_middleName) - 1] = '\0';
}
void Realtor::setEmail(const std::string& email) {
    std::strncpy(m_email, email.c_str(), sizeof(m_email) - 1);
    m_email[sizeof(m_email) - 1] = '\0';
}
void Realtor::setPhoneNumber(unsigned int phoneNumber) {
    m_phoneNumber = phoneNumber;
}

