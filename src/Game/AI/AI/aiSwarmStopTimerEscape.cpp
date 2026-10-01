#include "Game/AI/AI/aiSwarmStopTimerEscape.h"

namespace uking::ai {

SwarmStopTimerEscape::SwarmStopTimerEscape(const InitArg& arg) : SwarmEscapeDie(arg) {}

SwarmStopTimerEscape::~SwarmStopTimerEscape() = default;

bool SwarmStopTimerEscape::init_(sead::Heap* heap) {
    return SwarmEscapeDie::init_(heap);
}

void SwarmStopTimerEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmEscapeDie::enter_(params);
}

void SwarmStopTimerEscape::calc_() {
    SwarmEscapeDie::calc_();
    if (!_80.isAllocatedOrFailed())
        return;

    if (_80.isProcReady())
        sub_71005B31CC();
    else if (_80.hasProcCreationFailed())
        _80.deleteProcIfFailed();
}

void SwarmStopTimerEscape::leave_() {
    if (_80.isAllocatedOrFailed())
        _80.deleteProc();
    SwarmEscapeDie::leave_();
}

void SwarmStopTimerEscape::loadParams_() {
    SwarmEscapeDie::loadParams_();
    getStaticParam(&mStopActorName_s, "StopActorName");
}

}  // namespace uking::ai
