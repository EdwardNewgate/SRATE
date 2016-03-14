/**
* @file   emulator.h
* @Author Andre (shirohige.git@gmail.com)
* @date   June, 2014
* @brief  Declaration file
*
* The declaration file for the Terminal Emulator.
*/

#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <iostream>
#include <sstream>

#include "Agency.h"
#include "User.h"

/*----------------------------------------------------------------------*/
/*				CLASSES					*/
/*----------------------------------------------------------------------*/

class Agency agency("../assets/texts/agency.txt");

/* User with all the basic permissions */
class User user(0x00022222, 3);

/*----------------------------------------------------------------------*/
/*				MACROS					*/
/*----------------------------------------------------------------------*/

/**
* Print out the hexadecimal terminal number, with 0xFF format, used in many
* print macros
*/
#define HTERM		std::hex << std::showbase << Terminal

/**
* This is used for creating the prompt of the terminal, in a way that it
* displays the abbreviation of your agency. If your agency's abbreviation is
* SCP, this macro will add "@SCP" to your prompt.
*/
#define CABBR		"@" << agency.get_abbr()

/**
* Print only the head of the prompt, without any text, like 0xf1@SCP.
*/
#define PRINTTH		std::cout << HTERM << CABBR << ">> ";

/**
* Print out the head of the kernel prompt without company abbreviation,
* used in hacking mode.
*/
#define PRINTKH		std::cout << HTERM << ":kernel>> "; 

