#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"

// The forwarding wrappers are kept apart from the functions they call (in aiUnk_710073fa94.cpp), as in the
// original, where they are not inlined.

void sub_710073FA90(sead::Matrix33f* mtx, ksys::act::Actor* actor) {
    sub_710073FA94(mtx, actor);
}

void sub_7100741034(sead::Matrix33f* mtx, ksys::act::Actor* actor) {
    sub_7100741038(mtx, actor);
}

void sub_71007419B4(sead::Matrix33f* mtx, const sead::Vector3f& up) {
    const sead::Vector3f z{mtx->m[0][2], mtx->m[1][2], mtx->m[2][2]};
    ksys::util::sub_71011EFE58(mtx, z, up, true);
}
