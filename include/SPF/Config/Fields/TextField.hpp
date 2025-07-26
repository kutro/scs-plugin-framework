#pragma once

#include <string>
#include <memory>

#include "SPF/Config/ConfigFieldBase.hpp"

SPF_NS_BEGIN

class TextField : public ConfigFieldBase
{
private:
    std::string _value;
    std::string _defaultValue;
    std::string* _bindValue;

public:
    TextField(std::string id, std::string label, std::string description, std::string defaultValue, std::string* bindValue);

    void imguiRender() override;

    bool isDirty() const override;
    void applyChanges() override;
    void cancelChanges() override;
    bool canResetToDefault() const override;
    void resetToDefault() override;

    void setupCallbackData(ConfigCallbackData& data) override;
};

class TextFieldBuilder
{
private:
    std::string _id;
    std::string _label;
    std::string _description;
    std::string _defaultValue;
    std::string* _bindValue;

public:
    TextFieldBuilder();

    TextFieldBuilder& setID(const std::string& id);
    TextFieldBuilder& setLabel(const std::string& label);
    TextFieldBuilder& setDescription(const std::string& description);
    TextFieldBuilder& setDefaultValue(const std::string& defaultValue);
    TextFieldBuilder& bind(std::string* bindValue);

    std::unique_ptr<TextField> build();
};

SPF_NS_END
