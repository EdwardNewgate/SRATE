#include "User.h"

#include <fstream>
#include <iostream>

User::User(uint32_t starting_permissions, uint32_t violation_max)
	: violations(0)
{
	this->set_permissions(starting_permissions);
	this->violation_threshold = violation_max;
}
