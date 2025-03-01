#include "../src/pragma_log.hpp"

PRAGMA_DECLARE_LOGGING_CATEGORY(TEST);
PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(TEST, "TEST");


#include "app_bundle.hpp"
int main()
{
    PRAGMA_REGISTER_LOGGING_CATEGORY(TEST);

    PRAGMA_LOGGING_CONFIGURE("TEST.debug=false,TEST.warning=true,TEST.error=true");

    
    pragma_debug(TEST)<<"TEST";
    pragma_warning(TEST)<<"TEST";
    pragma_error(TEST)<<"TEST";

    //AppBundle app;

    //pragma_debug(TEST) << "Prova pragma debug";


    //pragma_debug(TEST) << "TEST";
    //pragma_warning(TEST) << "TEST";
    //pragma_error(TEST) << "TEST";
}