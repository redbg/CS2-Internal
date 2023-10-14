#pragma once

namespace CS2::Class
{
    struct CBoneData
    {
        SDK::Vector pos;
        char        pad[0x14];
    };

    class CGameSceneNode
    {
    public:
    };

    class CSkeletonInstance : public CGameSceneNode
    {
    public:
        CBoneData *GetBoneData()
        {
            return *(CBoneData **)((DWORD64)this + 0x1E0);
        }
    };

} // namespace CS2::Class
