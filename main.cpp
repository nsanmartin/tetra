#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <expected>

#include <SdlMedia.h>
#include <Game.h>
#include "util.h"

using tetra::Game;
using tetra::get_time_millis;
using tetra::MS_PER_SECOND;
using tetra::NS_PER_MS;
using std::cout;
using std::cerr;
using std::vector;
using std::expected;

namespace tetra {
vector<long unsigned> get_minos_table();
}

constexpr int WINW = 480;
constexpr int WINH = 640;

void loop(Game& game) {
    long previous = get_time_millis();
    long lag = 0;
    int error = 0;

    while (!game.quit()) {
        long current = get_time_millis();
        lag += current - previous;
        previous = current;
        

        //todo: extract update from within readInput 
        game.readInput();
        for (;!game.quit() && lag >= game.slice; lag -= game.slice){
            //todo: this is tick 
            game.update();
        }

        error = game.render();
        if (error) {
            cerr << "An error ocurred rendering game. Exiting\n";
        }

        SDL_Delay(70);
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
    expected<Game,int> maybe_game = Game::withDimensions(WINW, WINH);

    if (maybe_game) {
        Game& game = *maybe_game;
        loop(game);
    } else {
         cerr << "An error ocurred :/: "<< maybe_game.error() <<"\n"; 
    }


    for (auto n:tetra::get_minos_table()) {
        cout << n << '\n';
    }

}
