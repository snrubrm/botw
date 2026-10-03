#include "Game/AI/Behavior/behaviorSwarmPatternDisc.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSwarm.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::behavior {

SwarmPatternDisc::SwarmPatternDisc(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternDisc::~SwarmPatternDisc() = default;

bool SwarmPatternDisc::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

void SwarmPatternDisc::m7() {
    SwarmPattern::m7();
}

void SwarmPatternDisc::m8() {
    SwarmPattern::m8();
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm)
        return;

    const s32 count = swarm->_14c8.size();
    const f32 radius = *mRadius_s;
    const f32 spacing = std::sqrt(sead::Mathf::pi() * radius * radius / (count - 1));

    swarm->_14c8[0]->_60 = sead::Vector3f::zero;
    s32 idx = 1;
    for (s32 ring = 0; swarm->_14c8.size() > idx; ++ring) {
        const f32 ring_radius = spacing * ring;
        s32 n = ring_radius * sead::Mathf::pi2() / spacing;
        if (n > swarm->_14c8.size() - idx)
            n = swarm->_14c8.size() - idx;
        for (s32 j = 0; j < n && idx < swarm->_14c8.size(); ++j) {
            sead::Vector3f pos{0, ring_radius, 0};
            const f32 angle = ring % 2 ? j * sead::Mathf::pi2() / n :
                                         (j + 0.5f) * sead::Mathf::pi2() / n;
            ksys::util::sub_71011EF070(&pos, angle);
            swarm->_14c8[idx++]->_60 = pos;
        }
    }
}
void SwarmPatternDisc::m9() {
    SwarmPattern::m9();
}

void SwarmPatternDisc::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mRadius_s, "Radius");
}

void SwarmPatternDisc::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 5;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
