#include "debug_logger.hpp"
#include "warning_logger.hpp"
#include "error_logger.hpp"
#include "logging_category.hpp"
#include "logging_registry.hpp"
    
#define PRAGMA_DECLARE_LOGGING_CATEGORY(name) \
    extern pragma::LoggingCategory name;

#define PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(name, categoryName) \
    pragma::LoggingCategory name(categoryName);
    
#define PRAGMA_REGISTER_LOGGING_CATEGORY(name) \
    pragma::LoggingRegistry::register_category(name);

#define PRAGMA_LOGGING_CONFIGURE(rules) \
    pragma::LoggingRegistry::configure(rules);

#define pragma_debug(category) pragma::DebugLogger(category, __FILE__, __LINE__)
#define pragma_warning(category) pragma::WarningLogger(category, __FILE__, __LINE__)
#define pragma_error(category) pragma::ErrorLogger(category, __FILE__, __LINE__)
