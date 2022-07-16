#include <array> 
#include <cassert> 
#include <cstdint> 
#include <iostream> 
#include <memory> 
#include <random>
#include <sstream>
#include <tuple>  
#include <optional> 

using i32 = int32_t; 

class GameBoard {
    private: 
        using This = GameBoard; 
    public: 
        enum class State : unsigned char {
            None, Black, White,
        }; 
        inline static constexpr i32 GAME_BOARD_LENGTH {6}; 
    private: 
        std::array<State, 36> a; 

        struct Visitor {
            GameBoard const *p; 
            i32 v; 

            std::optional<State> operator [] (i32 i) const && {
                if (this->v < 0 || this->v >= GAME_BOARD_LENGTH) {
                    return {}; 
                }
                if (i < 0 || i >= GAME_BOARD_LENGTH) {
                    return {}; 
                }
                return p->a.at(this->v * GAME_BOARD_LENGTH + i); 
            }
        }; 

    public: 
        GameBoard() {
#           ifdef DEBUG
            for (auto &s: a) {
                assert (s == State::None); 
            }
#           endif
        }

        Visitor operator [] (i32 i) const {
            return {
                .p = this, 
                .v = i, 
            }; 
        }

        State get_player() const {
            bool exist_blank = false; 
            i32 cnt {}; 
            for (auto i: this->a) {
                if (i == State::Black) {
                    ++cnt; 
                } else if (i == State::White) {
                    --cnt; 
                } else if (i == State::None) {
                    exist_blank = true; 
                }
            }
#           ifdef DEBUG
            assert (cnt == 0 || cnt == 1); 
#           endif 

            return !exist_blank ? State::None : (!cnt ? State::Black : State::White); 
        }

        // op % 4 == 0, 1, 2, 3 means the board to choose
        // 0 1 
        // 2 3 
        // 
        // op / 4 == 0, 1 means the direction
        // 0: clockwise, 
        // 1: counterclockwise 
        void rotate(i32 op) {
#           ifdef DEBUG
            assert (op >= 0 && op < 8);
#           endif 
            bool counter = op / 4; 
            i32 position = op % 4; 
            i32 base_index; 
            switch (position) {
                case 0: 
                    base_index = 0; 
                    break; 
                case 1: 
                    base_index = 3; 
                    break; 
                case 2: 
                    base_index = 18; 
                    break; 
                case 3: 
                    base_index = 21; 
                    break; 
            }
            static i32 const diff[] {0, 1, 2, 8, 14, 13, 12, 6}; 
            constexpr i32 LENGTH = sizeof diff / sizeof(i32); 
            State movement[LENGTH]; 
            for (i32 i{}; i < LENGTH; ++i) {
                movement[i] = this->a.at(base_index + diff[i]); 
            }
            State move_to_next[LENGTH]; 
            for (i32 i{}; i < LENGTH; ++i) {
                move_to_next[i] = !counter ? movement[(i - 2 + LENGTH) % LENGTH] : movement[(i + 2) % LENGTH]; 
            }
            for (i32 i{}; i < LENGTH; ++i) {
                this->a.at(base_index + diff[i]) = move_to_next[i]; 
            }
        }

        void set_index(i32 index) {
#           ifdef DEBUG
            assert (index >= 0 && index < GAME_BOARD_LENGTH * GAME_BOARD_LENGTH); 
            assert (this->a.at(index) == State::None); 
#           endif             
            auto player = get_player(); 
#           ifdef DEBUG
            assert (player != State::None); 
#           endif 
            this->a.at(index) = player; 
        }

