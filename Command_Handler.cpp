#include "Command_Handler.h"
#include "Config_Display.h"
#include <iostream>
#include <string>
#include <windows.h>

std::string removeWord(std::string str, std::string word){
	if (str.find(word) != std::string::npos){
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
	HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);
	Config_Display obj;

	obj.return_format();
	
	SetConsoleTextAttribute(std_output, 3);
	std::cout << "> ";
	SetConsoleTextAttribute(std_output, 7);

	while (true) {
		std::string in = "";
		std::getline(std::cin, in);
		
		if (in == "clear") {
			system("CLS");

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}

		else if (in == "-on") {
			connection_status = true;

		}

		else if (in == "-off") 
			connection_status = false;


		else if (in == "exit" || in == "quit") {
			break;
		}

		else if (in.find("-amplitude") != std::string::npos) {
			try {
				removeSpaces(in);
				AMPLITUDE = std::stoi(removeWord(in, "-amplitude"));

				SetConsoleTextAttribute(std_output, FOREGROUND_RED);
				std::cout << "Set amplitude to " << removeWord(in, "-amplitude") << std::endl;
				SetConsoleTextAttribute(std_output, 7);

				status_changed = true;
			}
			catch (int e) {
				SetConsoleTextAttribute(std_output, 10);
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
				SetConsoleTextAttribute(std_output, 7);
			}

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}
		else if (in.find("-frequency") != std::string::npos) {
			try {
				removeSpaces(in);
				increment = (float)std::stoi(removeWord(in, "-frequency")) / SAMPLE_RATE;

				SetConsoleTextAttribute(std_output, FOREGROUND_RED);
				std::cout << "Set frequency to " << removeWord(in, "-frequency") << std::endl;
				SetConsoleTextAttribute(std_output, 7);

				status_changed = true;
			}
			catch (int e) {
				SetConsoleTextAttribute(std_output, 10);
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
				SetConsoleTextAttribute(std_output, 7);
			}

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}
		else if (in.find("-wave") != std::string::npos) {
			try {
				removeSpaces(in);
				wave = std::stoi(removeWord(in, "-wave"));

				SetConsoleTextAttribute(std_output, FOREGROUND_RED);
				std::cout << "Set wave to " << removeWord(in, "-wave") << std::endl;
				SetConsoleTextAttribute(std_output, 7);

				status_changed = true;
			}
			catch (int e) {
				SetConsoleTextAttribute(std_output, 10);
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
				SetConsoleTextAttribute(std_output, 7);
			}

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}
		else if (in.find("-config") != std::string::npos) {
			try {
				obj.status = currently_connected;
				obj.amplitude = AMPLITUDE;
				obj.frequency = (int)(increment * SAMPLE_RATE);
				obj.wave = wave;

				obj.return_format();
			}
			catch (int e) {
				SetConsoleTextAttribute(std_output, 10);
				std::cout << "Exception Nr." << e << " Has occured. It could be linked to incorrect syntax. Try rewritting the command?\n";
				SetConsoleTextAttribute(std_output, 7);
			}

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}

		else if (in == "-help") {
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "\n-on |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " turns on wave based off config\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "-off |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " turns off wave\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "-config |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " shows configuration for wave.\n\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "-amplitude -input |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " sets amplitude for wave off - input.Max is 30000.\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "-frequency -input |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " sets frequency for wave off - input.Max is 20khz.\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "-wave -index |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " chooses type of wave off - index.Max index is 3.\n\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "-clear |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " clears terminal.\n";
			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "exit / quit |";
			SetConsoleTextAttribute(std_output, 3);
			std::cout << " closes application window.\n \n";

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}

		else {
			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}


		if (status_changed == true && connection_status == true) {
		    End_Wave();
			Generate_Wave();

			currently_connected = true;
			status_changed = false;
		}

		else if (connection_status == true && currently_connected == false) {
			Generate_Wave();

			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "Wave generated from selected configuration!\n";
			SetConsoleTextAttribute(std_output, 7);

			currently_connected = true;

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}

		else if (connection_status == false && currently_connected == true) {
			End_Wave();

			SetConsoleTextAttribute(std_output, FOREGROUND_RED);
			std::cout << "Stopped wave\n";
			SetConsoleTextAttribute(std_output, 7);

			currently_connected = false;

			SetConsoleTextAttribute(std_output, 3);
			std::cout << "> ";
			SetConsoleTextAttribute(std_output, 7);
		}


		sf::sleep(sf::milliseconds(100));
	}
	return "\0";
}