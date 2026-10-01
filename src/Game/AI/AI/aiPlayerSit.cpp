#include "Game/AI/AI/aiPlayerSit.h"

namespace uking::ai {

PlayerSit::PlayerSit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerSit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerSit::calc_() {
    if (handlePendingChildChange())
        return;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("開始"))
        changeChild("待機");
    else if (isCurrentChild("待機"))
        changeChild("終了");
}

void PlayerSit::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool PlayerSit::isFinished() const {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("終了"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
