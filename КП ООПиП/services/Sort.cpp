#include "Sort.h"

void Sort::by_price(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.getPrice(); });
}

void Sort::by_area(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.getAreaTotal(); });
}

void Sort::by_rooms(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.getRooms(); });
}

void Sort::by_floor(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.getFloor(); });
}

void Sort::by_status(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.getStatus(); });
}
