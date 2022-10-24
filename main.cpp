#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <SdlMedia.h>
#include <Game.h>
#include "util.h"

using tetra::Game;
using tetra::get_time_millis;
using tetra::MS_PER_SECOND;
using tetra::NS_PER_MS;
using std::variant;


constexpr int WINW = 480;
constexpr int WINH = 640;
// constexpr int slice = 140;

void loop(Game& game) {
    long previous = get_time_millis();
    long lag = 0;

    while (game.keepRunning()) {
        long current = get_time_millis();
        lag += current - previous;
        previous = current;
        
        //game->process_input(game);

        //for (;!game->quit && lag >= slice; lag -= slice){
            //game->update(game);
        //}

        //game->render(game);
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
    variant<Game,int> maybe = Game::withDimensions(WINW, WINH);
}
