#include "../src/pragma_log.hpp"
#include "app_bundle.hpp"
#include <iostream>
#include <functional>
#include <chrono>

PRAGMA_DECLARE_LOGGING_CATEGORY(TEST);
PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(TEST, "TEST");


void measure_execution_time(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";
}

int main()
{
    PRAGMA_LOGGING_CONFIGURE("TEST.*=false");

    measure_execution_time([]() {
        for (int i = 0; i < 1000000; ++i) {
            pragma_debug(TEST) << "TEST";
        }
    });

    measure_execution_time([]() {
        for (int i = 0; i < 1000000; ++i) {
            pragma_warning(TEST) << "TEST";
        }
    });

    measure_execution_time([]() {
        for (int i = 0; i < 1000000; ++i) {
            pragma_error(TEST) << "TEST";
        }
    });
    pragma_debug(TEST)<<"TEST";
    pragma_warning(TEST)<<"TEST";
    pragma_error(TEST)<<"TEST";

    pragma_debug(TEST1) << "TEST";

    AppBundle app;
}