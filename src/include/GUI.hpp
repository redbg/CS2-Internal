#pragma once
#include "imgui.h"

#include "Config.hpp"
#include "Interface.hpp"
#include "Offset.hpp"

namespace GUI
{
    void ShowCheatsWindow();
    void ShowDebugWindow();

    void ShowMainWindow()
    {
        // ImGui::ShowDemoWindow();

        ImGui::Begin("Main");

        ShowCheatsWindow();
        ShowDebugWindow();

        ImGui::End();
    }

    void ShowCheatsWindow()
    {
        if (ImGui::CollapsingHeader("Cheats"))
        {
            ImGui::Checkbox("Triggerbot", &Config::Triggerbot);
            ImGui::Checkbox("RadarSpotted", &Config::RadarSpotted);
            ImGui::Checkbox("Aimbot", &Config::Aimbot);
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

                for (int i = 1; i <= 64; i++)
                {
                    CS2::Class::CCSPlayerController *playerController = static_cast<CS2::Class::CCSPlayerController *>(CS2::Offset::GetBaseEntity(*CS2::Offset::GameEntitySystem, i));

                    if (playerController == nullptr)
                        continue;

                    auto playerPawn = static_cast<CS2::Class::C_CSPlayerPawn *>(playerController->m_hPawn().Get());

                    printf("[%d] playerController:%p [%s] m_bPawnIsAlive:%d m_iTeamNum:%d m_hPawn:%p m_iHealth:%d m_bSpotted:%d SpottedByMask:%llx\n", i,
                           playerController,
                           playerController->m_sSanitizedPlayerName(),
                           playerController->m_bPawnIsAlive(),
                           playerController->m_iTeamNum(),
                           playerPawn,
                           playerPawn->m_iHealth(),
                           playerPawn->m_entitySpottedState().m_bSpotted,
                           playerPawn->m_entitySpottedState().GetSpottedByMask());
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
