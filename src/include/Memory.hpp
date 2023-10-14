#pragma once
#include <Psapi.h>

namespace Memory
{
    bool CompareByteArray(uintptr_t dest, std::string pattern)
    {
        for (DWORD i = 0; i < pattern.length(); i++)
        {
            if (pattern[i] == '?')
            {
                continue;
            }

            if (((char *)dest)[i] != pattern[i])
            {
                return false;
            }
        }

        return true;
    }

    uintptr_t FindPattern(std::string moduleName, std::string pattern)
    {
        // 获取模块句柄
        if (HMODULE hModule = GetModuleHandleA(moduleName.c_str()))
        {
            // 获取模块信息
            MODULEINFO moduleInfo = {};
            if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo)))
            {
                // 开始搜索
                for (uintptr_t i = 0; i < moduleInfo.SizeOfImage - pattern.length(); i++)
                {
                    if (CompareByteArray((uintptr_t)moduleInfo.lpBaseOfDll + i, pattern))
                    {
                        // 搜索成功,返回地址
                        return (uintptr_t)moduleInfo.lpBaseOfDll + i;
                    }
                }
            }
        }

        // 搜索失败,返回0
        return 0;
    }

    uintptr_t RelativeRIP(uintptr_t address, int instruction)
    {
        return address + instruction + *(int *)(address + instruction - 4);
    }

} // namespace Memory
