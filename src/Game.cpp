#include "util.h"
#include "Game.h"

namespace tetra {

using std::get;
using std::get_if;

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

}
