#pragma once

#include "User.h"

class Buyer : public User {
public:
	virtual Role role() const override;
};
