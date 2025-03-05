#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class DebugLogger : public BaseLogger 
{
public:
    constexpr DebugLogger(const LoggingCategory& category, 
                const char* file, 
                const char* function, 
                int line) : 
        BaseLogger(category,
                    file, 
                    function,
                    line, 
                    LoggingCategory::Level::DEBUG) 
    {}
};

}