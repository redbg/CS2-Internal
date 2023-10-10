#pragma once
#include "C_BaseEntity.hpp"

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

    // C_CSPlayerPawnBase
    class C_CSPlayerPawnBase : public C_BasePlayerPawn
    {
    public:
        SCHEMA(int, m_iIDEntIndex, "m_iIDEntIndex", "C_CSPlayerPawnBase", "client.dll"); // C_CSPlayerPawn
    };

    // C_CSPlayerPawn
    class C_CSPlayerPawn : public C_CSPlayerPawnBase
    {
    public:
    };

} // namespace CS2::Class
