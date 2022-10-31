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
    variant<SdlMedia,int> maybe = SdlMedia::withDimensions(w, h);

    int cols = 10;
    int rows = 25;
    int block_width = min(w/cols, h/rows);

    Point orig = Point{0,0};
    Point end = Point{cols * block_width, rows * block_width};
    //
    // if(SdlMedia* pval = get_if<SdlMedia>(&maybe))
    //     return  variant<Game,int>(Game(*pval)); 
    // else 
    //     return variant<Game,int>(get<int>(maybe));

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

        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT: {
                        int& posx = g.board.mino.get()->getPos().x;
                        Point& leftist = g.board.mino->min([](auto&p,auto&q){return p.x<q.x;});
                        if (posx + leftist.x) {
                             g.board.mino->getPos().x -= 1;
                        }
                    }
                    break;
                case SDLK_RIGHT: {
                        int& posx = g.board.mino.get()->getPos().x;
                        Point& rightmost = g.board.mino->max([](auto&p,auto&q){return p.x<q.x;});
                        if (posx + rightmost.x < g.board.w) {
                             g.board.mino->getPos().x += 1;
                        }
                    }
                    break;

                case SDLK_SPACE: {
                    //auto f = [](Point& p) { return true;}

                        auto blocks_free = [&g](const Point& p) { 
                            Point r = rotate90deg(p) + g.board.mino->pos();
                            if(auto color = g.board.at(r.x, r.y)) { return color->get() == 0; }
                            printf("fue\n");
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


void Game::Title::render(Game& g) {
    SDL_Renderer* rend = g.media.getRenderer();
    //SDL_SetRenderDrawColor(rend, 0, 81, 177, 253 );
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0xff );
    SDL_RenderClear(rend);
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

    for (auto* it = g.board.mino->beg(); it < g.board.mino->end(); ++it) {
        Point p = *it + g.board.mino->pos();
        g.renderBlock(p.x, p.y, 0xffffffff);
    }
    SDL_RenderPresent(rend);
}

bool mino_can_fall(Board& b, Point p) {

    //if (p.y <= b.h) {
        if (auto color = b.at(p.x, p.y) ) {
            return color->get() == 0;
        }
    //}
    return false;
}

void Game::Title::update(Game& g) {
        auto lower = max_element(
                g.board.mino->beg(),
                g.board.mino->end(),
                [](const Point& p, const Point& q) { return p.y < q.y; }
        );

        if (mino_can_fall(g.board, *lower + g.board.mino->pos() + Point{0,1})) {
                g.board.mino->stepDown();
        } else {
            for (auto* it = g.board.mino->beg(); it < g.board.mino->end(); ++it) {
                    Point p = *it + g.board.mino->pos();
                    if (auto color = g.board.at(p.x, p.y)) {
                            color->get() = 0xffffffff;
                    }
                printf("__(%d, %d) ", p.x, p.y);
            }
        puts("");

                g.board.mino = unique_ptr<Tetramino>(Tetramino::L(Point{g.board.w/2,1}));
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
