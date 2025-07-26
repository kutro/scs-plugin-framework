#include <memory>

#include <MinHook.h>
#include <Windows.h>
#include <scssdk_telemetry.h>

#include "fmt/core.h"

#include "SPF/Core.hpp"
#include "scssdk.h" // This is from SCS SDK, not our SPF

// Global instance of Core
static std::unique_ptr<SPF::Core> core;

__declspec(dllexport) SCSAPI_RESULT
    scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params)
{
    if (version != SCS_TELEMETRY_VERSION_1_01)
    {
        return SCS_RESULT_unsupported;
    }

    auto* initParams = (scs_telemetry_init_params_v100_t*)(params);

    auto log = initParams->common.log;

    if (core && core->isInited())
    {
        // Already initialized, do nothing.
        return SCS_RESULT_ok;
    }

    // If core exists but failed to init, or doesn't exist, we can proceed.
    // The Core constructor is now called in DllMain, so 'core' should always exist here.
    if (!core) 
    {
        log(SCS_LOG_TYPE_error, "[SPF-Framework] Core object is null, cannot initialize.");
        return SCS_RESULT_generic_error;
    }

    try
    {
        if (core->init(initParams))
        {
            return SCS_RESULT_ok;
        }
    }
    catch (const std::exception& ex)
    {
        log(SCS_LOG_TYPE_error, fmt::format("[SPF-Framework] {}", ex.what()).c_str());
    }

    return SCS_RESULT_generic_error;
}

__declspec(dllexport) SCSAPI_VOID scs_telemetry_shutdown(void)
{
    core.reset();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID /*unused*/)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            MH_Initialize();
            core = std::make_unique<SPF::Core>(hinstDLL);
        }
        break;
        case DLL_PROCESS_DETACH:
        {
            MH_Uninitialize();
        }
        break;
    }

    return TRUE;
}
