#pragma once

namespace CS2::Class
{
    // CBasePlayerController
    class CBasePlayerController : public C_BaseEntity
    {
    public:
        SCHEMA(CHandle<C_BasePlayerPawn>, m_hPawn, "m_hPawn", "CBasePlayerController", "client.dll");
        SCHEMA(bool, m_bIsLocalPlayerController, "m_bIsLocalPlayerController", "CBasePlayerController", "client.dll");
    };

    // CCSPlayerController
    class CCSPlayerController : public CBasePlayerController
    {
    public:
        SCHEMA(const char *, m_sSanitizedPlayerName, "m_sSanitizedPlayerName", "CCSPlayerController", "client.dll");
        SCHEMA(bool, m_bPawnIsAlive, "m_bPawnIsAlive", "CCSPlayerController", "client.dll");
    };

} // namespace CS2::Class
