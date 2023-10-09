#pragma once
#include "Virtual.hpp"

namespace CS2::Class
{
    // Source2EngineToClient001
    class CEngineClient
    {
    public:
        bool IsInGame()
        {
            return Virtual::Call<32, bool>(this);
        }

        bool IsConnected()
        {
            return Virtual::Call<33, bool>(this);
        }

        SIZE GetScreenSize()
        {
            // size.cx = width
            // size.cy = height
            SIZE size = {};
            Virtual::Call<50, void>(this, &size.cx, &size.cy);
            return size;
        }
    };

} // namespace CS2::Class
