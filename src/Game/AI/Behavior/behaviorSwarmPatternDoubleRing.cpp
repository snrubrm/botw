#include "Game/AI/Behavior/behaviorSwarmPatternDoubleRing.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSwarm.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::behavior {

SwarmPatternDoubleRing::SwarmPatternDoubleRing(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternDoubleRing::~SwarmPatternDoubleRing() = default;

bool SwarmPatternDoubleRing::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternDoubleRing::m7() {
    SwarmPattern::m7();
}

void SwarmPatternDoubleRing::m8() {
    SwarmPattern::m8();
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm)
        return;

    const s32 count = swarm->_14c8.size();
    const s32 half = count / 2;
    const f32 radius = *mRadius_s;
    const f32 center_offset = *mCenterOffsetHalf_s;
    const f32 step = sead::Mathf::pi2() / half;
    for (s32 i = 0; i < count; ++i) {
        const s32 row = i / half;
        const s32 col = i % half;
        sead::Vector3f pos{0, radius, 0};
        ksys::util::sub_71011EF070(&pos, step * col);
        pos.x += row == 0 ? center_offset : -center_offset;
        swarm->_14c8[i]->_60 = pos;
    }
}

void SwarmPatternDoubleRing::m9() {
    SwarmPattern::m9();
}

void SwarmPatternDoubleRing::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mCenterOffsetHalf_s, "CenterOffsetHalf");
}

void SwarmPatternDoubleRing::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 5;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
