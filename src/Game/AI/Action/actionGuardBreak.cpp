#include "Game/AI/Action/actionGuardBreak.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GuardBreak::GuardBreak(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardBreak::~GuardBreak() = default;

bool GuardBreak::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardBreak::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardBreak::loadParams_() {
    getStaticParam(&mKnockBackTime_s, "KnockBackTime");
    getStaticParam(&mDropIdx_s, "DropIdx");
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mWeaponVel_s, "WeaponVel");
    getStaticParam(&mWeaponVelY_s, "WeaponVelY");
}

void GuardBreak::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (_50.value <= sead::Mathf::epsilon()) {
        controller->sub_7100F5E7F0(0.0f);
        sub_7100738660(controller, *mVelReduce_s);
    } else {
        sub_71007377D4(controller, *mVelReduce_s);
        sub_7100738660(controller, *mVelReduce_s);
        _50.update();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

void GuardBreak::m32() {
    playAS("GuardBreak", false, 0, 0, -1.0f);
}

int GuardBreak::m33() {
    return *mDropIdx_s;
}

void GuardBreak::m34() {}

}  // namespace uking::action
