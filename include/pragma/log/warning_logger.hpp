#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class WarningLogger : public BaseLogger 
{
public:
    constexpr WarningLogger(const LoggingCategory& category, 
                const char* file, 
                const char* function, 
                int line) : 
        BaseLogger(category,
                    file,
                    function,
                    line, 
                    LoggingCategory::Level::WARNING) 
    {}
};

}