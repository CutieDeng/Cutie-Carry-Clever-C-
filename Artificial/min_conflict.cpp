#include <chrono> 
#include <cstdint> 
#include <cstring> 
#include <compare>
#include <ctime> 
#include <exception> 
#include <iostream> 
#include <optional> 
#include <random> 
#include <string>
#include <thread> 
#include <vector> 

// unistd 用于 UNIX 系统下的系统调用，调用 isatty 函数分析当前的程序是否被重定向。
#include <unistd.h> 
// extern int isatty(int ); 

// 关闭常规的 debug 输出
#define NDEBUG

// 输出随机选择皇后的过程
// #define DEBUG_RAND

// 输出调用 get_float 函数获得的随机数的值
// #define DEBUG_RAND_FLOAT

// 输出正在移动位置的皇后当前行的 cache 值
// #define DEBUG_CACHE_VALUE

// 输出当前轮次开始时的棋盘状态
// #define DEBUG_PEEK_STEP

// 缓存加速开关
#define OPTIMIZE_CACHE

// 断言定义
#include <cassert> 

// 定义常用的数值类型
using i32 = int32_t; 
using i64 = int64_t; 

// 全局变量 n, 用于存储 minimum-conflict 算法处理的 类八皇后问题 的皇后数，不应为负。
i32 n; 

// 标记当前的程序是否被重定向，以便调整输出控制符的使用与否。
bool is_redefine_cout; 

// 使用 arg1 字符串，设置当前程序的 皇后 数目。
void set_n(char const *arg1) {
    try {
        size_t l; 
        n = std::stoi(arg1, &l); 
        if (l != strlen(arg1)) {
            throw std::invalid_argument(""); 
        }
        goto check_negative; 
    } catch (std::invalid_argument &) {
        std::cerr << "\e[1;31m非法的输入参数：'" << arg1 << "'，请输入正确的正整数以描述问题。\e[0m"; 
    } catch (std::out_of_range &) {
        std::cerr << "\e[1;31m非法的输入参数，n 的数值过大。本程序无法解决过大的问题规模。\e[0m"; 
    }
    endl(std::cerr); 
    _Exit(1); 
    check_negative: 
    if (n <= 0) {
        std::cerr << "\e[1;31m非法的输入参数：n = " << n << ", [Invalid Bound is POSITIVE]. 请输入一个正整数来描述 n 皇后问题的规模范围。\e[0m"; 
        endl(std::cerr); 
//      程序传入参数错误时退出，其错误码为 1. 
        _Exit(1); 
    }
//  除此之处，n = 2 / 3 时程序无解
    if (n == 2 || n == 3) {
        std::cerr << "\e[1;31mn = " << n << " 时程序无解。\e[0m"; 
        endl(std::cerr); 
        _Exit(23); 
    }
}

// 变长数组
using std::vector; 

// 初始化函数
// 初始化其重定向标签
void init() {
    is_redefine_cout = (isatty(ftell(stdout))); 
}

// 缓存修改函数，用于调整策略变化时同步缓存的变化。
template <i32 movex, i32 movey, i32 value> 
void move(i32 x, i32 y, vector<i32> &cache) {
    if constexpr (!value) 
        return ; 
    while (1) {
        if constexpr (movex > 0) {
            if (x >= n) 
                return ; 
        } else if constexpr (movex < 0) {
            if (x < 0) 
                return ; 
        }
        if constexpr (movey > 0) {
            if (y >= n) 
                return ; 
        } else if constexpr (movey < 0) {
            if (y < 0) 
                return ; 
        }
        cache[x * n + y] += value; 
        x += movex; 
        y += movey; 
    }
}

// 缓存修改函数，用于调用下一级函数以修改缓存。
template <i32 value=1> 
void add_pos(i32 x, i32 y, vector<i32> &cache) {
    move<1, 1, value>(x, y, cache); 
    move<1, -1, value>(x, y, cache); 
    move<-1, 1, value>(x, y, cache); 
    move<-1, -1, value>(x, y, cache); 
    move<1, 0, value>(x, y, cache); 
    move<-1, 0, value>(x, y, cache); 
    move<0, 1, value>(x, y, cache); 
    move<0, -1, value>(x, y, cache); 
}

// 输出声明，用于输出棋盘的解
template <bool = true> void output(vector<i32> const &); 

