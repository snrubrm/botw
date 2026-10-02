#include "Game/AI/Behavior/behaviorSetStaticSystemGroupHandler.h"

namespace uking::behavior {

SetStaticSystemGroupHandler::SetStaticSystemGroupHandler(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetStaticSystemGroupHandler::~SetStaticSystemGroupHandler() = default;

bool SetStaticSystemGroupHandler::m6(sead::Heap* heap) {
    return true;
}

void SetStaticSystemGroupHandler::m7() {}

void SetStaticSystemGroupHandler::loadParams() {
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mOnLeaveReset_s, "OnLeaveReset");
}

}  // namespace uking::behavior
