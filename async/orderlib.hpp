typedef std::uint32_t u32; 

#include <thread>
#include <chrono>
#include <vector>
#include <array>
#include <cstdlib>

namespace StoneSpace {

    class IllegalGameException: std::runtime_error {
        using std::runtime_error::runtime_error;
    }; 

    struct Stone {
        private: 
        u32 prior; 
        std::string name;
        std::mutex mutex; 

        private: 
        Stone(u32 val = 0, std::string name = ""): prior(val), name(std::move(name)) {} 

        friend bool swap(Stone&, Stone&); 

        public: 
        Stone &operator=(Stone const&) = delete; 
        Stone(Stone const& ) = delete; 

        template <u32 size> 
        static std::array<Stone, size> randomly_construct();

        u32 get_prior() {return prior; }
        std::string_view get_name() {return name; }
    }; 

    namespace TimeCnt {
        std::chrono::nanoseconds total_time_counts; 
        std::mutex clock_lock; 
        decltype(std::chrono::steady_clock::now()) clock; 
        bool record_timeing; 
    }

    bool swap(Stone &a, Stone &b) {
        using namespace std::literals::chrono_literals; 

        if (&a == &b) 
            return false; 
        std::lock(a.mutex, b.mutex); 
        std::this_thread::sleep_for(100ms); 
        std::lock_guard a_ (a.mutex, std::adopt_lock); 
        std::lock_guard b_ (b.mutex, std::adopt_lock); 
        using std::swap; 
        swap(a.prior, b.prior); 
        swap(a.name, b.name); 
        return true; 
    }

    template <u32 size> 
    std::array<Stone, size> Stone::randomly_construct() {
        constexpr u32 MOD = 65535; 
        std::array<Stone, size> result; 
        for (auto &s: result) {
            s.prior = rand() % MOD; 
        }
        return result; 
    }

    template <typename T> 
    bool test (T &array) {

        u32 tmp = 0; 
        for (auto &p: array) {
            if (p.get_prior() < tmp) 
                return false; 
            tmp = p.get_prior(); 
        }

        {
            using namespace TimeCnt; 
            std::lock_guard c_(clock_lock);
            if (record_timeing) {
                total_time_counts += std::chrono::steady_clock::now() - clock; 
                record_timeing = false; 
            } 
            std::cout << "["; 
            for (int i = 0; i < 50; ++i) {
                using namespace std::literals::chrono_literals;
                std::cout << "="; 
                std::cout.flush();
                std::this_thread::sleep_for(60ms); 
            }
            std::cout << "]\n"; 
            std::cout << "You pays " << total_time_counts.count() / 1e6L << " ms for this task! " << std::endl;  
        }
        return true; 
    }

    void start() {
        using namespace TimeCnt;
        std::lock_guard c_(clock_lock); 
        if (!record_timeing) {
            record_timeing = true; 
            clock = std::chrono::steady_clock::now(); 
        }
    }
}

using StoneSpace::Stone;
using StoneSpace::start;  