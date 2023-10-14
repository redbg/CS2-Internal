#pragma once

namespace CS2::Class
{
    // CEntityInstance
    class CEntityInstance
    {
    public:
    };

    // C_BaseEntity
    class C_BaseEntity : public CEntityInstance
    {
    public:
        SCHEMA(uint8_t, m_iTeamNum, "m_iTeamNum", "C_BaseEntity", "client.dll");
        SCHEMA(int32_t, m_iHealth, "m_iHealth", "C_BaseEntity", "client.dll");
        SCHEMA(CGameSceneNode *, m_pGameSceneNode, "m_pGameSceneNode", "C_BaseEntity", "client.dll");
    };

} // namespace CS2::Class
