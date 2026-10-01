#include "Game/AI/AI/aiLargeCannonAttackRoot.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

LargeCannonAttackRoot::LargeCannonAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LargeCannonAttackRoot::~LargeCannonAttackRoot() = default;

bool LargeCannonAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LargeCannonAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = *mAttackWaitTime_s;
    changeChild("攻撃待機");
    mFlags.set(Flag::Changeable);
}

void LargeCannonAttackRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;

    if (child->isFinished() || child->isFailed()) {
        _40 = *mAttackWaitTime_s;
        changeChild("攻撃待機");
        return;
    }

    if (isCurrentChild("攻撃待機")) {
        ksys::Timer::update(&_40, -1.0f);
        if (_40 <= 0.0f)
            m34();
    }
}

void LargeCannonAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LargeCannonAttackRoot::loadParams_() {
    getStaticParam(&mAttackWaitTime_s, "AttackWaitTime");
}

void LargeCannonAttackRoot::m34() {
    changeChild("ビーム攻撃");
}

}  // namespace uking::ai
