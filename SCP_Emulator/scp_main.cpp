/**
* @file   scp_main.cpp
* @Author Andre (shirohige.git@gmail.com)
* @date   June, 2014
* @brief  Basically a Terminal Emulator, but cool.
*
* A Terminal Emulator, which gives the user the experience of hacking through
* a database of a secret organization, called SCU. The name SCU was inspired
* by the (<a href="http://www.scp-wiki.net/">SCP project</a>), but I have no
* ties to them.
*/

#include "scp_main.h"

#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#pragma comment(lib,"Winmm.lib")

/*----------------------------------------------------------------------*/
/*			HELPER FUNCTIONS				*/
/*----------------------------------------------------------------------*/

/**
* Just a little function to simulate some waiting time while the system is
* allegedly processing something. It will print out dots in fixed intervals.
* @param x The number of dots which will be printed
* @param y The time interval between each dot in y*0.5 seconds
*/
void sleep_and_print_dots(int x)
{
	while (x > 0) {
		Sleep(500);
		std::cout << ".";
		x--;
	}
}

/**
* Display a progress bar with adaptable width and progress speed
* @param step the step size await_and_print_dotsfter each interval
* @param width bar width
* @param interval wait interval in milliseconds, between each step
* @param info information string printed in front of the progress bar
*/
int progress_bar(double step, int width, unsigned long interval, std::string info)
{
	unsigned long time_in_millisec = interval;
	double bar_width = width;

	double progress = 0.0;
	while (progress <= 1.0) {
		std::cout << info << " [";
		double pos = bar_width * progress;
		for (double i = 0; i < bar_width; i++) {
			if (i < pos)
				std::cout << "*";
			else if (i == pos)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << "] " << std::dec << int(progress * 100.0) << "%\r";
		std::cout.flush();

		Sleep(time_in_millisec);
		progress += step;
	}

	progress = 1.0;
	std::cout << info.append(" [");
	double pos = bar_width * progress;
	for (double i = 0; i < bar_width; ++i) {
		if (i < pos)
			std::cout << "*";
		else if (i == pos)
			std::cout << "*";
		else
			std::cout << " ";
	}
	std::cout << "] " << std::dec << int(progress * 100.0) << "%\r";
	std::cout.flush();
	Sleep(time_in_millisec);
	std::cout << std::endl;

	return 0;
}

/**
* This is the intro which will be displayed when starting the programm. It
* simulates a connection process to make it look a little bit cooler.
*/
void play_intro(void)
{
	clear_screen();

	PRINTC(std::string("Welcome to ").append(agency.get_abbr().append(" OS 9.04.10\n")));
	Sleep(1000);

	//PlaySound(TEXT("../assets/sounds/ui/background terminal (1)"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);

	PRINTC(agency.get_name().append(" \n"));
	Sleep(500);

	PRINTC(agency.get_agenda().append(" \n"));
	Sleep(1000);

	PRINTLINE;
	Sleep(1000);

	display_line(">> Terminal ", 25);
	std::cout << HTERM;
	display_line(std::string(" connecting to ").append(agency.get_abbr()).append(" Central Archives"), 25);
	sleep_and_print_dots(4);
	std::cout << std::endl;

	PRINTC("Connection established\n");
	Sleep(1000);

	PRINTLINE;
	Sleep(1000);

	PRINTT("Establishing Secure VPN Tunnel");
	sleep_and_print_dots(3);
	std::cout << std::endl;
	PRINTT("VPN Tunnel opened\n");
	Sleep(500);

	PRINTT("Encrypting Connection\n");
	Sleep(750);
	PRINTT("Applying QES-16K RC32 Cipher Suite\n");
	progress_bar(0.02, 40, 40, "Status: ");
	Sleep(1000);

	PRINTT("Encryption complete\n");
	Sleep(500);

	PRINTT("Secure VPN Tunnel established\n");
	Sleep(1000);

	PRINTLINE;
	Sleep(1000);

	PRINTT("Loading Archive Data into System");
	sleep_and_print_dots(4);
	std::cout << std::endl;
	progress_bar(0.02, 40, 40, "Loading Object Archives:    ");
	Sleep(300);
	progress_bar(0.01, 40, 40, "Loading Report Archives:    ");
	Sleep(300);
	progress_bar(0.05, 40, 40, "Loading Personnel Archives: ");
	Sleep(300);
	progress_bar(0.08, 40, 40, "Loading Inventory Archives: ");
	Sleep(300);
	progress_bar(0.10, 40, 40, "Loading Event Archives:     ");
	Sleep(300);
	PRINTT("Database fully loaded\n");
	Sleep(1000);

	PRINTLINE;
	Sleep(2000);

	clear_screen();
}

/**
* Help function for the main menu.
* @return 0
*/
int main_help(void)
{
	clear_screen();
	header_main();
	print_help(MainRequestTable);
	return 0;
}
/**
* Help function for the object menu.
* @return 0
*/
int obj_help(void)
{
	clear_screen();
	header_obj();
	print_help(ObjectRequestTable);
	return 0;
}
/**
* Help function for the report menu.
* @return 0
*/
int rep_help(void)
{
	clear_screen();
	header_rep();
	print_help(ReportRequestTable);
	return 0;
}
/**
* Help function for the Personnel menu.
* @return 0
*/
int per_help(void)
{
	clear_screen();
	header_per();
	print_help(PersonnelRequestTable);
	return 0;
}
/**
* Help function for the event menu.
* @return 0
*/
int evt_help(void)
{
	clear_screen();
	header_evt();
	print_help(EventRequestTable);
	return 0;
}
/**
* Help function for the inventory menu.
* @return 0
*/
int inv_help(void)
{
	clear_screen();
	header_inv();
	print_help(InventoryRequestTable);
	return 0;
}


/**
* Printing out the descriptions of tab, giving the user some human-readable
* help.
* @param tab pointer to the table
* @return 0
*/
int print_help(struct menu_req_desc *tab) {
	struct menu_req_desc *main_req;

	for (main_req = tab; main_req->desc; main_req++) {
		if (main_req->id == (CHAR_IDENT | '#')) {
			continue;
		}
		else if ((main_req->id & CHAR_IDENT_MASK) == CHAR_IDENT) {
			printf("[%c]: %s %s\n", main_req->id & ~CHAR_IDENT_MASK,
				main_req->desc ? main_req->desc : "<no description>",
				main_req->func ? "" : "(unsupported)");
		}
		else {
			if (main_req->id == 0)
				continue;
			printf("[%d]: %s %s\n", main_req->id, main_req->desc ? main_req->desc
				: "<no description>", main_req->func ? "" : "(unsupported)");
		}
	}

	return (0);
}

/**
* Simulate a security violation in the system and eventually go into a
* security lockdown.
* @return 0
*/
int violation(int id)
{
	std::string msg;

	user.increase_violations();
	Sleep(1000);
	PRINTT("Access Denied\n");
	Sleep(1000);
	PRINTTH;
	display_line("Security Violation detected (", 25);
	std::cout << std::dec << user.get_violations() << "/" <<
		user.get_violation_threshold() << ")" << std::endl;;
	Sleep(1000);
	if (user.violation_treshold_reached()) {
		PRINTT("Security Violation Threshold reached\n");
		Sleep(1000);
		PRINTT("System Lockdown\n");
		Sleep(1000);
		PRINTT("Please stay calm. Authorities are on their way\n");
		while (AccessRightsHack.compare("unlock_kernel 0x1337")) {
			clear_screen();
			std::cout << HTERM << CABBR << ">> " <<
				"Security Violation Threshold reached\n";
			std::cout << HTERM << CABBR << ">> " <<
				"System Lockdown\n";
			std::cout << HTERM << CABBR << ">> " <<
				"Please stay calm. Authorities are on their way\n";
			std::getline(std::cin, AccessRightsHack);
		}
		user.reset_violations();
		AccessRightsHack = 1;
		msg.assign("System Unlocked\n");
		hack_header(id, msg);
		return 1;
	}
	return 0;
}

/**
* Check if the user has the necessary access rights for the menu.
* @param id Identifies which menu is requested
* @return 0 if user has access rights, -1 if not.
*/
int check_menu_access(int id)
{
	switch (id) {
	case MAIN_MENU_ID:
		return 0;
		break;
	case OBJ_MENU_ID:
		if (user.has_permissions(PERMISSIONS_OBJ_BASIC))
			return 0;
		break;
	case REP_MENU_ID:
		if (user.has_permissions(PERMISSIONS_REP_BASIC))
			return 0;
		break;
	case PER_MENU_ID:
		if (user.has_permissions(PERMISSIONS_PER_BASIC))
			return 0;
		break;
	case INV_MENU_ID:
		if (user.has_permissions(PERMISSIONS_INV_BASIC))
			return 0;
		break;
	case EVT_MENU_ID:
		if (user.has_permissions(PERMISSIONS_EVT_BASIC))
			return 0;
		break;
	default:
		std::cout << "Unknown Menu Id" << std::endl;

	}

	return -1;
}

/**
* Enter the object menu
* @return 0
*/
int obj_menu(void)
{
	if (check_menu_access(OBJ_MENU_ID) == -1) {
		violation(OBJ_MENU_ID);
		UserRequest = OBJ_REQ_NO_ACT;
	}
	else {
		clear_screen();
		header_obj();
		check_valid_cmd(ObjectRequestTable, std::string("@").append(agency.get_abbr()).append("-OBJ>> "));
		UserRequest = OBJ_REQ_NO_ACT;
	}

	return (0);
}

/**
* Enter the report menu
* @return 0
*/
int rep_menu(void)
{
	if (check_menu_access(REP_MENU_ID) == -1) {
		violation(REP_MENU_ID);
		UserRequest = REP_REQ_NO_ACT;
	}
	else {
		clear_screen();
		header_rep();
		check_valid_cmd(ReportRequestTable, std::string("@").append(agency.get_abbr()).append("-REP>> "));
		UserRequest = REP_REQ_NO_ACT;
	}

	return (0);
}

/**
* Enter the Personnel menu
* @return 0
*/
int per_menu(void)
{
	if (check_menu_access(PER_MENU_ID) == -1) {
		violation(PER_MENU_ID);
		UserRequest = PER_REQ_NO_ACT;
	}
	else {
		clear_screen();
		header_per();
		check_valid_cmd(PersonnelRequestTable, std::string("@").append(agency.get_abbr()).append("-PER>> "));
		UserRequest = PER_REQ_NO_ACT;
	}

	return (0);
}

/**
* Enter the event menu
* @return 0
*/
int evt_menu(void)
{
	if (check_menu_access(EVT_MENU_ID) == -1) {
		violation(EVT_MENU_ID);
		UserRequest = EVT_REQ_NO_ACT;
	}
	else {
		clear_screen();
		header_evt();
		check_valid_cmd(EventRequestTable, std::string("@").append(agency.get_abbr()).append("-EVT>> "));
		UserRequest = EVT_REQ_NO_ACT;
	}

	return (0);
}

/**
* Enter the inventory menu
* @return 0
*/
int inv_menu(void)
{
	if (check_menu_access(INV_MENU_ID) == -1) {
		violation(INV_MENU_ID);
		UserRequest = INV_REQ_NO_ACT;
	}
	else {
		clear_screen();
		header_inv();
		check_valid_cmd(InventoryRequestTable, std::string("@").append(agency.get_abbr()).append("-INV>> "));
		UserRequest = INV_REQ_NO_ACT;
	}

	return (0);
}

/**
* Enter the main menu
* @return 0
*/
int main_menu(void)
{
	clear_screen();
	header_main();
	check_valid_cmd(MainRequestTable, std::string("@").append(agency.get_abbr()).append(">> "));
	UserRequest = MAIN_REQ_NO_ACT;

	return (0);
}

/**
* Simulates a blinking print at the top of the screen
* @param text The text which shall appear blinking
* @param cnt Number of times it shall blink
*/
void blink(std::string text, unsigned long cnt)
{
	while (cnt > 0) {
		clear_screen();
		PRINTTH;
		std::cout << text;
		Sleep(1000);
		clear_screen();
		Sleep(1000);
		cnt--;
	}
	PRINTTH;
	std::cout << text;
	Sleep(1000);
}

int main_hack(void)
{
	hack_menu(MAIN_MENU_ID);
	main_help();
	return 0;
}

int obj_hack(void)
{
	hack_menu(OBJ_MENU_ID);
	obj_help();
	return 0;
}

int rep_hack(void)
{
	hack_menu(REP_MENU_ID);
	rep_help();
	return 0;
}

int per_hack(void)
{
	hack_menu(PER_MENU_ID);
	per_help();
	return 0;
}

int evt_hack(void)
{
	hack_menu(EVT_MENU_ID);
	evt_help();
	return 0;
}

int inv_hack(void)
{
	hack_menu(INV_MENU_ID);
	inv_help();
	return 0;
}

/**
* Enter the hacking menu. After hacking is done, show the main menu again.
* @return 0
*/
int hack_menu(int id)
{
	blink("System Exception detected\n", 2);

	PRINTT("Entering Kernel Mode\n");
	Sleep(1000);
	PRINTLINE;
	Sleep(1000);
	if (hack(id) == -1) {
		std::cerr << "Error in hack function" << std::endl;
		exit(-1);
	}

	clear_screen();
	UserRequest = MAIN_REQ_CHAR_H;
	return (0);
}

/**
* Print out the header of the main menu
*/
void header_main(void)
{
	PRINTT(agency.get_header().append("\n"));
	PRINTT(agency.get_site().append("\n"));
	PRINTT("Central Archives\n");
	PRINTLINE;
	Sleep(1000);
}

/**
* Print out the header of the object menu
*/
void header_obj(void)
{
	PRINTT(agency.get_header().append("\n"));
	PRINTT(agency.get_site().append("\n"));
	PRINTT("Central Archives > Object Archives\n");
	PRINTLINE;
	Sleep(1000);
}

/**
* Print out the header of the report menu
*/
void header_rep(void)
{
	PRINTT(agency.get_header().append("\n"));
	PRINTT(agency.get_site().append("\n"));
	PRINTT("Central Archives > Report Archives\n");
	PRINTLINE;
	Sleep(1000);
}

/**
* Print out the header of the Personnel menu
*/
void header_per(void)
{
	PRINTT(agency.get_header().append("\n"));
	PRINTT(agency.get_site().append("\n"));
	PRINTT("Central Archives > Personnel Archives\n");
	PRINTLINE;
	Sleep(1000);
}

/**
* Print out the header of the event menu
*/
void header_evt(void)
{
	PRINTT(agency.get_header().append("\n"));
	PRINTT(agency.get_site().append("\n"));
	PRINTT("Central Archives > Event Archives\n");
	PRINTLINE;
	Sleep(1000);
}

/**
* Print out the header of the inventory menu
*/
void header_inv(void)
{
	PRINTT(agency.get_header().append("\n"));
	PRINTT(agency.get_site().append("\n"));
	PRINTT("Central Archives > Inventory Archives\n");
	PRINTLINE;
	Sleep(1000);
}

/**
* Logout from the main menu
* @return exits the program
*/
int main_logout(void)
{
	MainRequestQuit = 1;

	exit(0);
}

/**
* Logout from the object menu
* @return 0
*/
int obj_logout(void)
{
	MainRequestQuit = 1;
	main_help();

	return (0);
}

/**
* Logout from the report menu
* @return 0
*/
int rep_logout(void)
{
	MainRequestQuit = 1;
	main_help();

	return (0);
}

/**
* Logout from the Personnel menu
* @return 0
*/
int per_logout(void)
{
	MainRequestQuit = 1;
	main_help();

	return (0);
}

/**
* Logout from the event menu
* @return 0
*/
int evt_logout(void)
{
	MainRequestQuit = 1;
	main_help();

	return (0);
}

/**
* Logout from the inventory menu
* @return 0
*/
int inv_logout(void)
{
	MainRequestQuit = 1;
	main_help();

	return (0);
}

/**
* Take a command from the user and check if it is a valid command for the
* menus. If it is, execute the appropriate function from the menu table.
* @param test_req_table A pointer to the menu table
* @param prompt The current prompt of the terminal
*/
void check_valid_cmd(struct menu_req_desc *menu_table, std::string prompt)
{

	struct menu_req_desc *main_req;

	print_help(menu_table);
	MainRequestQuit = 0;

	UserRequest = MAIN_REQ_NO_ACT;

	while (!MainRequestQuit) {
		/* allow task swap */
		Sleep(500);

		/* get request from stdin */
		UserRequest = user_par(prompt);

		/* search request in table */
		for (main_req = menu_table; main_req->desc; main_req++) {
			if (main_req->id == UserRequest)
				break;
		}

		/* 'Enter' without default was pressed */
		if ((main_req->id & ~CHAR_IDENT_MASK) == MAIN_REQ_NO_ACT) {
			UserRequest = MAIN_REQ_NO_ACT;
			continue;
		}

		/* check if table entry found */
		if (main_req->desc == NULL) {
			PRINTTH;
			display_line("Unknown Request ", 50);
			std::cout << UserRequest << std::endl;
			UserRequest = MAIN_REQ_NO_ACT;
			continue;
		}

		/* check if handler routine available */
		if (!main_req->func) {
			PRINTTH;
			display_line("Unsupported Request ", 50);
			std::cout << UserRequest << std::endl;
			UserRequest = MAIN_REQ_NO_ACT;
			continue;
		}

		/* request processing by handler */
		(*main_req->func)();

		/* reset default for hotkeys */
		if ((main_req->id & CHAR_IDENT_MASK) == CHAR_IDENT)
			UserRequest = MAIN_REQ_NO_ACT;
	}

	MainRequestQuit = 0;
}

/**
* Take a user input and convert it either into an integer or a char. This
* converted value will be used for the menu tables.
* @param prompt The current prompt of the terminal.
* @return The converted value
*/
int user_par(std::string prompt)
{
	int num = 0;
	std::string input = "";

	if (!user.violation_treshold_reached())
		PRINTTP;

	std::getline(std::cin, input);
	/**
	* If nothing is entered, do nothing.
	*/
	if (input.empty()) {
		return MAIN_REQ_NO_ACT;
	}

	/**
	* Safely converting string to integer
	*/
	std::stringstream myStream(input);
	if (myStream >> num) {
		return num;
	}

	num = input.c_str()[0] | CHAR_IDENT;
	return num;
}


/**
* Display a string line with a time interval of x milliseconds between each
* character
* @param line string to print
* @param x time interval in milliseconds
*/
void display_line(std::string line, int x) {
	for (unsigned i = 0; i < line.length(); ++i) {
		if (i != 0)
			Sleep(x);
		std::cout << line.at(i);
	}
}

/**
* Check if the current user has the necessary access rights for a specific
* file entry
* @param l line with the access rights
* @param f name of the file
* @return 0 if user has necessary access rights, -1 if not.
*/
int check_entry_permissions(std::string l, int id)
{
	if (l.find(ENTRY_BASIC) != std::string::npos) {
		if ((id == OBJ_MENU_ID && user.has_permissions(PERMISSIONS_OBJ_BASIC)) ||
			(id == REP_MENU_ID && user.has_permissions(PERMISSIONS_REP_BASIC)) ||
			(id == PER_MENU_ID && user.has_permissions(PERMISSIONS_PER_BASIC)) ||
			(id == INV_MENU_ID && user.has_permissions(PERMISSIONS_INV_BASIC)) ||
			(id == EVT_MENU_ID && user.has_permissions(PERMISSIONS_EVT_BASIC))) {
			return 0;
		}
		else {
			PRINTT("Access for Personnels only\n");
			return -1;
		}
	}
	if (l.find(ENTRY_RESTRICTED) != std::string::npos) {
		if ((id == OBJ_MENU_ID && user.has_permissions(PERMISSIONS_OBJ_RESTRICTED)) ||
			(id == REP_MENU_ID && user.has_permissions(PERMISSIONS_REP_RESTRICTED)) ||
			(id == PER_MENU_ID && user.has_permissions(PERMISSIONS_PER_RESTRICTED)) ||
			(id == INV_MENU_ID && user.has_permissions(PERMISSIONS_INV_RESTRICTED)) ||
			(id == EVT_MENU_ID && user.has_permissions(PERMISSIONS_EVT_RESTRICTED))) {
			return 0;
		}
		else {
			PRINTT("Access Restricted\n");
			return -1;
		}
	}
	if (l.find(ENTRY_CLASSIFIED) != std::string::npos) {
		if ((id == OBJ_MENU_ID && user.has_permissions(PERMISSIONS_OBJ_CLASSIFIED)) ||
			(id == REP_MENU_ID && user.has_permissions(PERMISSIONS_REP_CLASSIFIED)) ||
			(id == PER_MENU_ID && user.has_permissions(PERMISSIONS_PER_CLASSIFIED)) ||
			(id == INV_MENU_ID && user.has_permissions(PERMISSIONS_INV_CLASSIFIED)) ||
			(id == EVT_MENU_ID && user.has_permissions(PERMISSIONS_EVT_CLASSIFIED))) {
			return 0;
		}
		else {
			std::cout << std::hex << user.get_permissions() << " " << PERMISSIONS_OBJ_CLASSIFIED << std::endl;
			PRINTT("Access Classified\n");
			return -1;
		}
	}
	return 0;
}

/**
* Confirm the label of a file entry.
* @param l a string with the current line in which the label is supposed ot be
* @param s a string with the search query of the user
* @param p a pattern with which to match the search pattern
* @return 1 if the search (s) matches the pattern (p), and 0 if not.
*/
int search_label_found(std::string l, std::string s, std::string p)
{
	if (l.find(s) == std::string::npos)
		return 0;
	if (s.find(p.substr(3, std::string::npos)) == std::string::npos)
		return 0;
	if (l.find(p) == std::string::npos)
		return 0;

	return 1;
}

int access_string_found(std::string l)
{
	if (l.find("Access: "))
		return 0;

	return -1;
}

/**
* Search an entry in a file and print its content.
* @param f the name of the file you want to search
* @param p the file pattern
* @return 0 if successful, -1 else.
*/
int search_and_print_entry(std::string f, int id) {
	std::string search;
	std::string l;
	std::ifstream file;
	std::string pattern;

	switch (id) {
	case OBJ_MENU_ID:
		PRINTTOBJ("Search for: ");
		pattern.assign(PAT_OBJ);
		break;
	case REP_MENU_ID:
		PRINTTREP("Search for: ");
		pattern.assign(PAT_REP);
		break;
	case PER_MENU_ID:
		PRINTTPER("Search for: ");
		pattern.assign(PAT_PER);
		break;
	case EVT_MENU_ID:
		PRINTTEVT("Search for: ");
		pattern.assign(PAT_EVT);
		break;
	case INV_MENU_ID:
		PRINTTINV("Search for: ");
		pattern.assign(PAT_INV);
		break;
	default:
		PRINTT("Search for: ");
		break;
	}

	std::getline(std::cin, search);
	if (search.compare(QUIT) == 0)
		return 1;

	switch (id) {
	case OBJ_MENU_ID:
		PRINTTOBJ("Searching Database");
		break;
	case REP_MENU_ID:
		PRINTTREP("Searching Database");
		break;
	case PER_MENU_ID:
		PRINTTPER("Searching Database");
		break;
	case EVT_MENU_ID:
		PRINTTEVT("Searching Database");
		break;
	case INV_MENU_ID:
		PRINTTINV("Searching Database");
		break;
	default:
		PRINTT("Searching Database");
		break;
	}
	sleep_and_print_dots(4);
	std::cout << std::endl;

	file.open(f, std::fstream::in);
	if (!file.is_open())
		return -1;

	bool search_label_confirmed = false;
	bool access_string_confirmed = false;
	while (std::getline(file, l)) {
		if (!search_label_found(l, search, pattern) && !search_label_confirmed) 
			continue;
		else
			search_label_confirmed = true;

		if (!access_string_found(l) && !access_string_confirmed) 
			continue;
		else 
			access_string_confirmed = true;

		/**
		* check for required permissions and only continue if positive
		*/
		if (check_entry_permissions(l, id) == -1)
			return (-1);

		while (std::getline(file, l)) {
			/**
			* End of entry, close the file and return success
			*/
			if (l.find(Pattern_Delimiter) != std::string::npos) {
				file.close();
				return 0;
			}

			/**
			* print line from entry
			*/
			display_line(l, 25);

			std::cout << std::endl;
		}
	}

	PRINTT("Invalid Search Request\n");
	PRINTTH;
	PRINTT(search);
	display_line(" not found.\n", 25);

	file.close();
	return 0;
}

/**
* Print a list with all the labels in a file
* @param f the name of the file
* @param p the file pattern
* @return
*/

int print_list(std::ifstream *f, int id)
{
	std::string line;
	std::string pattern;

	switch (id) {
	case OBJ_MENU_ID:
		PRINTTOBJ("Searching Database");
		pattern.assign(PAT_OBJ);
		sleep_and_print_dots(3);
		std::cout << std::endl << "Object List" << std::endl;
		break;
	case REP_MENU_ID:
		PRINTTREP("Searching Database");
		pattern.assign(PAT_REP);
		sleep_and_print_dots(3);
		std::cout << std::endl << "Report List" << std::endl;
		break;
	case PER_MENU_ID:
		PRINTTPER("Searching Database");
		pattern.assign(PAT_PER);
		sleep_and_print_dots(3);
		std::cout << std::endl << "Personnel List" << std::endl;
		break;
	case EVT_MENU_ID:
		PRINTTEVT("Searching Database");
		pattern.assign(PAT_EVT);
		sleep_and_print_dots(3);
		std::cout << std::endl << "Event List" << std::endl;
		break;
	case INV_MENU_ID:
		PRINTTEVT("Searching Database");
		pattern.assign(PAT_INV);
		sleep_and_print_dots(3);
		std::cout << std::endl << "Inventory List" << std::endl;
		break;
	default:
		std::cerr << "Wrong ID" << std::endl;
		return -1;
	}


	while (std::getline(*f, line)) {
		if (line.find(pattern) == std::string::npos)
			continue;

		display_line(line.substr(3, std::string::npos), 25);
		std::cout << std::endl;
	}
	return 0;
}

/**
* List all the objects
* @return 0
*/
int obj_list()
{
	make_list(FILE_OBJ, OBJ_MENU_ID);
	UserRequest = OBJ_REQ_NO_ACT;
	return 0;
}

/**
* List all the reports
* @return 0
*/
int rep_list()
{
	make_list(FILE_REP, REP_MENU_ID);
	UserRequest = REP_REQ_NO_ACT;
	return 0;
}

/**
* List all the Personnels
* @return 0
*/
int per_list()
{
	make_list(FILE_PER, PER_MENU_ID);
	UserRequest = PER_REQ_NO_ACT;
	return 0;
}

/**
* List all the events
* @return 0
*/
int evt_list()
{
	make_list(FILE_EVT, EVT_MENU_ID);
	UserRequest = EVT_REQ_NO_ACT;
	return 0;
}

/**
* List all the inventory
* @return 0
*/
int inv_list()
{
	make_list(FILE_INV, INV_MENU_ID);
	UserRequest = INV_REQ_NO_ACT;
	return 0;
}

/**
* Make a list of all the labels in a file, if you have the necessary access
* rights
* @param f the name of the file
* @return 0 if successful, -1 else.
*/
int make_list(std::string f, int id)
{
	std::ifstream file;
	file.open(f);
	if (!file.is_open())
		return -1;

	switch (id) {
	case OBJ_MENU_ID:
		if (user.has_permissions(PERMISSIONS_OBJ_BASIC))
			print_list(&file, id);
		break;
	case REP_MENU_ID:
		if (user.has_permissions(PERMISSIONS_REP_BASIC))
			print_list(&file, id);
		break;
	case PER_MENU_ID:
		if (user.has_permissions(PERMISSIONS_PER_BASIC))
			print_list(&file, id);
		break;
	case EVT_MENU_ID:
		if (user.has_permissions(PERMISSIONS_EVT_BASIC))
			print_list(&file, id);
		break;
	case INV_MENU_ID:
		if (user.has_permissions(PERMISSIONS_INV_BASIC))
			print_list(&file, id);
		break;
	default:
		file.close();
		violation(id);
		return -1;
	}

	file.close();
	return 0;
}

/**
* Get a specific entry from the object file
* @return 0
*/
int obj_get()
{
	int result;

	result = get_entry(FILE_OBJ, OBJ_MENU_ID);
	UserRequest = MAIN_REQ_NO_ACT;

	/**
	* if the result was 1, the program just came from a violation
	* threshold, so the help has to be printed out again.
	*/
	if (result == 1) {
		obj_help();
	}

	return 0;
}

/**
* Get a specific entry from the report file
* @return 0
*/
int rep_get()
{
	int result;

	result = get_entry(FILE_REP, REP_MENU_ID);
	UserRequest = MAIN_REQ_NO_ACT;

	/**
	* if the result was 1, the program just came from a violation
	* threshold, so the help has to be printed out again.
	*/
	if (result == 1) {
		rep_help();
	}

	return 0;
}

/**
* Get a specific entry from the Personnel file
* @return 0
*/
int per_get()
{
	int result;

	result = get_entry(FILE_PER, PER_MENU_ID);
	UserRequest = MAIN_REQ_NO_ACT;

	/**
	* if the result was 1, the program just came from a violation
	* threshold, so the help has to be printed out again.
	*/
	if (result == 1) {
		per_help();
	}

	return 0;
}

/**
* Get a specific entry from the event file
* @return 0
*/
int evt_get()
{
	int result;

	result = get_entry(FILE_EVT, EVT_MENU_ID);
	UserRequest = MAIN_REQ_NO_ACT;

	/**
	* if the result was 1, the program just came from a violation
	* threshold, so the help has to be printed out again.
	*/
	if (result == 1) {
		evt_help();
	}

	return 0;
}

/**
* Get a specific entry from the inventory file
* @return 0
*/
int inv_get()
{
	int result;

	result = get_entry(FILE_INV, INV_MENU_ID);
	UserRequest = MAIN_REQ_NO_ACT;

	/**
	* if the result was 1, the program just came from a violation
	* threshold, so the help has to be printed out again.
	*/
	if (result == 1) {
		inv_help();
	}

	return 0;
}

/**
* Get an entry from a file, if you have the necessary access rights
* @param f the name of the file
* @return 0 if successfull, -1 else
*/
int get_entry(std::string f, int id)
{
	int result = 0;
	uint32_t current_permissions = agency.get_permissions();

	switch (id) {
	case MAIN_MENU_ID:
		return 0;
		break;
	case OBJ_MENU_ID:
		if (current_permissions & PERMISSIONS_OBJ_BASIC)
			result = search_and_print_entry(f, id);
		break;
	case REP_MENU_ID:
		if (current_permissions & PERMISSIONS_REP_BASIC)
			result = search_and_print_entry(f, id);
		break;
	case PER_MENU_ID:
		if (current_permissions & PERMISSIONS_PER_BASIC)
			result = search_and_print_entry(f, id);
		break;
	case INV_MENU_ID:
		if (current_permissions & PERMISSIONS_INV_BASIC)
			result = search_and_print_entry(f, id);
		break;
	case EVT_MENU_ID:
		if (current_permissions & PERMISSIONS_EVT_BASIC)
			result = search_and_print_entry(f, id);
		break;
	default:
		std::cout << "Unknown Menu Id" << std::endl;
	}

	if (result == -1) {
		result = violation(id);
		return result;
	}

	return 0;
}

/**
* clear the current screen.
*/
static inline void clear_screen(void)
{
	std::system("cls");
}

/**
* This header will be displayed when the user has done some hacking
*/
int hack_header(int id, std::string msg)
{
	clear_screen();
	PRINTK("System Inconsistency detected\n");
	sleep_and_print_dots(6);
	PRINTK(msg);
	PRINTK("Checking System Integrity");
	sleep_and_print_dots(3);
	std::cout << std::endl;
	progress_bar(0.05, 40, 50, "Status");
	PRINTK("System Integrity validated\n");
	Sleep(1000);
	PRINTLINE;
	Sleep(1000);
	PRINTK("Reloading Archive Data");
	sleep_and_print_dots(2);
	std::cout << std::endl;
	progress_bar(0.02, 40, 25, "Loading Object Archives");
	Sleep(250);
	progress_bar(0.01, 40, 25, "Loading Report Archives");
	Sleep(250);
	progress_bar(0.05, 40, 25, "Loading Personnel Archives");
	Sleep(250);
	progress_bar(0.08, 40, 25, "Loading Inventory Archives");
	Sleep(250);
	progress_bar(0.1, 40, 25, "Loading Event Archives");
	Sleep(1000);
	PRINTT("Database fully loaded\n");
	Sleep(1000);
	PRINTLINE;
	Sleep(2000);

	return id;
}

/**
* This function checks if the hack of the user is valid and grants him the
* appropriate access rights.
*/
int hack(int id)
{
	std::ifstream hack_file;
	std::string cmd;
	std::string line;
	std::string msg;

	hack_file.open(FILE_HACK);
	if (!hack_file.is_open()) {
		std::cerr << "Could not open file" << std::endl;
		return -1;
	}

	/* get hacking command from user */
	PRINTKH;
	std::getline(std::cin, cmd);

	while (std::getline(hack_file, line)) {
		/* look for the hacking command in the file */
		if (line.find(cmd) == std::string::npos)
			continue;

		/* if command was found, skip the # after it */
		int substring_index = line.find("#");
		line = line.substr(substring_index + 1, std::string::npos);

		/* retrieve the permissions bitmask */
		uint32_t permissions_bitmask = std::stoi(line.c_str(), nullptr, 16);
		agency.set_permissions(permissions_bitmask);

		/* set appropriate message */
		msg.assign("Access Permission Vector modified\n");
		hack_file.close();
	}

	if (hack_file.is_open()) {
		/* set appropriate message */
		msg.assign("System Intrusion detected\n");
		hack_file.close();
	}

	hack_header(id, msg);

	return 0;
}

/**
* The main entry point for the program.
* @return 0 when finished.
*/
int main(void)
{
	/**
	* Make stdout unbuffered. This is needed to print out strings one char
	* at a time.
	*/
	setvbuf(stdout, NULL, _IONBF, 0);

	/**
	* Initialize the random number generator, which is being used
	* throughout the whole program.
	*/
	srand((int)time(NULL));
	int r = rand();

	/**
	* Assign a randon number between 0 and 255 to \c Terminal
	*/
	Terminal = r % 255;

	/**
	* Start the intro
	*/
	//play_intro();

	/**
	* Go into the main menu
	*/
	main_menu();

	return 0;
}
