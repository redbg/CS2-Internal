#pragma once
#include <stdint.h>

namespace Virtual
{
    template <int Index, typename ReturnType, typename... Args>
    inline ReturnType Call(void *pThis, Args... args)
    {
        using func = ReturnType(__thiscall *)(void *, Args...);
        return (*(func **)(pThis))[Index](pThis, args...);
    }
} // namespace Virtual
