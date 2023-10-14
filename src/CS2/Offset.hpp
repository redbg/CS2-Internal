#pragma once

namespace CS2::Offset
{
    class CGameEntitySystem
    {
    public:
    };

    class CCSGOInput
    {
    public:
    };

    CGameEntitySystem               **GameEntitySystem      = (CGameEntitySystem **)Memory::RelativeRIP(Memory::FindPattern("client.dll", "\x48\x8B\x0D????\x48\x89\x7C\x24\x30\x8B\xFA"), 7);       // CGameEntitySystem
    CS2::Class::CCSPlayerController **LocalPlayerController = (CS2::Class::CCSPlayerController **)Memory::RelativeRIP(Memory::FindPattern("client.dll", "\x48\x8B\x05????\x48\x85\xC0\x74\x4F"), 7); // CCSPlayerController
    CCSGOInput                       *CSGOInput             = (CCSGOInput *)Memory::RelativeRIP(Memory::FindPattern("client.dll", "\x48\x8D\x0D????\xE8????\x66\x0F\x6F\x05"), 7);
    auto                              GetBaseEntity         = (CS2::Class::C_BaseEntity * (*)(CGameEntitySystem *, int)) Memory::FindPattern("client.dll", "\x81\xFA\xFE\x7F??\x77\x36");

    auto SetViewAngle = (bool (*)(CCSGOInput *, int, SDK::Vector &))Memory::FindPattern("client.dll", "\xF2\x41\x0F\x10?\x4C\x63\xCA");
    auto GetViewAngle = (SDK::Vector & (*)(CCSGOInput *, int)) Memory::FindPattern("client.dll", "\x4C\x63\xC2\x4B\x8D\x04\x40\x4C\x8D\x0C\xC1");
} // namespace CS2::Offset
