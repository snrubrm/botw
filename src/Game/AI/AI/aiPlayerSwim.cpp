#include "Game/AI/AI/aiPlayerSwim.h"

namespace uking::ai {

PlayerSwim::PlayerSwim(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerSwim::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerSwim::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerSwim::loadParams_() {
    getStaticParam(&mCatchHeightL_s, "CatchHeightL");
    getStaticParam(&mCatchHeightH_s, "CatchHeightH");
    getStaticParam(&mEnableHeight_s, "EnableHeight");
}

bool PlayerSwim::isChangeable() const {
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("泳ぎ待機") || isCurrentChild("泳ぎ移動") || isCurrentChild("泳ぎダッシュ") ||
            isCurrentChild("スピンアタック")) {
            return true;
        }
    }
    return false;
}

}  // namespace uking::ai
