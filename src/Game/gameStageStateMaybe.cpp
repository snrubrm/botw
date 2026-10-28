#include "Game/gameStageStateMaybe.h"
#include "Game/gameGraphics.h"
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
    updateGraphicsLayers();
}

// NON_MATCHING: the original computes the mask select before the _28 branch (ours sinks it into the
// branch and uses tst for the first test) and restores the frame one instruction earlier in the tail.
void StageStateMaybe::updateGraphicsLayers() {
    StageStateMaybeObject* object = _58[_38];

    auto* holder = object->_440;
    const u32* flags = holder ? &holder->mFlags : &object->_660;
    const u32 mask0 = holder ? 4 : 0x10000;
    const u32 mask1 = holder ? 8 : 0x20000;
    const u32 value = *flags;

    if (_28) {
        const u32 masked = value & mask0;
        const bool on = masked != 0;
        if (on != (_a00 & 1)) {
            _a00 = masked ? _a00 | 1u : _a00 & ~1u;
            Graphics::instance()->sub_7100F35F50(_28, _a00 & 1);
        }
    }

    if (_30) {
        const u32 masked = value & mask1;
        const bool on = masked != 0;
        if (on != ((_a00 >> 1) & 1)) {
            _a00 = masked ? _a00 | 2u : _a00 & ~2u;
            Graphics::instance()->sub_7100F35F50(_30, (_a00 >> 1) & 1);
        }
    }
}

}  // namespace uking
