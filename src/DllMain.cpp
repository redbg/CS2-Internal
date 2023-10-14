#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

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

DWORD WINAPI UnloadThread(LPVOID hModule)
{
    while (!GetAsyncKeyState(VK_END))
    {
        Sleep(100);
    }

    FreeLibraryAndExitThread((HMODULE)hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, UnloadThread, (HMODULE)hModule, 0, 0);
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
