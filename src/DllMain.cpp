#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

HMODULE g_hModule = NULL;

DWORD WINAPI UnloadThread(LPVOID)
{
    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}

#include "Memory.hpp"
#include "Virtual.hpp"
#include "SDK.hpp"

#include "Interface.hpp"
#include "Schema.hpp"

#include "CSkeletonInstance.hpp"
#include "C_BaseEntity.hpp"
#include "CHandle.hpp"
#include "C_CSPlayerPawn.hpp"
#include "CCSPlayerController.hpp"

#include "Offset.hpp"

// include
#include "Config.hpp"

#include "Cheats.hpp"
#include "Console.hpp"
#include "GUI.hpp"
#include "Hook.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        g_hModule = hModule;
        Console::Initialize();
        Hook::Initialize();
        break;
    case DLL_PROCESS_DETACH:
        Hook::Uninitialize();
        Console::Uninitialize();
        break;
    }

    return TRUE;
}
