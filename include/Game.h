#ifndef __H_TETRA_GAME_H_
#define __H_TETRA_GAME_H_

#include "SdlMedia.h"

namespace tetra {

using std::move;

class Game {
    enum class State { Title, Menu, Play, Options, Ended, Quit };
    SdlMedia media;
    State state;

    Game(SdlMedia& media) : media{move(media)}, state{State::Title} {}
    Game(Game const&g) = delete;
    Game& operator=(const Game& o) = delete;
    Game& operator=(Game&& o) = delete;

    public:
    Game(Game&& g) noexcept :
        media{move(g.media)}, state{g.state} {}
    static variant<Game,int> withDimensions(int w, int h);

    bool keepRunning() const { return state == State::Quit; }
};


}
#endif

