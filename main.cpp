#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <iostream>

#include <SdlMedia.h>
#include <Game.h>
#include "util.h"

using tetra::Game;
using tetra::get_time_millis;
using tetra::MS_PER_SECOND;
using tetra::NS_PER_MS;
using std::variant;
using tetra::overloaded;
using std::cout;
using std::visit;


constexpr int WINW = 480;
constexpr int WINH = 640;
constexpr int slice = 140;

// constexpr int slice = 140;

void loop(Game& game) {
    cout << "loop\n";
    long previous = get_time_millis();
    long lag = 0;

    while (!game.quit()) {
        long current = get_time_millis();
        lag += current - previous;
        previous = current;
        
        game.readInput();

        //for (;!game.quit() && lag >= slice; lag -= slice){
        game.update();
        //}

        SDL_Delay(500);
        game.render();
    }
}

//void run_game (YrrGame* game) {
//    do {
//        loop(game);
//        yrrGamePrintResults(game);
//        if (game->state != YrrStateGameOver) { return; }
//        int error = yrrResetGame(game);
//        if (error) { return; }
//    } while (true);
//}

int main() {
    //variant<SdlMedia,int> maybe = SdlMedia::withDimensions(WINW, WINH);
    variant<Game,int> maybe_play = Game::withDimensions(WINW, WINH);
    visit(overloaded {
            [](Game& game) { loop(game); },
            [](int error) { cout << "An error ocurred :/: "<<error<<"\n"; }
        },
        maybe_play
    );
}
