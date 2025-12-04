//#include "ui/Screen.h"

/*
void Run()
{
	Screen screen;

	StorageManager<Realtor> storage{ "data/realtors/realtors.bin" };
	Repository<Realtor> repo{ storage.load() };

	AuthService as{ repo, "data/realtors/id.bin" };

	while (true) {
		std::string login, password;

		if (screen.auth(login, password) == 2) break;

		std::shared_ptr<User> out_user;

		AuthResult res = as.login(login, password, out_user);

		if (res == AuthResult::Success) {
			if (Role::AdminRole == out_user->role()) {
				while (true) {
					int res = screen.admin_main();

					if (res == 1) {
						while (true) {
							std::string l, p1, p2;
							if (screen.admin_create_realtor(l, p1, p2) == 1) break;

							if (p1 != p2)
								screen.admin_create_realtor_failed_password();
							else if (as.registerUser(l, p1) == AuthResult::AlreadyExists)
								screen.admin_create_realtor_failed_login();
							else {
								screen.admin_create_realtor_success();
								break;
							}
						}
					}
					else if (res == 2) break;
				}
			}
			else if (out_user->role() == Role::RealtorRole) {
				std::shared_ptr<Realtor> realtor = std::dynamic_pointer_cast<Realtor>(out_user);
				while (true) {
					int res = screen.realtor_main(std::string(realtor->lastName()) + " " + realtor->firstName() + " " + realtor->middleName());

					if (res == 1) {

					}
					else if (res == 2) break;
				}
			}
		}
		else if (res == AuthResult::UserNotFound || res == AuthResult::WrongPassword) screen.auth_error();
	}
}
*/

#include <windows.h>
#include "core/Application.h"
#include "ui/Screen.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Application app;
	app.run();

	return 0;
}
