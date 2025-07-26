#pragma once

#include <string>
#include <vector>
#include <memory>
#include <windows.h>

#include "Namespace.hpp"
#include "SPF/Utils/Delegate.hpp"
#include "SPF/System/Keyboard.hpp"
#include "SPF/Events/Event.hpp"

SPF_NS_BEGIN

class KeyBind
{
private:
    std::string _id;
    std::string _label;
    std::string _description;
    Keyboard::Key _defaultKey = Keyboard::Key::Unknown;
    Keyboard::Key* _currentKey = nullptr;
    Delegate<void(ButtonState)> _onPress;
    Delegate<void(ButtonState)> _onRelease;

public:
    explicit KeyBind(std::string id) : _id(std::move(id)) {}

    // --- Builder-style methods ---
    KeyBind& setLabel(std::string label) { _label = std::move(label); return *this; }
    KeyBind& setDescription(std::string desc) { _description = std::move(desc); return *this; }
    KeyBind& setDefaultKey(Keyboard::Key key) { _defaultKey = key; return *this; }
    KeyBind& setPressCallback(Delegate<void(ButtonState)> callback) { _onPress = std::move(callback); return *this; }
    KeyBind& setReleaseCallback(Delegate<void(ButtonState)> callback) { _onRelease = std::move(callback); return *this; }

    // --- Getters ---
    const std::string& getID() const { return _id; }
    const std::string& getLabel() const { return _label; }
};

class KeyBinds
{
private:
    std::string _name;
    std::vector<std::unique_ptr<KeyBind>> _keyBinds;

public:
    explicit KeyBinds(std::string name);
    ~KeyBinds();

    // Creates a new KeyBind, stores it, and returns a reference to it for configuration.
    KeyBind& add(const std::string& id)
    {
        auto keyBind = std::make_unique<KeyBind>(id);
        _keyBinds.push_back(std::move(keyBind));
        return *_keyBinds.back();
    }

    const std::string& getName() const { return _name; }
    const std::vector<std::unique_ptr<KeyBind>>& getKeyBinds() const { return _keyBinds; }

    void saveToFile();
    bool loadFromFile();
};

SPF_NS_END