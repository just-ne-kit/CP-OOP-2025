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
				RealtorPtr realtor = std::dynamic_pointer_cast<Realtor>(out_user);
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
#ifdef _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	if (hIn == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwOriginalOutMode = 0;
	DWORD dwOriginalInMode = 0;
	if (!GetConsoleMode(hOut, &dwOriginalOutMode))
	{
		return false;
	}
	if (!GetConsoleMode(hIn, &dwOriginalInMode))
	{
		return false;
	}

	DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
	DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

	DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
	if (!SetConsoleMode(hOut, dwOutMode))
	{
		// we failed to set both modes, try to step down mode gracefully.
		dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
		if (!SetConsoleMode(hOut, dwOutMode))
		{
			// Failed to set any VT mode, can't do anything here.
			return -1;
		}
	}

	DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
	if (!SetConsoleMode(hIn, dwInMode))
	{
		// Failed to set VT input mode, can't do anything here.
		return -1;
	}
	

	//todo setprec(2)
#endif

	SetConsoleCtrlHandler(Application::ConsoleHandler, TRUE);
	Application::run();

	return 0;
}
