#include <cmath>
#include <utility>

#include "Matrix1x3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.hh"
#include "Vector4D.hh"

#include "Vector3D.hh"

#include <sstream>

namespace Hyrule
{
    Vector3D::operator Matrix1x3() noexcept
    {
        return Matrix1x3{ x, y, z };
    }

    float Vector3D::Length() const noexcept
    {
        return powf((x * x) + (y * y) + (z * z), 0.5);
    }

    float Vector3D::LengthSquare() const noexcept
    {
        return (x * x) + (y * y) + (z * z);
    }

    Vector3D Vector3D::Cross(const Vector3D& other) const noexcept
    {
        return Vector3D(
            (this->y * other.z - this->z * other.y),
            (this->z * other.x - this->x * other.z),
            (this->x * other.y - this->y * other.x));
    }

    float Vector3D::Dot(const Vector3D& other) const noexcept
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }


    float Vector3D::ScalarTriple(const Vector3D& v1, const Vector3D& v2) const noexcept
    {
        return this->Dot(v1.Cross(v2));
    }


    Vector3D Vector3D::VectorTriple(const Vector3D& v1, const Vector3D& v2) const noexcept
    {
        return this->Cross(v1.Cross(v2));
    }

    float Vector3D::FastInvSqrt(float number) const noexcept
    {
        long i;
        float x2, y;
        const float threehalfs = 1.5f;

        x2 = number * 0.5f;
        y = number;
        i = *(long*)&y;
        //	i = 0x5f3759df - (i >> 1);
        i = 0x5f375a86 - (i >> 1);
        y = *(float*)&i;
        y = y * (threehalfs - (x2 * y * y));
        //	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

        return y;
    }

    Vector3D& Vector3D::Normalize() noexcept
    {
        float temp = LengthSquare();

        if (temp == 0)
        {
            return *this;
        }

        float invSqrt = FastInvSqrt(temp);
        x *= invSqrt;
        y *= invSqrt;
        z *= invSqrt;

        return *this;
    }

    Vector3D Vector3D::Normalized() const noexcept
    {
        float temp = LengthSquare();

        if (temp == 0)
        {
            return Vector3D(*this);
            // return Vector3D(0.f, 0.f, 0.f);
        }

        float invSqrt = FastInvSqrt(temp);

        return Vector3D(x * invSqrt, y * invSqrt, z * invSqrt);
    }


    Vector3D Vector3D::Forward()
    {
        return Vector3D{ 0.f, 0.f, 1.f };
    }


    Vector3D Vector3D::Up()
    {
        return Vector3D{ 0.f, 1.f, 0.f };
    }


    Vector3D Vector3D::Right()
    {
        return Vector3D{ 1.f, 0.f, 0.f };
    }

    Vector3D& Vector3D::operator+=(const Vector3D& other) noexcept
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other) noexcept
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

        return *this;
    }

    Vector3D Vector3D::operator+(const Vector3D& other) const noexcept
    {
        return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vector3D Vector3D::operator-(const Vector3D& other) const noexcept
    {
        return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    Vector3D Vector3D::operator-() const noexcept
    {
        return Vector3D(-x, -y, -z);
    }

    Vector3D& Vector3D::operator*=(const float n) noexcept
    {
        this->x *= n;
        this->y *= n;
        this->z *= n;

        return *this;
    }

    Vector3D& Vector3D::operator*=(const Matrix4x4& _mat) noexcept
    {
        Vector4D temp(*this, 1.f);
        temp *= _mat;

        this->x = temp.x;
        this->y = temp.y;
        this->z = temp.z;

        return *this;
    }

    Vector3D Vector3D::operator*(const Matrix4x4& _mat) const noexcept
    {
        Vector4D temp(*this, 1.f);
        temp *= _mat;

        return Vector3D(temp.x, temp.y, temp.z);
    }

    Vector3D& Vector3D::operator/=(const float n) noexcept
    {
        this->x /= n;
        this->y /= n;
        this->z /= n;

        return *this;
    }

    Vector3D Vector3D::operator*(const float n) const noexcept
    {
        Vector3D temp(*this);

        return temp *= n;
    }

    Vector3D Vector3D::operator/(const float n) const noexcept
    {
        Vector3D temp(*this);

        return temp /= n;
    }

    Vector3D& Vector3D::operator*=(const Matrix3x3& other) noexcept
    {
        Vector3D temp(*this);

        this->x = temp.x * other.e00 + temp.y * other.e10 + temp.z * other.e20;
        this->y = temp.x * other.e01 + temp.y * other.e11 + temp.z * other.e21;
        this->z = temp.x * other.e02 + temp.y * other.e12 + temp.z * other.e22;

        return *this;
    }

    Vector3D Vector3D::operator*(const Matrix3x3& other) const noexcept
    {
        Vector3D temp(*this);

        return temp *= other;
    }

    bool Vector3D::operator==(const Vector3D& other) const noexcept
    {
        return (this->x == other.x && this->y == other.y && this->z == other.z);
    }

    std::ostream& operator<<(std::ostream& out, const Vector3D& point) noexcept
    {
        out << (abs(point.x) > 0.001 ? point.x : 0) << " ";
        out << (abs(point.y) > 0.001 ? point.y : 0) << " ";
        out << (abs(point.z) > 0.001 ? point.z : 0);
        return out;
    }

    std::istream& operator>>(std::istream& in, Vector3D& point) noexcept
    {
        in >> point.x >> point.y >> point.z;
        return in;
    }

    std::string Vector3D::ToString() noexcept
    {
        std::ostringstream out;
        out << (abs(x) > 0.001 ? x : 0) << " ";
        out << (abs(y) > 0.001 ? y : 0) << " ";
        out << (abs(z) > 0.001 ? z : 0);
        return out.str();
    }


    Vector3D operator*(const Quaternion& q, const Vector3D& v) noexcept
    {
        Quaternion conjugate = q.Conjugate();
        Quaternion result = q * Quaternion(0.f, v.x, v.y, v.z) * conjugate;
        return Vector3D(result.x, result.y, result.z);
    }
}
