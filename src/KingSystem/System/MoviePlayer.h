#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Name from the CSV (MoviePlayer::createInstance 0x71010b9934, init, __auto0 .. __auto2). A singleton (instance pointer
// at 0x710261f140). Only the members used so far are declared (layout incomplete; lane2 s47).
class MoviePlayer {
public:
    static MoviePlayer* instance() { return sInstance; }
    static MoviePlayer* sInstance;

    // 0x71010b9a08 (CSV name): empty; InitializeApp calls it with the createInstance heap.
    void init(sead::Heap* heap);

    // Native cleanup clears +0x31/+0x32; start sets +0x31 and StageMgrRun tests it.
    void sub_71010B9C04();
    // 0x71010b9c84 (declared only; placeholder name): forwards to the movie object's update when there is one
    // (false otherwise); EventFlowMovie::m14 returns it
    bool sub_71010B9C84();

    u8 _0[0x31];
    bool _31;
    u8 _32[0x3d8 - 0x32];
    /* 0x3d8 */ s32 mFrameCount;
    /* 0x3dc */ bool _3dc;  // set while a movie event is being played (S7Movie::x)
};

}  // namespace ksys
