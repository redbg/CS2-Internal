#pragma once
#include "imgui.h"

#include "Interface.hpp"
#include "Offset.hpp"

namespace GUI
{
    void ShowMainWindow()
    {
        // ImGui::ShowDemoWindow();

        ImGui::Begin("Main");

        if (ImGui::CollapsingHeader("Debug"))
        {
            // Offset
            ImGui::SeparatorText("Offset");
            ImGui::LabelText("GameEntitySystem", "0x%p", CS2::Offset::GameEntitySystem);
            ImGui::LabelText("LocalPlayerController", "0x%p", CS2::Offset::LocalPlayerController);
            ImGui::LabelText("GetEntity()", "0x%p", CS2::Offset::GetEntity);
            if (ImGui::Button("Entity Dump"))
            {
                printf("------------------------------ [Entity Dump] ------------------------------\n");
                printf("GameEntitySystem: 0x%p\n", *CS2::Offset::GameEntitySystem);
                printf("LocalPlayerController: 0x%p\n", *CS2::Offset::LocalPlayerController);
                for (int i = 1; i <= 32; i++)
                {
                    auto entity = CS2::Offset::GetEntity(*CS2::Offset::GameEntitySystem, i);
                    if (entity)
                    {
                        printf("[%d] %p\n", i, entity);
                    }
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

        ImGui::End();
    }

} // namespace GUI
