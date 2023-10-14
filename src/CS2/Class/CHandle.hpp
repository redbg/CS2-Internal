#pragma once

constexpr auto INVALID_EHANDLE_INDEX     = 0xffffffff;
constexpr auto ENT_ENTRY_MASK            = 0x7fff;
constexpr auto NUM_SERIAL_NUM_SHIFT_BITS = 15;

namespace CS2::Class
{
    template <typename T>
    class CHandle
    {
    public:
        uint32_t m_Index;

        bool IsValid() { return m_Index != INVALID_EHANDLE_INDEX; }
        int  GetEntryIndex() { return IsValid() ? m_Index & ENT_ENTRY_MASK : ENT_ENTRY_MASK; }
        int  GetSerialNumber() { return m_Index >> NUM_SERIAL_NUM_SHIFT_BITS; }

        T *Get()
        {
            return static_cast<T *>(CS2::Offset::GetBaseEntity(*CS2::Offset::GameEntitySystem, GetEntryIndex()));
        }
    };

} // namespace CS2::Class
