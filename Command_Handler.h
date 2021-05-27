#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>
#include "Wave_Generator.h"

class Command_Handler : public Wave_Generator{
private:
	bool connection_status = false;
	bool status_changed = false;
	bool currently_connected = false;

public:
	std::string start_session();
};

#endif
