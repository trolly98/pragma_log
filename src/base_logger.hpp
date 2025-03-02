#pragma once

#include "logging_category.hpp"
    
namespace pragma
{

class BaseLogger
{
public:
    constexpr BaseLogger(const LoggingCategory& category, 
               const char* file, 
               int line, 
               const LoggingCategory::Level level)
        : 
        _category(category), 
        _file(file), 
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
        return 
        (
            _level == LoggingCategory::Level::INFO ? _category.is_info_enabled() :
            _level == LoggingCategory::Level::DEBUG ? _category.is_debug_enabled() :
            _level == LoggingCategory::Level::WARNING ? _category.is_warning_enabled() :
            _level == LoggingCategory::Level::ERROR ? _category.is_error_enabled() : false
        );
    }

protected:
    const LoggingCategory& _category;
    const char* _file;
    int _line;
    LoggingCategory::Level _level;
};

}