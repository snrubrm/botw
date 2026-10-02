#include "Game/AI/AI/aiLynelRepeatAttack.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

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

void LynelRepeatAttack::calc_() {
    if (_48)
        return;

    if (hasAttackInfo(mActor)) {
        auto* info = getAttackInfo(mActor, 0);
        if (info && (info->_18 & 3) == 0) {
            _48 = true;
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;

    if (_4c == *mAttackNum_s - 1) {
        ++_4c;
        changeChild("ラスト");
    } else if (_4c < *mAttackNum_s - 1) {
        ++_4c;
        changeChild("連撃");
    }
}

}  // namespace uking::ai
