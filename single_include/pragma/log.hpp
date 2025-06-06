/*


██████  ██████   █████   ██████  ███    ███  █████          ██       ██████   ██████  
██   ██ ██   ██ ██   ██ ██       ████  ████ ██   ██         ██      ██    ██ ██       
██████  ██████  ███████ ██   ███ ██ ████ ██ ███████         ██      ██    ██ ██   ███ 
██      ██   ██ ██   ██ ██    ██ ██  ██  ██ ██   ██         ██      ██    ██ ██    ██ 
██      ██   ██ ██   ██  ██████  ██      ██ ██   ██ ███████ ███████  ██████   ██████  

        Version: 0.1

        Maintainer: trolly

        Last Release Date: 2025-03-16


*/
#pragma once


#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdint> 
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <syslog.h>
#include <thread>
#include <unordered_map>


// File: log/pattern_utils.hpp



#define THREAD_ID() []() -> std::string { \
    std::ostringstream oss; \
    oss << std::this_thread::get_id(); \
    return oss.str(); \
}()

static std::string time_formatted(const std::string& format) 
{
    std::ostringstream oss;
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    oss << std::put_time(&tm, format.c_str());
    return oss.str();
}

static std::string time() 
{
    return time_formatted("%H:%M:%S");
}

static std::string full_time() 
{
    return time_formatted("%Y-%m-%d %H:%M:%S");
}

static std::string precise_time() 
{
    std::ostringstream oss;
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    oss << std::put_time(&tm, "%H:%M:%S") << "." << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
}


// File: log/logging_pattern.hpp



namespace pragma
{

class LoggingPattern
{
public:
    static LoggingPattern& instance() 
    {
        static LoggingPattern instance;
        return instance;
    }

    void set_pattern(const std::string &pattern)
    {
        _log_pattern = pattern;
    }

    template<typename T>
    const std::string format(       
                                const T& message,
                                const char* level,
                                const char* file,
                                int line,
                                const char* function,
                                const char* category_name
                            ) 
    {
        std::string result = _log_pattern;
        
        _replace(result, "%{level}", level);
        
        _replace(result, "%{full_time}", full_time());
        _replace(result, "%{time}", time());
        _replace(result, "%{precise_time}", precise_time());

        _replace(result, "%{file}", file);
        _replace(result, "%{line}", std::to_string(line));
        _replace(result, "%{function}", function);
        _replace(result, "%{message}", message);
        _replace(result, "%{threadid}", THREAD_ID());
        _replace(result, "%{category}", category_name);

        _replace(result, "%{ms_time_process}", std::to_string(LoggingPattern::_ms_time_processed()));
        _replace(result, "%{mic_time_process}", std::to_string(LoggingPattern::_micros_time_processed()));
        _replace(result, "%{sec_time_process}", std::to_string(LoggingPattern::_seconds_time_processed()));
        _replace(result, "%{min_time_process}", std::to_string(LoggingPattern::_minutes_time_processed()));

        return result;
    }

private:
    const std::chrono::steady_clock::time_point _start_time;

    std::string _log_pattern = "[%{time}] [%{level}] %{message} (%{file}:%{line})";

    explicit LoggingPattern() : 
        _start_time(std::chrono::steady_clock::now())
    {}

    std::int64_t _minutes_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - _start_time).count();
    }

    std::int64_t _seconds_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _start_time).count();
    }

    std::int64_t _ms_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start_time).count();
    }

    std::int64_t _micros_time_processed()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _start_time).count();
    }

    template<typename T>
    static typename std::enable_if<std::is_floating_point<T>::value, void>::type
    _replace(std::string& text, const std::string& placeholder, const T& value)
    {
        std::string value_str = std::to_string(value);

        // REMOVE extra zeros
        value_str.erase(value_str.find_last_not_of('0') + 1, std::string::npos);
        if (value_str.back() == '.') 
        {
            value_str.pop_back();
        }
        return _replace_placeholder(text, placeholder, value_str);
    }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, void>::type
    _replace(std::string& text, const std::string& placeholder, const T& value)
    {
        return _replace_placeholder(text, placeholder, std::to_string(value));
    }

    template<typename T>
    static typename std::enable_if<!std::is_arithmetic<T>::value, void>::type
    _replace(std::string& text, const std::string& placeholder, const T& value)
    {
        return _replace_placeholder(text, placeholder, std::string(value));
    }

    static void _replace_placeholder(std::string& text, const std::string& placeholder, const std::string& value_str)
    {
        size_t pos = 0;
        while ((pos = text.find(placeholder, pos)) != std::string::npos)
        {
            text.replace(pos, placeholder.length(), value_str);
            pos += value_str.length();
        }
    }

};

