#include "FieldContext.h"

FieldContext::FieldContext(std::vector<std::vector<Field>> fields)
    : currentY(0), currentX(0), fields(fields) {
    count = fields.size();
}

void FieldContext::handleInput() {
    int ch = _getch();

    // спец-клавиши: стрелки и т.п.
    if ((ch == 0 || ch == 224) && _kbhit()) {
        ch = _getch(); // второй байт

        Field& f = fields[currentY][currentX];
        f.commit();

        switch (ch) {
        case 72: up(); break;
        case 80: down(); break;
        case 75: left(); break;
        case 77: right(); break;
        }
        return; // ← ВАЖНО: не продолжаем дальше!
    }

    // обычные клавиши
    Field& f = fields[currentY][currentX];

    switch (ch) {
    case '\r':
        if(f.type == FieldType::ButtonExit || f.type == FieldType::ButtonToogle) f.isActivated = !f.isActivated;
        else f.commit();
        break;
    case '\b': f.backspace(); break;
    case 27:   f.rollback(); break;
    default:   f.append(static_cast<unsigned char>(ch)); break;
    }
}

void FieldContext::down() {
    currentY = (currentY + 1) % count;
    if (currentX >= fields[currentY].size())
        currentX = fields[currentY].size() - 1;
}

void FieldContext::up() {
    currentY = (currentY + count - 1) % count;
    if (currentX >= fields[currentY].size())
        currentX = fields[currentY].size() - 1;
}

void FieldContext::left() {
    currentX = (currentX + fields[currentY].size() - 1) % fields[currentY].size();
}

void FieldContext::right() {
    currentX = (currentX + 1) % fields[currentY].size();
}

void FieldContext::commitAll() {
    for (unsigned int i = 0; i < count; i++)
        for (unsigned int j = 0; j < fields[i].size(); j++)
            fields[i][j].commit();
}

std::vector<std::string> FieldContext::getLines() {
    std::vector<std::string> res;

    for (unsigned int i = 0; i < count; i++) {
        res.push_back("");
        for (unsigned int j = 0; j < fields[i].size(); j++) {
            res[i] += fields[i][j].to_str(i == currentY && j == currentX);
        }
    }

    return res;
}
