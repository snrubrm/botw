#include "Game/AI/Action/actionWarpToPos.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WarpToPos::WarpToPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToPos::~WarpToPos() = default;

bool WarpToPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToPos::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetRot_d, "TargetRot");
}

// NON_MATCHING: scheduling only (the original materialises the setMtx arguments before the matrix math and
// keeps the actor in x20 after it).
bool WarpToPos::oneShot_() {
    if (!mActor)
        return false;
    _60.set(mActor->getScale());
    _30.makeSRT(_60, *mTargetRot_d * sead::Mathf::deg2rad(1), *mTargetPos_d);
    mActor->setMtx(_30, true, true);
    mActor->nullsub_4648();
    return true;
}

}  // namespace uking::action
