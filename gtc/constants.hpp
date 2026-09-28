#pragma once

namespace mgl {

    template <typename T = float>
    constexpr inline T pi() noexcept {return static_cast<T>(3.14159265);}

    template <typename T = float>
    constexpr inline T two_pi() noexcept {return static_cast<T>(2) * pi<T>();}

    template <typename T = float>
    constexpr inline T half_pi() noexcept {return pi<T>() / static_cast<T>(2);}

    template <typename T = float>
    constexpr inline T quarter_pi() noexcept {return pi<T>() / static_cast<T>(4);}

    template <typename T = float>
    constexpr inline T tau() noexcept {return two_pi<T>();}

    template <typename T = float>
    constexpr inline T e() noexcept {return static_cast<T>(2.71828182);}

    template <typename T = float>
    constexpr inline T sqrt2() noexcept {return static_cast<T>(1.41421356);}

    template <typename T = float>
    constexpr inline T epsilon() noexcept {return static_cast<T>(1e-6);}
}
