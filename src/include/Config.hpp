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
        bool Enable             = true;
        bool CheckTeam          = true;
        bool CheckVisible       = true;
        int  AimBoneIndex       = 6;
        int  ScopedAimBoneIndex = 4;
    } // namespace Aimbot

    namespace Radar
    {
        bool Spotted = true;
    } // namespace Radar

} // namespace Config
