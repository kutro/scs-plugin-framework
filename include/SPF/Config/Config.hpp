#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "Namespace.hpp"
#include "SPF/Utils/Delegate.hpp" // For Delegate
#include <nlohmann/json.hpp> // Added for nlohmann::json

SPF_NS_BEGIN

class ConfigFieldBase; // Forward declaration

struct ConfigCallbackData
{
    void* data;
    size_t size;

    template <typename T>
    const T* getData() const
    {
        return static_cast<const T*>(data);
    }
};

class Config
{
private:
    std::string _name;
    std::string _configFilePath;
    std::vector<std::unique_ptr<ConfigFieldBase>> _fields;

    std::function<void*()> _bindingStructCtor;
    std::function<void(void*)> _bindingStructDtor;
    size_t _bindingStructSize = 0;

public:
    Delegate<void(const ConfigCallbackData&)> onChangesApplied;

public:
    Config(std::string name);
    ~Config();

    template <typename T>
    void setBindingType()
    {
        _bindingStructCtor = []() { return new T(); };
        _bindingStructDtor = [](void* ptr) { delete static_cast<T*>(ptr); };
        _bindingStructSize = sizeof(T);
    }

    void add(std::unique_ptr<ConfigFieldBase> field);

    void saveToFile() const;
    bool loadFromFile();

    bool isDirty() const;
    void applyChanges();
    void cancelChanges();
    void resetToDefault();

    void imguiRender();

private:
    void toJson(void* data, nlohmann::json& json) const; // Assuming nlohmann::json
    void fromJson(void* data, const nlohmann::json& json); // Assuming nlohmann::json
    void invokeCallback();
};

SPF_NS_END
