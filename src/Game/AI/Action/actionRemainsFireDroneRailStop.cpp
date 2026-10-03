#include "Game/AI/Action/actionRemainsFireDroneRailStop.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RemainsFireDroneRailStop::RemainsFireDroneRailStop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsFireDroneRailStop::~RemainsFireDroneRailStop() = default;

bool RemainsFireDroneRailStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsFireDroneRailStop::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getBase(_34, 1);
    _30 = 0.0f;
    mFlags.set(Flag::Changeable);
}

void RemainsFireDroneRailStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireDroneRailStop::loadParams_() {
    getDynamicParam(&mDynStopTime_d, "DynStopTime");
    getDynamicParam(&mDynStopPos_d, "DynStopPos");
}

void RemainsFireDroneRailStop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
