#include "Game/AI/Action/actionForkAlwaysForceGetUpWithOffset.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

ForkAlwaysForceGetUpWithOffset::ForkAlwaysForceGetUpWithOffset(const InitArg& arg)
    : ForkAlwaysForceGetUp(arg) {}

ForkAlwaysForceGetUpWithOffset::~ForkAlwaysForceGetUpWithOffset() = default;

bool ForkAlwaysForceGetUpWithOffset::init_(sead::Heap* heap) {
    return ForkAlwaysForceGetUp::init_(heap);
}

void ForkAlwaysForceGetUpWithOffset::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysForceGetUp::enter_(params);
}

void ForkAlwaysForceGetUpWithOffset::leave_() {
    ForkAlwaysForceGetUp::leave_();
}

void ForkAlwaysForceGetUpWithOffset::loadParams_() {
    ForkAlwaysForceGetUp::loadParams_();
    getStaticParam(&mRotCenterPos_s, "RotCenterPos");
}

// NON_MATCHING: same arithmetic; the original loads the rotation centre after the matrix elements and
// schedules the multiplications differently
void ForkAlwaysForceGetUpWithOffset::calc_() {
    ForkAlwaysForceGetUp::calc_();
    if (_80)
        return;
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    sead::Vector3f current = *mRotCenterPos_s;
    current.rotate(mActor->getMtx());
    sead::Vector3f previous = *mRotCenterPos_s;
    previous.rotate(_54);
    sead::Vector3f velocity = current - previous;
    if (controller->sub_7100F5F0E4() != ksys::act::MotionType::Hover)
        velocity.y += mActor->getVelocity().y;
    sub_7100737710(controller, velocity);
}

}  // namespace uking::action
