#pragma once

namespace sead {
class Heap;
}

namespace ksys {
namespace act {
class PlayerLink;
}

struct InitParams {
    sead::Heap* king_sys_heap;
};

// 0x0000007100f3a4e4
bool isGameOver();
// 0x0000007100f3a4f0
void setIsGameOver(bool is_game_over);

void initBaseProcMgr(sead::Heap* heap);

// 0x0000007100f3a8d8
void preInitializeApp(const InitParams& params);

// 0x0000007100f40370
void setPlayerLink(act::PlayerLink* link);

// 0x0000007100f40428: stores `camera` (a Camera actor pointer or null) in the camera-using singletons.
void sub_7100F40428(void* camera);

}  // namespace ksys
