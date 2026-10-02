#include "Game/AI/Action/actionHorseRideDynSetGearCommand.h"

namespace uking::action {

HorseRideDynSetGearCommand::HorseRideDynSetGearCommand(const InitArg& arg)
    : HorseRideCommand(arg) {}

HorseRideDynSetGearCommand::~HorseRideDynSetGearCommand() = default;

bool HorseRideDynSetGearCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideDynSetGearCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideDynSetGearCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideDynSetGearCommand::loadParams_() {
    HorseRideCommand::loadParams_();
    getDynamicParam(&mGear_d, "Gear");
}

void HorseRideDynSetGearCommand::calc_() {
    HorseRideCommand::calc_();
}

bool HorseRideDynSetGearCommand::m32(ksys::act::Actor* actor) {
    const int gear = *mGear_d;
    if (gear >= 1) {
        _60._18 = gear;
        return _60.sub_710070DC38(actor, true);
    }
    if (gear != 0)
        return true;
    return _80.sub_710070DC38(actor, true);
}

}  // namespace uking::action
