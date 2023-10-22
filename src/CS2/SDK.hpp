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

    Vector NormalizeAngles(Vector angle)
    {
        while (angle.x > 89.0f)
            angle.x -= 180.f;

        while (angle.x < -89.0f)
            angle.x += 180.f;

        while (angle.y > 180.f)
            angle.y -= 360.f;

        while (angle.y < -180.f)
            angle.y += 360.f;

        return angle;
    }

    float GetFov(Vector viewAngle, Vector aimAngle)
    {
        Vector delta = aimAngle - viewAngle;
        delta        = NormalizeAngles(delta);
        return sqrt(pow(delta.x, 2.0f) + pow(delta.y, 2.0f));
    }

} // namespace CS2::SDK
