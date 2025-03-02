#include "app_bundle.hpp"
#include "../src/pragma_log.hpp"

PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(TEST1, "TEST1");

AppBundle::AppBundle()
{
    pragma_debug(TEST1) << "TEST1";   
}