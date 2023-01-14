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

Tetramino* getNthTetra(auto n, Point pos) {
    switch (n) {
        case 0: return new Tetramino_I(pos);
        case 1: return new Tetramino_O(pos);
        case 2: return new Tetramino_T(pos);
        case 3: return new Tetramino_J(pos);
        case 4: return new Tetramino_L(pos);
        case 5: return new Tetramino_S(pos);
        case 6: return new Tetramino_Z(pos);
        default: return NULL;
    }
}


Tetramino* Tetramino::Rand(Point pos) {
    static int ix = 0;
    MinoSz  t = tetras[ix];
    ix = (ix + 1) % LEN(tetras);
    return new Tetramino{pos, t.ps, t.ps + t.sz};
    return getNthTetra(ix, pos);
}

Tetramino_I::Tetramino_I(Point pos) : Tetramino{ pos, tetras[0].ps, tetras[0].ps + tetras[0].sz } {}
Tetramino_O::Tetramino_O(Point pos) : Tetramino{ pos, tetras[1].ps, tetras[1].ps + tetras[1].sz } {}
Tetramino_T::Tetramino_T(Point pos) : Tetramino{ pos, tetras[2].ps, tetras[2].ps + tetras[2].sz } {}
Tetramino_J::Tetramino_J(Point pos) : Tetramino{ pos, tetras[3].ps, tetras[3].ps + tetras[3].sz } {}
Tetramino_L::Tetramino_L(Point pos) : Tetramino{ pos, tetras[4].ps, tetras[4].ps + tetras[4].sz } {}
Tetramino_S::Tetramino_S(Point pos) : Tetramino{ pos, tetras[5].ps, tetras[5].ps + tetras[5].sz } {}
Tetramino_Z::Tetramino_Z(Point pos) : Tetramino{ pos, tetras[6].ps, tetras[6].ps + tetras[6].sz } {}

} // namespace tetra