// 标准的矛盾量计算函数
i32 get_conflict(vector<i32> const &solution, vector<i32> &cache) {
    assert (cache.size() == (size_t )n * n); 
    assert (solution.size() == n); 
    i32 result {}; 
//  在缓存优化开关打开的情形下，无需重置 cache 的任何信息。 
//  因为此时该函数只会被调用一次。
#   ifndef OPTIMIZE_CACHE
    for (auto &c: cache) c = 0; 
#   endif 
//  错误的函数实现，vector 没有 fill 函数用于快速填充值。
//  cache.fill(0); 
    for (i32 x = 0; x < n; ++x) {
        i32 y = solution.at(x); 
        add_pos(x, y, cache); 
    }
    for (i32 i = 0; i < n; ++i) {
        assert (cache.at(i * n + solution.at(i)) >= 8); 
        result += cache.at(i * n + solution.at(i)) - 8; 
    }
    assert (!(result & 1)); 
//  旧版的 conflict 值计算实现，由于在接下来的过程中无法快速求取 minimum conflict position 而被弃用。
    // for (size_t i = 1; i < n; ++i) {
    //     for (size_t j = 0; j < i; ++j) {
    //         i32 diff = solution.at(i) - solution.at(j); 
    //         if (diff < 0) 
    //             diff = - diff; 
    //         if ((!diff) || (diff == i - j)) {
    //             cache.at(i) += 1; 
    //             cache.at(j) += 1; 
    //             result += 1; 
    //         }
    //     }
    // }
//  返回 result 的一半表示矛盾的皇后对数。
    return result >> 1; 
}

// 快速求取 conflict 皇后对总数。
i32 get_conflict_fast(vector<i32> const &solution, vector<i32> &cache) {
    assert (cache.size() == (size_t )n * n); 
    assert (solution.size() == n); 
    i32 result {}; 
    for (i32 x = 0; x < n; ++x) {
        assert (cache.at(x * n + solution.at(x)) >= 8); 
        result += cache.at(x * n + solution.at(x)) - 8; 
    }
    assert (!(result & 1)); 
    return result >> 1; 
}

// 尝试得到该问题的解
// 解以每行第几列的元素放置皇后的方式进行编码。
auto find_result() -> vector<i32> {
    vector<i32> solution (n);
//  构建简单的线性同余随机数生成器引擎。
    std::linear_congruential_engine random = std::minstd_rand0(time(nullptr)); 
//  初始化一个简单的升充数组。
    for (i32 i = 0; i < n; ++i) 
        solution.at(i) = i; 
//  shuffle 该数组以得到一个解。
    for (i32 i = 0; i < n; ++i) {
        std::swap(solution.at(i), solution.at((random() % (n-i)) + i)); 
    }
//  Deprecated codes: 停止一段时间，以便于 debug 时观察程序运行过程。
    // using namespace std::literals::chrono_literals; 
    // std::this_thread::sleep_for(1s); 
//  程序的 n 值过多，n^2 的数组元素个数大于 i32 所能表示的范围，部分取索引的操作将会有安全隐患。
//  直接退出程序，退出码为 84
    if ((i64)n * n >= std::numeric_limits<i32>::max()) {
        std::cerr << "\e[1;33m程序退出，退出原因：过大的棋盘 n = " << n << ". " << "\e[0m"; 
        endl(std::cerr); 
        _Exit(84); 
    }
//  构建缓存数组
    vector<i32> cache(n * n); 
// 程序优化开关开启时，cache 会在初始时被初始化，且之后不再被做初始化
#   ifdef OPTIMIZE_CACHE
    get_conflict(solution, cache); 
#   endif 
//  程序基本 debug 信息存储，round_cnt 用于记录当前的运行程序的爬山次数。
#   ifndef NDEBUG
    size_t round_cnt {}; 
#   endif 
    while (1) {
//      conflict-total 变量用于计算当前的 solution 的矛盾数目
//      优化开关开启时，其相关缓存不再会被重置
        i32 conflict_total = 
#           ifdef OPTIMIZE_CACHE
            get_conflict_fast(solution, cache); 
#           else 
            get_conflict(solution, cache); 
#           endif 
        using std::optional; 
//      当该解不造成任何矛盾时，则退出循环
        if (!conflict_total) 
            break; 
//      初始化为空的 select-line-id 变量，用于表示本轮游戏中我们选择【即修改皇后位置】的行号
        optional<i32> select_line_id {}; 
        i32 cnt; 
//      获取指定 solution 索引下其对应的元素的冲突值（即 cache 值）
        auto fetch_cache = [&](auto line_id) -> decltype(auto) {
            return cache.at(line_id * n + solution.at(line_id)); 
        }; 
//      随机地获取 0-1 之间的浮点数
        constexpr auto get_float= [](auto &rand) constexpr -> double {
            double result = (double )rand() / std::numeric_limits<decltype(rand())>::max() * 2; 
#           ifdef DEBUG_RAND_FLOAT
            std::cout << "[Rand float: " << result << "]. \n"; 
#           endif 
            return result; 
        }; 
//      错误方法示例
//      选择矛盾最大的皇后进行移动
#       if 0
        for (i32 i = 0; i < n; ++i) {
            if (auto cmp_result = !select_line_id ? std::strong_ordering::less : 
                fetch_cache(*select_line_id) <=> fetch_cache(i); cmp_result == std::strong_ordering::less) {
                select_line_id = i; 
                cnt = 2; 
            } else if (cmp_result == std::strong_ordering::equal) {
                double k = get_float(random); 
                if (k < 1. / cnt) {
                    select_line_id = i; 
                }
                ++cnt; 
            }
        } 
//      正确方法示例
//      以矛盾值为权重进行随机选择
#       else 
        {
            cnt = 0; 
            i32 ground[n]; 
            for (i32 i = 0; i < n; ++i) {
                ground[i] = fetch_cache(i) - 8; 
                cnt += ground[i]; 
            }
            i32 ran_val = random() % cnt; 
#           ifdef DEBUG_RAND
            i32 ran_val_backup = ran_val; 
#           endif 
            i32 select = 0; 
            for (; select < n && ran_val >= ground[select]; ++select) {
                ran_val -= ground[select];  
            }
#           ifdef DEBUG_RAND
            if (select >= n) {
                std::cout << "Ground: ["; 
                for (auto i: ground) {
                    std::cout << i << " "; 
                }
                std::cout << "]. \n"; 
                std::cout << "The rand value is " << ran_val_backup << "\n"; 
//              随机选择失败，发生了不明错误
                _Exit(2); 
            } 
#           endif
            select_line_id = select; 
        }
#       endif 
//      假设成功地选择了某一个皇后
        assert (select_line_id); 
//      选择当前行冲突值最小的位置，以便将皇后移过去
//      如有多个相同权值的位置，则随机选择一个进行移动
        optional<i32> change_to {}; 
        for (i32 i = 0; i < n; ++i) {
            if (auto cmp_result = !change_to ? std::strong_ordering::less : 
                cache.at(*select_line_id * n + i) <=> cache.at(*select_line_id * n + *change_to); cmp_result == std::strong_ordering::less) {
#               ifdef DEBUG_CACHE_VALUE
                std::cout << "Change change-to value from "; 
                if (change_to) 
                    std::cout << *change_to; 
                else 
                    std::cout << "null"; 
                std::cout << " to " << i << ". \n"; 
#               endif 
                change_to = i; 
                cnt = 2; 
            } else if (cmp_result == std::strong_ordering::equal) {
                double k = get_float(random);
                if (k < 1. / cnt) {
                    change_to = i; 
                }
                ++cnt; 
            }
        }
//      每轮的简要 debug 信息，包括各轮的解的情形
#       ifndef NDEBUG
        std::cout << "第 " << round_cnt << " 轮，当前解的矛盾值为：" << conflict_total << "\n"; 
        ++round_cnt; 
        std::cout << "\t将 " << *select_line_id << " 行的皇后移至 " << *change_to << " 位置上。\n"; 
#       endif 
#       ifdef DEBUG_CACHE_VALUE
        std::cout << "Line ID: " << *select_line_id << ", the cache list: \n"; 
        for (i32 i = 0; i < n; ++i) {
            std::cout << cache.at(*select_line_id * n + i) << ' '; 
        }
        endl(std::cout); 
#       endif 
#       ifdef DEBUG_PEEK_STEP
        output<false>(solution); 
#       endif 
#       ifdef OPTIMIZE_CACHE
        add_pos<-1>(*select_line_id, solution.at(*select_line_id), cache); 
        add_pos<1>(*select_line_id, *change_to, cache); 
#       endif 
        solution.at(*select_line_id) = *change_to; 
    }
    return solution; 
}

