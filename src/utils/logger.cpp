#include <format>
#include <fstream>
#include <utility>
#include "utils/logger.hpp"

logger* logger::logger_instance = nullptr;

bool logger::create_instance(){
    if(is_instantiated()) return false;

    logger_instance = new logger();
    return true;
}

void logger::instantiate(){
    create_instance();
}

void logger::instantiate(const log_level _level){
    if(!create_instance()) return;

    logger_instance->level = _level;
}

void logger::instantiate(const log_level _level, std::ostream& _stream){
    if(!create_instance()) return;

    logger_instance->level = _level;
    logger_instance->output_stream = &_stream;
}

void logger::instantiate(const log_level _level, const std::string& _filename){
    if(is_instantiated()) return;

    std::unique_ptr<std::ofstream> stream = std::make_unique<std::ofstream>(_filename);
    if(!stream->is_open()){
        throw std::runtime_error(std::format("Failed to open the log file {}", _filename));
    }

    create_instance();
    logger_instance->level = _level;
    logger_instance->output_stream = stream.get();
    logger_instance->file_stream = std::move(stream);
}

void logger::destroy(){
    if(!logger_instance) return;

    delete logger_instance;
    logger_instance = nullptr;
}
