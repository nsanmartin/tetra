#include "Mino.h"

namespace tetra {

#define LEN(ARR) (sizeof(ARR)/sizeof(ARR[0]))
#define BEG(ARR) (&ARR[0])
#define END(ARR) (&ARR[LEN(ARR)])

Point tetramino_I[] { {0, -1}, {0, 0}, {0, 1}, {0, 2}};
//todo
Point tetramino_O[] { {0, 0}, {0, 1}, {1, 0}, {1, 1}};
Point tetramino_T[] { {-1, 0}, {0, 0}, {0, 1}, {1, 0}};
Point tetramino_L[] { {0, -2}, {0, -1}, {0, 0}, {1, 0}};
Point tetramino_J[] { {0, -2}, {0, -1}, {0, 0}, {-1, 0}};
Point tetramino_S[] { {0, -1}, {0, 0}, {1, 0}, {1, 1}};
Point tetramino_Z[] { {0, -1}, {0, 0}, {-1, 0}, {-1, 1}};

struct MinoSz {
    Point* ps;
    int sz;
};

struct MinoSz tetras[] {
    { tetramino_I, 4},
    { tetramino_O, 4},
    { tetramino_T, 4},
    { tetramino_J, 4},
    { tetramino_L, 4},
    { tetramino_S, 4},
    { tetramino_Z, 4}
};

Tetramino* Tetramino::Rand(Point pos) {
    static int ix = 0;
    MinoSz  t = tetras[ix];
    ix = (ix + 1) % LEN(tetras);
    return new Tetramino{pos, t.ps, t.ps + t.sz};
}

} // namespace tetra