template <bool colored>
void output(vector<i32> const &solution) {
    assert (solution.size() == n); 
    for (size_t line = 0; line < n; ++line) {
        i32 i = solution.at(line); 
        constexpr char const *SQUARE = "\u25ef "; 
        for (i32 j = 0; j < i; ++j) {
            std::cout << SQUARE; 
        }
        if constexpr (colored) {
            if (!is_redefine_cout)
                std::cout << "\e[1;31m"; 
        }
        std::cout << "\u2776 "; 
        if constexpr (colored) {
            if (!is_redefine_cout)
                std::cout << "\e[0m"; 
        }
        for (; i + 1< n; ++i) {
            std::cout << SQUARE; 
        }
        endl(std::cout); 
    }
}

int main(int argc, char const * const argv[]) {
    init(); 
//  测试 debug 环境，输出程序运行时的参数数目
#   ifndef NDEBUG
    std::cout << "程序输入参数个数：" << argc << '\n'; 
#   endif 
    if (argc != 2) {
        std::cerr << "\e[1;31m错误的程序运行格式，请输入 ‘" << argv[0] << " [integer]' 以便求取其相关的 n 皇后问题解，例 '"
            << argv[0] << " 8' 以得到八皇后问题的解。\e[0m"; 
        endl(std::cerr); 
        return 1; 
    }
    set_n(argv[1]); 
    auto start_idx = std::chrono::system_clock::now(); 
    auto result = find_result(); 
    auto cost_time = std::chrono::system_clock::now() - start_idx; 
    std::cout << "计算出结果，共耗时 " << (double)std::chrono::duration_cast<std::chrono::microseconds>(cost_time).count() / 1000 << " 毫秒。"; 
    endl(std::cout); 
    output(result); 
}