#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class ErrorLogger : public BaseLogger 
{
public:
    constexpr ErrorLogger(const LoggingCategory& category, 
                const char* file, 
                int line) : 
        BaseLogger(category, 
                    file, 
                    line, 
                    LoggingCategory::Level::ERROR) 
    {}
};

}