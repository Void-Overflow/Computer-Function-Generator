#include "Wave_Generator.h"
#include <cmath>
#include <iostream>

void Wave_Generator::Generate_Wave() {
	const unsigned SAMPLES = 44100;

	sf::Int16 raw[SAMPLES];
	
	if (wave > 0) {
		wave = 0;
	}
	if (wave == 0) {
		for (unsigned i = 0; i < SAMPLES; i++) {
			raw[i] = AMPLITUDE * sin(x * TWO_PI);
			x += increment;
		}
	}
	else if (wave == 1) {
		for (unsigned i = 0; i < SAMPLES; i++) {
			raw[i] = AMPLITUDE * sin(x * TWO_PI);
			x += increment;
		}
	}
	else  if (wave == 2) {
		for (unsigned i = 0; i < SAMPLES; i++) {
			raw[i] = AMPLITUDE * sin(x * TWO_PI);
			x += increment;
		}
	}
	else if (wave == 3) {
		for (unsigned i = 0; i < SAMPLES; i++) {
			raw[i] = AMPLITUDE * sin(x * TWO_PI);
			x += increment;
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