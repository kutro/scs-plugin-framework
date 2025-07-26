#pragma once

#include "SPF/Config/ConfigFieldBase.hpp"

SPF_NS_BEGIN

class BoolField : public ConfigFieldBase
{
private:
    bool _value;
    bool _defaultValue;
    bool* _bindValue;

public:
    BoolField(std::string id, std::string label, std::string description, bool defaultValue, bool* bindValue);

    void imguiRender() override;

    bool isDirty() const override;
    void applyChanges() override;
    void cancelChanges() override;
    bool canResetToDefault() const override;
    void resetToDefault() override;

    void setupCallbackData(ConfigCallbackData& data) override;
};

class BoolFieldBuilder
{
private:
    std::string _id;
    std::string _label;
    std::string _description;
    bool _defaultValue;
    bool* _bindValue;

public:
    BoolFieldBuilder();

    BoolFieldBuilder& setID(const std::string& id);
    BoolFieldBuilder& setLabel(const std::string& label);
    BoolFieldBuilder& setDescription(const std::string& description);
    BoolFieldBuilder& setDefaultValue(bool defaultValue);
    BoolFieldBuilder& bind(bool* bindValue);

    std::unique_ptr<BoolField> build();
};

SPF_NS_END
