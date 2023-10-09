#include "Console.hpp"
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
