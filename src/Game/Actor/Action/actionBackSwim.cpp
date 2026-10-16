#include "Game/Actor/Action/actionBackSwim.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

BackSwim::BackSwim(const InitArg& arg) : WaterFloatBase(arg) {}

BackSwim::~BackSwim() = default;

bool BackSwim::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void BackSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    const f32 time = *mParams.mTime_s;
    _e4 = ksys::Timer(time, time);
    _f0 = ksys::Timer(20.0f, 20.0f);

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

// NON_MATCHING: fadd operand order of the offset point and the final bool (cset instead of two branches)
bool BackSwim::sub_71000B5798() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& target = sub_71005D9330(mActor);
    sead::Vector3f dir = {pos.x - target.x, 0.0f, pos.z - target.z};
    dir.normalize();
    sead::Vector3f point = dir * 5.0f;
    point += pos;
    if (!sub_710072F8E4(mActor, point, nullptr, 3.0f))
        return true;
    const auto result = ksys::phys::HavokAI::instance()->sub_7100F87ED0(nullptr, point, 3.0f);
    if (!result.sub_7100F7EB40() || result.sub_7100F7EEE4() == 6)
        return false;
    return true;
}

}  // namespace uking::action
