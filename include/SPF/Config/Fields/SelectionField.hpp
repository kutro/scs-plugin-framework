#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SPF/Config/ConfigFieldBase.hpp"

SPF_NS_BEGIN

class SelectionField : public ConfigFieldBase
{
private:
    int _value;
    int _defaultValue;
    int* _bindValue;
    std::vector<std::string> _options;

public:
    SelectionField(std::string id, std::string label, std::string description, int defaultValue, int* bindValue, std::vector<std::string> options);

    void imguiRender() override;

    bool isDirty() const override;
    void applyChanges() override;
    void cancelChanges() override;
    bool canResetToDefault() const override;
    void resetToDefault() override;

    void setupCallbackData(ConfigCallbackData& data) override;
};

class SelectionFieldBuilder
{
private:
    std::string _id;
    std::string _label;
    std::string _description;
    int _defaultValue;
    int* _bindValue;
    std::vector<std::string> _options;

public:
    SelectionFieldBuilder();

    SelectionFieldBuilder& setID(const std::string& id);
    SelectionFieldBuilder& setLabel(const std::string& label);
    SelectionFieldBuilder& setDescription(const std::string& description);
    SelectionFieldBuilder& setDefaultValue(int defaultValue);
    SelectionFieldBuilder& bind(int* bindValue);
    SelectionFieldBuilder& addOptions(const std::vector<std::string>& options);

    std::unique_ptr<SelectionField> build();
};

SPF_NS_END
