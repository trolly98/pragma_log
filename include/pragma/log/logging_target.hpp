#pragma once

namespace pragma
{

class LoggingTarget
{
public:
    enum class Target
    {
        SYSLOG,
        CONSOLE,
        BOTH
    };

    static LoggingTarget& instance() 
    {
        static LoggingTarget instance;
        return instance;
    }

    constexpr Target get() const
    {
        return _target;
    }

    void set(Target target) 
    { 
        _target = target; 
    }

private:
    Target _target = Target::BOTH;
};

}