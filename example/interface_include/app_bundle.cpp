
#include "app_bundle.hpp"
#include <iostream>

PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(appBundle, "app.bundle");

AppBundle::AppBundle() 
{
    pragma_info(appBundle) << "AppBundle created";
}

AppBundle::~AppBundle() 
{
    pragma_error(appBundle) << "AppBundle destroyed";
    pragma_warning(appBundle) << "AppBundle destroyed";
}

bool AppBundle::test() 
{
    pragma_debug(appBundle) << "AppBundle test method called";
    return true;
}