#include "Game/AI/Action/actionHorseRideCommand.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideCommand::HorseRideCommand(const InitArg& arg) : HorseRideOneTimeCommandBase(arg) {}

HorseRideCommand::~HorseRideCommand() = default;

bool HorseRideCommand::init_(sead::Heap* heap) {
    return HorseRideOneTimeCommandBase::init_(heap);
}

void HorseRideCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mASName_s.isEmpty()) {
        if (auto* actor = sub_71005D7348(mActor))
            m32(actor);
        setFinished();
        return;
    }
    HorseRideOneTimeCommandBase::enter_(params);
    if (*mCommandTiming_s == 1) {
        if (auto* actor = sub_71005D7348(mActor))
            m32(actor);
    }
}

void HorseRideCommand::leave_() {
    HorseRideOneTimeCommandBase::leave_();
}

void HorseRideCommand::loadParams_() {
    HorseRideOneTimeCommandBase::loadParams_();
    getStaticParam(&mCommandTiming_s, "CommandTiming");
}

void HorseRideCommand::calc_() {
    HorseRideOneTimeCommandBase::calc_();
    if (*mCommandTiming_s == 0 && sub_71001ADA78()) {
        if (auto* actor = sub_71005D7348(mActor))
            m32(actor);
    }
}

bool HorseRideCommand::m32(ksys::act::Actor* actor) {
    return true;
}

}  // namespace uking::action
