#include "Game/AI/Action/actionGuardianMoveToPosition.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

GuardianMoveToPosition::GuardianMoveToPosition(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianMoveToPosition::~GuardianMoveToPosition() = default;

bool GuardianMoveToPosition::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianMoveToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
    mFlags.set(Flag::Changeable);
    _48 = 1.0f;
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F76790();
        nav->inlineReset();
    } else {
        setFailed();
    }
}

void GuardianMoveToPosition::leave_() {
    GuardianMoveTo::leave_();
    if (auto* nav = mActor->m45())
        nav->inlineReset();
}

void GuardianMoveToPosition::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDecelerate_s, "Decelerate");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

void GuardianMoveToPosition::calc_() {
    GuardianMoveTo::calc_();
}

}  // namespace uking::action
