#ifndef PERSONAL_UTILS_LOGGER_HPP
#define PERSONAL_UTILS_LOGGER_HPP

#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

/**
 * @brief Represents the severity level of a log message.
 */
enum class log_level : std::uint8_t{
    notset   = 0, ///< No logging threshold.
    debug    = 1, ///< Detailed diagnostic information.
    info     = 2, ///< General informational messages.
    warning  = 3, ///< Potentially problematic situations.
    error    = 4, ///< Errors that may affect normal operation.
    critical = 5  ///< Critical errors that may cause application failure.
};

/**
 * @brief A singleton class supporting console and file output.
 *
 * The logger must be instantiated using one of the instantiate()
 * overloads before any logging function is called.
 *
 * The configured logger level acts as a minimum severity threshold.
 * Messages below this threshold are ignored.
 *
 * Logging functions are static and can be accessed directly through
 * the logger class.
 *
 * The logger supports configurable severity filtering and
 * std::format-based message formatting.
 *
 * @note The logger does not own an externally supplied std::ostream.
 *       The caller must ensure that the stream remains valid for the
 *       entire lifetime of the logger instance.
 *
 * @throws std::runtime_error Logging functions throw if the logger
 *         has not been instantiated.
 */
class logger{
private:
    log_level level = log_level::info;
    static logger* logger_instance;
    std::ostream* output_stream = &std::cerr;
    std::unique_ptr<std::ofstream> file_stream;

    /**
     * @brief Constructs the logger.
     *
     * Private to prevent direct instantiation. Use instantiate()
     * to create the singleton instance.
     */
    logger() = default;

    /**
     * @brief Creates the singleton instance if one does not exist.
     *
     * @return true if the instance was created successfully;
     *         false otherwise.
     */
    static bool create_instance();

    /**
     * @brief Converts a logging severity level to its string representation.
     *
     * @param _level The severity level to convert.
     *
     * @return The corresponding uppercase string representation.
     *
     * @throws std::logic_error If the supplied value does not correspond
     *         to a valid log_level enumerator.
     */
    static constexpr std::string_view log_level_to_string(const log_level _level);

    /**
     * @brief Writes a formatted log message if it meets the configured threshold.
     *
     * The message is prefixed with its severity level and written to
     * the configured output stream.
     *
     * @tparam args Types of the formatting arguments.
     *
     * @param _level Severity level of the message.
     * @param _line Compile-time checked format string.
     * @param _args Arguments used to format the message.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     * @throws std::format_error If formatting fails.
     */
    template<typename... args>
    static void log(const log_level _level, const std::format_string<args...> _line, args&&... _args);

public:
    /**
     * @brief Copy construction is disabled.
     */
    logger(const logger& _logger) = delete;

    /**
     * @brief Copy assignment is disabled.
     */
    logger& operator=(const logger& _logger) = delete;

    /**
     * @brief Move construction is disabled.
     */
    logger(logger&& _logger) = delete;

    /**
     * @brief Move assignment is disabled.
     */
    logger& operator=(logger&& _logger) = delete;

    /**
     * @brief Checks whether the logger has been instantiated.
     *
     * @return true if the singleton instance exists; false otherwise.
     */
    static bool is_instantiated();

    /**
     * @brief Verifies that the logger has been instantiated.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     */
    static void assert_is_instantiated();

    /**
     * @brief Instantiates the logger with the default configuration.
     *
     * Uses log_level::info as the severity threshold and std::cerr
     * as the output stream.
     *
     * If an instance already exists, it is not recreated.
     */
    static void instantiate();

    /**
     * @brief Instantiates the logger with a specified severity threshold.
     *
     * Uses std::cerr as the output stream.
     *
     * If an instance already exists, it is not recreated.
     *
     * @param _level Minimum severity level for messages to be logged.
     */
    static void instantiate(const log_level _level);

    /**
     * @brief Instantiates the logger with a specified output stream.
     *
     * If an instance already exists, it is not recreated.
     *
     * @param _level Minimum severity level for messages to be logged.
     * @param _stream Output stream to which log messages are written.
     *
     * @note The logger does not take ownership of _stream.
     *       The caller must ensure that it remains valid while the
     *       logger uses it.
     */
    static void instantiate(const log_level _level, std::ostream& _stream);

