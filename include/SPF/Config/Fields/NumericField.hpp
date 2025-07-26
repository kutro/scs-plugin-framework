#pragma once

#include <string>
#include <memory>

#include "SPF/Config/ConfigFieldBase.hpp"

SPF_NS_BEGIN

template <typename T, typename = void>
class NumericField : public ConfigFieldBase
{
protected:
    T _value;
    T _defaultValue;
    T* _bindValue;

public:
    NumericField(std::string id, std::string label, std::string description, T defaultValue, T* bindValue);

    void imguiRender() override;

    bool isDirty() const override;
    void applyChanges() override;
    void cancelChanges() override;
    bool canResetToDefault() const override;
    void resetToDefault() override;

    void setupCallbackData(ConfigCallbackData& data) override;
};

template <typename T>
class NumericFieldBuilder
{
private:
    std::string _id;
    std::string _label;
    std::string _description;
    T _defaultValue;
    T* _bindValue;

    bool _useSlider = false;
    T _sliderMin = 0;
    T _sliderMax = 0;
    std::string _sliderFormat = "%.3f";

    bool _useDrag = false;
    float _dragSpeed = 1.0f;
    T _dragMin = 0;
    T _dragMax = 0;
    std::string _dragFormat = "%.3f";

public:
    NumericFieldBuilder();

    NumericFieldBuilder<T>& setID(const std::string& id);
    NumericFieldBuilder<T>& setLabel(const std::string& label);
    NumericFieldBuilder<T>& setDescription(const std::string& description);
    NumericFieldBuilder<T>& setDefaultValue(T defaultValue);
    NumericFieldBuilder<T>& bind(T* bindValue);

    NumericFieldBuilder<T>& useSlider(T min, T max, const std::string& format = "%.3f");
    NumericFieldBuilder<T>& useDrag(float speed, T min, T max, const std::string& format = "%.3f");

    std::unique_ptr<NumericField<T>> build();
};

SPF_NS_END
