#include "Game/gameStageStateMaybe.h"
#include "KingSystem/System/GameTool.h"

namespace uking {

StageStateMaybe* StageStateMaybe::sInstance;

bool StageStateMaybe::isActiveNaviMaybe(const Unk_71024f13f0* tool) {
    StageStateMaybe* state = sInstance;
    return state->_58[state->_38]->m24() == tool;
}

void StageStateMaybe::sub_710109CB20(agl::lyr::Layer* a, agl::lyr::Layer* b) {
    _28 = a;
    _30 = b;
    if (a && !a->getFlags().isOnBit(0))
        _a00 &= ~1u;
    else
        _a00 |= 1u;
    if (b && !b->getFlags().isOnBit(0))
        _a00 &= ~2u;
    else
        _a00 |= 2u;
    sub_710109CA1C();
}

}  // namespace uking
