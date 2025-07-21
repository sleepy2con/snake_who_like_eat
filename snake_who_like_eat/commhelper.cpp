#include <random>   // 包含随机数引擎和分布
#include <chrono>   // 用于更好的种子
#include <iostream> // 用于示例输出
#include "commhelper.h"

/**
 * @brief 生成指定范围内（包含 min 和 max）的随机整数。
 * @author:gemini
 * @param min_val 随机数的最小值。
 * @param max_val 随机数的最大值。
 * @return 在 [min_val, max_val] 范围内的随机整数。
 */
int generateRandomInt(int min_val, int max_val) {
    // 1. 创建一个随机数引擎
    // std::random_device 用于获取一个非确定性（真）随机数作为种子，
    // 如果系统支持。
    // std::mt19937 是一个高质量的伪随机数生成器 (Mersenne Twister)，
    // 通常用于大多数应用。
    std::random_device rd;

    // 结合 random_device 和时间戳作为种子，以获得更好的随机性和每次运行的独特性。
    // 异或 (^) 运算可以混合两个种子的优点。
    std::mt19937 gen(rd() ^
        static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

    // 2. 创建一个均匀整数分布
    // std::uniform_int_distribution<> 会将引擎生成的原始随机数，
    // 映射到我们所需的 [min_val, max_val] 范围之内（包含 min_val 和 max_val）。
    std::uniform_int_distribution<> distrib(min_val, max_val);

    // 3. 生成并返回随机数
    // 调用分布对象的 operator()，传入随机数引擎，即可生成一个符合分布的随机数。
    return distrib(gen);
}
