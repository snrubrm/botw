#include "Game/AI/Action/actionHorseTurnAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HorseTurnAction::HorseTurnAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseTurnAction::~HorseTurnAction() = default;

bool HorseTurnAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: only the clamp of the dot product differs (the original branches with the constant in
// the acos argument register: `fcmp x, -1; b.mi; fmov s0, 1; fcmp x, s0; b.gt; mov s0, x`)
void HorseTurnAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (!controller || !rideable) {
        setFailed();
        return;
    }

    sead::Vector3f dir{mTargetDirection_d->x, 0.0f, mTargetDirection_d->z};
    dir.normalize();
    const sead::Vector3f& forward = controller->get64();
    f32 dot = dir.dot(forward);
    if (dot < -1.0f)
        dot = -1.0f;
    else if (dot > 1.0f)
        dot = 1.0f;
    const f32 angle = sead::Mathf::acos(dot);
    auto& s1 = rideable->_18;
    if (sead::Mathf::rad2deg(angle) <= *mGoalDegToleranceAtEnter_s) {
        s1.sub_7100E770C4(false);
        setFinished();
    } else {
        const f32 cross = dir.z * forward.x - dir.x * forward.z;
        if (!(cross >= 0.0f))
            s1.sub_7100E76E74(act::sUnk_7102603120, false);
        else
            s1.sub_7100E76E74(act::sUnk_7102603130, false);
    }
}

void HorseTurnAction::leave_() {
    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E770C4(false);
}

void HorseTurnAction::loadParams_() {
    getStaticParam(&mGoalDegToleranceAtEnter_s, "GoalDegToleranceAtEnter");
    getStaticParam(&mGoalDegTolerance_s, "GoalDegTolerance");
    getDynamicParam(&mTargetDirection_d, "TargetDirection");
}

void HorseTurnAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
