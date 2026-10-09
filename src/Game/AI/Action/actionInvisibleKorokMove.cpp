#include "Game/AI/Action/actionInvisibleKorokMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

InvisibleKorokMove::InvisibleKorokMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InvisibleKorokMove::~InvisibleKorokMove() = default;

bool InvisibleKorokMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InvisibleKorokMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void InvisibleKorokMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void InvisibleKorokMove::loadParams_() {
    getDynamicParam(&mSpeed_d, "Speed");
    getDynamicParam(&mIsBezier_d, "IsBezier");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: position registers and vector copy/add scheduling differ.
void InvisibleKorokMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    if (*mIsBezier_d) {
        controller->sub_7100F5FBE0(*mTargetPos_d);
        setFinished();
        return;
    }
    auto position = mActor->getMtx().getTranslation();
    const auto& target = *mTargetPos_d;
    const f32 step = *mSpeed_d * ksys::VFR::instance()->getDeltaFrame();
    auto difference = target - position;
    const f32 distance = difference.length();
    if (distance <= step) {
        position = target;
    } else {
        difference *= 1.0f / distance;
        position += difference * step;
    }
    controller->sub_7100F5FBE0(position);
    auto projected_target = *mTargetPos_d;
    projected_target.y = position.y;
    if ((position - projected_target).length() < *mSpeed_d)
        setFinished();
}

}  // namespace uking::action
