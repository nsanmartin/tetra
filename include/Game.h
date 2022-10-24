#ifndef __H_TETRA_GAME_H_
#define __H_TETRA_GAME_H_

#include <cassert>
#include <vector>

#include "SdlMedia.h"
#include "util.h"

namespace tetra {

using std::move;
using std::same_as;
using std::vector;

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
        // virtual void update() = 0;
        // virtual void render() = 0;
    };

    SdlMedia media;
    State state;
    unique_ptr<Behaviour> behaviour;
    //Board* board;
    

    Game(SdlMedia& media) : media{move(media)}, state{State::Title}, behaviour{new Title{}} {}
    Game(Game const&g) = delete;
    Game& operator=(const Game& o) = delete;
    Game& operator=(Game&& o) = delete;

    public:
    Game(Game&& g) noexcept :
        media{move(g.media)}, state{g.state}, behaviour{move(g.behaviour)} {}
    static variant<Game,int> withDimensions(int w, int h);

    bool quit() const { return behaviour->quit(); }
    void readInput() ;


    private:
    friend class Behaviour;
    void changeState(Behaviour* newstate);

    class Title : public Behaviour {
        public:
        Title() {}
        bool quit() override { return false; }
        void readInput(Game& g) override; // {}
    };

    class Quit : public Behaviour {
        public:
        bool quit() override { return true; }
        void readInput(Game& g) override { g.ignoreInput(); }
    };


    void ignoreInput() const {};
};


}
#endif