static LoggingPattern& forceLoggingPatternInitialization = LoggingPattern::instance();

}


// File: log/utils.hpp


namespace pragma
{

using category_id_t = std::uint32_t;

constexpr category_id_t djb2_hash(const char* str, unsigned int hash = 5381) 
{
    return (str[0] == '\0') ? hash : djb2_hash(str + 1, ((hash << 5) + hash) + static_cast<unsigned char>(str[0]));
}

}


// File: log/logging_category.hpp

namespace pragma
{

class LoggingCategory 
{
public:
    enum class Level
    {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        ALL
    };

    static constexpr const char* level_to_string(Level level)
    {
        return 
        (
            level == Level::INFO ? "INFO" :
            level == Level::DEBUG ? "DEBUG" :
            level == Level::WARNING ? "WARNING" :
            level == Level::ERROR ? "ERROR" : "ALL"
        );
    }
    static constexpr Level string_to_level(const char* level)
    {
        return 
        (
            strcasecmp(level, "info") == 0 ? Level::INFO :
            strcasecmp(level, "debug") == 0 ? Level::DEBUG :
            strcasecmp(level, "warning") == 0 ? Level::WARNING :
            strcasecmp(level, "error") == 0 ? Level::ERROR : Level::ALL
        );
    }

    constexpr explicit LoggingCategory(const char* name) : 
            _category_name(name),
            _enabled_levels(0b111) // All levels enabled initially (DEBUG, WARNING, ERROR)
    {}

    constexpr const char* get_category_name() const 
    { 
        return _category_name;
    }
    constexpr category_id_t get_category_id() const 
    { 
        return djb2_hash(_category_name);
    }

    constexpr bool is_info_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::INFO))) != 0; }
    constexpr bool is_debug_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::DEBUG))) != 0; }
    constexpr bool is_warning_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::WARNING))) != 0; }
    constexpr bool is_error_enabled() const { return (_enabled_levels & (1 << static_cast<uint8_t>(Level::ERROR))) != 0; }

    void set_enabled(const Level level, bool state) 
    {
        uint8_t mask = (1 << static_cast<uint8_t>(level));
        _enabled_levels = state ? (_enabled_levels | mask) : (_enabled_levels & ~mask);
    }
    
private:
    const char* _category_name;
    mutable uint8_t _enabled_levels; // Bitset to represent the three levels (DEBUG, WARNING, ERROR)
};

};


// File: log/logging_registry.hpp


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


// File: log/logging_target.hpp

namespace pragma
{

class LoggingTarget
{
public:
    enum class Target
    {
        SYSLOG,
        CONSOLE,
        BOTH
    };

    static LoggingTarget& instance() 
    {
        static LoggingTarget instance;
        return instance;
    }

    constexpr Target get() const
    {
        return _target;
    }

    void set(Target target) 
    { 
        _target = target; 
    }

private:
    Target _target = Target::BOTH;
};

}


// File: log/base_logger.hpp


namespace pragma
{

class BaseLogger
{
public:
    constexpr BaseLogger(const LoggingCategory& category, 
        const char* file, 
        const char* function, 
        int line, 
        const LoggingCategory::Level level)
    : 
        _category(category), 
        _file(file), 
        _function(function),
        _line(line), 
        _level(level)
    {}

    template<typename T>
    BaseLogger& operator<<(const T& message) 
    {
        _log(message);
        return *this;
    }

