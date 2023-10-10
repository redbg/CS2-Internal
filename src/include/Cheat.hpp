#pragma once
#include "Config.hpp"
#include "Offset.hpp"

namespace Cheat
{
    void Triggerbot()
    {
        auto localPlayerController = *CS2::Offset::LocalPlayerController;
        auto localPlayerPawn       = static_cast<CS2::Class::C_CSPlayerPawn *>(localPlayerController->m_hPawn().Get());
        int  iIDEntIndex           = localPlayerPawn->m_iIDEntIndex();

        if (iIDEntIndex != -1)
        {
            auto target = CS2::Offset::GetBaseEntity(*CS2::Offset::GameEntitySystem, iIDEntIndex);
            // printf("%x %d %d\n", iIDEntIndex, target->m_iTeamNum(), localPlayerController->m_iTeamNum());
            if (target->m_iTeamNum() != 0 && target->m_iTeamNum() != localPlayerController->m_iTeamNum())
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
        }
    }

    void Run()
    {
        if (CS2::Interface::EngineClient->IsInGame())
        {
            if (Config::Triggerbot && ImGui::IsKeyPressed(ImGuiKey_LeftShift))
                Triggerbot();
        }
    }

} // namespace Cheat
