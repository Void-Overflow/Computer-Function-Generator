#include "Command_Handler.h"
#include "Config_Display.h"
#include <iostream>
#include <string>
#include <windows.h>

std::string removeWord(std::string str, std::string word){
	if (str.find(word) != std::string::npos)
	{
		size_t p = -1;
		std::string tempWord = word + " ";

		while ((p = str.find(word)) != std::string::npos)
			str.replace(p, tempWord.length(), "");

		tempWord = " " + word;

		while ((p = str.find(word)) != std::string::npos)
			str.replace(p, tempWord.length(), "");
	}

	return str;
}

std::string removeSpaces(std::string str){
	int count = 0;

	for (int i = 0; str[i]; i++)
		if (str[i] != ' ')
			str[count++] = str[i];

	str[count] = '\0';
	return str;
}

std::string Command_Handler::start_session() {
	while (true) {
		std::string in = "";
		std::getline(std::cin, in);
		
		if (in == "clear")
			system("CLS");

		if (in == "-on") {
			connection_status = true;
		}

		else if (in == "-off") {
			connection_status = false;
		}

		if (in.find("-amplitude") != std::string::npos) {
			try {
				removeSpaces(in);
				AMPLITUDE = std::stoi(removeWord(in, "-amplitude"));
				std::cout << "Set amplitude to " << removeWord(in, "-amplitude") << std::endl;
				status_changed = true;
			}
			catch (int e) {
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
			}
		}
		else if (in.find("-frequency") != std::string::npos) {
			try {
				removeSpaces(in);
				increment = (float)std::stoi(removeWord(in, "-frequency")) / SAMPLE_RATE;
				std::cout << "Set frequency to " << removeWord(in, "-frequency") << std::endl;
				status_changed = true;
			}
			catch (int e) {
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
			}
		}
		else if (in.find("-wave") != std::string::npos) {
			try {
				removeSpaces(in);
				wave = std::stoi(removeWord(in, "-wave"));
				std::cout << "Set wave to " << removeWord(in, "-wave") << std::endl;
				status_changed = true;
			}
			catch (int e) {
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
			}
		}

		if (status_changed == true && connection_status == true) {
		    End_Wave();
			Generate_Wave();

			currently_connected = true;
			status_changed = false;
		}

		else if (connection_status == true && currently_connected == false) {
			Generate_Wave();
			std::cout << "Wave generated from selected settings!\n";
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