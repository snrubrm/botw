#include "Game/AI/AI/aiPlayerGrab.h"

namespace uking::ai {

PlayerGrab::PlayerGrab(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerGrab::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerGrab::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerGrab::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerGrab::loadParams_() {}

bool PlayerGrab::isChangeable() const {
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("投げ") || isCurrentChild("立ち上がり"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
