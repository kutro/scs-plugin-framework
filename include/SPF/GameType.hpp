#pragma once

#include <string>
#include <string_view>

#include "Namespace.hpp"

SPF_NS_BEGIN

enum class GameType
{
    Unknown,
    ETS2,
    ATS
};

inline std::string_view GameTypeToString(GameType gameType)
{
    switch (gameType)
    {
        case GameType::ETS2: return "Euro Truck Simulator 2";
        case GameType::ATS: return "American Truck Simulator";
        default: return "Unknown";
    }
}

SPF_NS_END
