#include "Game/AI/AI/aiGiantSleepReaction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

GiantSleepReaction::GiantSleepReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantSleepReaction::~GiantSleepReaction() = default;

bool GiantSleepReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantSleepReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    changeChild("睡眠");
}

void GiantSleepReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantSleepReaction::loadParams_() {}

bool GiantSleepReaction::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000015)
        _38 = false;
    else if (message.getType().value == 0x3000016)
        _38 = true;
    return false;
}

}  // namespace uking::ai
