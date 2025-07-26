#pragma once

#include <cstdint>
#include <string>

#include <fmt/format.h>

#include "Namespace.hpp"

SPF_NS_BEGIN

struct Version
{
    uint8_t major;
    uint16_t minor;
    uint16_t patch;

    [[nodiscard]] std::string toString() const
    {
        return fmt::format("{}.{}.{}", major, minor, patch);
    }
};

constexpr inline Version ApiVersion{ 1, 0, 0 };

SPF_NS_END

template<>
struct fmt::formatter<SPF::Version> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const SPF::Version& v, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "{}.{}.{}", v.major, v.minor, v.patch);
    }
};
