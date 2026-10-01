#include "Game/AI/AI/aiPlayerLadder.h"

namespace uking::ai {

PlayerLadder::PlayerLadder(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerLadder::~PlayerLadder() = default;

bool PlayerLadder::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerLadder::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerLadder::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerLadder::loadParams_() {
    getStaticParam(&mLadderToClimbTime_s, "LadderToClimbTime");
}

bool PlayerLadder::isChangeable() const {
    return isCurrentChild("登り終わり") && getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
