#pragma once

#define PI 3.141592653589793f

namespace CS2::SDK
{
    // CUtlVector
    template <class T>
    class CUtlVector
    {
    public:
        int m_Size;
        T  *m_Elements;

        T &operator[](int i) { return m_Elements[i]; }
    };

    // CUtlTSHash

    // Vector
    class Vector
    {
    public:
        float x, y, z;

        Vector operator+(const Vector &v) const
        {
            return Vector{x + v.x, y + v.y, z + v.z};
        }

        Vector operator-(const Vector &v) const
        {
            return Vector{x - v.x, y - v.y, z - v.z};
        }

        Vector operator*(const Vector &v) const
        {
            return Vector{x * v.x, y * v.y, z * v.z};
        }

        Vector operator/(const Vector &v) const
        {
            return Vector{x / v.x, y / v.y, z / v.z};
        }

        float Size()
        {
            return std::sqrt((x * x) + (y * y) + (z * z));
        }
    };

    SDK::Vector CalcAngle(SDK::Vector viewPos, SDK::Vector aimPos)
    {
        SDK::Vector angle = {0, 0, 0};

        SDK::Vector delta = aimPos - viewPos;

        angle.x = -asin(delta.z / delta.Size()) * (180.0f / PI); // pitch
        angle.y = atan2(delta.y, delta.x) * (180.0f / PI);       // yaw

        return angle;
    }

} // namespace CS2::SDK
