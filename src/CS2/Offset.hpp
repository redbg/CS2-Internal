#pragma once
#include "CCSPlayerController.hpp"
#include "CGameEntitySystem.hpp"
#include "Memory.hpp"

namespace CS2::Offset
{
    CS2::Class::CGameEntitySystem   **GameEntitySystem      = (CS2::Class::CGameEntitySystem **)Memory::RelativeRIP(Memory::FindPattern("client.dll", "\x48\x8B\x0D????\x48\x89\x7C\x24\x30\x8B\xFA"), 7); // CGameEntitySystem
    CS2::Class::CCSPlayerController **LocalPlayerController = (CS2::Class::CCSPlayerController **)Memory::RelativeRIP(Memory::FindPattern("client.dll", "\x48\x8B\x05????\x48\x85\xC0\x74\x4F"), 7);       // CCSPlayerController
    auto                              GetEntity             = (CS2::Class::CCSPlayerController * (*)(CS2::Class::CGameEntitySystem *, int)) Memory::FindPattern("client.dll", "\x81\xFA\xFE\x7F\x00\x00\x77\x36");
} // namespace CS2::Offset
