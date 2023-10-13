#pragma once
#include "Offset.hpp"

#include "Config.hpp"

namespace CS2::Cheats
{
    void Triggerbot()
    {
        if (!Config::Triggerbot)
            return;

        if (!ImGui::IsKeyDown(ImGuiKey_MouseX2))
            return;

        if (!CS2::Interface::EngineClient->IsInGame())
            return;

        auto localPlayerController = *CS2::Offset::LocalPlayerController;

        if (!localPlayerController->m_bPawnIsAlive())
            return;

        auto localPlayerPawn = static_cast<CS2::Class::C_CSPlayerPawn *>(localPlayerController->m_hPawn().Get());
        int  iIDEntIndex     = localPlayerPawn->m_iIDEntIndex();

        if (iIDEntIndex == -1)
            return;

        auto playerPawn = CS2::Offset::GetBaseEntity(*CS2::Offset::GameEntitySystem, iIDEntIndex); // C_CSPlayerPawn
        if (playerPawn->m_iTeamNum() != 0 && playerPawn->m_iTeamNum() != localPlayerController->m_iTeamNum())
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }

    void RadarSpotted()
    {
        if (!Config::RadarSpotted)
            return;

        if (!ImGui::IsKeyDown(ImGuiKey_MouseX2))
            return;

        if (!CS2::Interface::EngineClient->IsInGame())
            return;

        auto localPlayerController = *CS2::Offset::LocalPlayerController;

        for (uint64_t i = 1; i <= 64; i++)
        {
            auto playerController = (Class::CCSPlayerController *)Offset::GetBaseEntity(*Offset::GameEntitySystem, i);

            if (playerController == nullptr)
                continue;

            if (playerController->m_bIsLocalPlayerController())
                continue;

            if (playerController->m_iTeamNum() == localPlayerController->m_iTeamNum())
                continue;

            if (!playerController->m_bPawnIsAlive())
                continue;

            auto playerPawn = static_cast<CS2::Class::C_CSPlayerPawn *>(playerController->m_hPawn().Get());

            playerPawn->m_entitySpottedState().m_bSpotted = true;
        }
    }

    void Aimbot()
    {
        if (!Config::Aimbot)
            return;

        if (!ImGui::IsKeyDown(ImGuiKey_MouseX2) && !ImGui::IsKeyDown(ImGuiKey_MouseLeft))
            return;

        if (!CS2::Interface::EngineClient->IsInGame())
            return;

        auto localPlayerController = *CS2::Offset::LocalPlayerController;
        auto localPlayerPawn       = static_cast<CS2::Class::C_CSPlayerPawn *>(localPlayerController->m_hPawn().Get());
        int  iIDEntIndex           = localPlayerPawn->m_iIDEntIndex();

        if (!localPlayerController->m_bPawnIsAlive())
            return;

        static uint64_t localPlayerControllerIndex = 1;

        for (uint64_t i = 1; i <= 64; i++)
        {
            auto playerController = (Class::CCSPlayerController *)Offset::GetBaseEntity(*Offset::GameEntitySystem, i);

            if (playerController == nullptr)
                continue;

            if (playerController->m_bIsLocalPlayerController())
            {
                localPlayerControllerIndex = i;
                continue;
            }

            if (playerController->m_iTeamNum() == localPlayerController->m_iTeamNum())
                continue;

            if (!playerController->m_bPawnIsAlive())
                continue;

            auto playerPawn = static_cast<CS2::Class::C_CSPlayerPawn *>(playerController->m_hPawn().Get());

            // Visible Check
            if (playerPawn->m_entitySpottedState().GetSpottedByMask() & (uint64_t(1) << (localPlayerControllerIndex - 1)) ||
                localPlayerPawn->m_entitySpottedState().GetSpottedByMask() & (uint64_t(1) << (i - 1)))
            {
                SDK::Vector aimbotAngle = SDK::CalcAngle(localPlayerPawn->m_vecLastClipCameraPos(), playerPawn->m_vecLastClipCameraPos());
                Offset::SetViewAngle(Offset::CSGOInput, 0, aimbotAngle);
                break;
            }
        }
    }

    void Run()
    {
        Triggerbot();
        RadarSpotted();
        Aimbot();
    }

} // namespace CS2::Cheats
