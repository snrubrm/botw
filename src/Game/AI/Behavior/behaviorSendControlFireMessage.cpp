#include "Game/AI/Behavior/behaviorSendControlFireMessage.h"

namespace uking::behavior {

SendControlFireMessage::SendControlFireMessage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SendControlFireMessage::~SendControlFireMessage() = default;

bool SendControlFireMessage::m6(sead::Heap* heap) {
    return true;
}

void SendControlFireMessage::m9() {}

void SendControlFireMessage::loadParams() {
    getStaticParam(&mIsIgnite_s, "IsIgnite");
}

}  // namespace uking::behavior
