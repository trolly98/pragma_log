#pragma once

#include <string>
#include <iostream>
#include <bitset>
#include <cstdint>

namespace pragma
{

class LoggingCategory 
{
public:
    enum class Level
    {
        DEBUG,
        WARNING,
        ERROR
    };

    static constexpr const char* level_to_string(Level level)
    {
        return (level == Level::DEBUG ? "DEBUG" :
            level == Level::WARNING ? "WARNING" : 
            level == Level::ERROR ? "ERROR" : "Unknown");
    }

    explicit LoggingCategory(const std::string& name) : 
            _category_name(name.c_str()),
            _enabled_levels(0b111) // All levels enabled initially (DEBUG, WARNING, ERROR)
    {}

    constexpr const char* get_category_name() const 
    { 
        return _category_name;
    }

    constexpr bool is_debug_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::DEBUG))) != 0; }
    constexpr bool is_warning_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::WARNING))) != 0; }
    constexpr bool is_error_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::ERROR))) != 0; }

    constexpr void set_enabled(const Level level, bool state) 
    {
        uint8_t mask = (1 << static_cast<uint8_t>(level));
        _enabled_levels = state ? (_enabled_levels | mask) : (_enabled_levels & ~mask);

        // if (state)
        // {
        //     _enabled_levels.set(static_cast<size_t>(level));
        // }
        // else
        // {
        //     _enabled_levels.reset(static_cast<size_t>(level));
        // }
    }
    
private:
    const char* _category_name;
    uint8_t _enabled_levels; // Bitset to represent the three levels (DEBUG, WARNING, ERROR)
};

};