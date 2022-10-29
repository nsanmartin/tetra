#include <iostream>
#include "util.h"
#include "Game.h"

namespace tetra {

using std::get;
using std::get_if;
using std::make_unique;

variant<Game,int> Game::withDimensions(int w, int h) {
    variant<SdlMedia,int> maybe = SdlMedia::withDimensions(w, h);

    // if(SdlMedia* pval = get_if<SdlMedia>(&maybe))
    //     return  variant<Game,int>(Game(*pval)); 
    // else 
    //     return variant<Game,int>(get<int>(maybe));

    return variant(visit(overloaded{
                [&w, &h](SdlMedia& media) { return variant<Game,int>(Game(media)); },
                [](int error) { return variant<Game,int>{error}; }, },
                maybe)
            );
}


static bool sdl_quit_event(const SDL_Event* e) {
    return e->type == SDL_QUIT || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_q);
}

void Game::changeState(Game::Behaviour* newstate) {
    behaviour = unique_ptr<Behaviour>(newstate);
}

void Game::readInput() {
    behaviour->readInput(*this);
}

void Game::Title::readInput(Game& g) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (sdl_quit_event(&e)) {
            std::cout << "state changed\n";
            g.changeState(new Quit{});
            //todo: use uniq ptr
            //game->keep_running = false;
            //game->state = GameStateEnded;
            //return set_game_state(game, GameStateEnded);
        }
    }
}


void Game::Title::render(Game& g) {
    SDL_Renderer* rend = g.media.getRenderer();
    //SDL_SetRenderDrawColor(rend, 0, 81, 177, 253 );
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0xff );
    SDL_RenderClear(rend);
    for (int x = 0; x < g.board.w; ++x) {
        for (int y = 0; y < g.board.h; ++y) {
            //todo: else case
            if (auto color = g.board.at(x, y)) {
                g.renderBlock(x, y, *color);
            }
        }
    }

    for (auto* it = g.board.mino->beg(); it < g.board.mino->end(); ++it) {
	    Point p = *it + g.board.mino->pos();
	    g.renderBlock(p.x, p.y, 0xffffffff);
    }
    SDL_RenderPresent(rend);
}

void Game::Title::update(Game& g) {
        g.board.mino->stepDown();
}

void Game::renderBlock(int x, int y, uint32_t color) {
    SDL_Renderer* rend = media.getRenderer();

    SDL_SetRenderDrawColor(
        rend,
        (color >> 24) & 0xff,
        (color >> 16) & 0xff,
        (color >> 8) & 0xff,
        color & 0xff
    );

    SDL_Rect rect = board.toSdlRect(x, y);
    SDL_RenderFillRect(rend, &rect );

}
} // namespace
