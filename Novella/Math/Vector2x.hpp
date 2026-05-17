#pragma once
#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <type_traits>

namespace Novella::Math{

    template <typename T>

    struct Vector2x{

        T x{};
        T y{};

        constexpr Vector2x() = default;

        constexpr Vector2x(T x, T y)
            :
            x(x),
            y(y)
            {}

        constexpr Vector2x(const ::Vector2& raylibVector)
            :
            x(static_cast<T>(raylibVector.x)),
            y(static_cast<T>(raylibVector.y))
            {}

        constexpr operator ::Vector2() const{

            return{

                static_cast<float>(x),
                static_cast<float>(y)
            };
        }     

        static_assert(std::is_arithmetic_v<T>, "Vector2i requires a numeric type");

        constexpr Vector2x operator+(const Vector2x& other) const{

            return {x + other.x, y + other.y};
        }

        constexpr Vector2x operator-(const Vector2x& other) const{

            return {x - other.x, y - other.y};
        }

        constexpr Vector2x operator*(T scalar) const{

            return {x * scalar, y * scalar};
        }

        constexpr Vector2x operator/(T scalar) const{
            
            return {x / scalar, y / scalar};
        }

        constexpr Vector2x& operator+=(const Vector2x& other){

            x += other.x;
            y += other.y;

            return *this;
        }

        constexpr Vector2x& operator-=(const Vector2x& other){

            x -= other.x;
            y -= other.y;

            return *this;
        }

        constexpr Vector2x& operator*=(T scalar){

            x *= scalar;
            y *= scalar;

            return *this;
        }

        auto length() const{

            return std::sqrt(static_cast<double>(x * x + y * y ));
        }

        constexpr T lengthSquared() const{

            return x * x + y * y;
        }

        Vector2x normalized() const{

            static_assert(std::is_floating_point_v<T>, "Normalized requires a floating point type");

            T len = length();

            if(len == T(0)) return {T(0), T(0)};

            return { x / len, y / len};
        };

        static auto distance(const Vector2x& a, const Vector2x& b){

            return (a - b).length();
        }

        constexpr T dot(const Vector2x& other) const{

            return x * other.x + y * other.y;
        }

        Vector2x clamped(T minX, T maxX, T minY, T maxY) const{

            return {std::clamp(x, minX, maxX), std::clamp(y, minY, maxY)};
        }

        static Vector2x lerp(const Vector2x& a, const Vector2x& b, T t){

            return a + (b - a) * t;
        }

        Vector2x mirror(bool flipX, bool flipY) const{

            return {flipX ? -x : x, flipY ? -y : y};
        };

    };

    using Vector2f = Vector2x<float>;
    using Vector2d = Vector2x<double>;
    using Vector2i = Vector2x<int>;
    using Vector2ui = Vector2x<unsigned int>;
}