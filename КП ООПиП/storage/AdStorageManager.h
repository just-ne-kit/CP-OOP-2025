#pragma once

#include "../core/Ad.h"
#include "StorageManager.h"

class AdStorageManager : public StorageManager<Ad>
{
public:
	AdStorageManager(std::string filename) : StorageManager(filename) {}
};