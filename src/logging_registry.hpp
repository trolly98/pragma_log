#pragma once

#include <sstream>
#include <unordered_map>
#include "logging_category.hpp"

#include <array>
#include <string>

namespace pragma
{

class LoggingRegistry 
{
public:
    static void register_category(LoggingCategory& category) 
    {
        _categories()[category.get_category_name()] = &category;
    }

    static LoggingCategory* get_category(const std::string& name) 
    {
        auto it = _categories().find(name);
        return it != _categories().end() ? it->second : nullptr;
    }

    static void configure(const std::string& rules) 
    {
        std::istringstream ss(rules);
        std::string rule;
        while (std::getline(ss, rule, ',')) 
        {
            size_t dot = rule.find('.');
            size_t equal = rule.find('=');
            if (dot != std::string::npos && equal != std::string::npos) 
            {
                std::string category = rule.substr(0, dot);
                std::string level = rule.substr(dot + 1, equal - dot - 1);
                bool state = rule.substr(equal + 1) == "true";
                LoggingCategory* cat = get_category(category);
                if (cat) 
                {
                    if (level == "info")
                    {
                        cat->set_enabled(LoggingCategory::Level::INFO, state);
                    }
                    else if (level == "debug")
                    {
                        cat->set_enabled(LoggingCategory::Level::DEBUG, state);
                    }
                    else if (level == "warning")
                    {
                        cat->set_enabled(LoggingCategory::Level::WARNING, state);
                    }
                    else if (level == "error")
                    {
                        cat->set_enabled(LoggingCategory::Level::ERROR, state);
                    }
                    else if (level == "*") 
                    {
                        cat->set_enabled(LoggingCategory::Level::INFO, state);
                        cat->set_enabled(LoggingCategory::Level::DEBUG, state);
                        cat->set_enabled(LoggingCategory::Level::WARNING, state);
                        cat->set_enabled(LoggingCategory::Level::ERROR, state);
                    }
                }
            }
        }
    }

private:
    static std::unordered_map<std::string, LoggingCategory*>& _categories() 
    {
        static std::unordered_map<std::string, LoggingCategory*> instance;
        return instance;
    }
};

}