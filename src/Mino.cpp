#include "Mino.h"

namespace tetra {

Point tetramino_L[4] {
	{0, -1},
	{0, 0},
	{0, 1},
	{0, 2}
};

Point* TetraminoL::beg() {
	return &tetramino_L[0];
}

Point* TetraminoL::end() {
	return &tetramino_L[4];
}

// TetraminoL::TetraminoL() { }
} // namespace tetra
