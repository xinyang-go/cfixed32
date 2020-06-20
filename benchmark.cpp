#include <iostream>
#include <chrono>
#include "cfixed.h"

#define P   (16)

int main() {
    float f1 = 1.001, f2 = -0.999;
    float f3 = 0;
//    std::cin >> f1 >> f2;
    auto c1 = cfixed32<P>::from(f1);
    auto c2 = cfixed32<P>::from(f2);
    auto c3 = cfixed32<P>::from(f3);

    // 范围输出
    printf("cfixed32<%d> max: %.8f\n", P, cfixed32<P>::max().to<float>());
    printf("cfixed32<%d> min: %.8f\n", P, cfixed32<P>::min().to<float>());
    printf("cfixed32<%d> e: %.8f\n", P, cfixed32<P>::e().to<float>());

    // 精度对比
    printf("[f1: %.8f], [c1: %.8f], [delta: %.8f]\n", f1, c1.to<float>(), std::abs(f1 - c1.to<float>()));
    printf("[f2: %.8f], [c2: %.8f], [delta: %.8f]\n", f2, c2.to<float>(), std::abs(f2 - c2.to<float>()));
    printf("+: [f: %.8f], [c: %.8f], [delta: %.8f]\n", f1 + f2, (c1 + c2).to<float>(),
           std::abs((f1 + f2) - (c1 + c2).to<float>()));
    printf("-: [f: %.8f], [c: %.8f], [delta: %.8f]\n", f1 - f2, (c1 - c2).to<float>(),
           std::abs((f1 - f2) - (c1 - c2).to<float>()));
    printf("*: [f: %.8f], [c: %.8f], [delta: %.8f]\n", f1 * f2, (c1 * c2).to<float>(),
           std::abs((f1 * f2) - (c1 * c2).to<float>()));
    printf("/: [f: %.8f], [c: %.8f], [delta: %.8f]\n", f1 / f2, (c1 / c2).to<float>(),
           std::abs((f1 / f2) - (c1 / c2).to<float>()));

    // 时间对比，累积误差对比
    {
        auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) {
            if (i % 2) f3 += f1 * f2;
            else f3 -= f1 / f2;
        }
        auto t1 = std::chrono::steady_clock::now();
        std::cout << "float: " << f3
                  << " cost: " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << "us"
                  << std::endl;
    }
    {
        auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) {
            if (i % 2) c3 += c1 * c2;
            else c3 -= c1 / c2;
        }
        auto t1 = std::chrono::steady_clock::now();
        std::cout << "cfixed: " << c3.to<float>()
                  << " cost: " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << "us"
                  << std::endl;
    }
    return 0;
}
