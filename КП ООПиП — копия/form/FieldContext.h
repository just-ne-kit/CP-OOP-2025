#pragma once
#include <vector>
#include <string>
#include <conio.h>
#include "../ui/Field.h"

class FieldContext {
public:
    unsigned int count;
    unsigned int currentY; // index [0, ... , count - 1]
    unsigned int currentX;
    std::vector<std::vector<Field>> fields;

    FieldContext(std::vector<std::vector<Field>> fields);

    void handleInput();
    void down();
    void up();
    void left();
    void right();
    void commitAll();
    std::vector<std::string> getLines();
};
