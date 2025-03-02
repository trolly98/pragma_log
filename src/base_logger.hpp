#pragma once

#include "logging_category.hpp"
    
namespace pragma
{

class BaseLogger
{
public:
    constexpr BaseLogger(const LoggingCategory& category, 
               const std::string& file, 
               int line, 
               const LoggingCategory::Level level)
        : 
        _category(category), 
        _file(file.c_str()), 
        _line(line), 
        _level(level) 
    {}

    template<typename T>
    BaseLogger& operator<<(const T& message) 
    {
        if (this->is_enabled()) 
        {
            std::cout << "[" << LoggingCategory::level_to_string(_level) << "] " 
                      << _category.get_category_name() 
                      << " (" << _file << ":" << _line << ") " 
                      << message << std::endl;
        }
        return *this;
    }

    constexpr bool is_enabled() const 
    {
        switch (_level) 
        {
            case LoggingCategory::Level::DEBUG: return _category.is_debug_enabled();
            case LoggingCategory::Level::WARNING: return _category.is_warning_enabled();
            case LoggingCategory::Level::ERROR: return _category.is_error_enabled();
            default: return false;
        }
    }

protected:
    const LoggingCategory& _category;
    const char* _file;
    int _line;
    LoggingCategory::Level _level;
};

}