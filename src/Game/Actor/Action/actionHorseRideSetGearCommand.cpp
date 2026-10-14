#include "Game/Actor/Action/actionHorseRideSetGearCommand.h"

namespace uking::action {

HorseRideSetGearCommand::HorseRideSetGearCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideSetGearCommand::~HorseRideSetGearCommand() = default;

bool HorseRideSetGearCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideSetGearCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideSetGearCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideSetGearCommand::loadParams_() {
    HorseRideCommand::loadParams_();
    getStaticParam(&mGear_s, "Gear");
}

void HorseRideSetGearCommand::calc_() {
    HorseRideCommand::calc_();
}

bool HorseRideSetGearCommand::m32(ksys::act::Actor* actor) {
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
