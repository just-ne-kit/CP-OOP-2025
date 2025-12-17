#pragma once

#include "../core/Realtor.h"
#include "../core/Admin.h"
#include "../core/Client.h"
#include "../repositories/Repository.h"
#include "../id/IdGenerator.h"

enum class AuthResult {
	Success,
	UserNotFound,
	WrongPassword,
	AlreadyExists,
};

class AuthService
{
private:
	Repository<Client>& client_repo_;
	Repository<Realtor>& realtor_repo_;
	IdGenerator client_id_gen_;
	IdGenerator realtor_id_gen_;
	bool username_exists(const std::string& name);
public:
	AuthService(Repository<Client>& client_repo,
		Repository<Realtor>& realtor_repo,
		const std::string& client_id_gen_path,
		const std::string& realtor_id_gen_path)
		: 
		client_repo_(client_repo),
		realtor_repo_(realtor_repo),
		client_id_gen_(client_id_gen_path),
		realtor_id_gen_(realtor_id_gen_path) { }

	AuthResult login(const std::string& username, const std::string& password, std::shared_ptr<User>& out_user);
	AuthResult register_client(const std::string& username, const std::string& password);
	AuthResult register_realtor(const std::string& username, const std::string& password);
};