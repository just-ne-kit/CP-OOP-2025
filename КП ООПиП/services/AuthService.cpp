#include "AuthService.h"

bool AuthService::login(const std::string& name, const std::string& password)
{

}
bool AuthService::registerUser(const std::string& name, const std::string& password)
{
	if (m_clientRepository.exists(name)) return false;

	m_clientRepository.addClient()

	return true;
}