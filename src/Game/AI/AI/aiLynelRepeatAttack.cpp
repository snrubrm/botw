#include "Game/AI/AI/aiLynelRepeatAttack.h"

namespace uking::ai {

LynelRepeatAttack::LynelRepeatAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRepeatAttack::~LynelRepeatAttack() = default;

bool LynelRepeatAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRepeatAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = false;
    _4c = 1;
    changeChild("初撃", params);
}

bool LynelRepeatAttack::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelRepeatAttack::isFinished() const {
    return getCurrentChild()->isFinished();
}

void LynelRepeatAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelRepeatAttack::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

bool LynelRepeatAttack::isChangeable() const {
    return isCurrentChild("ラスト") && getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
