#include "Sort.h"

void Sort::by_price(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.price(); });
}

void Sort::by_area(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.area_total(); });
}

void Sort::by_rooms(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.rooms(); });
}

void Sort::by_floor(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.floor(); });
}

void Sort::by_status(Repository<Property>& repo) {
    Sort::sort_by(repo, [](const Property& p) { return p.status(); });
}
