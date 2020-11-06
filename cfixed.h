//
// Created by xinyang on 2020/6/20.
//

/*
 * 定点数计算。
 * 使用定点数类，需要开编译优化，否则函数中间变量会导致负优化。
 */

#ifndef _CFIXED_H_
#define _CFIXED_H_

#include <cstdint>
#include <type_traits>

/*
 * C风格宏定义方式的32位定点数计算。
 * 默认16位整数和16位小数
 */
#define cfixed32_from_floating(f)   ((int32_t)((f)*(1u<<16u)))
#define cfixed32_from_integral(i)   ((int32_t)((i)<<16u))
#define cfixed32_to_floating(t, c)  ((t)((c)/(1u<<16u)))
#define cfixed32_to_integral(t, c)  ((t)((c)>>16u))
#define cfixed32_mul(c1, c2)        ((int32_t)(((int64_t)(c1)*(int64_t)(c2))>>16u))
#define cfixed32_div(c1, c2)        ((int32_t)(((int64_t)(c1)<<16u)/(int64_t)(c2))
#define cfixed32_max_val            ((int32_t)0x7fffffff)
#define cfixed32_min_val            ((int32_t)0x80000000)
#define cfixed32_e_val              ((int32_t)1)

/*
 * 32位定点数类。
 * 可自定义精度。
 * 默认16位整数，16位小数。
 */
template<size_t P = 16u>
class cfixed32 {
    static_assert(0 <= P && P < 32, "precision of cfixed32 must be 0-31.");
private:
    int32_t v{0};
public:
    static constexpr size_t precision = P;

    inline cfixed32(int32_t _v = 0) : v(_v) {};

    // 最大值
    static inline constexpr cfixed32 max() { return {(int32_t) 0x7fffffff}; }

    // 最小值
    static inline constexpr cfixed32 min() { return {(int32_t) 0x80000000}; }

    // 最小表示精度
    static inline constexpr cfixed32 e() { return {1}; }

    // 从浮点数构造定点数
    template<class T>
    static inline constexpr std::enable_if_t<std::is_floating_point_v<T>, cfixed32> from(T f) {
        return {(int32_t) (f * (1u << P))};
    }

    // 从整数构造定点数
    template<class T>
    static inline constexpr std::enable_if_t<std::is_integral_v<T>, cfixed32> from(T i) {
        return {(int32_t) (i << P)};
    }

    // 定点数转浮点数
    template<class T>
    inline constexpr std::enable_if_t<std::is_floating_point_v<T>, T> to() const {
        return (T) v / (T) (1u << P);
    }

    // 定点数转整数
    template<class T>
    inline constexpr std::enable_if_t<std::is_integral_v<T>, T> to() const {
        return (T) (v >> P);
    }

    // 定点数加法
    constexpr cfixed32 operator+(const cfixed32 &c) const {
        return {v + c.v};
    }

    cfixed32 &operator+=(const cfixed32 &c) {
        v += c.v;
        return *this;
    }

    // 定点数减法
    constexpr cfixed32 operator-(const cfixed32 &c) const {
        return {v - c.v};
    }

    cfixed32 &operator-=(const cfixed32 &c) {
        v -= c.v;
        return *this;
    }

    // 定点数乘法
    constexpr cfixed32 operator*(const cfixed32 &c) const {
        return {(int32_t) (((int64_t) v * (int64_t) c.v) >> P)};
    }

    cfixed32 &operator*=(const cfixed32 &c) {
        v = (int32_t) (((int64_t) v * (int64_t) c.v) >> P);
        return *this;
    }

    // 定点数除法
    constexpr cfixed32 operator/(const cfixed32 &c) const {
        return {(int32_t) (((int64_t) v << P) / (int64_t) c.v)};
    }

    cfixed32 &operator/=(const cfixed32 &c) {
        v = (int32_t) (((int64_t) v << P) / (int64_t) c.v);
        return *this;
    }
};

#endif /* _CFIXED_H_ */
