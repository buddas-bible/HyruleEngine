#include <cmath>
#include <string>
#include<sstream>
#include "Vector2D.hh"

namespace Hyrule
{
	float Hyrule::Vector2D::Length() const noexcept
	{
		return std::powf((x * x) + (y * y), 0.5);
	}

	float Vector2D::LengthSquare() const noexcept
	{
		return (x * x) + (y * y);
	}

	float Vector2D::Cross(const Vector2D& _other) const noexcept
	{
		return x * _other.y - y * _other.x;
	}

	float Vector2D::Dot(const Vector2D& _other) const noexcept
	{
		return x * _other.x + y * _other.y;
	}

	float Vector2D::FastInvSqrt(float number) const noexcept
	{
		return 1 / this->Length();
	}

	Hyrule::Vector2D& Vector2D::Normalize() noexcept
	{
		auto temp = this->LengthSquare();

		if (temp == 0.f)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);
		this->x *= invSqrt;
		this->y *= invSqrt;

		return *this;
	}

	Hyrule::Vector2D Vector2D::Normalized() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return Vector2D(*this);
		}

		float invSqrt = FastInvSqrt(temp);

		return Vector2D(x * invSqrt, y * invSqrt);
	}

	Hyrule::Vector2D& Vector2D::operator+=(const Vector2D& _other) noexcept
	{
		this->x += _other.x;
		this->y += _other.y;

		return *this;
	}

	Hyrule::Vector2D& Vector2D::operator-=(const Vector2D& _other) noexcept
	{
		this->x -= _other.x;
		this->y -= _other.y;

		return *this;
	}

	Hyrule::Vector2D Vector2D::operator+(const Vector2D& _other) const noexcept
	{
		Vector2D temp(*this);
		return temp += _other;
	}

	Hyrule::Vector2D Vector2D::operator-(const Vector2D& _other) const noexcept
	{
		Vector2D temp(*this);
		return temp -= _other;
	}

	Hyrule::Vector2D Vector2D::operator-() const noexcept
	{
		Vector2D temp(*this);
		return temp *= -1;
	}

	Hyrule::Vector2D& Vector2D::operator*=(float n) noexcept
	{
		this->x *= n;
		this->y *= n;

		return *this;
	}

	Hyrule::Vector2D& Vector2D::operator/=(float n) noexcept
	{
		auto temp = 1 / n;
		this->x *= temp;
		this->y *= temp;

		return *this;
	}

	Hyrule::Vector2D Vector2D::operator*(float n) noexcept
	{
		Vector2D temp(*this);
		return temp *= n;
	}

	Hyrule::Vector2D Vector2D::operator/(float n) noexcept
	{
		Vector2D temp(*this);
		return temp /= n;
	}

	Vector2D operator*(float n, const Vector2D& vec) noexcept
	{
		return Vector2D(vec.x * n, vec.y * n);
	}

    std::ostream& operator<<(std::ostream& out, const Vector2D& point) noexcept
    {
        out << (abs(point.x) > 0.001 ? point.x : 0) << " ";
        out << (abs(point.y) > 0.001 ? point.y : 0);
        return out;
    }

    std::istream& operator>>(std::istream& in, Vector2D& point) noexcept
    {
        in >> point.x >> point.y;
        return in;
    }

    std::string Vector2D::ToString() noexcept
    {
        std::ostringstream out;
        out << (abs(x) > 0.001 ? x : 0) << " ";
        out << (abs(y) > 0.001 ? y : 0);
        return out.str();
    }

	bool Vector2D::operator==(const Vector2D& _other) const noexcept
	{
		return this->x == _other.x && this->y == _other.y;
	}
}
