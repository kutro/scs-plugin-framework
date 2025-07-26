#pragma once

#include <functional>
#include <vector>
#include <utility>

#include "Namespace.hpp"

SPF_NS_BEGIN

// A wrapper for a callable object.
template <typename T>
class Delegate;

template <typename Ret, typename... Args>
class Delegate<Ret(Args...)>
{
public:
    using Func = std::function<Ret(Args...)>;

private:
    Func _func;

public:
    // Default constructor for an empty delegate
    Delegate() = default;

    // Constructor for any compatible callable object (free functions, lambdas, etc.)
    Delegate(Func func) : _func(std::move(func)) {}

    // Constructor for free functions and static methods
    Delegate(Ret (*funcPtr)(Args...)) : _func(funcPtr) {}

    // Constructor for member functions
    template <typename TClass>
    Delegate(TClass* obj, Ret (TClass::*funcPtr)(Args...))
    {
        _func = [obj, funcPtr](Args... args) { return (obj->*funcPtr)(std::forward<Args>(args)...); };
    }

    // Constructor for const member functions
    template <typename TClass>
    Delegate(const TClass* obj, Ret (TClass::*funcPtr)(Args...) const)
    {
        _func = [obj, funcPtr](Args... args) {
            return (obj->*funcPtr)(std::forward<Args>(args)...);
        };
    }

    Ret operator()(Args... args) const
    {
        if (!_func)
        {
            if constexpr (!std::is_void_v<Ret>) { return Ret{}; }
            else { return; }
        }
        return _func(std::forward<Args>(args)...);
    }

    explicit operator bool() const
    {
        return _func != nullptr;
    }
};

// A collection of delegates that can be called at once.
template <typename... Args>
class Sink
{
public:
    using DelegateType = Delegate<void(Args...)>;

private:
    std::vector<DelegateType> _delegates;

public:
    // Connect a delegate to the sink
    void connect(DelegateType delegate)
    {
        _delegates.push_back(std::move(delegate));
    }

    // Call all connected delegates
    void call(Args... args) const
    {
        for (const auto& delegate : _delegates)
        {
            if (delegate)
            {
                // Call without forwarding to prevent moving from args in a loop.
                // This ensures all listeners receive the same valid arguments.
                delegate(args...);
            }
        }
    }
};

SPF_NS_END
