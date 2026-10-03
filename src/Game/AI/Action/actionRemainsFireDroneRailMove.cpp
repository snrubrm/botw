#include "Game/AI/Action/actionRemainsFireDroneRailMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RemainsFireDroneRailMove::RemainsFireDroneRailMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsFireDroneRailMove::~RemainsFireDroneRailMove() = default;

bool RemainsFireDroneRailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsFireDroneRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getBase(_38, 1);
    mFlags.set(Flag::Changeable);
}

void RemainsFireDroneRailMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireDroneRailMove::loadParams_() {
    getStaticParam(&mNearDistance_s, "NearDistance");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mTargetSpeed_a, "TargetSpeed");
}

void RemainsFireDroneRailMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
