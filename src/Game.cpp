#include <iostream>

#include "util.h"
#include "Game.h"

namespace tetra {

using std::get;
using std::get_if;
using std::make_unique;
using std::max_element;
using std::min;


variant<Game,int> Game::withDimensions(int w, int h) {
    int cols = 10;
    int rows = 25;
    int block_width = min(w/cols, h/rows);

    Point orig = Point{block_width, 1};
    Point end = Point{cols * block_width, rows * block_width};

    variant<SdlMedia,int> maybe = SdlMedia::withDimensions(w, h);

    return variant(visit(overloaded{
                [&orig, &end, &cols, &rows](SdlMedia& media) {
                    return variant<Game,int>(Game(media, orig, end, cols, rows));
                },
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

void Game::Play::readInput(Game& g) {
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

        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT: {
                        auto blocks_free = [&g](const Point& p) { 
                            Point r = p + g.board.mino->pos();
                            if(auto color = g.board.at(r.x - 1, r.y)) { return color->get() == 0; }
                            return false;
                        };

                        if (g.board.mino->all(blocks_free)) {
                             g.board.mino->getPos().x -= 1;
                        }
                    }
                    break;
                case SDLK_RIGHT: {
                        auto blocks_free = [&g](const Point& p) { 
                            Point r = p + g.board.mino->pos();
                            if(auto color = g.board.at(r.x + 1, r.y)) { return color->get() == 0; }
                            return false;
                        };

                        if (g.board.mino->all(blocks_free)) {
                             g.board.mino->getPos().x += 1;
                        }
                    }
                    break;

                case SDLK_DOWN: {
                        auto blocks_free = [&g](const Point& p) { 
                            Point r = p + g.board.mino->pos();
                            if(auto color = g.board.at(r.x, r.y + 1)) { return color->get() == 0; }
                            return false;
                        };

                        if (g.board.mino->all(blocks_free)) {
                             g.board.mino->getPos().y += 1;
                        }
                    }
                    break;
                case SDLK_UP:
                case SDLK_SPACE: {
                        auto blocks_free = [&g](const Point& p) { 
                            Point r = rotate90deg(p) + g.board.mino->pos();
                            if(auto color = g.board.at(r.x, r.y)) { return color->get() == 0; }
                            return false;
                        };

                        if (g.board.mino->all(blocks_free)) {
                            g.board.mino->for_each_block( [](Point& p) { p.rotate90deg(); });

                        };
                    }
                    break;
            }
        }
    }
}

int Game::Play::renderFallingMino(Game& g) {
    for (auto* it = g.board.mino->beg(); it < g.board.mino->end(); ++it) {
        Point p = *it + g.board.mino->pos();
        g.renderBlock(p.x, p.y, 0xffffffff);
    }
    return 0;
}

int Game::Play::renderDroppedMinos(Game& g) {
    for (int x = 0; x < g.board.w; ++x) {
        for (int y = 0; y < g.board.h; ++y) {
            //todo: else case
            if (auto color = g.board.at(x, y)) {
                    if (color->get() != 0) {
                        g.renderBlock(x, y, *color);
                    }
            }
        }
    }
    return 0;
}

int Game::Play::renderBoardFrame(Game& g) {
    int y = 0;
    int x = g.board.w;
    //const int x = 0;
    //todo find better colors
    //const uint32_t color = 0xafbfccfd;
    const uint32_t color = 0xffffffff;
    constexpr uint32_t even = 0x7aa7a7aa;
    constexpr uint32_t odd = 0x67f29fde;

    for (y = 0; y < g.board.h; ++y) {
        g.renderBlock(g.board.w, y, color & ((y % 2 == 0) ? even : odd));
        g.renderBlock(-1, y, color & ((y % 2 == 0) ? odd : even));
    }

    y = g.board.h;
    for (x = 0; x <= g.board.w; ++x) {
        g.renderBlock(x, y, color & ((x % 2 == 1) ? even : odd));
    }
    g.renderBlock(-1, y, color & even);

    return 0;
}

int Game::Play::render(Game& g) {
    SDL_Renderer* rend = g.media.getRenderer();
    //SDL_SetRenderDrawColor(rend, 0, 81, 177, 253 );
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0xff );
    SDL_RenderClear(rend);

    int error = renderFallingMino(g);
    if (error) { return error; }
    error = renderDroppedMinos(g);
    if (error) { return error; }
    error = renderBoardFrame(g);
    if (error) { return error; }

    SDL_RenderPresent(rend);
    return 0;
}

bool mino_can_fall(Board& b, Point p) {

    //if (p.y <= b.h) {
        if (auto color = b.at(p.x, p.y) ) {
            return color->get() == 0;
        }
    //}
    return false;
}

void Game::Play::update(Game& g) {
        auto blocks_free = [&g](const Point& p) { 
            Point r = p + g.board.mino->pos();
            if(auto color = g.board.at(r.x, r.y + 1)) { return color->get() == 0; }
            return false;
        };

        if (g.board.mino->all(blocks_free)) {
            g.board.mino->stepDown();
        } else {
            for (auto* it = g.board.mino->beg(); it < g.board.mino->end(); ++it) {
                Point p = *it + g.board.mino->pos();
                if (auto color = g.board.at(p.x, p.y)) {
                    color->get() = 0xffffffff;
                }
            }

            g.board.mino = unique_ptr<Tetramino>(Tetramino::Rand(Point{g.board.w/2,1}));
            auto lines = g.board.getLines();
            if (lines.size()) {
                g.board.clearLines(lines);
                g.board.dropLines(lines.size(), lines.back());
            }

            if (!g.board.mino->all(blocks_free)) {
                //todo: transition to Ended state
                exit(0); // :)
            }
        }
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
