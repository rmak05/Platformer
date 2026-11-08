#include <stdexcept>
#include "Game.hpp"

int main(){
	try{
		Game platformer;
		platformer.run();
	}
	catch(const std::exception& _e){
		print(_e.what());
	}

	return 0;
}

/*
TODO: constructor args of many classes can be made "const &", and use intitaliser like "class() : obj() {}"
*/
