#include "Game/AI/Behavior/behaviorSwarmPatternBeeAttack.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternBeeAttack::SwarmPatternBeeAttack(const InitArg& arg) : SwarmPattern(arg) {}

SwarmPatternBeeAttack::~SwarmPatternBeeAttack() = default;

bool SwarmPatternBeeAttack::m6(sead::Heap* heap) {
    return SwarmPattern::m6(heap);
}

// NON_MATCHING: same maths and branch structure; the original schedules the row division (sdiv) and the
// float conversions differently (about 20 instructions are reordered).
void SwarmPatternBeeAttack::m7() {
    SwarmPattern::m7();
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm)
        return;

    const s32 count = swarm->_14c8.size();
    const s32 half = count / 2;
    for (s32 i = 0; i < count; ++i) {
        auto* unit = swarm->_14c8[i];
        if (!unit)
            continue;

        const s32 col = i % half;
        sead::Vector3f offset;
        if (col == 0) {
            offset.set(0, 0, -0.0f);
        } else {
            const f32 side = (col & 1) == 0 ? f32(col) * 0.1f : -(f32(col) * 0.1f);
            offset.set(side + 0.0f, 0, f32(-col) * 0.1f + f32(i / half) * -0.5f);
        }
        unit->_60 = offset;
    }
}

void SwarmPatternBeeAttack::m8() {
    SwarmPattern::m8();
}

void SwarmPatternBeeAttack::m9() {
    SwarmPattern::m9();
}

void SwarmPatternBeeAttack::loadParams() {
    SwarmPattern::loadParams();
    getStaticParam(&mDepth_s, "Depth");
    getStaticParam(&mWidth_s, "Width");
}

void SwarmPatternBeeAttack::m14(f32 value, act::Swarm* swarm) {
    swarm->_162c = 7;
    SwarmPattern::m14(value, swarm);
}

}  // namespace uking::behavior
