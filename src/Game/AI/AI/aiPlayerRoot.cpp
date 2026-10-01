#include "Game/AI/AI/aiPlayerRoot.h"

namespace uking::ai {

PlayerRoot::PlayerRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void PlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (hasPendingChildChange()) {
        changeChild(mPendingChildIdx);
        return;
    }
    changeChild("Normal");
}

void PlayerRoot::calc_() {
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx);
}

}  // namespace uking::ai
