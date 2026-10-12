#include "Game/AI/Action/actionGuardianMoveToTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

GuardianMoveToTarget::GuardianMoveToTarget(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianMoveToTarget::~GuardianMoveToTarget() = default;

bool GuardianMoveToTarget::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
    mFlags.set(Flag::Changeable);
    _30 = 1.0f;
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F76790();
        nav->inlineReset();
    } else {
        setFailed();
    }
}

void GuardianMoveToTarget::leave_() {
    GuardianActionBase::leave_();
    if (auto* nav = mActor->m45())
        nav->inlineReset();
}

void GuardianMoveToTarget::loadParams_() {
    GuardianActionBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
}

void GuardianMoveToTarget::calc_() {
    GuardianActionBase::calc_();
}

}  // namespace uking::action
