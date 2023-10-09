#include <Windows.h>
#include <stdio.h>

#include <TlHelp32.h>

BOOL InjectDLL(DWORD dwProcessId, const char *lpPath)
{
    BOOL  status     = FALSE;
    DWORD dwPathSize = (DWORD)strlen(lpPath) + 1;
    // The Resources need Release
    HANDLE hTargetProcess  = NULL;
    HANDLE hRemoteThread   = NULL;
    LPVOID lpRemoteAddress = NULL;

    do
    {
        // OpenProcess
        hTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

        if (hTargetProcess == NULL)
            break;

        // VirtualAllocEx
        lpRemoteAddress = VirtualAllocEx(
            hTargetProcess,
            NULL,
            dwPathSize,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_EXECUTE_READWRITE);

        if (lpRemoteAddress == NULL)
            break;

        // WriteProcessMemory
        SIZE_T numberOfBytesWritten = 0;
        WriteProcessMemory(
            hTargetProcess,
            lpRemoteAddress,
            lpPath,
            dwPathSize,
            &numberOfBytesWritten);

        if (numberOfBytesWritten != dwPathSize)
            break;

        // UnHook LdrLoadDll
        DWORD oldProtect = 0;
        auto  LdrLoadDll = GetProcAddress(GetModuleHandleA("ntdll.dll"), "LdrLoadDll");
        VirtualProtectEx(hTargetProcess, LdrLoadDll, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteProcessMemory(hTargetProcess, LdrLoadDll, LdrLoadDll, 5, &numberOfBytesWritten);
        VirtualProtectEx(hTargetProcess, LdrLoadDll, 5, oldProtect, &oldProtect);
        // UnHook NtOpenFile
        auto NtOpenFile = GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtOpenFile");
        VirtualProtectEx(hTargetProcess, NtOpenFile, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteProcessMemory(hTargetProcess, NtOpenFile, NtOpenFile, 5, &numberOfBytesWritten);
        VirtualProtectEx(hTargetProcess, NtOpenFile, 5, oldProtect, &oldProtect);

        // CreateRemoteThread
        hRemoteThread = CreateRemoteThread(
            hTargetProcess,
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)LoadLibraryA,
            lpRemoteAddress,
            0,
            NULL);

        if (hRemoteThread == NULL)
            break;

        // 等待线程结束
        WaitForSingleObject(hRemoteThread, INFINITE);

        // Inject DLL Successful
        status = TRUE;
    } while (false);

    if (hRemoteThread != NULL)
        CloseHandle(hRemoteThread);
    if (lpRemoteAddress != NULL)
        VirtualFreeEx(hTargetProcess, lpRemoteAddress, 0, MEM_RELEASE);
    if (hTargetProcess != NULL)
        CloseHandle(hTargetProcess);

    return status;
}

int main()
{
    char path[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, path);
    strcat_s(path, "\\CS2-Internal.dll");

    // 遍历进程
    HANDLE         hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32         = {sizeof(PROCESSENTRY32)};
    Process32First(hProcessSnap, &pe32);
    do
    {
        if (!strcmp(pe32.szExeFile, "cs2.exe"))
        {
            InjectDLL(pe32.th32ProcessID, path);
        }
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);

    return 0;
}
