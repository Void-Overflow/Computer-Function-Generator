#include "Wave_Generator.h"
#include <cmath>
#include <iostream>

float mod(float a, float b) {
	return a - (long long)(a / b) * b;
}

float pingpong(float x, float period) {
	auto a = mod(x, period);
	return (a < period / 2 ? a : period - a);
}

void Wave_Generator::Generate_Wave() {
	const unsigned SAMPLES = 44100;

	sf::Int16 raw[SAMPLES];
	
	if (wave > 3) {
		wave = 0;
	}
	//Sine
	if (wave == 0) {
		for (unsigned i = 0; i < SAMPLES ; i++) {
			raw[i] = AMPLITUDE * sin(x * TWO_PI);
			x += increment;
		}
	}
	//Square
	else if (wave == 1) {
		for (unsigned i = 0; i < SAMPLES; i++) {
			raw[i] = AMPLITUDE * (sin(x * TWO_PI) < 0 ? -1 : 1);
			x += 5 * increment;
		}
	}
	//Noise
	else  if (wave == 2) {
		for (unsigned i = 0; i < SAMPLES; i++) {
			raw[i] = 100000000 * sin(x * TWO_PI);
			x += 100000000 * increment;
		}
	} 
	//Triangle
	else if (wave == 3) {
		for (unsigned i = 0; i < SAMPLES ; i++) {
			raw[i] = AMPLITUDE * (2 / 3.14159 * pingpong(x, TWO_PI) - 1);
			x += 40 * increment;
		}
	}

	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cout << "Loading Failed!\n";
	}

	Sound.setBuffer(Buffer);
	Sound.setLoop(true);
	Sound.play();
}

void Wave_Generator::End_Wave() {
	Sound.setLoop(false);
	Sound.stop();
}