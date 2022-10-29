#include "Mino.h"

namespace tetra {

#define LEN(ARR) (sizeof(ARR)/sizeof(ARR[0]))
#define BEG(ARR) (&ARR[0])
#define END(ARR) (&ARR[LEN(ARR)])

Point tetramino_L[] { {0, -1}, {0, 0}, {0, 1}, {0, 2}};

Tetramino* Tetramino::L(Point pos) {
    return new Tetramino{pos, BEG(tetramino_L), END(tetramino_L)};
}

} // namespace tetra
