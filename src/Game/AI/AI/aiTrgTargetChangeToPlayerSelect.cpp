#include "Game/AI/AI/aiTrgTargetChangeToPlayerSelect.h"

namespace uking::ai {

TrgTargetChangeToPlayerSelect::TrgTargetChangeToPlayerSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TrgTargetChangeToPlayerSelect::~TrgTargetChangeToPlayerSelect() = default;

bool TrgTargetChangeToPlayerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrgTargetChangeToPlayerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsTrgTargetChangeToPlayer_a)
        changeChild("プレイヤーに変更", params);
    else
        changeChild("通常", params);
}

void TrgTargetChangeToPlayerSelect::calc_() {}

void TrgTargetChangeToPlayerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrgTargetChangeToPlayerSelect::loadParams_() {
    getAITreeVariable(&mIsTrgTargetChangeToPlayer_a, "IsTrgTargetChangeToPlayer");
}

}  // namespace uking::ai