    template<typename... Args>
    BaseLogger& operator()(Args&&... args)
    {
        std::string result;
        this->_concat(result, std::forward<Args>(args)...);
        _log(result);
        return *this;
    }

protected:
    const LoggingCategory& _category;
    const char* _file;
    const char* _function;
    int _line;
    LoggingCategory::Level _level;

private:
    template<typename T>
    constexpr void _log(const T& message)
    {
        if (this->_is_enabled()) 
        {
            const auto target = LoggingTarget::instance().get();

            const auto msg = LoggingPattern::instance().format(
                message,
                LoggingCategory::level_to_string(_level),
                _file,
                _line,
                _function,
                _category.get_category_name()
                );

            if (target == LoggingTarget::Target::BOTH)
            {
                syslog  (LOG_INFO, "%s", msg.c_str());
                std::cout << msg << std::endl;
                return;
            }
            if (target == LoggingTarget::Target::CONSOLE)
            {
                std::cout << msg << std::endl;
                return;
            }
            if (target == LoggingTarget::Target::SYSLOG)
            {
                syslog  (LOG_INFO, "%s", msg.c_str());
                return;
            }
        }
        return;
    }    

    constexpr bool _is_enabled() const 
    {
        return 
        (
            _level == LoggingCategory::Level::INFO ? _category.is_info_enabled() :
            _level == LoggingCategory::Level::DEBUG ? _category.is_debug_enabled() :
            _level == LoggingCategory::Level::WARNING ? _category.is_warning_enabled() :
            _level == LoggingCategory::Level::ERROR ? _category.is_error_enabled() : false
        );
    }

    void _concat(std::string& result) {}

    template<typename T, typename... Args>
    void _concat(std::string& result, const T& first, Args&&... args) 
    {
        result += this->_to_string_helper(first) + " ";
        this->_concat(result, std::forward<Args>(args)...);
    }

    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
    _to_string_helper(const T& value)
    {
        return std::to_string(value);
    }

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, std::string>::type
    _to_string_helper(const T& value)
    {
        return std::to_string(value);
    }

    template<typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value, std::string>::type
    _to_string_helper(const T& value)
    {
        return std::string(value);
    }
};

}


// File: log/info_logger.hpp

    
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


// File: log/debug_logger.hpp

    
namespace pragma
{

class DebugLogger : public BaseLogger 
{
public:
    constexpr DebugLogger(const LoggingCategory& category, 
                const char* file, 
                const char* function, 
                int line) : 
        BaseLogger(category,
                    file, 
                    function,
                    line, 
                    LoggingCategory::Level::DEBUG) 
    {}
};

}


// File: log/warning_logger.hpp

    
namespace pragma
{

class WarningLogger : public BaseLogger 
{
public:
    constexpr WarningLogger(const LoggingCategory& category, 
                const char* file, 
                const char* function, 
                int line) : 
        BaseLogger(category,
                    file,
                    function,
                    line, 
                    LoggingCategory::Level::WARNING) 
    {}
};

}


// File: log/error_logger.hpp

    
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


// File: log.hpp


#define PRAGMA_DECLARE_LOGGING_CATEGORY(name) \
    extern pragma::LoggingCategory name;

#define PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(name, categoryName) \
    pragma::LoggingCategory name(categoryName); \
    const struct name##_registrator { \
        name##_registrator() { pragma::LoggingRegistry::register_category(name); } \
    } name##_registrator_instance;
        
#define PRAGMA_LOGGING_CONFIGURE(rules) \
    pragma::LoggingRegistry::configure(rules);

#define PRAGMA_LOGGING_PATTERN(pattern) \
    pragma::LoggingPattern::instance().set_pattern(pattern);

#define PRAGMA_LOGGING_TARGET_BOTH() \
    pragma::LoggingTarget::instance().set(pragma::LoggingTarget::Target::BOTH);

#define PRAGMA_LOGGING_TARGET_CONSOLE() \
    pragma::LoggingTarget::instance().set(pragma::LoggingTarget::Target::CONSOLE);

#define PRAGMA_LOGGING_TARGET_SYSLOG() \
    pragma::LoggingTarget::instance().set(pragma::LoggingTarget::Target::SYSLOG);

#define pragma_info(category) pragma::InfoLogger(category, __FILE__, __func__, __LINE__)
#define pragma_debug(category) pragma::DebugLogger(category, __FILE__, __func__, __LINE__)
#define pragma_warning(category) pragma::WarningLogger(category, __FILE__, __func__, __LINE__)
#define pragma_error(category) pragma::ErrorLogger(category, __FILE__, __func__, __LINE__)


