
#include <expected>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <vector>
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

int main() {
    std::expected<Game,int> maybe_play = Game::withDimensions(WINW, WINH);
    if (!maybe_play.has_value()) {
         cerr << "An error ocurred :/: "<< maybe_play.error() <<"\n";
    } else {
        loop(*maybe_play);
    }

    for (auto n:tetra::get_minos_table()) {
        cout << n << '\n';
    }

}
