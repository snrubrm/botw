#include "Game/AI/AI/aiPracticeGuardianMiniNormal.h"

namespace uking::ai {

PracticeGuardianMiniNormal::PracticeGuardianMiniNormal(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PracticeGuardianMiniNormal::~PracticeGuardianMiniNormal() = default;

bool PracticeGuardianMiniNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PracticeGuardianMiniNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mGuardianMiniPracticeState_a) {
    case 1:
        changeChild("集中の試練", params);
        break;
    case 2:
        changeChild("盾はじきの試練", params);
        break;
    case 3:
        changeChild("回避の試練Ｈ", params);
        break;
    case 4:
        changeChild("回避の試練Ｖ", params);
        break;
    default:
        changeChild("集中の試練", params);
        break;
    }
}

void PracticeGuardianMiniNormal::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFailed();
}

void PracticeGuardianMiniNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PracticeGuardianMiniNormal::loadParams_() {
    getAITreeVariable(&mGuardianMiniPracticeState_a, "GuardianMiniPracticeState");
}

}  // namespace uking::ai
