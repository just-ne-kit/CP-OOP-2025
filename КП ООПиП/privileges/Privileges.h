#pragma once
#include "../repositories/Repository.h"
#include "../core/Property.h"
#include "../id/IdGenerator.h"
#include "../services/PropertyViewer.h"
#include "../ui/ConsoleUI.h"

class ViewPermission {
public:
    virtual void viewProperties(const Repository<Property>& repo) = 0;
    virtual ~ViewPermission() = default;
};

class AddPermission {
public:
    virtual void addProperty(IdGenerator& id_gen, Repository<Property>& repo) = 0;
    virtual ~AddPermission() = default;
};

class EditPermission {
public:
    virtual void editProperty(Repository<Property>& repo) = 0;
    virtual ~EditPermission() = default;
};

class DeletePermission {
public:
    virtual void deleteProperty(Repository<Property>& repo) = 0;
    virtual ~DeletePermission() = default;
};

class ReportPermission {
public:
    virtual void report(Repository<Property>& repo) = 0;
    virtual ~ReportPermission() = default;
};

// Админ: может смотреть, редактировать, удалять, делать отчёты
class AdminPriv : 
    public ViewPermission,
    public EditPermission,
    public DeletePermission,
    public ReportPermission 
{};

// Риэлтор: может смотреть, добавлять, редактировать, удалять, делать отчёты
class RealtorPriv : 
    public ViewPermission,
    public AddPermission,
    public EditPermission,
    public DeletePermission,
    public ReportPermission 
{};

// Клиент: может только смотреть
class ClientPriv : public ViewPermission {};
