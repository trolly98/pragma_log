#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class WarningLogger : public BaseLogger 
{
public:
    constexpr WarningLogger(const LoggingCategory& category, 
                const char* file, 
                int line) : 
        BaseLogger(category,
                    file,
                    line, 
                    LoggingCategory::Level::WARNING) 
    {}
};

}