﻿#pragma once

namespace GUI
{
    void ShowCheatsWindow();
    void ShowDebugWindow();

    void ShowMainWindow()
    {
        // ImGui::ShowDemoWindow();

        if (ImGui::IsKeyPressed(ImGuiKey_Home))
        {
            Config::Open = !Config::Open;
        }

        if (ImGui::IsKeyPressed(ImGuiKey_End))
        {
            CreateThread(0, 0, UnloadThread, 0, 0, 0);
        }

        if (Config::Open)
        {
            ImGui::Begin("https://github.com/redbg/CS2-Internal", &Config::Open);

            ShowCheatsWindow();
            ShowDebugWindow();

            ImGui::End();
        }
    }

    void ShowCheatsWindow()
    {
        if (ImGui::CollapsingHeader("Cheats"))
        {
            // Triggerbot
            ImGui::SeparatorText("Triggerbot");
            ImGui::Checkbox("Enable##Triggerbot", &Config::Triggerbot::Enable);
            ImGui::Checkbox("Check Team##Triggerbot", &Config::Triggerbot::CheckTeam);
            ImGui::DragFloat("Delay##Triggerbot", &Config::Triggerbot::Delay, 0.001f, 0.0f, 1.0f);

            // Aimbot
            ImGui::SeparatorText("Aimbot");
            ImGui::Checkbox("Enable##Aimbot", &Config::Aimbot::Enable);
            ImGui::Checkbox("Check Team##Aimbot", &Config::Aimbot::CheckTeam);
            ImGui::Checkbox("Check Visible##Aimbot", &Config::Aimbot::CheckVisible);
            ImGui::Checkbox("Recoil Control##Aimbot", &Config::Aimbot::RecoilControl);
            ImGui::DragFloat("FOV##Aimbot", &Config::Aimbot::FOV, 0.1f, 0.0f, 180.0f);
            ImGui::DragInt("AimBoneIndex##Aimbot", &Config::Aimbot::AimBoneIndex, 0.1f, 0, 6);

            // Radar
            ImGui::SeparatorText("Radar");
            ImGui::Checkbox("Spotted##Radar", &Config::Radar::Spotted);
        }
    }

    void ShowDebugWindow()
    {
        if (ImGui::CollapsingHeader("Debug"))
        {
            // Offset
            ImGui::SeparatorText("Offset");
            ImGui::LabelText("GameEntitySystem", "0x%p", CS2::Offset::GameEntitySystem);
            ImGui::LabelText("LocalPlayerController", "0x%p", CS2::Offset::LocalPlayerController);
            ImGui::LabelText("CSGOInput", "0x%p", CS2::Offset::CSGOInput);
            ImGui::LabelText("GetEntity()", "0x%p", CS2::Offset::GetBaseEntity);
            ImGui::LabelText("SetViewAngle()", "0x%p", CS2::Offset::SetViewAngle);
            ImGui::LabelText("GetViewAngle()", "0x%p", CS2::Offset::GetViewAngle);
            if (ImGui::Button("Entity Dump"))
            {
                printf("------------------------------ [Entity Dump] ------------------------------\n");
                printf("GameEntitySystem: 0x%p\n", *CS2::Offset::GameEntitySystem);
                printf("LocalPlayerController: 0x%p\n", *CS2::Offset::LocalPlayerController);

                if (!CS2::Interface::EngineClient->IsInGame())
                    return;

                for (int i = 0; i < 64; i++)
                {
                    CS2::Class::CCSPlayerController *playerController = static_cast<CS2::Class::CCSPlayerController *>(CS2::Offset::GetBaseEntity(*CS2::Offset::GameEntitySystem, i + 1));

                    if (playerController == nullptr)
                        continue;

                    auto playerPawn = static_cast<CS2::Class::C_CSPlayerPawn *>(playerController->m_hPawn().Get());

                    printf("[%d] playerController:%p [%s] m_bPawnIsAlive:%d m_iTeamNum:%d m_hPawn:%p m_iHealth:%d m_bSpotted:%d SpottedByMask:%llx BoneData:%p\n", i,
                           playerController,
                           playerController->m_sSanitizedPlayerName(),
                           playerController->m_bPawnIsAlive(),
                           playerController->m_iTeamNum(),
                           playerPawn,
                           playerPawn->m_iHealth(),
                           playerPawn->m_entitySpottedState().m_bSpotted,
                           playerPawn->m_entitySpottedState().GetSpottedByMask(),
                           static_cast<CS2::Class::CSkeletonInstance *>(playerPawn->m_pGameSceneNode())->GetBoneData());
                }
                printf("\n");
            }

            // Interface
            ImGui::SeparatorText("Interface");
            ImGui::LabelText("CSchemaSystem", "0x%p", CS2::Interface::SchemaSystem);
            ImGui::LabelText("CEngineClient", "0x%p", CS2::Interface::EngineClient);

            // Schema
            ImGui::SeparatorText("Schema");
            static char moduleName[256] = "client.dll";
            static char className[256]  = "CCSPlayerController";
            ImGui::InputText("ModuleName", moduleName, sizeof(moduleName), ImGuiInputTextFlags_CharsNoBlank);
            ImGui::InputText("ClassName", className, sizeof(className), ImGuiInputTextFlags_CharsNoBlank);
            if (ImGui::Button("Schema Dump"))
            {
                printf("------------------------------ [Schema Dump %s %s] ------------------------------\n", moduleName, className);
                CS2::Interface::SchemaSystem->FindTypeScopeForModule(moduleName)->FindDeclaredClass(className)->Dump();
                printf("\n");
            }

            // CEngineClient
            ImGui::SeparatorText("CEngineClient");
            ImGui::LabelText("IsInGame", "%d", CS2::Interface::EngineClient->IsInGame());
            ImGui::LabelText("IsConnected", "%d", CS2::Interface::EngineClient->IsConnected());
            ImGui::LabelText("Screen Width", "%d", CS2::Interface::EngineClient->GetScreenSize().cx);
            ImGui::LabelText("Screen Height", "%d", CS2::Interface::EngineClient->GetScreenSize().cy);
        }
    }

} // namespace GUI
