#include "Game/AI/Action/actionNPCTurnAction.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

NPCTurnAction::NPCTurnAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTurnAction::~NPCTurnAction() = default;

void NPCTurnAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = ksys::Timer(*mTurnFrame_s, *mTurnFrame_s);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5E7F0(0.0f);

    sead::Vector3f front = mActor->getMtx().getBase(2);
    front.y = 0.0f;
    front.normalize();

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _54 = *mTargetPos_d - pos;
    _54.y = 0.0f;
    _54.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, _54, sead::Vector3f::ey);
    _60 = axis.y;
    _64 = angle / _48.value;
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
    playAS(mASName_s.cstr(), *mIsIgnoreSameKey_s, 0, 0, -1.0f);
}

void NPCTurnAction::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void NPCTurnAction::loadParams_() {
    getStaticParam(&mTurnFrame_s, "TurnFrame");
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: regalloc (initial 1.0f copies and the final angular velocity register)
void NPCTurnAction::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    _48.update();

    f32 delta_frame = 1.0f;
    f32 interval_ratio = 1.0f;
    if (auto* vfr = ksys::VFR::instance()) {
        delta_frame = vfr->getDeltaFrame();
        interval_ratio = vfr->getIntervalRatio();
    }

    const f32 step = delta_frame * _64;
    const f32 dot = front.dot(_54);
    sead::Vector3f cross;
    cross.setCross(front, _54);
    const f32 remaining = std::atan2(cross.length(), dot);
    f32 speed;
    if (step > remaining)
        speed = remaining * _60 / interval_ratio;
    else
        speed = _64 * _60;
    controller->sub_7100F5FB24({0.0f, speed * 30.0f, 0.0f});

    if (_48.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
