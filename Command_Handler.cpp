#include "Command_Handler.h"
#include "Config_Display.h"
#include <iostream>
#include <string>

std::string Command_Handler::start_session() {
	while (true) {
		std::string in = "";
		std::getline(std::cin, in);
		
		if (in == "-on") {
			connection_status = true;
		}

		else if (in == "-off") {
			connection_status = false;
		}


		if (status_changed == true) {
		    End_Wave();
			Generate_Wave();
			status_changed == false;
		}

		else if (connection_status == true && currently_connected == false) {
			Generate_Wave();
			std::cout << "Sine wave generated from selected settings!\n";
			currently_connected = true;
		}
		else if (connection_status == false && currently_connected == true) {
			End_Wave();
			std::cout << "Stopped wave\n";
			currently_connected = false;
		}

		sf::sleep(sf::milliseconds(100));
	}
}