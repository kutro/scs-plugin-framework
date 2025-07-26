#pragma once

#include <memory>
#include <string>

#include "Namespace.hpp"
#include "SPF/Logger/Logger.hpp"
#include "SPF/Events/EventDispatcher.hpp"

SPF_NS_BEGIN

class LoggerFactory
{
public:
    static void Init(const std::string& logFilePath, EventDispatcher& eventDispatcher);
    static std::unique_ptr<Logger> GetLogger(const std::string& name);
};

SPF_NS_END
