#include "Game/AI/Action/actionForkOnLeaveChildDelete.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkOnLeaveChildDelete::ForkOnLeaveChildDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkOnLeaveChildDelete::~ForkOnLeaveChildDelete() = default;

bool ForkOnLeaveChildDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnLeaveChildDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkOnLeaveChildDelete::leave_() {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (child)
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    mActor->resetConnectedCalcChild(*mForceDelete_s);
}

void ForkOnLeaveChildDelete::loadParams_() {
    getStaticParam(&mForceDelete_s, "ForceDelete");
}

void ForkOnLeaveChildDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
