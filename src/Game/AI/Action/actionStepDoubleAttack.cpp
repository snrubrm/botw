#include "Game/AI/Action/actionStepDoubleAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
StepDoubleAttack::StepDoubleAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void StepDoubleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("DoubleAttack", false, 0, 0, -1.0f);
    _bc = mActor->getVelocity();
    _bc.y = 0.0f;
    const f32 speed = _bc.normalize();
    _88.value = speed;
    _88.prev_value = speed;
    _94 = -1.0f;
    _c8 = 0;
    sub_710073FA90(&_98, mActor);
    setDamageCallbackTiming(mActor, 4, &_60);
}

void StepDoubleAttack::leave_() {
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    sub_71005DA114(mActor, &_60);
}

void StepDoubleAttack::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mCloseDist_s, "CloseDist");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mParams.mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mParams.mJustAvoidAngle_s, "JustAvoidAngle");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void StepDoubleAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

bool StepDoubleAttack::isChangeable() const {
    return false;
}

int StepDoubleAttack::m32() {
    return 1;
}

}  // namespace uking::action
