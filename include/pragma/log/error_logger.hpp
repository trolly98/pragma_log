#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class ErrorLogger : public BaseLogger 
{
public:
    constexpr ErrorLogger(const LoggingCategory& category, 
                const char* file, 
                const char* function, 
                int line) : 
        BaseLogger(category, 
                    file, 
                    function,
                    line, 
                    LoggingCategory::Level::ERROR) 
    {}
};

}