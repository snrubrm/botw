#include "Game/AI/Action/actionNPCLerpAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

NPCLerpAction::NPCLerpAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void NPCLerpAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCLerpAction::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void NPCLerpAction::loadParams_() {
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
    getStaticParam(&mArriveDist_s, "ArriveDist");
    getStaticParam(&mIsRotateByRot_s, "IsRotateByRot");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetRot_d, "TargetRot");
}

// NON_MATCHING: register allocation of the two abs() values
void NPCLerpAction::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller || isFinished() || isFailed())
        return;

    controller->sub_7100F5E7F0(0.0f);
    if (_64) {
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        setFinished();
        return;
    }

    const sead::Vector3f move = mActor->getASList()->sub_710115D3B8();
    const auto& mtx = mActor->getMtx();
    sead::Vector3f front = mtx.getBase(2);
    front.y = 0.0f;
    front.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, _58, sead::Vector3f::ey);

    const f32 ratio = ksys::VFR::instance()->getIntervalRatio();
    if (sead::Mathf::abs(angle) < sead::Mathf::abs(move.y * ratio)) {
        controller->sub_7100F5FB24({0.0f, angle * axis.y / ratio * 30.0f, 0.0f});
        setFinished();
    } else if (isFinishedAS(0, 0)) {
        setFinished();
    } else {
        controller->sub_7100F5FB24(move * 30.0f);
    }
}

const char* NPCLerpAction::m32() {
    return mASName_s.cstr();
}

}  // namespace uking::action
