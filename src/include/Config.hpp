#pragma once

namespace Config
{
    bool Open = true;

    namespace Triggerbot
    {
        bool  Enable    = true;
        bool  CheckTeam = true;
        float Delay     = 0.1;
    } // namespace Triggerbot

    namespace Aimbot
    {
        bool  Enable        = true;
        bool  CheckTeam     = true;
        bool  CheckVisible  = true;
        bool  RecoilControl = true;
        float FOV           = 10.0f;
        int   AimBoneIndex  = 4;
    } // namespace Aimbot

    namespace Radar
    {
        bool Spotted = true;
    } // namespace Radar

} // namespace Config
