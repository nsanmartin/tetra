#ifndef __H_UTIL_H_
#define __H_UTIL_H_

#include "time.h"

namespace tetra {


//constexpr long SLICE = 140;
constexpr long MS_PER_SECOND = 1000;
constexpr long NS_PER_MS = 1000000;

long get_time_millis();

}
#endif
