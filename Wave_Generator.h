#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

#include <SFML/Audio.hpp>


class Wave_Generator{
private:
	const double TWO_PI = 6.28318;
	double x = 0;

	sf::SoundBuffer Buffer;
	sf::Sound Sound;
public:
	const unsigned SAMPLE_RATE = 44100;
	unsigned AMPLITUDE = 30000;
	unsigned int wave = 0;
	double increment = 500. / SAMPLE_RATE;

	void Generate_Wave();
	void End_Wave();
};

#endif
