#pragma once

#include <iostream>
#include <cstring>
#include <array>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <thread>


#define THREAD_ID() []() -> std::string { \
    std::ostringstream oss; \
    oss << std::this_thread::get_id(); \
    return oss.str(); \
}()

static std::string time_formatted(const std::string& format) 
{
    std::ostringstream oss;
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    oss << std::put_time(&tm, format.c_str());
    return oss.str();
}

static std::string time() 
{
    return time_formatted("%H:%M:%S");
}

static std::string full_time() 
{
    return time_formatted("%Y-%m-%d %H:%M:%S");
}

static std::string precise_time() 
{
    std::ostringstream oss;
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    oss << std::put_time(&tm, "%H:%M:%S") << "." << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
}