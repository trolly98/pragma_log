#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class WarningLogger : public BaseLogger 
{
public:
    WarningLogger(const LoggingCategory& category, 
                const std::string& file, 
                int line) : 
        BaseLogger(category, 
                    file, 
                    line, 
                    LoggingCategory::Level::WARNING) 
    {}
};

}