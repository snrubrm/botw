#include "Game/AI/AI/aiAssassinBossFirstBattleMove.h"

namespace uking::ai {

AssassinBossFirstBattleMove::AssassinBossFirstBattleMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinBossFirstBattleMove::~AssassinBossFirstBattleMove() = default;

bool AssassinBossFirstBattleMove::init_(sead::Heap* heap) {
    sub_7100316D50();
    _64 = 15;
    _68 = 15;
    return true;
}

void AssassinBossFirstBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool AssassinBossFirstBattleMove::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AssassinBossFirstBattleMove::isFinished() const {
    return getCurrentChild()->isFinished();
}

void AssassinBossFirstBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossFirstBattleMove::loadParams_() {
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mCheckTargetDist_s, "CheckTargetDist");
    getStaticParam(&mTooFarXZ_s, "TooFarXZ");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
