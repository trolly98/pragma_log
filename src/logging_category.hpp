#pragma once

#include <string>
#include <iostream>
#include <bitset>

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
            _category_name(name),
            _enabled_levels(0b111) // All levels enabled initially (DEBUG, WARNING, ERROR)
    {}

    const std::string& get_category_name() const 
    { 
        return _category_name; 
    }

    bool is_debug_enabled() const { return _enabled_levels.test(static_cast<size_t>(Level::DEBUG)); }
    bool is_warning_enabled() const { return _enabled_levels.test(static_cast<size_t>(Level::WARNING)); }
    bool is_error_enabled() const { return _enabled_levels.test(static_cast<size_t>(Level::ERROR)); }

    void set_enabled(const Level level, bool state) 
    {
        if (state)
        {
            _enabled_levels.set(static_cast<size_t>(level));
        }
        else
        {
            _enabled_levels.reset(static_cast<size_t>(level));
        }
    }
    
private:
    std::string _category_name;
    std::bitset<3> _enabled_levels; // Bitset to represent the three levels (DEBUG, WARNING, ERROR)
};

};