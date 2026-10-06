#include "Game/AI/Action/actionSwimMoveBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: order of the zeroing stores for the params
SwimMoveBase::SwimMoveBase(const InitArg& arg) : WaterFloatBase(arg) {}

bool SwimMoveBase::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void SwimMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
    auto* actor = mActor;
    if (auto* controller = actor->getCharacterController()) {
        const f32 speed = sead::Mathf::sqrt(actor->getVelocity().x * actor->getVelocity().x +
                                            actor->getVelocity().z * actor->getVelocity().z);
        _98.value = speed;
        _98.prev_value = speed;
        sub_7100741034(&_b0, actor);
        const f32 ang_speed = actor->getAngVelocity().length();
        _e0 = ang_speed > *mParams.mRotSpeed_s ? *mParams.mRotSpeed_s : ang_speed;
        _d4.set(*mParams.mTargetPos_d);
        _d4 -= actor->getMtx().getTranslation();
        _d4.normalize();
        controller->sub_7100F60AE0();
        sub_7100737708(controller, _98.value);
        _a4 = ksys::Timer(0.0f, 0.0f, 1.0f);
        mFlags.set(Flag::Changeable);
    }
}

void SwimMoveBase::leave_() {
    WaterFloatBase::leave_();
}

void SwimMoveBase::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mFinRadius_s, "FinRadius");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: identical code; the address computation of _98 is hoisted differently in the
// original (parameter meanings are guesses).
void SwimMoveBase::m32(f32 a, f32 b, f32 c, f32 d, f32 e) {
    if (b * 2.5f < a) {
        const f32 target = c * 0.5f;
        _98.chase(target, c * 0.05f);
        _98.setToMin(e);
    } else if (e < d) {
        _98.chase(0.0f, c * 0.1f);
    } else if (c + c + d > e) {
        const f32 target = c * 0.5f;
        _98.chase(target, c * 0.1f);
        _98.setToMin(e);
    } else {
        _98.chase(c, c * 0.1f);
        _98.setToMin(e);
    }
    _98.updateStats();
}

void SwimMoveBase::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