/*
* The following macros are situational prompts, so that you always have the
* correct one depending on in which menu you currently are.
*/
#define PRINTT(txt) \
	do { \
		std::cout << HTERM << CABBR << ">> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTTOBJ(txt) \
	do { \
		std::cout << HTERM << CABBR << "-OBJ>> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTTREP(txt)	\
	do { \
		std::cout << HTERM << CABBR << "-REP>> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTTPER(txt) \
	do { \
		std::cout << HTERM << CABBR << "-PER>> ";  \
		display_line(txt, 25); \
	} while (0);

#define PRINTTEVT(txt) \
	do { \
		std::cout << HTERM << CABBR << "-EVT>> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTTINV(txt) \
	do { \
		std::cout << HTERM << CABBR << "-INV>> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTK(txt) \
	do { \
		std::cout << HTERM << ":kernel>> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTC(txt) \
	do { \
		std::cout << ">> "; \
		display_line(txt, 25); \
	} while (0);

#define PRINTTP			std::cout << HTERM << prompt


#define PRINTLINE		std::cout << "---------------------------------------------" << std::endl;

#define CHAR_IDENT		0x01000000
#define CHAR_IDENT2		0x00100000
#define CHAR_IDENT_MASK		0xffffff00

/*
* Access right codes in a PERMISSIONS_X_Y format, where X identifies the location in
* the database and Y the level of access. The actual access right codes are
* in a hexadecimal format.
*/
#define PERMISSIONS_OBJ_BASIC		0x00000002
#define PERMISSIONS_OBJ_RESTRICTED	0x00000004
#define PERMISSIONS_OBJ_CLASSIFIED	0x00000008
#define PERMISSIONS_REP_BASIC		0x00000020
#define PERMISSIONS_REP_RESTRICTED	0x00000040
#define PERMISSIONS_REP_CLASSIFIED	0x00000080
#define PERMISSIONS_PER_BASIC		0x00000200
#define PERMISSIONS_PER_RESTRICTED	0x00000400
#define PERMISSIONS_PER_CLASSIFIED	0x00000800
#define PERMISSIONS_INV_BASIC		0x00002000
#define PERMISSIONS_INV_RESTRICTED	0x00004000
#define PERMISSIONS_INV_CLASSIFIED	0x00008000
#define PERMISSIONS_EVT_BASIC		0x00020000
#define PERMISSIONS_EVT_RESTRICTED	0x00040000
#define PERMISSIONS_EVT_CLASSIFIED	0x00080000
#define PERMISSIONS_BASIC		0x00022222
#define PERMISSIONS_RESTRICTED		0x00044444
#define PERMISSIONS_CLASSIFIED		0x00088888
#define PERMISSIONS_GOD_MODE		0xffffffff

/*
* The there kinds of access modes: Basic, Restricted and Classified, whereas
* Classified is the highest rank
*/
#define ENTRY_BASIC		"Basic"
#define ENTRY_RESTRICTED	"Restricted"
#define ENTRY_CLASSIFIED	"Classified"

/*
* those are the filenames from which the program gets all its data. For more
* on those files, see X
*/
#define FILE_OBJ		"../assets/texts/data/objects.txt"
#define FILE_REP		"../assets/texts/data/reports.txt"
#define FILE_PER		"../assets/texts/data/personnel.txt"
#define FILE_EVT		"../assets/texts/data/events.txt"
#define FILE_INV		"../assets/texts/data/inventory.txt"
#define FILE_HACK		"../assets/texts/data/hacking.txt"

/*
* Those are the patterns describe the labels from the file entries.
*/
#define PAT_OBJ			std::string(">> ").append(agency.get_abbr()).append("-OBJ-")
#define PAT_REP			std::string(">> ").append(agency.get_abbr()).append("-REP-")
#define PAT_PER			std::string(">> ").append(agency.get_abbr()).append("-PER-")
#define PAT_INV			std::string(">> ").append(agency.get_abbr()).append("-INV-")
#define PAT_EVT			std::string(">> ").append(agency.get_abbr()).append("-EVT-")

/**
* These are used to leave/abort a menu.
*/
#define QUIT			"q"
/*----------------------------------------------------------------------*/
/*				DATATYPES				*/
/*----------------------------------------------------------------------*/

/**
* Enum for identifying the different menus in the code.
*/
enum menu_identifier {
	MAIN_MENU_ID,	/* 0 */		//!< MAIN_MENU_ID
	OBJ_MENU_ID,	/* 1 */		//!< OBJ_MENU_ID
	REP_MENU_ID,	/* 2 */		//!< REP_MENU_ID
	PER_MENU_ID,	/* 3 */		//!< PER_MENU_ID
	INV_MENU_ID,	/* 4 */		//!< INV_MENU_ID
	EVT_MENU_ID	/* 5 */		//!< EVT_MENU_ID
};

/**
* All commands of the main menu.
*/
enum main_request_table {
	MAIN_REQ_NO_ACT,			//!< MAIN_REQ_NO_ACT No command
	MAIN_REQ_OBJ,				//!< MAIN_REQ_OBJ Request access to object menu
	MAIN_REQ_REP,				//!< MAIN_REQ_REP Request access to report menu
	MAIN_REQ_PER,				//!< MAIN_REQ_PER Request access to Personnel menu
	MAIN_REQ_EVT,				//!< MAIN_REQ_EVT Request access to event menu
	MAIN_REQ_INV,				//!< MAIN_REQ_INV Request access to inventory menu
	MAIN_REQ_HACK = CHAR_IDENT | '#',	//!< MAIN_REQ_HACK Request access to hack menu
	MAIN_REQ_CHAR_QST = CHAR_IDENT | '?',	//!< MAIN_REQ_CHAR_QUEST Print main menu help
	MAIN_REQ_CHAR_H = CHAR_IDENT | 'h',	//!< MAIN_REQ_CHAR_H Print main menu help
	MAIN_REQ_CHAR_Q = CHAR_IDENT | 'q',	//!< MAIN_REQ_CHAR_Q Quit main menu
	MAIN_REQ_MAX				//!< MAIN_REQ_MAX
};

/**
* All commands of the object menu.
*/
enum obj_request_table {
	OBJ_REQ_NO_ACT,				//!< OBJ_REQ_NO_ACT
	OBJ_REQ_LIST,				//!< OBJ_REQ_LIST
	OBJ_REQ_ENTRY,				//!< OBJ_REQ_ENTRY
	OBJ_REQ_HACK_ADV,			//!< OBJ_REQ_HACK_ADV
	OBJ_REQ_CHAR_QST = CHAR_IDENT | '?',	//!< OBJ_REQ_CHAR_QUEST
	OBJ_REQ_CHAR_H = CHAR_IDENT | 'h',	//!< OBJ_REQ_CHAR_H
	OBJ_REQ_CHAR_Q = CHAR_IDENT | 'q',	//!< OBJ_REQ_CHAR_Q
	OBJ_REQ_MAX				//!< OBJ_REQ_MAX
};

/**
* All commands of the report menu.
*/
enum rep_request_table {
	REP_REQ_NO_ACT,				//!< REP_REQ_NO_ACT
	REP_REQ_LIST,				//!< REP_REQ_LIST
	REP_REQ_ENTRY,				//!< REP_REQ_ENTRY
	REP_REQ_HACK_ADV,			//!< REP_REQ_HACK_ADV
	REP_REQ_CHAR_QST = CHAR_IDENT | '?',	//!< REP_REQ_CHAR_QUEST
	REP_REQ_CHAR_H = CHAR_IDENT | 'h',	//!< REP_REQ_CHAR_H
	REP_REQ_CHAR_Q = CHAR_IDENT | 'q',	//!< REP_REQ_CHAR_Q
	REP_REQ_MAX				//!< REP_REQ_MAX
};

/**
* All commands of the Personnel menu.
*/
enum per_request_table {
	PER_REQ_NO_ACT,				//!< PER_REQ_NO_ACT
	PER_REQ_LIST,				//!< PER_REQ_LIST
	PER_REQ_ENTRY,				//!< PER_REQ_ENTRY
	PER_REQ_HACK_ADV,			//!< PER_REQ_HACK_ADV
	PER_REQ_CHAR_QST = CHAR_IDENT | '?',	//!< PER_REQ_CHAR_QUEST
	PER_REQ_CHAR_H = CHAR_IDENT | 'h',	//!< PER_REQ_CHAR_H
	PER_REQ_CHAR_Q = CHAR_IDENT | 'q',	//!< PER_REQ_CHAR_Q
	PER_REQ_MAX				//!< PER_REQ_MAX
};

/**
* All commands of the inventory menu.
*/
enum inv_request_table {
	INV_REQ_NO_ACT,				//!< INV_REQ_NO_ACT
	INV_REQ_LIST,				//!< INV_REQ_LIST
	INV_REQ_ENTRY,				//!< INV_REQ_ENTRY
	INV_REQ_HACK_ADV,			//!< INV_REQ_HACK_ADV
	INV_REQ_CHAR_QST = CHAR_IDENT | '?',	//!< INV_REQ_CHAR_QUEST
	INV_REQ_CHAR_H = CHAR_IDENT | 'h',	//!< INV_REQ_CHAR_H
	INV_REQ_CHAR_Q = CHAR_IDENT | 'q',	//!< INV_REQ_CHAR_Q
	INV_REQ_MAX				//!< INV_REQ_MAX
};

/**
* All commands of the event menu.
*/
enum evt_request_table {
	EVT_REQ_NO_ACT,				//!< EVT_REQ_NO_ACT
	EVT_REQ_LIST,				//!< EVT_REQ_LIST
	EVT_REQ_ENTRY,				//!< EVT_REQ_ENTRY
	EVT_REQ_HACK_ADV,			//!< EVT_REQ_HACK_ADV
	EVT_REQ_CHAR_QST = CHAR_IDENT | '?',	//!< EVT_REQ_CHAR_QUEST
	EVT_REQ_CHAR_H = CHAR_IDENT | 'h',	//!< EVT_REQ_CHAR_H
	EVT_REQ_CHAR_Q = CHAR_IDENT | 'q',	//!< EVT_REQ_CHAR_Q
	EVT_REQ_MAX				//!< EVT_REQ_MAX
};

/**
* A generic handler for all the menu commands
* @return integer
*/
typedef int(*REQ_HNDL)(void);

/**
* A structure to compose all the menu tables.
*/
struct menu_req_desc {
	int id;			/*! test request identifier */
	const char *desc;	/*! test description string */
	REQ_HNDL func;		/*! test request handler */
};

/*----------------------------------------------------------------------*/
/*			FUNCTION PROTOTYPES				*/
/*----------------------------------------------------------------------*/

/*
* Main menu related functions
*/
void play_intro(void);
int main_menu(void);
int main_help(void);
int main_logout(void);

/*
* Object menu related functions
*/
int obj_menu(void);
int obj_list(void);
int obj_get(void);
int obj_help(void);
int obj_logout(void);

/*
* Report menu related functions
*/
int rep_menu(void);
int rep_list(void);
int rep_get(void);
int rep_help(void);
int rep_logout(void);

/*
* Personnel menu related functions
*/
int per_menu(void);
int per_list(void);
int per_get(void);
int per_help(void);
int per_logout(void);

/*
* Event menu related functions
*/
int evt_menu(void);
int evt_list(void);
int evt_get(void);
int evt_help(void);
int evt_logout(void);

/*
* Inventory menu related functions
*/
int inv_menu(void);
int inv_list(void);
int inv_get(void);
int inv_help(void);
int inv_logout(void);

/*
* Hacking related functions
*/
int main_hack(void);
int obj_hack(void);
int rep_hack(void);
int per_hack(void);
int evt_hack(void);
int inv_hack(void);
int hack_menu(int id);
int hack(int id);
int violation(int id);
int check_menu_access(int id);
void blink(std::string text, unsigned long cnt);

int make_list(std::string f, int id);
int get_entry(std::string f, int id);
int search_and_print_entry(std::string f, int id);
int check_entry_permissions(std::string l, int id);
int search_label_found(std::string l, std::string s, std::string p);
int access_string_found(std::string l);
int print_list(std::ifstream *f, int id);
int hack_header(int id, std::string msg);

int print_help(struct menu_req_desc *tab);
void header_main(void);
void header_obj(void);
void header_rep(void);
void header_per(void);
void header_evt(void);
void header_inv(void);

int progress_bar(double step, int width, unsigned long interval, std::string info);
void display_line(std::string line, int x);
void sleep_and_print_dots(int x);
static inline void clear_screen(void);

void check_valid_cmd(struct menu_req_desc *menu_table, std::string prompt);
int user_par(std::string prompt);

/*----------------------------------------------------------------------*/
/*				GLOBALS					*/
/*----------------------------------------------------------------------*/

/* search related */

/**
* delimiter pattern all data files
*/
std::string Pattern_Delimiter = "####";

/**
* Search patterns for each of the files. The program uses these to find the
* labels of an entry, for either printing out the entry or listing all the
* labels.
*/
std::string PatternObject(PAT_OBJ);
std::string PatternReport = PAT_REP;
std::string PatternPersonnel = PAT_PER;
std::string PatternInventory = PAT_INV;
std::string PatternEvent = PAT_EVT;
std::string PatternAccess = "Access:";

/**
* Access rights related
*/
/**
* As default the user has basic access rights to everything.
*/
std::string AccessRightsHack = "";
uint16_t Terminal = 0x0001;

int UserRequest = MAIN_REQ_NO_ACT; /*!< user request */
int MainRequestQuit = 0; /*!< quit test request handling flag */


						 /**
						 * main request description table
						 */
static struct menu_req_desc MainRequestTable[] = { {
		MAIN_REQ_NO_ACT, 	"no action", 					NULL },{
		MAIN_REQ_OBJ, 		"Access Object Archive", 		obj_menu },{
		MAIN_REQ_REP, 		"Access Report Archive", 		rep_menu },{
		MAIN_REQ_PER, 		"Access Personnel Archive",		per_menu },{
		MAIN_REQ_EVT, 		"Access Event Archive",			evt_menu },{
		MAIN_REQ_INV,		"Access Inventory Archive",		inv_menu },{

		MAIN_REQ_HACK, 		"Access Rights", 				main_hack },{
		MAIN_REQ_CHAR_QST,	"Show Main Menu", 				main_help },{
		MAIN_REQ_CHAR_H, 	"Show Main Menu", 				main_help },{
		MAIN_REQ_CHAR_Q, 	"Logout", 						main_logout },{
		MAIN_REQ_MAX, 		NULL, 							NULL }
};

static struct menu_req_desc ObjectRequestTable[] = { {
		OBJ_REQ_NO_ACT,		"no action", 							NULL },{
		OBJ_REQ_LIST, 		"(SCI-1F-OBJ) List all Objects", 		obj_list },{
		OBJ_REQ_ENTRY, 		"(SCI-1F-OBJ) Search Object Entry",		obj_get },{

		MAIN_REQ_HACK, 		"Access Rights", 						obj_hack },{
		OBJ_REQ_CHAR_QST, 	"?: Show Command Menu", 				obj_help },{
		OBJ_REQ_CHAR_H, 	"h: Show Command Menu", 				obj_help },{
		OBJ_REQ_CHAR_Q, 	"q:  Back to main menu", 				obj_logout },{
		OBJ_REQ_MAX, 		NULL, 									NULL }
};

static struct menu_req_desc ReportRequestTable[] = { {
		REP_REQ_NO_ACT, 	"no action", 							NULL },{
		REP_REQ_LIST, 		"(SCI-1F-REP) List all Reports",		rep_list },{
		REP_REQ_ENTRY, 		"(SCI-1F-REP) Search Report Entry", 	rep_get },{

		MAIN_REQ_HACK, 		"Access Rights", 						rep_hack },{
		REP_REQ_CHAR_QST, 	"?: Show Command Menu", 				rep_help },{
		REP_REQ_CHAR_H, 	"h: Show Command Menu", 				rep_help },{
		REP_REQ_CHAR_Q, 	"q:  Back to main menu", 				rep_logout },{
		REP_REQ_MAX, 		NULL, 									NULL }
};

static struct menu_req_desc PersonnelRequestTable[] = { {
		PER_REQ_NO_ACT, 	"no action", 							NULL },{
		PER_REQ_LIST, 		"(SCI-1F-PER) List all Personnel",		per_list },{
		PER_REQ_ENTRY, 		"(SCI-1F-PER) Search Personnel Entry",	per_get },{

		MAIN_REQ_HACK, 		"Access Rights", 						per_hack },{
		PER_REQ_CHAR_QST, 	"?: Show Command Menu", 				per_help },{
		PER_REQ_CHAR_H, 	"h: Show Command Menu", 				per_help },{
		PER_REQ_CHAR_Q, 	"q:  Back to main menu", 				per_logout },{
		PER_REQ_MAX, 		NULL, 									NULL }
};

static struct menu_req_desc EventRequestTable[] = { {
		EVT_REQ_NO_ACT, 	"no action", 						NULL },{
		EVT_REQ_LIST, 		"(SCI-1F-EVT) List all Events", 	evt_list },{
		EVT_REQ_ENTRY, 		"(SCI-1F-EVT) Search Event Entry", 	evt_get },{

		MAIN_REQ_HACK, 		"Access Rights", 					evt_hack },{
		EVT_REQ_CHAR_QST, 	"?: Show Command Menu", 			evt_help },{
		EVT_REQ_CHAR_H, 	"h: Show Command Menu", 			evt_help },{
		EVT_REQ_CHAR_Q, 	"q:  Back to main menu", 			evt_logout },{
		EVT_REQ_MAX, 		NULL, 								NULL }
};

static struct menu_req_desc InventoryRequestTable[] = { {
		INV_REQ_NO_ACT, 	"no action", 							NULL },{
		INV_REQ_LIST, 		"(SCI-1F-INV) List all Inventory", 		inv_list },{
		INV_REQ_ENTRY, 		"(SCI-1F-INV) Search Inventory Entry",	inv_get },{

		MAIN_REQ_HACK, 		"Access Rights", 						inv_hack },{
		INV_REQ_CHAR_QST, 	"?: Show Command Menu", 				inv_help },{
		INV_REQ_CHAR_H, 	"h: Show Command Menu", 				inv_help },{
		INV_REQ_CHAR_Q, 	"q:  Back to main menu", 				inv_logout },{
		INV_REQ_MAX, 		NULL, 									NULL }
};

struct thread_parameters {
	int loop = 1;
};

#ifdef CLASSES
class User_Class {
public:
	int get_access_rights();
	int set access_rights();

private:
	unsigned short access_rights;

};

class Server_Class {
public:

private:

};
#endif

#endif /* EMULATOR_H_ */
