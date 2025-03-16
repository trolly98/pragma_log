#pragma once

#include <sstream>
#include <unordered_map>
#include "logging_category.hpp"

#include <array>
#include <algorithm>
#include <string>
#include "utils.hpp"
namespace pragma
{

class LoggingRegistry 
{
public:
    using category_list_t = std::unordered_map<category_id_t, LoggingCategory*>;

    static void register_category(LoggingCategory& category) 
    {
        _categories()[category.get_category_id()] = &category;
    }

    static LoggingCategory* get_category(const category_id_t id) 
    {
       return _categories().at(id);
    }

    static const category_list_t& get_categories()
    {
        return _categories();
    }

    static void configure(std::string rules)
    {
        rules.erase(std::remove_if(rules.begin(), rules.end(), ::isspace), rules.end());
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

                if (category == "*") 
                {
                    for (auto& cat : _categories()) 
                    {
                        _enable_category_level(cat.second, level, state);
                    }
                }
                else 
                {
                    auto cat_id = djb2_hash(category.c_str());
                
                    LoggingCategory* cat = get_category(cat_id);
                    LoggingRegistry::_enable_category_level(cat, level, state);
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

    static void _enable_category_level(LoggingCategory* category, const std::string &level_str, bool state) 
    {
        auto level = LoggingCategory::string_to_level(level_str.c_str());
        if (level == LoggingCategory::Level::ALL)
        {
            category->set_enabled(LoggingCategory::Level::INFO, state);
            category->set_enabled(LoggingCategory::Level::DEBUG, state);
            category->set_enabled(LoggingCategory::Level::WARNING, state);
            category->set_enabled(LoggingCategory::Level::ERROR, state);
        }
        else
        {
            category->set_enabled(level, state);
        }
    }
};

}