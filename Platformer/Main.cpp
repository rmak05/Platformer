#include "Game.hpp"

int main() {
	std::ofstream error_file("error.txt");
	if (error_file.fail()) std::cerr << "Failed to redirect stderr to error.txt" << std::endl;
	else redirect_stderr(error_file);
	debug::activate();

	Game platformer;
	platformer.run();

	debug::deactivate();
	error_file.close();
	
	return 0;
}