        // None: two winners, or two loser. 
        // nullopt: continue to play. 
        std::optional<State> check_winner() const {
            bool black = false, white = false; 
            // row check 
            for (i32 row = 0; row < GAME_BOARD_LENGTH; ++row) {
                i32 black_cnt {}, white_cnt {}; 
                for (i32 col = 0; col < GAME_BOARD_LENGTH; ++col) {
                    switch (this->a.at(row * GAME_BOARD_LENGTH + col)) {
                        case State::Black: 
                            ++black_cnt; 
                            white_cnt = 0; 
                            break; 
                        case State::White: 
                            ++white_cnt; 
                            black_cnt = 0; 
                            break; 
                        case State::None: 
                            white_cnt = black_cnt = 0; 
                            break; 
                    }
                    black = black || black_cnt >= 5; 
                    white = white || white_cnt >= 5; 
                }
            }
            // column check 
            for (i32 col = 0; col < GAME_BOARD_LENGTH; ++col) {
                i32 black_cnt {}, white_cnt {}; 
                for (i32 row = 0; row < GAME_BOARD_LENGTH; ++row) {
                    switch (this->a.at(row * GAME_BOARD_LENGTH + col)) {
                        case State::Black: 
                            ++black_cnt; 
                            white_cnt = 0; 
                            break; 
                        case State::White: 
                            ++white_cnt; 
                            black_cnt = 0; 
                            break; 
                        case State::None: 
                            white_cnt = black_cnt = 0; 
                            break; 
                    }
                    black = black || black_cnt >= 5; 
                    white = white || white_cnt >= 5; 
                }
            }
            // bias check 
            auto test_bias = [&black, &white]<i32 row_step, i32 col_step>(auto &a, auto start_row, auto start_col) {
                i32 black_cnt {}, white_cnt {}; 
                while (1) {
                    if (start_row < 0 || start_row >= GAME_BOARD_LENGTH) 
                        break; 
                    if (start_col < 0 || start_col >= GAME_BOARD_LENGTH) 
                        break; 
                    switch (a.at(start_row * GAME_BOARD_LENGTH + start_col)) {
                        case State::Black: 
                            ++black_cnt; 
                            white_cnt = 0; 
                            break; 
                        case State::White: 
                            ++white_cnt; 
                            black_cnt = 0; 
                            break; 
                        case State::None: 
                            white_cnt = black_cnt = 0; 
                            break; 
                    }
                    black = black || black_cnt >= 5; 
                    white = white || white_cnt >= 5; 
                    start_row += row_step; 
                    start_col += col_step; 
                }
            }; 

            test_bias.operator()<1, 1>(this->a, 0, 0); 
            test_bias.operator()<1, 1>(this->a, 0, 1); 
            test_bias.operator()<1, 1>(this->a, 1, 0); 

            test_bias.operator()<1, -1>(this->a, 0, 5); 
            test_bias.operator()<1, -1>(this->a, 0, 4); 
            test_bias.operator()<1, -1>(this->a, 1, 5); 

            // return black ? ( white ? State::None : State::Black ) : ( white ? State::White : std::nullopt ); 
            if (black) {
                if (white) {
                    return State::None; 
                } else {
                    return State::Black; 
                }
            } else {
                if (white) {
                    return State::White; 
                } else {
                    if (this->get_player() == State::None) 
                        return State::None; 
                    else 
                        return {}; 
                }
            }
        }
}; 

std::ostream & operator << (std::ostream &out, GameBoard const &game) {
    std::stringstream buffer; 
    for (i32 row = 0; row < GameBoard::GAME_BOARD_LENGTH; ++row) {
        for (i32 col = 0; col < GameBoard::GAME_BOARD_LENGTH; ++col) {
            switch (game[row][col].value()) {
                case GameBoard::State::None: 
                    buffer << "\u25cc"; 
                    break; 
                case GameBoard::State::Black: 
                    buffer << "\u24ff"; 
                    break; 
                case GameBoard::State::White: 
                    buffer << "\u24ea"; 
                    break; 
            }
            if (col + 1 == GameBoard::GAME_BOARD_LENGTH) 
                buffer << '\n'; 
            else 
                buffer << ' '; 
        }
    }
    return out << buffer.str(); 
}

class GameController {
    private: 
        using PositionIndex = i32; 
        using StageIndex = i32; 
    public: 
        using ArtificialFunctionType = std::pair<PositionIndex, StageIndex> (GameBoard const &); 
    private: 
        std::unique_ptr<GameBoard> game_board = std::make_unique<GameBoard>(); 
        std::function<ArtificialFunctionType> black {}, white {}; 
    
    public: 
        template <typename F>
        void set_black(F &&f) {
            black = std::forward<F>(f); 
        }

        template <typename F> 
        void set_white(F &&f) {
            white = std::forward<F>(f); 
        }

        void start() {
#           ifdef DEBUG
            assert (black && white); 
#           endif 
            while (1) {
                auto winner = game_board->check_winner(); 
                if (winner) 
                    break; 
                switch (game_board->get_player()) {
                    case GameBoard::State::Black: {
                        auto [pos, stage] = black(*game_board); 
                        game_board->set_index(pos); 
                        game_board->rotate(stage); 
                        break; 
                    }
                    case GameBoard::State::White: {
                        auto [pos, stage] = white(*game_board); 
                        game_board->set_index(pos); 
                        game_board->rotate(stage); 
                        break; 
                    }
                    default: 
                        throw std::runtime_error("无法下子异常"); 
                } 
#               ifdef DISPLAY_STEP
                std::cout << *game_board << "\n\n"; 
#               endif 
            }
        }
}; 

std::pair<i32, i32> random_select(GameBoard const &v) {
    static std::linear_congruential_engine random_machine = std::minstd_rand0(time(nullptr)); 

    auto float_random = [&]() -> float {
        return 2 * (double) random_machine() / std::numeric_limits<decltype(random_machine())>::max(); 
    }; 

    i32 cnt = 2; 
    std::optional<i32> select {}; 

    for (i32 r = 0; r < GameBoard::GAME_BOARD_LENGTH; ++r) {
        for (i32 c = 0; c < GameBoard::GAME_BOARD_LENGTH; ++c) {
            if (v[r][c].value() != GameBoard::State::None)
                continue; 
            if (!select) {
                select = r * GameBoard::GAME_BOARD_LENGTH + c; 
            } else {
                if (float_random() < 1. / cnt) {
                    select = r * GameBoard::GAME_BOARD_LENGTH + c; 
                } 
                ++cnt; 
            }
        }
    }

    return {select.value(), 
        random_machine() % 8 }; 
}

int main() {
    auto controller = GameController(); 
    controller.set_black(random_select); 
    controller.set_white(random_select); 
    controller.start(); 
}