#ifndef __H_UTIL_H_
#define __H_UTIL_H_

#include "time.h"

namespace tetra {


// https://en.cppreference.com/w/cpp/utility/variant/visit
// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

//constexpr long SLICE = 140;
constexpr long MS_PER_SECOND = 1000;
constexpr long NS_PER_MS = 1000000;

long get_time_millis();

}
#endif
