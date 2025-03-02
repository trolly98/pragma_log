#pragma once

#include "info_logger.hpp"
#include "debug_logger.hpp"
#include "warning_logger.hpp"
#include "error_logger.hpp"
#include "logging_category.hpp"
#include "logging_registry.hpp"
    
#define PRAGMA_DECLARE_LOGGING_CATEGORY(name) \
    extern pragma::LoggingCategory name;

#define PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(name, categoryName) \
    pragma::LoggingCategory name(categoryName); \
    const struct name##_registrator { \
        name##_registrator() { pragma::LoggingRegistry::register_category(name); } \
    } name##_registrator_instance;
        
#define PRAGMA_LOGGING_CONFIGURE(rules) \
    pragma::LoggingRegistry::configure(rules);

#define pragma_info(category) pragma::InfoLogger(category, __FILE__, __LINE__)
#define pragma_debug(category) pragma::DebugLogger(category, __FILE__, __LINE__)
#define pragma_warning(category) pragma::WarningLogger(category, __FILE__, __LINE__)
#define pragma_error(category) pragma::ErrorLogger(category, __FILE__, __LINE__)
