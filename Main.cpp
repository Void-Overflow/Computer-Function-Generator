#include <iostream>
#include "Command_Handler.h"

int main() {
	Command_Handler obj; 
	std::cout << obj.start_session() << std::endl;
	return 0;
}