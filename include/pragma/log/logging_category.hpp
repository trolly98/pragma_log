#pragma once

#include <string>
#include <iostream>
#include <cstdint> 
#include <cstring>
#include "utils.hpp"
namespace pragma
{

class LoggingCategory 
{
public:
    enum class Level
    {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        ALL
    };

    static constexpr const char* level_to_string(Level level)
    {
        return 
        (
            level == Level::INFO ? "INFO" :
            level == Level::DEBUG ? "DEBUG" :
            level == Level::WARNING ? "WARNING" :
            level == Level::ERROR ? "ERROR" : "ALL"
        );
    }
    static constexpr Level string_to_level(const char* level)
    {
        return 
        (
            strcasecmp(level, "info") == 0 ? Level::INFO :
            strcasecmp(level, "debug") == 0 ? Level::DEBUG :
            strcasecmp(level, "warning") == 0 ? Level::WARNING :
            strcasecmp(level, "error") == 0 ? Level::ERROR : Level::ALL
        );
    }

    constexpr explicit LoggingCategory(const char* name) : 
            _category_name(name),
            _enabled_levels(0b111) // All levels enabled initially (DEBUG, WARNING, ERROR)
    {}

    constexpr const char* get_category_name() const 
    { 
        return _category_name;
    }
    constexpr const category_id_t get_category_id() const 
    { 
        return djb2_hash(_category_name);
    }

    constexpr bool is_info_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::INFO))) != 0; }
    constexpr bool is_debug_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::DEBUG))) != 0; }
    constexpr bool is_warning_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::WARNING))) != 0; }
    constexpr bool is_error_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::ERROR))) != 0; }

    void set_enabled(const Level level, bool state) 
    {
        uint8_t mask = (1 << static_cast<uint8_t>(level));
        _enabled_levels = state ? (_enabled_levels | mask) : (_enabled_levels & ~mask);
    }
    
private:
    const char* _category_name;
    mutable uint8_t _enabled_levels; // Bitset to represent the three levels (DEBUG, WARNING, ERROR)
};

};