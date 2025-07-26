#pragma once

#include <string>
#include <fmt/format.h>

#include "Namespace.hpp"

SPF_NS_BEGIN

class Logger
{
public:
    enum class Level
    {
        Info,
        Warning,
        Error
    };

public:
    virtual ~Logger() = default;

    virtual void log(Level level, const std::string& message) = 0;

    template <typename... Args>
    void info(const std::string& format, Args&&... args)
    {
        log(Level::Info, fmt::format(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void warn(const std::string& format, Args&&... args)
    {
        log(Level::Warning, fmt::format(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error(const std::string& format, Args&&... args)
    {
        log(Level::Error, fmt::format(format, std::forward<Args>(args)...));
    }
};

SPF_NS_END
