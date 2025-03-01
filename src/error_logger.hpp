#pragma once

#include "base_logger.hpp"
    
namespace pragma
{

class ErrorLogger : public BaseLogger 
{
public:
    ErrorLogger(const LoggingCategory& category, 
                const std::string& file, 
                int line) : 
        BaseLogger(category, 
                    file, 
                    line, 
                    LoggingCategory::Level::ERROR) 
    {}
};

}