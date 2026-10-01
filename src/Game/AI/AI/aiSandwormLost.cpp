#include "Game/AI/AI/aiSandwormLost.h"

namespace uking::ai {

SandwormLost::SandwormLost(const InitArg& arg) : EnemyLost(arg) {}

SandwormLost::~SandwormLost() = default;

bool SandwormLost::init_(sead::Heap* heap) {
    return EnemyLost::init_(heap);
}

void SandwormLost::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = false;
    EnemyLost::enter_(params);
}

void SandwormLost::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("潜る")) {
        if (child->isFinished() || child->isFailed())
            m34();
    } else {
        EnemyLost::calc_();
    }
}

void SandwormLost::leave_() {
    EnemyLost::leave_();
}

void SandwormLost::loadParams_() {
    EnemyLost::loadParams_();
    getStaticParam(&mDiveSandOffset_s, "DiveSandOffset");
}

}  // namespace uking::ai
