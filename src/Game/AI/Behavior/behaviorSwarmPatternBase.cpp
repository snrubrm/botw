#include "Game/AI/Behavior/behaviorSwarmPatternBase.h"
#include "Game/AI/aiUnk_710072A944.h"
#include "Game/Actor/actSwarm.h"

namespace uking::behavior {

SwarmPatternBase::SwarmPatternBase(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SwarmPatternBase::~SwarmPatternBase() = default;

bool SwarmPatternBase::m6(sead::Heap* heap) {
    return true;
}

void SwarmPatternBase::m7() {}

void SwarmPatternBase::m8() {
    if (!*mIsAutoMove_s)
        return;
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
        m14(*mSpeed_s, swarm);
        sub_710072A944(swarm, *mAccRateMin_s, *mAccRateMax_s);
    }
}

void SwarmPatternBase::m9() {
    if (!*mIsAutoMove_s)
        return;
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
        swarm->_1628 = 0;
        swarm->_162c = 0;
    }
}

void SwarmPatternBase::loadParams() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAccRateMin_s, "AccRateMin");
    getStaticParam(&mAccRateMax_s, "AccRateMax");
    getStaticParam(&mIsAutoMove_s, "IsAutoMove");
}

void SwarmPatternBase::m14(f32 value, act::Swarm* swarm) {
    swarm->_1628 = 2;
    swarm->_162c = 3;
    swarm->_1620 = value;
}

}  // namespace uking::behavior
