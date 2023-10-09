#pragma once

namespace CS2::SDK
{
    template <class T>
    class CUtlVector
    {
    public:
        int m_Size;
        T  *m_Elements;

        T &operator[](int i) { return m_Elements[i]; }
    };

    // CUtlTSHash

} // namespace CS2::SDK
