#pragma once

#include <sstream>
#include <unordered_map>
#include "logging_category.hpp"

#include <array>
#include <string>
#include "utils.hpp"
namespace pragma
{

class LoggingRegistry 
{
public:
    static void register_category(LoggingCategory& category) 
    {
        _categories()[category.get_category_id()] = &category;
    }

    static LoggingCategory* get_category(const category_id_t id) 
    {
       return _categories().at(id);
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
                auto cat_id = djb2_hash(category.c_str());
                LoggingCategory* cat = get_category(cat_id);
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
    static std::unordered_map<category_id_t, LoggingCategory*>& _categories() 
    {
        static std::unordered_map<category_id_t, LoggingCategory*> instance;
        return instance;
    }
};

}