#include "Agency.h"

#include <fstream>
#include <iostream>

Agency::Agency(std::string file_name)
	: abbreviation(""), name(""), agenda(""), site(""), header("")
{
	std::ifstream agency_file;
	std::string line;
	agency_file.open(file_name);
	if (!agency_file.is_open()) {
		std::cerr << "Could not open file" << std::endl;
	}

	while (std::getline(agency_file, line)) {
		if (line.find("/*") == std::string::npos) {
			break;
		}
	}

	this->set_abbr(line);
	std::getline(agency_file, line);
	this->set_name(line);
	std::getline(agency_file, line);
	this->set_agenda(line);
	std::getline(agency_file, line);
	this->set_site(line);
	std::getline(agency_file, line);
	this->set_header(line);

	this->set_permissions(0x00022222);
}
