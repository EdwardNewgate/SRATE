/*
* scp.h
*
*  Created on: Jul 24, 2014
*      Author: andre
*/

#ifndef USER_H_
#define USER_H_

#include <string>

class User {
public:
	User(uint32_t default_permissions, uint32_t violation_maximum);
	~User() {};

	/* Set Methods */
	void set_permissions(uint32_t bitmask)
	{
		this->permissions |= bitmask;
	}

	void increase_violations(void)
	{
		this->violations++;
	}

	void reset_violations(void)
	{
		this->violations = 0;
	}

	/* Get Methods */
	uint32_t get_permissions(void)
	{
		return this->permissions;
	}

	bool has_permissions(uint32_t bitmask)
	{
		if (this->get_permissions() & bitmask)
			return true;
		else
			return false;
	}

	uint32_t get_violations(void)
	{
		return this->violations;
	}

	uint32_t get_violation_threshold(void)
	{
		return this->violation_threshold;
	}

	bool violation_treshold_reached(void)
	{
		if (this->violations < this->violation_threshold)
			return false;
		else
			return true;
	}

private:
	uint32_t permissions;
	uint32_t violations;
	uint32_t violation_threshold;
};



#endif /* USER_H_ */
