#include "SPF/Logger/Logger.hpp"

#include <iostream>

SPF_NS_BEGIN

// Simple console logger for now
class ConsoleLogger : public Logger
{
public:
    void log(Level level, const std::string& message) override
    {
        switch (level)
        {
            case Level::Info:
                std::cout << "[INFO] " << message << std::endl;
                break;
            case Level::Warning:
                std::cout << "[WARN] " << message << std::endl;
                break;
            case Level::Error:
                std::cerr << "[ERROR] " << message << std::endl;
                break;
        }
    }
};

// This will be replaced by LoggerFactory later
// For now, just a simple global logger
Logger* g_Logger = new ConsoleLogger();

SPF_NS_END
