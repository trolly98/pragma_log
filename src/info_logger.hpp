#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class InfoLogger : public BaseLogger 
{
public:
    constexpr InfoLogger(const LoggingCategory& category, 
                const char* file, 
                int line) : 
        BaseLogger(category,
                    file, 
                    line, 
                    LoggingCategory::Level::INFO) 
    {}
};

}