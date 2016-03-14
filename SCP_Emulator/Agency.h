/*
* scp.h
*
*  Created on: Jul 24, 2014
*      Author: andre
*/

#ifndef AGENCY_H_
#define AGENCY_H_

#include <string>

class Agency {
public:
	Agency(std::string);
	~Agency() {};

	/*
	* Set Methods
	*/
	void set_abbr(std::string x)
	{
		this->abbreviation.assign(x); 
	}

	void set_name(std::string x)
	{ 
		this->name.assign(x);
	}

	void set_agenda(std::string x) 
	{
		this->agenda.assign(x); 
	}

	void set_site(std::string x) 
	{
		this->site.assign(x);
	}

	void set_header(std::string x)
	{ 
		this->header.assign(x); 
	}

	void set_permissions(uint32_t bitmask) 
	{ 
		this->permissions |= bitmask; 
	}

	/*
	 * Get Methods
	*/
	std::string get_abbr(void) 
	{ 
		return this->abbreviation; 
	}

	std::string get_name(void) 
	{ 
		return this->name;
	}

	std::string get_agenda(void) 
	{ 
		return this->agenda;
	}

	std::string get_site(void)
	{ 
		return this->site;
	}

	std::string get_header(void) 
	{ 
		return this->header;
	}

	uint32_t get_permissions(void)
	{
		return this->permissions;
	}

private:
	std::string abbreviation;
	std::string name;
	std::string agenda;
	std::string site;
	std::string header;

	uint16_t permissions;
};



#endif /* AGENCY_H_ */
