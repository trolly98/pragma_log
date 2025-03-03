#pragma once

#include <iostream>
#include <string>

#include "pattern_utils.hpp"

namespace pragma
{

class LoggingPattern
{
public:
    static LoggingPattern& instance() 
    {
        static LoggingPattern instance;
        return instance;
    }

    const void set_pattern(const std::string &pattern)
    {
        _log_pattern = pattern;
    }

    const std::string format(const char* message,
                                    const char* level,
                                    const char* file,
                                    int line,
                                    const char* function,
                                    const char* category_name) 
    {
        std::string result = _log_pattern;
        
        _replace(result, "%{level}", level);
        
        _replace(result, "%{full_time}", full_time());
        _replace(result, "%{time}", time());
        _replace(result, "%{precise_time}", precise_time());

        _replace(result, "%{file}", file);
        _replace(result, "%{line}", std::to_string(line));
        _replace(result, "%{function}", function);
        _replace(result, "%{message}", message);
        _replace(result, "%{threadid}", THREAD_ID());
        _replace(result, "%{category}", category_name);
        _replace(result, "%{time process}", TIME_PROCESS());

        return result;
    }

private:
    std::string _log_pattern = "[%{time}] [%{level}] %{message} (%{file}:%{line})";

    static void _replace(std::string& text, const std::string& placeholder, const std::string& value)
    {
        size_t pos = 0;
        while ((pos = text.find(placeholder, pos)) != std::string::npos)
        {
            text.replace(pos, placeholder.length(), value);
            pos += value.length();
        }
    }
};

}
