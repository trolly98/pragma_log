
#pragma once

#include <pragma/log.hpp>

PRAGMA_DECLARE_LOGGING_CATEGORY(appBundle);

class AppBundle 
{
public:
    AppBundle();  // Constructor
    ~AppBundle(); // Destructor
    bool test();
};
