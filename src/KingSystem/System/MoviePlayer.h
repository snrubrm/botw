#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Name from the CSV (MoviePlayer::createInstance 0x71010b9934, init, __auto0 .. __auto2). A singleton (instance pointer
// at 0x710261f140). Only the members used so far are declared (layout incomplete; lane2 s47).
class MoviePlayer {
public:
    static MoviePlayer* instance() { return sInstance; }
    static MoviePlayer* sInstance;

    u8 _0[0x3dc];
    /* 0x3dc */ bool _3dc;  // set while a movie event is being played (S7Movie::x)
};

}  // namespace ksys
