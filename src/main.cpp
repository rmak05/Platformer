#include <iostream>
#include <stdexcept>
// #include "Game.hpp"

#include "utils/logger.hpp"

void test_logger(){
    logger::instantiate(log_level::debug);

    logger::debug("test");
    logger::info("test {} {}", 3, 4);
    logger::warning("test {} {}", "hi", 3.5f);
    logger::error("test {} {}", 0xa, "bye");
    logger::critical("test {}", 0);

    logger::destroy();
}

int main(){
    try{
        // Game platformer;
        // platformer.run();
        test_logger();
    }
    catch(const std::exception& _e){
        std::cout << _e.what() << std::endl;
    }

    return 0;
}

/*
TODO:
Constructor args of many classes can be made "const &", and use intitaliser like "class() : obj() {}"
Check that files don't contain tabs (use spaces instead).
Create a Logger (singleton class).
See if functions can be made inline.
Add GHA for tests and file formatting (like sorted imports, files containing only spaces no tabs)
Use specify variables like uint_x, int_x as opposed to unsigned, int
{} vs () variable initialization
*/
