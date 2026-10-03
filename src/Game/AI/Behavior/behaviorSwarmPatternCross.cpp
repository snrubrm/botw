#include "Game/AI/Behavior/behaviorSwarmPatternCross.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternCross::SwarmPatternCross(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternCross::~SwarmPatternCross() = default;

bool SwarmPatternCross::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternCross::m7() {
    SwarmPattern::m7();
}

// NON_MATCHING: only the register allocation of the x/y phi differs (w9/w10 swapped, 3 instructions).
void SwarmPatternCross::m8() {
    SwarmPattern::m8();
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm)
        return;

    const s32 count = swarm->_14c8.size();
    const s32 half = count / 2;
    const f32 width = *mWidth_s;
    const f32 step = width / half;
    const f32 half_width = width * 0.5f;
    for (s32 i = 0; i < count; ++i) {
        sead::Vector3f pos;
        if (i < half) {
            const f32 v = step * i - half_width;
            pos.set(v, v, sead::GlobalRandom::instance()->getF32() * 0.1f);
        } else {
            const f32 v = step * (i - half);
            pos.set(v - half_width, half_width - v, 0);
        }
        swarm->_14c8[i]->_60 = pos;
    }
}
void SwarmPatternCross::m9() {
    SwarmPattern::m9();
}

void SwarmPatternCross::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mWidth_s, "Width");
}

void SwarmPatternCross::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 5;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
