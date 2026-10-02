#include "Game/AI/Action/actionHorseRideMoveCommand.h"

namespace uking::action {

HorseRideMoveCommand::HorseRideMoveCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideMoveCommand::~HorseRideMoveCommand() = default;

bool HorseRideMoveCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideMoveCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideMoveCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideMoveCommand::loadParams_() {
    HorseRideCommand::loadParams_();
    getStaticParam(&mGear_s, "Gear");
}

void HorseRideMoveCommand::calc_() {
    HorseRideCommand::calc_();
}

bool HorseRideMoveCommand::m32(ksys::act::Actor* actor) {
    const int gear = *mGear_s;
    if (gear >= 1) {
        _60._18 = gear;
        return _60.sub_710070DC38(actor, true);
    }
    if (gear != 0)
        return true;
    return _80.sub_710070DC38(actor, true);
}

}  // namespace uking::action
