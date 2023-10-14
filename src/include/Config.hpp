#pragma once

namespace Config
{
    namespace Triggerbot
    {
        bool  Enable    = true;
        bool  CheckTeam = true;
        float Delay     = 0.1;
    } // namespace Triggerbot

    namespace Aimbot
    {
        bool Enable       = true;
        bool CheckTeam    = true;
        bool CheckVisible = true;
        int  BoneIndex    = 6;
    } // namespace Aimbot

    namespace Radar
    {
        bool Spotted = true;
    } // namespace Radar

} // namespace Config
