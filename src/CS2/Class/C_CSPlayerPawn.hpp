#pragma once

namespace CS2::Class
{
    // C_BaseModelEntity
    class C_BaseModelEntity : public C_BaseEntity
    {
    public:
    };

    // CBaseAnimGraph
    class CBaseAnimGraph : public C_BaseModelEntity
    {
    public:
    };

    // C_BaseFlex
    class C_BaseFlex : public CBaseAnimGraph
    {
    public:
    };

    // C_BaseCombatCharacter
    class C_BaseCombatCharacter : public C_BaseFlex
    {
    public:
    };

    // C_BasePlayerPawn
    class C_BasePlayerPawn : public C_BaseCombatCharacter
    {
    public:
    };

    class EntitySpottedState_t
    {
    public:
        void    *vt;
        bool     m_bSpotted;
        uint32_t m_bSpottedByMask[2];

        uint64_t GetSpottedByMask()
        {
            return m_bSpottedByMask[0] | ((uint64_t)m_bSpottedByMask[1] << 32);
        }
    };

    class CountdownTimer
    {
    public:
        SCHEMA(float, m_timestamp, "m_timestamp", "CountdownTimer", "client.dll");
    };

    // C_CSPlayerPawnBase
    class C_CSPlayerPawnBase : public C_BasePlayerPawn
    {
    public:
        SCHEMA(bool, m_bIsScoped, "m_bIsScoped", "C_CSPlayerPawnBase", "client.dll");               // 是否开镜
        SCHEMA(bool, m_bIsWalking, "m_bIsWalking", "C_CSPlayerPawnBase", "client.dll");             // 是否静步
        SCHEMA(bool, m_bGunGameImmunity, "m_bGunGameImmunity", "C_CSPlayerPawnBase", "client.dll"); // 无敌状态
        SCHEMA(int32_t, m_iShotsFired, "m_iShotsFired", "C_CSPlayerPawnBase", "client.dll");
        SCHEMA(int, m_iIDEntIndex, "m_iIDEntIndex", "C_CSPlayerPawnBase", "client.dll");
        SCHEMA(CountdownTimer, m_delayTargetIDTimer, "m_delayTargetIDTimer", "C_CSPlayerPawnBase", "client.dll");
        SCHEMA(CountdownTimer, m_holdTargetIDTimer, "m_holdTargetIDTimer", "C_CSPlayerPawnBase", "client.dll");
        SCHEMA(SDK::Vector, m_vecLastClipCameraPos, "m_vecLastClipCameraPos", "C_CSPlayerPawnBase", "client.dll");
        SCHEMA(EntitySpottedState_t, m_entitySpottedState, "m_entitySpottedState", "C_CSPlayerPawnBase", "client.dll"); // EntitySpottedState_t
    };

    // C_CSPlayerPawn
    class C_CSPlayerPawn : public C_CSPlayerPawnBase
    {
    public:
        SCHEMA(SDK::Vector, m_aimPunchAngle, "m_aimPunchAngle", "C_CSPlayerPawn", "client.dll");
        SCHEMA(SDK::CUtlVector<SDK::Vector>, m_aimPunchCache, "m_aimPunchCache", "C_CSPlayerPawn", "client.dll");
    };

} // namespace CS2::Class
