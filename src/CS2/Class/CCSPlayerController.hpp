#pragma once
#include "CHandle.hpp"
#include "C_CSPlayerPawn.hpp"

namespace CS2::Class
{
    // CBasePlayerController
    class CBasePlayerController : public C_BaseEntity
    {
    public:
        SCHEMA(CHandle<C_BasePlayerPawn>, m_hPawn, "m_hPawn", "CBasePlayerController", "client.dll");
    };

    // CCSPlayerController
    class CCSPlayerController : public CBasePlayerController
    {
    public:
        SCHEMA(uint32_t, m_iPawnHealth, "m_iPawnHealth", "CCSPlayerController", "client.dll");
    };

} // namespace CS2::Class
