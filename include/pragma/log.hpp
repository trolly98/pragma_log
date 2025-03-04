#pragma once

#include "log/info_logger.hpp"
#include "log/debug_logger.hpp"
#include "log/warning_logger.hpp"
#include "log/error_logger.hpp"
#include "log/logging_category.hpp"
#include "log/logging_registry.hpp"
#include "log/logging_target.hpp"
#include "log/logging_pattern.hpp"

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

#define pragma_info(category) pragma::InfoLogger(category, __FILE__, __LINE__)
#define pragma_debug(category) pragma::DebugLogger(category, __FILE__, __LINE__)
#define pragma_warning(category) pragma::WarningLogger(category, __FILE__, __LINE__)
#define pragma_error(category) pragma::ErrorLogger(category, __FILE__, __LINE__)
