#pragma once

#include <cstdint>

#include "Namespace.hpp"

SPF_NS_BEGIN

class Detour
{
public:
    enum class Status : int32_t
    {
        Ok = 0,
        Error = 1,
        AlreadyCreated = 2,
        NotFound = 3,
        NotEnabled = 4,
        NotExecutable = 5,
        Unsupported = 6,
        NotInitialized = 7,
        AlreadyEnabled = 8,
        AlreadyDisabled = 9,
        InvalidParameter = 10,
        MemoryAlloc = 11,
        MemoryProtect = 12,
        InternalError = 13
    };

private:
    void* _target;
    void* _detour;
    void* _original;

public:
    Detour(void* target, void* detour);
    ~Detour();

    Status create();
    Status enable();
    Status disable();
    Status remove();

    template <typename T>
    T getOriginal()
    {
        return reinterpret_cast<T>(_original);
    }
};

SPF_NS_END
