#include "Game/AI/AI/aiLastBossShieldBash.h"

namespace uking::ai {

LastBossShieldBash::LastBossShieldBash(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossShieldBash::~LastBossShieldBash() = default;

bool LastBossShieldBash::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossShieldBash::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossShieldBash::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossShieldBash::loadParams_() {
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LastBossShieldBash::isChangeable() const {
    auto* child = getCurrentChild();
    if (!child)
        return false;
    return child->isChangeable();
}

}  // namespace uking::ai
