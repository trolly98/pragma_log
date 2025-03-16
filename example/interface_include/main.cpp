#include <pragma/log.hpp>

#include <iostream>
#include <functional>
#include <chrono>
#include <future>

#include "app_bundle.hpp"

PRAGMA_DECLARE_LOGGING_CATEGORY(TEST);
PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(TEST, "TEST");

int main(int argc, char* argv[])
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    PRAGMA_LOGGING_PATTERN("[%{full_time}] [%{level}] %{message} (%{file}:%{line}) --> %{function} : %{threadid} %{category} \
        MIN: %{min_time_process} SEC: %{sec_time_process} MS: %{ms_time_process} MIC: %{mic_time_process}");

    PRAGMA_LOGGING_CONFIGURE("TEST.*=true");
    PRAGMA_LOGGING_TARGET_BOTH();
    
    pragma_info(TEST) << 5.9;
    pragma_debug(TEST) << 5;
    pragma_info(TEST) << "Info";
    pragma_debug(TEST) << "Debug";
    pragma_warning(TEST) << "Warning";
    pragma_error(TEST) << "Error";

    {
        AppBundle app_bundle;
        auto future = std::async(std::launch::async, [&app_bundle]() {
            app_bundle.test();
        });
        app_bundle.test();
    }
    
    return 0;
}