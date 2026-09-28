#pragma once 

namespace mgl {
    template <typename T = float>
    using angle = T;

    template <typename T = float>
    using radian = T;

    template <typename T = float>
    using degree = T;

    template <typename T = float>
    constexpr inline radian<T> radians(degree<T> deg) noexcept { return deg * (pi<T>() / static_cast<T>(180.0));}

    template <typename T = float>
    constexpr inline degree<T> degrees(radian<T> rad) noexcept {return rad * (static_cast<T>(180.0) / pi<T>());}
}