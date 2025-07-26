#pragma once

#include <string>
#include <memory>

#include "Namespace.hpp"

SPF_NS_BEGIN

struct ConfigCallbackData; // Forward declaration

class ConfigFieldBase
{
protected:
    std::string _id;
    std::string _label;
    std::string _description;

public:
    ConfigFieldBase(std::string id, std::string label, std::string description);
    virtual ~ConfigFieldBase() = default;

    virtual void imguiRender() = 0;

    virtual bool isDirty() const = 0;
    virtual void applyChanges() = 0;
    virtual void cancelChanges() = 0;
    virtual bool canResetToDefault() const = 0;
    virtual void resetToDefault() = 0;

    virtual void setupCallbackData(ConfigCallbackData& data) = 0;
};

SPF_NS_END
