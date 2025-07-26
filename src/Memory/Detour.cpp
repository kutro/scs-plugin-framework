#include "SPF/Memory/Detour.hpp"

#include <MinHook.h>

#include "SPF/Logger/Logger.hpp"

SPF_NS_BEGIN

extern Logger* g_Logger;

Detour::Detour(void* target, void* detour) : _target(target), _detour(detour)
{
}

Detour::~Detour()
{
    remove();
}

Detour::Status Detour::create()
{
    if (auto err = MH_CreateHook(_target, _detour, &_original); err != MH_OK)
    {
        g_Logger->error("Cannot create hook: {}", MH_StatusToString(err));
        return static_cast<Status>(err);
    }

    return Status::Ok;
}

Detour::Status Detour::enable()
{
    if (auto err = MH_EnableHook(_target); err != MH_OK)
    {
        g_Logger->error("Cannot enable hook: {}", MH_StatusToString(err));
        return static_cast<Status>(err);
    }

    return Status::Ok;
}

Detour::Status Detour::disable()
{
    if (auto err = MH_DisableHook(_target); err != MH_OK)
    {
        g_Logger->error("Cannot disable hook: {}", MH_StatusToString(err));
        return static_cast<Status>(err);
    }

    return Status::Ok;
}

Detour::Status Detour::remove()
{
    if (auto err = MH_RemoveHook(_target); err != MH_OK)
    {
        g_Logger->error("Cannot remove hook: {}", MH_StatusToString(err));
        return static_cast<Status>(err);
    }

    return Status::Ok;
}

SPF_NS_END
