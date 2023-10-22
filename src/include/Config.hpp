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
        bool  Enable       = true;
        bool  CheckTeam    = true;
        bool  CheckVisible = true;
        float FOV          = 10.0f;
    } // namespace Aimbot

    namespace Radar
    {
        bool Spotted = true;
    } // namespace Radar

} // namespace Config
