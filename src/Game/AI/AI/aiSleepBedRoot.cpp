#include "Game/AI/AI/aiSleepBedRoot.h"

namespace uking::ai {

SleepBedRoot::SleepBedRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SleepBedRoot::~SleepBedRoot() = default;

bool SleepBedRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SleepBedRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("Wait");
}

void SleepBedRoot::leave_() {
    _38.x();
}

void SleepBedRoot::loadParams_() {}

bool SleepBedRoot::handleMessage_(const ksys::Message& message) {
    if (!_38._30 && isCurrentChild("Wait"))
        return _38.m2(message);
    return false;
}

}  // namespace uking::ai
