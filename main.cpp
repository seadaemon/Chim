#include <iostream>
#include <exception>
#include "chim.hpp"

int main(int argc, char *argv[]) {
	
	chim::Chim app;

	try {
		app.Init();
		app.Run();
		app.Cleanup();
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}