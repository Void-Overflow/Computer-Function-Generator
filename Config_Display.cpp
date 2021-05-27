#include "Config_Display.h"
#include <windows.h>
#include <iostream>

std::string Config_Display::return_status() {
	std::string status_string = "";
	if (status == true) 
		status_string = "ON";
	else
		status_string = "OFF";

	return "On/Off: " + status_string + ";";
}

std::string Config_Display::return_amplitude() {
	return " Amp. " + std::to_string(amplitude) + ";";
}

std::string Config_Display::return_frequency() {
	return " Freq. " + std::to_string((int)frequency) + ";";
}

std::string Config_Display::return_wave() {
	std::string wave_type = "";
	
	if (wave > 3) {
		wave = 0;
	}

	if (wave == 0) {
		wave_type = "Sine";
	}

	else if (wave == 1) {
		wave_type = "Square";
	}

	else if (wave == 2) {
		wave_type = "Triangle";
	}

	else if (wave == 3) {
		wave_type = "Noise";
	}

	return " Wave:" + wave_type + ";";
}

std::string Config_Display::return_format() {
	std::string status_value = return_status();
	std::string amplitude_value = return_amplitude();
	std::string frequency_value = return_frequency();
	std::string wave_value = return_wave();

	HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(std_output, 13);
	std::cout << "Configuration - \n ";

	if(status == true)
		SetConsoleTextAttribute(std_output, FOREGROUND_GREEN);
	else
		SetConsoleTextAttribute(std_output, FOREGROUND_RED);

	std::cout << status_value;

	SetConsoleTextAttribute(std_output, 9);
	std::cout << wave_value;

	SetConsoleTextAttribute(std_output, FOREGROUND_RED);
	std::cout << frequency_value;

	SetConsoleTextAttribute(std_output, 3);
	std::cout << amplitude_value << std::endl;

	SetConsoleTextAttribute(std_output, 7);

	return status_value + wave_value + frequency_value + amplitude_value;
}