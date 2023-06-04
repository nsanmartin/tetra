#ifndef __H_TETRA_GAME_H_
#define __H_TETRA_GAME_H_

#include <cassert>
#include <expected>
#include <tuple>
#include <vector>

#include "SdlMedia.h"
#include "util.h"
#include "Board.h"

namespace tetra {

using std::same_as;
using std::vector;
using std::ignore;

// template <typename T>
// concept GameBehaviour = requires (T v) {
//     {v.keepRunning()} -> same_as<bool>;
//     //{v.processInput()} -> same_as<void>;
//     //{v.update()()} -> same_as<void>;
//     //{v.render()} -> same_as<void>;
// };
// 
// auto keep_running(GameBehaviour auto gb) {
//     return gb.keepRunning();
// }

class Game {
    enum class State { Title, Menu, Play, Options, Ended, Quit, StateCount };
    class Behaviour {
        public:
        virtual bool quit() = 0;
        virtual void readInput(Game& g) = 0;
        virtual void update(Game& g) = 0;
        virtual int render(Game& g) = 0;
        virtual ~Behaviour() = default;
    };

    SdlMedia media;
    State state;
    unique_ptr<Behaviour> behaviour;
    Board board;

    public:
    int slice;

    private:
    

    Game(
        SdlMedia&& media,
        Point board_origin,
        Point board_end,
        int cols,
        int rows,
        int slice,
        unique_ptr<Behaviour>& behaviour
    ) : media{std::move(media)}
      , state{State::Play}
      , behaviour{std::move(behaviour)}
      , board{board_origin, board_end, cols, rows, 0}
      , slice{slice}
    {}

    Game(Game const&g) = delete;
    
    Game& operator=(const Game& o) = delete;
    Game& operator=(Game&& o) = delete;

    public:
    Game(Game&& g) noexcept
        : media{std::move(g.media)}
        , state{g.state}
        , behaviour{std::move(g.behaviour)}
        , board{std::move(g.board)}
        , slice{g.slice}
        {}

    static std::expected<Game,int> withDimensions(int w, int h);

    bool quit() const { return behaviour->quit(); }
    int render() { return behaviour->render(*this); }
    void update() { behaviour->update(*this); }
    void readInput() ;

    void renderBlock(int x, int y, uint32_t color);

    private:
    friend class Behaviour;
    void changeState(Behaviour* newstate);

    class Play : public Behaviour {
        int renderFallingMino(Game& g) ;
        int renderDroppedMinos(Game& g) ;
        int renderBoardFrame(Game& g);
        public:
        Play() {}
        bool quit() override { return false; }
        void readInput(Game& g) override; // {}
        int render(Game& g) override ;
        void update(Game& g) override;

    };

    class Pause : public Play {
        public:
        void readInput(Game& g) override; // {}
        void update(Game& g) override { ignore = g; }
    };

    class Quit : public Behaviour {
        public:
        bool quit() override { return true; }
        void readInput(Game& g) override { ignore = g; }
        int render(Game& g) override { ignore = g; return 0; } //Todo render something
	void update(Game& g) override { ignore = g; }
    };

};


}
#endif

