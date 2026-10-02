#include "Game/AI/Action/actionMove2HomePos.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

Move2HomePos::Move2HomePos(const InitArg& arg) : Move2HomePosBase(arg) {}

Move2HomePos::~Move2HomePos() = default;

bool Move2HomePos::init_(sead::Heap* heap) {
    return Move2HomePosBase::init_(heap);
}

void Move2HomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    Move2HomePosBase::enter_(params);
}

void Move2HomePos::leave_() {
    Move2HomePosBase::leave_();
}

void Move2HomePos::loadParams_() {
    Move2HomePosBase::loadParams_();
    getStaticParam(&mVibDirection_s, "VibDirection");
    getStaticParam(&mVibPattern_s, "VibPattern");
    getStaticParam(&mVibPower_s, "VibPower");
    getStaticParam(&mVibRange_s, "VibRange");
    getStaticParam(&mIsVibration_s, "IsVibration");
}

void Move2HomePos::calc_() {
    Move2HomePosBase::calc_();
}

// NON_MATCHING: the original never sets the return register (w0 is whatever the last call returned)
bool Move2HomePos::handleMessage_(const ksys::Message& message) {
    if (message.getType() != 0x2000001)
        return false;
    _78 = *static_cast<const int*>(message.getUserData());
    return true;
}

}  // namespace uking::action
