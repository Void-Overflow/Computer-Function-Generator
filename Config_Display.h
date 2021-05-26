#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#include <string>

class Config_Display{
public:
	bool status = false;
	unsigned long amplitude = 30000;
	long double frequency = 500.;
	unsigned long wave = 0;

	std::string return_status();
	std::string return_amplitude();
	std::string return_frequency();
	std::string return_wave();

	std::string return_format();
};

#endif
