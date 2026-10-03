#include "Game/AI/Action/actionBackSwim.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: the original computes this + 0xa8 after the memset (hoisted into x20 here)
BackSwim::BackSwim(const InitArg& arg) : WaterFloatBase(arg) {}

BackSwim::~BackSwim() = default;

bool BackSwim::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

// NON_MATCHING: the original stores _f4 as one 64-bit immediate (two 32-bit stores here)
void BackSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    const f32 time = *mParams.mTime_s;
    _ec.set(-1.0f, 20.0f);
    _f4 = _ec;
    _e4 = {time, time};

    const f32 speed = mActor->getVelocity().length();
    _a8.value = speed;
    _a8.prev_value = speed;
    sub_710073FA90(&_c0, mActor);
    const f32 ang_speed = mActor->getAngVelocity().length();
    _b4.value = ang_speed;
    _b4.prev_value = ang_speed;

    const sead::Vector3f velocity{_a8.value, _a8.value, _a8.value};
    controller->sub_7100F5E7F0(velocity.length() * 30.0f);
    const auto& mtx = mActor->getMtx();
    sub_710072C1B4(controller, {-mtx(0, 2), -mtx(1, 2), -mtx(2, 2)});
    mFlags.set(Flag::Changeable);

    if (auto* as_list = mActor->getASList()) {
        if (as_list->sub_710115AA68("SwimBack"))
            playAS("SwimBack", true, 0, 0, -1.0f);
    }
}

void BackSwim::leave_() {
    WaterFloatBase::leave_();
}

void BackSwim::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mParams.mFinishDist_s, "FinishDist");
    getStaticParam(&mParams.mDecelRatio_s, "DecelRatio");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mIsCheckCliff_s, "IsCheckCliff");
}

void BackSwim::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