    /**
     * @brief Instantiates the logger with a file as its output destination.
     *
     * If an instance already exists, it is not recreated.
     *
     * @param _level Minimum severity level for messages to be logged.
     * @param _filename Path of the file to which log messages are written.
     *
     * @note The logger manages the lifetime of the file stream.
     */
    static void instantiate(const log_level _level, const std::string& _filename);

    /**
     * @brief Destroys the singleton logger instance.
     *
     * Releases any resources owned by the logger.
     *
     * Calling this function when no instance exists has no effect.
     */
    static void destroy();

    /**
     * @brief Logs a debug-level message.
     *
     * @tparam args Types of the formatting arguments.
     * @param _line Compile-time checked format string.
     * @param _args Arguments used to format the message.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     */
    template<typename... args>
    static void debug(const std::format_string<args...> _line, args&&... _args);

    /**
     * @brief Logs an info-level message.
     *
     * @tparam args Types of the formatting arguments.
     * @param _line Compile-time checked format string.
     * @param _args Arguments used to format the message.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     */
    template<typename... args>
    static void info(const std::format_string<args...> _line, args&&... _args);

    /**
     * @brief Logs a warning-level message.
     *
     * @tparam args Types of the formatting arguments.
     * @param _line Compile-time checked format string.
     * @param _args Arguments used to format the message.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     */
    template<typename... args>
    static void warning(const std::format_string<args...> _line, args&&... _args);

    /**
     * @brief Logs an error-level message.
     *
     * @tparam args Types of the formatting arguments.
     * @param _line Compile-time checked format string.
     * @param _args Arguments used to format the message.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     */
    template<typename... args>
    static void error(const std::format_string<args...> _line, args&&... _args);

    /**
     * @brief Logs a critical-level message.
     *
     * @tparam args Types of the formatting arguments.
     * @param _line Compile-time checked format string.
     * @param _args Arguments used to format the message.
     *
     * @throws std::runtime_error If the logger has not been instantiated.
     */
    template<typename... args>
    static void critical(const std::format_string<args...> _line, args&&... _args);
};

inline constexpr std::string_view logger::log_level_to_string(const log_level _level){
    switch(_level){
        case log_level::notset  : return "NOTSET";
        case log_level::debug   : return "DEBUG";
        case log_level::info    : return "INFO";
        case log_level::warning : return "WARNING";
        case log_level::error   : return "ERROR";
        case log_level::critical: return "CRITICAL";
    }

    throw std::logic_error(std::format("Unknown value of `log_level`: {}", static_cast<int>(_level)));
}

inline bool logger::is_instantiated(){
    return logger_instance;
}

inline void logger::assert_is_instantiated(){
    if(!is_instantiated()) throw std::runtime_error("`logger` is not instantiated.");
}

template<typename... args>
void logger::log(const log_level _level, const std::format_string<args...> _line, args&&... _args){
    assert_is_instantiated();
    if(_level < logger_instance->level) return;

    (*logger_instance->output_stream) << std::format(
        "{:<10}: {}",
        std::format("[{}]", log_level_to_string(_level)),
        std::format(_line, std::forward<args>(_args)...)
    ) << std::endl;
}

template<typename... args>
void logger::debug(const std::format_string<args...> _line, args&&... _args){
    log(log_level::debug, _line, std::forward<args>(_args)...);
}

template<typename... args>
void logger::info(const std::format_string<args...> _line, args&&... _args){
    log(log_level::info, _line, std::forward<args>(_args)...);
}

template<typename... args>
void logger::warning(const std::format_string<args...> _line, args&&... _args){
    log(log_level::warning, _line, std::forward<args>(_args)...);
}

template<typename... args>
void logger::error(const std::format_string<args...> _line, args&&... _args){
    log(log_level::error, _line, std::forward<args>(_args)...);
}

template<typename... args>
void logger::critical(const std::format_string<args...> _line, args&&... _args){
    log(log_level::critical, _line, std::forward<args>(_args)...);
}

#endif // PERSONAL_UTILS_LOGGER_HPP
