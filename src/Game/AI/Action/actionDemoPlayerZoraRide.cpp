#include "Game/AI/Action/actionDemoPlayerZoraRide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

DemoPlayerZoraRide::DemoPlayerZoraRide(const InitArg& arg) : PlayerAction(arg) {}

DemoPlayerZoraRide::~DemoPlayerZoraRide() = default;

bool DemoPlayerZoraRide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void DemoPlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void DemoPlayerZoraRide::leave_() {
    static_cast<ksys::act::PlayerBase*>(mActor)->_c48.resetBit(8);
    mActor->sub_71011DA834(&_20);
}

void DemoPlayerZoraRide::loadParams_() {}

void DemoPlayerZoraRide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
