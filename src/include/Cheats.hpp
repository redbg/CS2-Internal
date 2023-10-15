#pragma once

namespace CS2::Cheats
{
    void Triggerbot()
    {
        if (!Config::Triggerbot::Enable)
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

        if ((localPlayerPawn->m_holdTargetIDTimer().m_timestamp() - localPlayerPawn->m_delayTargetIDTimer().m_timestamp() + 0.3) < Config::Triggerbot::Delay)
            return;

        // Check Team
        if (Config::Triggerbot::CheckTeam)
        {
            auto playerPawn = CS2::Offset::GetBaseEntity(*CS2::Offset::GameEntitySystem, iIDEntIndex); // C_CSPlayerPawn

            if (playerPawn->m_iTeamNum() == 0)
                return;

            if (playerPawn->m_iTeamNum() == localPlayerController->m_iTeamNum())
                return;
        }

        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }

    void RadarSpotted()
    {
        if (!Config::Radar::Spotted)
            return;

        if (!ImGui::IsKeyDown(ImGuiKey_MouseX2))
            return;

        if (!CS2::Interface::EngineClient->IsInGame())
            return;

        auto localPlayerController = *CS2::Offset::LocalPlayerController;

        for (uint64_t i = 0; i < 64; i++)
        {
            auto playerController = (Class::CCSPlayerController *)Offset::GetBaseEntity(*Offset::GameEntitySystem, i + 1);

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
        if (!Config::Aimbot::Enable)
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

        static uint64_t localPlayerControllerIndex = 0;

        for (uint64_t i = 0; i < 64; i++)
        {
            auto playerController = (Class::CCSPlayerController *)Offset::GetBaseEntity(*Offset::GameEntitySystem, i + 1);

            if (playerController == nullptr)
                continue;

            if (playerController->m_bIsLocalPlayerController())
            {
                localPlayerControllerIndex = i;
                continue;
            }

            // Check Team
            if (Config::Aimbot::CheckTeam)
            {
                if (playerController->m_iTeamNum() == localPlayerController->m_iTeamNum())
                    continue;
            }

            if (!playerController->m_bPawnIsAlive())
                continue;

            auto playerPawn = static_cast<CS2::Class::C_CSPlayerPawn *>(playerController->m_hPawn().Get());

            if (playerPawn->m_iHealth() <= 0)
                return;

            // Check Visible
            if (Config::Aimbot::CheckVisible == false ||
                playerPawn->m_entitySpottedState().GetSpottedByMask() & (uint64_t(1) << localPlayerControllerIndex) ||
                localPlayerPawn->m_entitySpottedState().GetSpottedByMask() & (uint64_t(1) << i))
            {
                auto BoneData = static_cast<CS2::Class::CSkeletonInstance *>(playerPawn->m_pGameSceneNode())->GetBoneData();

                SDK::Vector aimPos = BoneData[Config::Aimbot::BoneIndex].pos;

                // 通过骨骼索引压枪，效果不太好，先注释掉
                // if (localPlayerPawn->m_iShotsFired())
                // {
                //     int calcBoneIndex = Config::Aimbot::BoneIndex - localPlayerPawn->m_iShotsFired();
                //     aimPos            = BoneData[calcBoneIndex < 0 ? 0 : calcBoneIndex].pos;
                // }

                SDK::Vector aimAngle = SDK::CalcAngle(localPlayerPawn->m_vecLastClipCameraPos(), aimPos);
                Offset::SetViewAngle(Offset::CSGOInput, 0, aimAngle);
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
