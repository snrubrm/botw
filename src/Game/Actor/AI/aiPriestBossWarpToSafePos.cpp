#include "Game/Actor/AI/aiPriestBossWarpToSafePos.h"

namespace uking::ai {

PriestBossWarpToSafePos::PriestBossWarpToSafePos(const InitArg& arg) : PriestBoss(arg) {}

PriestBossWarpToSafePos::~PriestBossWarpToSafePos() = default;

bool PriestBossWarpToSafePos::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossWarpToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossWarpToSafePos::leave_() {
    PriestBoss::leave_();
}

void PriestBossWarpToSafePos::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mOffsetZ_s, "OffsetZ");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}

void PriestBossWarpToSafePos::calc_() {
    PriestBoss::calc_();
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable()) {
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::ai
