#include "SPF/Logger/LoggerFactory.hpp"

#include <fstream>
#include <memory>

#include "SPF/Events/EventDispatcher.hpp"
#include "SPF/Logger/Logger.hpp"

SPF_NS_BEGIN

namespace
{
std::ofstream logFile;
EventDispatcher* g_EventDispatcher = nullptr;

class FileLogger : public Logger
{
public:
    void log(Level level, const std::string& message) override
    {
        if (logFile.is_open())
        {
            switch (level)
            {
                case Level::Info:
                    logFile << "[info] " << message << std::endl;
                    break;
                case Level::Warning:
                    logFile << "[warn] " << message << std::endl;
                    break;
                case Level::Error:
                    logFile << "[error] " << message << std::endl;
                    break;
            }
        }
    }
};

class ConsoleLogger : public Logger
{
public:
    void log(Level level, const std::string& message) override
    {
        // For now, just print to console
        // In a real scenario, you might want to use platform-specific console output
    }
};

class EventLogger : public Logger
{
public:
    void log(Level level, const std::string& message) override
    {
        // For now, just print to console
        // In a real scenario, you might want to dispatch an event
    }
};

} // namespace

void LoggerFactory::Init(const std::string& logFilePath, EventDispatcher& eventDispatcher)
{
    logFile.open(logFilePath, std::ios_base::app);
    g_EventDispatcher = &eventDispatcher;
}

std::unique_ptr<Logger> LoggerFactory::GetLogger(const std::string& name)
{
    // For now, always return a file logger
    return std::make_unique<FileLogger>();
}

SPF_NS_END
