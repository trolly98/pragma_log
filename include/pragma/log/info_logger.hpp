#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class InfoLogger : public BaseLogger 
{
public:
    constexpr InfoLogger(const LoggingCategory& category, 
                const char* file, 
                const char* function, 
                int line) : 
        BaseLogger(category,
                    file, 
                    function,
                    line, 
                    LoggingCategory::Level::INFO) 
    {}
};

}