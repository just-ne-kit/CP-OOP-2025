#pragma once

#include "../core/User.h"
#include "StorageManager.h"

class ClientStorageManager : public StorageManager<User>
{
public:
	ClientStorageManager(std::string filename) : StorageManager(filename) {}
};