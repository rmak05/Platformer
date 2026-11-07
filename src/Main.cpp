#include <stdexcept>
#include "Game.hpp"

int main() {
	std::ofstream error_file("error.txt");
	if (error_file.fail()) std::cerr << "Failed to redirect stderr to error.txt" << std::endl;
	else redirect_stderr(error_file);
	debug::activate();

	try {
		Game platformer;
		platformer.run();
	}
	catch (const std::runtime_error& _re) {
		print(_re.what());
	}
	catch (const std::exception& _e) {
		print(_e.what());
	}

	debug::deactivate();
	error_file.close();
	
	return 0;
}

/*
TODO: constructor args of many classes can be made "const &", and use intitaliser like "class() : obj() {}"
*/