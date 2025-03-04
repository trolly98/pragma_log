#include "../../single_include/pragma/log.hpp"

PRAGMA_DECLARE_LOGGING_CATEGORY(TEST);
PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(TEST, "TEST");

int main(int argc, char* argv[])
{
    PRAGMA_LOGGING_PATTERN("[%{full_time}] [%{level}] %{message} (%{file}:%{line})");

    PRAGMA_LOGGING_CONFIGURE("TEST.*=true");
    PRAGMA_LOGGING_TARGET_BOTH();

    pragma_info(TEST) << "Info";
    pragma_debug(TEST) << "Debug";
    pragma_warning(TEST) << "Warning";
    pragma_error(TEST) << "Error";
    
    return 0;
}