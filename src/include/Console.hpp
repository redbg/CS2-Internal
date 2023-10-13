#pragma once
#include <Windows.h>
#include <locale>
#include <stdio.h>

namespace Console
{
    void Initialize()
    {
        AllocConsole();
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleTitleA("CS2-Internal");
        freopen_s((FILE **)stdin, "CONIN$", "r", stdin);
        freopen_s((FILE **)stdout, "CONOUT$", "w", stdout);
        freopen_s((FILE **)stderr, "CONOUT$", "w", stderr);
        std::setlocale(LC_ALL, ".utf8");
        printf("%s\n", __FUNCTION__);
    }

    void Uninitialize()
    {
        printf("%s\n", __FUNCTION__);
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        FreeConsole();
    }

} // namespace Console
