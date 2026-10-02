#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

// NON_MATCHING: the 0x90-0xa3 zero/-1 stores are merged differently (stp xzr,x8 @0x90 vs str/stur/str)
NavMeshAction::NavMeshAction(const InitArg& arg) : ActionEx(arg) {}

void NavMeshAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void NavMeshAction::leave_() {
    ActionEx::leave_();
}

void NavMeshAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NavMeshAction::calc_() {
    ActionEx::calc_();
}

sead::Vector3f* NavMeshAction::m35() {
    return mTargetPos_d;
}

void NavMeshAction::m36(ksys::phys::CharacterController* controller, f32 speed,
                        const sead::Vector3f& up) {
    if (!controller)
        return;
    controller->sub_7100F5E7F0(speed * 30.0f);
    sub_710072C1B4(controller, up);
}

void NavMeshAction::m37(const sead::Matrix34f& mtx) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FC8C(mtx);
}

}  // namespace uking::action
