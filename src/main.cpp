#include <stdexcept>
// #include "Game.hpp"

int main(){
    try{
        // Game platformer;
        // platformer.run();
    }
    catch(const std::exception& _e){
        // print(_e.what());
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
