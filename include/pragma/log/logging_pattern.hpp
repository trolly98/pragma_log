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

        _replace(result, "%{ms_time_process}", std::to_string(LoggingPattern::_ms_time_processed()));
        _replace(result, "%{mic_time_process}", std::to_string(LoggingPattern::_micros_time_processed()));
        _replace(result, "%{sec_time_process}", std::to_string(LoggingPattern::_seconds_time_processed()));
        _replace(result, "%{min_time_process}", std::to_string(LoggingPattern::_minutes_time_processed()));

        return result;
    }

private:
    const std::chrono::steady_clock::time_point _start_time;

    std::string _log_pattern = "[%{time}] [%{level}] %{message} (%{file}:%{line})";

    explicit LoggingPattern() : 
        _start_time(std::chrono::steady_clock::now())
    {}

    const std::int64_t _minutes_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - _start_time).count();
    }

    const std::int64_t _seconds_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _start_time).count();
    }

    const std::int64_t _ms_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start_time).count();
    }

    const std::int64_t _micros_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _start_time).count();
    }

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

static LoggingPattern& forceLoggingPatternInitialization = LoggingPattern::instance();

}
