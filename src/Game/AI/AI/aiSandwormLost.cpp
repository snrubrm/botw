#include "Game/AI/AI/aiSandwormLost.h"
#include "Game/Actor/actSandworm.h"

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

void SandwormLost::m34() {
    if (!_68) {
        auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor);
        if (sandworm && sandworm->_159c >= *mDiveSandOffset_s) {
            _68 = true;
            changeChild("潜る");
            return;
        }
    }
    _68 = true;
    EnemyLost::m34();
}

}  // namespace uking::ai
