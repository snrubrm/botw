#include "Game/AI/AI/aiPriestBossBlowoffDamageSelect.h"

namespace uking::ai {

PriestBossBlowoffDamageSelect::PriestBossBlowoffDamageSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossBlowoffDamageSelect::~PriestBossBlowoffDamageSelect() = default;

bool PriestBossBlowoffDamageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossBlowoffDamageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossBlowoffDamageSelect::calc_() {
    if (!getCurrentChild()->isFinished())
        return;

    if (isCurrentChild("リアクション準備"))
        sub_7100510A94();
    else
        setFinished();
}

void PriestBossBlowoffDamageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossBlowoffDamageSelect::loadParams_() {}

}  // namespace uking::ai
