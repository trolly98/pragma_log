#pragma once

#include <syslog.h>
#include "logging_category.hpp"
#include "logging_pattern.hpp"
#include "logging_target.hpp"

namespace pragma
{

class BaseLogger
{
public:
    constexpr BaseLogger(const LoggingCategory& category, 
        const char* file, 
        const char* function, 
        int line, 
        const LoggingCategory::Level level)
    : 
        _category(category), 
        _file(file), 
        _function(function),
        _line(line), 
        _level(level)
    {}

    template<typename T>
    BaseLogger& operator<<(const T& message) 
    {
        _log(message);
        return *this;
    }

    // template<typename T, typename... Args>
    // BaseLogger& operator()(const T& first, const Args&... args) 
    // {
    //     _log(first);
    //     return (*this)(args...);
    // }


protected:
    const LoggingCategory& _category;
    const char* _file;
    const char* _function;
    int _line;
    LoggingCategory::Level _level;

private:
    template<typename T>
    constexpr void _log(const T& message)
    {
        if (this->_is_enabled()) 
        {
            const auto target = LoggingTarget::instance().get();

            const auto msg = LoggingPattern::instance().format(
                message,
                LoggingCategory::level_to_string(_level),
                _file,
                _line,
                _function,
                _category.get_category_name()
                );

            if (target == LoggingTarget::Target::BOTH)
            {
                syslog  (LOG_INFO, "%s", msg.c_str());
                std::cout << msg << std::endl;
                return;
            }
            if (target == LoggingTarget::Target::CONSOLE)
            {
                std::cout << msg << std::endl;
                return;
            }
            if (target == LoggingTarget::Target::SYSLOG)
            {
                syslog  (LOG_INFO, "%s", msg.c_str());
                return;
            }
        }
        return;
    }    

    constexpr bool _is_enabled() const 
    {
        return 
        (
            _level == LoggingCategory::Level::INFO ? _category.is_info_enabled() :
            _level == LoggingCategory::Level::DEBUG ? _category.is_debug_enabled() :
            _level == LoggingCategory::Level::WARNING ? _category.is_warning_enabled() :
            _level == LoggingCategory::Level::ERROR ? _category.is_error_enabled() : false
        );
    }
};

}