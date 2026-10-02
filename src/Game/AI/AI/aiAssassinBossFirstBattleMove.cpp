#include "Game/AI/AI/aiAssassinBossFirstBattleMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

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

bool AssassinBossFirstBattleMove::isChangeable() const {
    if (!getCurrentChild()->isChangeable())
        return false;
    if (isCurrentChild("直進接近不能"))
        return false;

    sub_71005D9330(mActor);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - _6c.x, pos.z - _6c.z);
    return !(diff.length() <= *mDistXZ_s);
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
