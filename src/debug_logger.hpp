#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class DebugLogger : public BaseLogger 
{
public:
    constexpr DebugLogger(const LoggingCategory& category, 
                const std::string& file, 
                int line) : 
        BaseLogger(category,
                    file, 
                    line, 
                    LoggingCategory::Level::DEBUG) 
    {}
};

}