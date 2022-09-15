module; 

#include <vector> 
#include <cstdint> 
#include <type_traits> 
#include <ostream> 
#include <variant>
#include <syncstream> 
#include <optional> 
#include <functional> 

export module graph; 

using namespace std; 

namespace game::graph {
    template <typename... Args> 
    using default_container = vector<Args...>; 
}

export namespace game::graph {

    using size_type = uint32_t; 

    template <typename I_, template <typename ...> typename C_ = default_container> 
    class Graph {
        public: 
            using value_type = I_; 
            using This = Graph; 
            template <typename... Args>
            using container_type = C_<Args...>; 
        private: 
            // The specific graph node info in the graph. 
            size_type width_, height_;  
            typename conditional< 
                same_as<value_type, void>, 
                monostate, 
                container_type<value_type>
            >::type nodes_; 
        public: 
            constexpr Graph() : width_(), height_(), nodes_() {} 
            // Draw a simple graph, with the specific size. 
            constexpr Graph(size_type w, size_type h, value_type v) requires (sizeof v <= 8) : 
                width_(w), height_(h), 
                nodes_(w * h, v) 
            {
                // simple test. 
                // static_assert (!is_same<value_type, int>); 
            }
            constexpr bool empty() const {
                return nodes_.empty(); 
            }
            void display(auto &output_stream) const {
                unsigned w = width_, h = height_; 
                char cache[60]; 
                snprintf(cache, size(cache), "Graph Info: width=%u,height=%u,container.size=%zu.\n",
                    w, h, size(nodes_)); 
                osyncstream(output_stream) << cache << flush; 
            } 

            constexpr Graph &operator = (Graph const &g) & = default; 
            constexpr Graph &operator = (Graph &&g) & = default; 

        private: 
            using size_type_interface_t = 
                typename conditional<(sizeof (size_type) > 8), size_type const &, size_type>::type; 
        public: 
        // actually, we shouldn't modify our map directly with the row, col interface. 
            constexpr size_type_interface_t row() const {
                return height_; 
            }
            constexpr size_type_interface_t col() const {
                return width_; 
            }
            [[gnu::always_inline]]
            constexpr value_type &operator [] (size_type r, size_type c) {
                auto && value = ((This const &)(*this))[r, c]; 
                return const_cast<value_type&>(value); 
            }
            constexpr value_type const &operator [] (size_type r, size_type c) const {
                return nodes_[r * width_ + c]; 
            }
            [[gnu::always_inline]]
            constexpr optional<reference_wrapper<value_type>> at(size_type r, size_type c) {
                decltype(auto) result = ((This const &)(*this)).at(r, c); 
                if (result)
                    return const_cast<value_type&>(result->get()); 
                else 
                    return nullopt; 
            }
            constexpr optional<reference_wrapper<value_type const >> at(size_type r, size_type c) const {
                if (r < 0 || r >= height_ || c < 0 || c > width_) {
                    return nullopt; 
                }
                return (*this)[r, c]; 
            }
    }; 

    template <typename V_, typename Size_> 
    Graph(Size_, Size_, V_) -> Graph<V_, default_container>;

    template class Graph<int>; 
}