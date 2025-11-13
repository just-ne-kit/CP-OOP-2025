#pragma once

#include "FieldContext.h"

class FormBuilder {
private:
	std::vector<std::vector<Field>> rows;

public:
	FormBuilder& row(FieldType type, unsigned int maxLength, const std::string& left, const std::string& cur, const std::string& right = "") {
		rows.push_back({ Field(type, maxLength, left, cur, right) });
		return *this;
	}

	FormBuilder& row(std::vector<Field> fieldsInRow) {
		rows.push_back(std::move(fieldsInRow));
		return *this;
	}

	FieldContext build() {
		return FieldContext(rows);
	}
};